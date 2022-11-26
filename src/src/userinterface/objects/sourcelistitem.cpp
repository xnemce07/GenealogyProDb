/*!
 *  \file   sourcelistitem.cpp
 *  \author Eva Navratilova
 */

#include "sourcelistitem.h"

SourceListItem::SourceListItem(Kernel &k, Identifier ref, QListWidget *parent)
    : ListItem (k, ref, parent)
{
    this->setText(TextFormatter::getSourceText(_kernel, _ref));
}
