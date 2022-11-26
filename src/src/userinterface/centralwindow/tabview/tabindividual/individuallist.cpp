/*!
 *  \file   individuallist.cpp
 *  \author Eva Navratilova
 */

#include "individuallist.h"

IndividualList::IndividualList(Kernel &k, Identifier &p, QWidget *parent)
    : QTableWidget(parent), _kernel(k), _proband(p)
{
    // View
    QFontMetrics font(_defaultFont);
    this->verticalHeader()->setDefaultSectionSize(font.height() + _cellPadding);
    this->setFrameShape(QFrame::NoFrame);
    this->setTextElideMode(Qt::ElideRight);
    this->setWordWrap(false);

    this->fill();
}

IndividualList::~IndividualList()
{
    for(auto fourItems : _items)
    {
        for(auto item : fourItems)
        {
            delete item;
        }
    }
}

void IndividualList::defaultSettings()
{
    QSettings settings;
    settings.setValue("window/indiList/idCol", 25);
    settings.setValue("window/indiList/surnameCol", 80);
    settings.setValue("window/indiList/nameCol", 60);
    settings.setValue("window/indiList/birthCol", 35);
}

void IndividualList::columnHeaderClicked(int index)
{
    this->saveColumnSorting(index);
    this->restoreColumnSorting();
}

void IndividualList::individualClicked(int row, int col)
{
    TableCell* cell = static_cast<TableCell*>(this->item(row, col));

    emit(this->probandChanged(cell->getIdentifier()));
}

void IndividualList::update()
{
    // Remove old items
    this->remove();

    // Construct items
    Identifier first, last;
    first = this->_kernel.record()->getIdentifierIndividualFirst();
    last  = this->_kernel.record()->getIdentifierIndividualLast();

    for(Identifier current = first; current != last; _kernel.record()->getIdentifierIndividualNext(current))
    {
        if(! _kernel.record()->isIndividual(current))
        {
            qDebug() << "ID not INDI - B U G !!!! " << current.get();
            continue;
        }

        QString name = this->_kernel.record()->getIndividualNameGiven(current);
        QString surname = this->_kernel.record()->getIndividualNameSurnameBirthMarried(current);
        Date birth = this->_kernel.record()->getIndividualBirthDate1(current);

        QVector<TableCell *> item;
        item.append(new TableCellRef(current));
        item.append(new TableCellText(current, surname));
        item.append(new TableCellText(current, name));
        item.append(new TableCellDate(current, birth));
        //IndividualItemModel item(current, name, surname, birth);

        this->_items.append(item);

        // End the cycle
        if(current == last)
            break;
    }

    // Set row count
    this->setRowCount(this->_items.length());


    // Insert items into the table
    for(int i = 0; i < this->_items.length(); i++)
    {
        QVector<TableCell *> item = this->_items[i];
        this->setItem(i, 0, item[0]);
        this->setItem(i, 1, item[1]);
        this->setItem(i, 2, item[2]);
        this->setItem(i, 3, item[3]);
    }

    // Select proband
    TableCell *item = nullptr;
    for(auto it=this->_items.begin(); it!=this->_items.end(); it++)
    {
        if(it->first()->getIdentifier() == this->_proband)
        {
            item = it->first();
            break;
        }
    }

    this->restoreColumnSorting();

    if(item != nullptr)
        this->selectRow(this->row(item));
}

void IndividualList::remove()
{
    for(auto v1 = _items.begin(); v1 != _items.end(); v1++)
    {
        for(auto v2 = v1->begin(); v2 != v1->end(); v2++)
        {
            delete (*v2);
        }
    }

    _items.clear();
}

void IndividualList::fill()
{
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(QAbstractItemView::SingleSelection);

    // Set column count and labels
    this->setColumnCount(4);
    this->setHorizontalHeaderLabels(QStringList()
                                    << tr("ID")
                                    << tr("Surname")
                                    << tr("Name")
                                    << tr("Birth"));

    this->horizontalHeader()->setMinimumSectionSize(0);
    this->verticalHeader()->hide();
    this->applySettings();

    connect(this->horizontalHeader(), &QHeaderView::sectionClicked, this, &IndividualList::columnHeaderClicked);
    connect(this, &IndividualList::cellClicked, this, &IndividualList::individualClicked);
}

void IndividualList::applySettings()
{
    QSettings settings;
    this->setColumnWidth(0, settings.value("window/indiList/idCol").toInt());
    this->setColumnWidth(1, settings.value("window/indiList/surnameCol").toInt());
    this->setColumnWidth(2, settings.value("window/indiList/nameCol").toInt());
    this->setColumnWidth(3, settings.value("window/indiList/birthCol").toInt());
}

void IndividualList::sortByColumnHeader(int index)
{
    if(index == 0)
    {
        this->sortItems(index);
    }
    else
    {
        this->sortByColumn(index/*, Qt::AscendingOrder*/);
    }
}

void IndividualList::saveColumnSorting(int index)
{
    if(_columnClickedMemory.isEmpty() || (index != _columnClickedMemory.first()))
    {
        _columnClickedMemory.prepend(index);
    }
    if(_columnClickedMemory.length() > (this->columnCount()))
    {
        _columnClickedMemory.removeLast();
    }
}

void IndividualList::restoreColumnSorting()
{
    // Reset sorting
    this->sortByColumnHeader(0);

    // Reapply sorting
    for(auto i = _columnClickedMemory.rbegin(); i != _columnClickedMemory.rend(); i++)
    {
        this->sortByColumnHeader(*i);
    }
}


void IndividualList::saveSettings() const
{
    QSettings settings;
    settings.setValue("window/indiList/idCol", this->columnWidth(0));
    settings.setValue("window/indiList/surnameCol", this->columnWidth(1));
    settings.setValue("window/indiList/nameCol", this->columnWidth(2));
    settings.setValue("window/indiList/birthCol", this->columnWidth(3));
}



