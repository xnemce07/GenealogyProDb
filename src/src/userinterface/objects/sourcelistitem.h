/*!
 *  \file   sourcelistitem.h
 *  \author Eva Navratilova
 */

#ifndef SOURCELISTITEM_H
#define SOURCELISTITEM_H

#include "listitem.h"

#include "kernel.h"
#include "textformatter.h"

class SourceListItem : public ListItem
{
public:
    SourceListItem(Kernel &k, Identifier ref, QListWidget *parent = nullptr);
};

#endif // SOURCELISTITEM_H
