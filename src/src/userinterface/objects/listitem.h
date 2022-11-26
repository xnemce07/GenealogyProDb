/*!
 *  \file   listitem.h
 *  \author Eva Navratilova
 */

#ifndef LISTITEM_H
#define LISTITEM_H

#include <QListWidgetItem>

#include "kernel.h"
#include "textformatter.h"

class ListItem : public QListWidgetItem
{
protected:
    Kernel &_kernel;
    Identifier _ref;

public:
    ListItem(Kernel &k, Identifier ref, QListWidget *parent = nullptr);
    virtual ~ListItem() = default;

    Identifier getRef() const;
};

#endif // LISTITEM_H
