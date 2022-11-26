/*!
 *  \file   sourcelist.h
 *  \author Eva Navratilova
 */

#ifndef SOURCELIST_H
#define SOURCELIST_H

#include "list.h"
#include "sourcelistitem.h"

class SourceList : public List
{
    Q_OBJECT
public:
    SourceList(Kernel &k, Identifier &s, QWidget *parent = nullptr);

    ListItem* initialize(Identifier ref) override;

};

#endif // SOURCELIST_H
