#include "individuallistview.h"

IndividualListView::IndividualListView(Kernel &k)
    : _kernel(k)
{
    // From QListView
    /*
    this->setViewMode(QListView::ListMode);     // Items are viewed in alist without icons
    this->setFlow(QListView::TopToBottom);      // Items ate laid out top to bottom
    this->setMovement(QListView::Static);       // Items cannot be moved by the user
    */

    QSettings settings;

    Identifier first, last;
    first = this->_kernel.record()->getIdentifierIndividualFirst();
    last  = this->_kernel.record()->getIdentifierIndividualLast();

    for(Identifier current = first;;current++)
    {
        QString name = this->_kernel.record()->getIndividualNameGiven(current);
        QString surname = this->_kernel.record()->getIndividualNameLastname(current);
        QDate birth = this->_kernel.record()->getIndividualBirthDate1(current);

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

    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setSelectionMode(QAbstractItemView::SingleSelection);

    this->setColumnCount(4);
    this->setRowCount(this->_items.length());

    this->setHorizontalHeaderLabels(QStringList()
                                    << tr("ID")
                                    << tr("Surname")
                                    << tr("Name")
                                    << tr("Birth"));
    this->horizontalHeader()->setMinimumSectionSize(0);
    this->verticalHeader()->hide();
    this->setColumnWidth(0, settings.value("window/indiList/idCol").toInt());
    this->setColumnWidth(1, settings.value("window/indiList/surnameCol").toInt());
    this->setColumnWidth(2, settings.value("window/indiList/nameCol").toInt());
    this->setColumnWidth(3, settings.value("window/indiList/birthCol").toInt());

    connect(this->horizontalHeader(), &QHeaderView::sectionClicked, this, &IndividualListView::columnHeaderClicked);

    for(int i = 0; i < this->_items.length(); i++)
    {
        QVector<TableCell *> item = this->_items[i];
        this->setItem(i, 0, item[0]);
        this->setItem(i, 1, item[1]);
        this->setItem(i, 2, item[2]);
        this->setItem(i, 3, item[3]);
    }

    connect(this, &IndividualListView::cellDoubleClicked, this, &IndividualListView::individualDoubleClicked);

}

void IndividualListView::columnHeaderClicked(int index)
{
    if(index == 0)
    {
        this->sortItems(index);
    }
    else
    {
        this->sortByColumn(index);
    }
}

void IndividualListView::individualDoubleClicked(int row, int col)
{
    TableCell* cell = static_cast<TableCell*>(this->item(row, col));

    emit(this->probandChanged(cell->getIdentifier()));
}

void IndividualListView::saveSettings()
{
    QSettings settings;
    settings.setValue("window/indiList/idCol", this->columnWidth(0));
    settings.setValue("window/indiList/surnameCol", this->columnWidth(1));
    settings.setValue("window/indiList/nameCol", this->columnWidth(2));
    settings.setValue("window/indiList/birthCol", this->columnWidth(3));
}



