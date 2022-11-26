/*!
 *  \file   boxeditablelist.cpp
 *  \author Eva Navratilova
 */

#include "boxeditablelist.h"

BoxEditableList::BoxEditableList(QString title, Kernel &k, Identifier &p, QWidget *parent)
    : Box(title, BOX_NOT_CHECKABLE, k, p, parent)
{
    // Enable order change
    _list.setDragEnabled(true);
    _list.setDragDropMode(QAbstractItemView::InternalMove);

    this->fill();

    connect(&_buNew, &QPushButton::clicked, this, &BoxEditableList::clickAddButton);
    connect(&_buEdit, &QPushButton::clicked, this, &BoxEditableList::clickEditButton);
    connect(&_buDelete, &QPushButton::clicked, this, &BoxEditableList::clickDeleteButton);
    connect(&_buUp, &QPushButton::clicked, this, &BoxEditableList::clickUpButton);
    connect(&_buDown, &QPushButton::clicked, this, &BoxEditableList::clickDownButton);
    connect(&_list, &QListWidget::itemDoubleClicked, this, &BoxEditableList::doubleClickItem);
    connect(&_list, &QListWidget::currentRowChanged, this, &BoxEditableList::listRowChanged);
    connect(_list.model(), &QAbstractItemModel::rowsMoved, this, &BoxEditableList::moveRows);
}

void BoxEditableList::fill()
{
    // Set static text
    _buNew.setIcon(QIcon(":icons/add"));
    _buEdit.setIcon(QIcon(":icons/edit"));
    _buDelete.setIcon(QIcon(":icons/delete"));
    _buUp.setIcon(QIcon(":icons/arrow-up"));
    _buDown.setIcon(QIcon(":icons/arrow-down"));

    _buNew.setToolTip(tr("New..."));
    _buEdit.setToolTip(tr("Edit..."));
    _buDelete.setToolTip(tr("Delete"));
    _buUp.setToolTip(tr("Move Up"));
    _buDown.setToolTip(tr("Move Down"));

    // Adjust items
    /*QFont font;
    QFontMetrics metrics(font);
    int buttonWidth = metrics.horizontalAdvance(_buDelete.text()) + 10;
    _buNew.setFixedWidth(buttonWidth);
    _buEdit.setFixedWidth(buttonWidth);
    _buDelete.setFixedWidth(buttonWidth);
    _buUp.setFixedWidth(buttonWidth);
    _buDown.setFixedWidth(buttonWidth);
    _list.setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);*/

    // Set layout
    _layout.addWidget(&_list, 0, 0, 1, 6);
    _layout.addWidget(&_buNew, 1, 0);
    _layout.addWidget(&_buEdit, 1, 1);
    _layout.addWidget(&_buDelete, 1, 2);
    _layout.addWidget(&_buUp, 1, 4);
    _layout.addWidget(&_buDown, 1, 5);

    _layout.setColumnStretch(0, 1);
    _layout.setColumnStretch(1, 1);
    _layout.setColumnStretch(2, 1);
    _layout.setColumnStretch(3, 100);
    _layout.setColumnStretch(4, 1);
    _layout.setColumnStretch(5, 1);

    // Adjust widgets
    this->listRowChanged(-1);
}

void BoxEditableList::remove()
{
    _list.clear();
}

void BoxEditableList::clickAddButton(bool clicked)
{
    Q_UNUSED(clicked);

    this->clickAdd();

    _list.repaint();
}

void BoxEditableList::clickEditButton(bool clicked)
{
    Q_UNUSED(clicked);

    int index = _list.currentRow();
    if(index >= 0)
    {
        this->clickEdit(static_cast<unsigned>(index));
    }
    _list.repaint();
}

void BoxEditableList::clickDeleteButton(bool clicked)
{
    Q_UNUSED(clicked);

    int index = _list.currentRow();
    if(index >= 0)
    {
        _dialogDelete = new MessageDelete();
        int accepted = _dialogDelete->exec();
        if(accepted)
        {
            this->clickDelete(static_cast<unsigned>(index));
            _list.takeItem(index);
            this->listRowChanged(_list.currentRow());
        }
        _dialogDelete->deleteLater();
    }
    _list.repaint();

    /// TODO - Add messageBox - do you really want to delete?
}

void BoxEditableList::clickUpButton(bool clicked)
{
    Q_UNUSED(clicked);

    int currentRow = _list.currentRow();
    if(currentRow >= 0 && currentRow < _list.count())
    {
        unsigned int unsignedCurrentRow = static_cast<unsigned>(currentRow);
        this->swapIndexes(unsignedCurrentRow, unsignedCurrentRow - 1);
        this->update();
        _list.setCurrentRow(currentRow - 1);
    }
}

void BoxEditableList::clickDownButton(bool clicked)
{
    Q_UNUSED(clicked);

    int currentRow = _list.currentRow();
    if(currentRow >= 0 && currentRow < _list.count())
    {
        unsigned int unsignedCurrentRow = static_cast<unsigned>(currentRow);
        this->swapIndexes(unsignedCurrentRow + 1, unsignedCurrentRow);
        this->update();
        _list.setCurrentRow(currentRow + 1);
    }
    _list.repaint();
}

void BoxEditableList::listRowChanged(int row)
{
    bool isInRange = (row >= 0 && row < _list.count());
    bool notFirst = row != 0;
    bool notLast = row < (_list.count() - 1);
    _buEdit.setEnabled(isInRange);
    _buDelete.setEnabled(isInRange);
    _buUp.setEnabled(isInRange && notFirst);
    _buDown.setEnabled(isInRange && notLast);
}

void BoxEditableList::doubleClickItem(QListWidgetItem *item)
{
    _list.setCurrentItem(item);
    int currentRow = _list.currentRow();
    if(currentRow >= 0 && currentRow < _list.count())
    {
        this->clickEdit(static_cast<unsigned>(currentRow));
    }
}

void BoxEditableList::moveRows(const QModelIndex &sourceParent, int sourceStart, int sourceEnd, const QModelIndex &destinationParent, int destinationRow)
{
    // Source Parent Row        == -1
    // Source Parent Col        == -1
    // Source Start             == Row index BEFORE
    // Source End               == Row index BEFORE    == Source Start
    // Destination Parent Row   == -1
    // Destination Parent Col   == -1
    // Destination Row          == Row index AFTER

    Q_UNUSED(sourceParent);
    Q_UNUSED(destinationParent);
    Q_UNUSED(sourceEnd);

    // Usable only - sourceStart - AND - destinationRow -

    unsigned int src = static_cast<unsigned>(sourceStart);
    unsigned int dst = static_cast<unsigned>(destinationRow);

    if(src < dst)
    {
        dst--;
        while(src < dst)
        {
            this->swapIndexes(src, src + 1);
            src++;
        }
    }
    else // src >= dst
    {
        while(src > dst)
        {
            this->swapIndexes(src, src - 1);
            src--;
        }
    }
    this->listRowChanged(static_cast<signed>(dst));
}


