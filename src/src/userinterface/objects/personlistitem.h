/*!
 *  \file   personlistitem.h
 *  \author Eva Navratilova
 */

#ifndef PERSONLISTITEM_H
#define PERSONLISTITEM_H

#include "listitem.h"

#include "kernel.h"
#include "textformatter.h"

class PersonListItem : public ListItem
{
public:
    PersonListItem(Kernel &k, Identifier ref, QListWidget *parent = nullptr);
};

#endif // PERSONLISTITEM_H
