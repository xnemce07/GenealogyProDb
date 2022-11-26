/*!
 *  \file   list.cpp
 *  \author Eva Navratilova
 */

#include "list.h"

List::List(Kernel &k, Identifier &ref, QWidget *parent)
    : QListWidget (parent), _kernel(k), _ref(ref)
{
    this->setSelectionMode(SelectionMode::SingleSelection);

    connect(this, &List::clicked, this, &List::itemClicked);
}

List::~List()
{
    this->remove();
}

Identifier List::getCurrent()
{
    Identifier ref;
    auto selected = this->selectedItems();
    if(selected.length() > 0)
    {
        this->setCurrentItem(selected.first());
    }

    int row = this->currentRow();
    if(row >= 0 && row < _items.length())
    {
        ref = _items[row]->getRef();
    }
    return ref;
}

void List::update(QVector<Identifier> refs)
{
    this->remove();

    _refs = refs;

    // Initialize
    for(auto it = _refs.begin(); it != _refs.end(); it++)
    {
        _items.append(this->initialize(*it));
    }

    // Set layout
    for(auto it = _items.begin(); it != _items.end(); it++)
    {
        this->addItem(*it);
    }

    // Set selection
    for(auto it = _items.begin(); it != _items.end(); it++)
    {
        if((*it)->getRef() == _ref)
        {
            this->setCurrentItem(*it);
            break;
        }
    }
}

void List::itemClicked(const QModelIndex &index)
{
    Identifier newProband = _items.at(index.row())->getRef();
    emit(this->itemChanged(newProband));
}

void List::changeSelected(ListItem* item)
{
    Identifier newRef = item->getRef();
    if(newRef != _ref)
    {
        emit(this->selectedChanged(newRef));
    }
}

void List::selectFirst()
{
    if(this->count() > 0)
    {
        auto item = this->item(0);
        this->setItemSelected(item, true);
    }
}

void List::selectLine(const QString &text)
{
    bool isSelected = false;
    bool wasListInitialized = false;

    if(text == QString())
    {
        this->restore(false);
        return;
    }
    this->restore(true);


    QStringList texts = text.split(' ', QString::SkipEmptyParts);

    QList<QListWidgetItem*> foundItems;

    for(auto fract : texts)
    {
        auto foundItemsTemp = this->findItems(fract, Qt::MatchFlag::MatchContains);

        if(!wasListInitialized)
        {
            wasListInitialized = true;
            foundItems = foundItemsTemp;
        }
        else
        {
            auto formerList = foundItems;
            foundItems.clear();

            for(auto item : formerList)
            {
                if(foundItemsTemp.contains(item))
                {
                    foundItems.push_back(item);
                }
            }
        }
    }

    for(auto item : foundItems)
    {
        item->setHidden(false);
    }
    if((!foundItems.isEmpty()) && (!isSelected))
    {
        isSelected = true;
        auto item = foundItems.first();
        this->setItemSelected(item, true);
        this->changeSelected(static_cast<ListItem*>(item));
    }
}

void List::remove()
{
    this->clear();
    _refs.clear();
    for(auto it = _items.begin(); it != _items.end(); it++)
    {
        //delete (*it);     // Causes crash !!!
    }
    _items.clear();
}

void List::restore(bool hide)
{
    for(int i = 0; i < this->count(); i++)
    {
        auto item = this->item(i);
        item->setHidden(hide);
    }
}
