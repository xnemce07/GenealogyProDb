/*!
 *  \file   listitem.cpp
 *  \author Eva Navratilova
 */

#include "listitem.h"

ListItem::ListItem(Kernel &k, Identifier ref, QListWidget *parent)
    : QListWidgetItem (parent), _kernel(k), _ref(ref)
{

}

Identifier ListItem::getRef() const
{
    return _ref;
}
