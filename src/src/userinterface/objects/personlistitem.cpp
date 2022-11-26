/*!
 *  \file   personlistitem.cpp
 *  \author Eva Navratilova
 */

#include "personlistitem.h"

PersonListItem::PersonListItem(Kernel &k, Identifier ref, QListWidget *parent)
    :ListItem (k, ref, parent)
{
    this->setText(TextFormatter::getPersonLineText(_kernel, _ref));
}
