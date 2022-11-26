/*!
 *  \file   personlist.h
 *  \author Eva Navratilova
 */

#ifndef PERSONLIST_H
#define PERSONLIST_H

#include "list.h"
#include "personlistitem.h"

class PersonList : public List
{
    Q_OBJECT
public:
    PersonList(Kernel &k, Identifier &p, QWidget *parent = nullptr);

    ListItem* initialize(Identifier ref) override;

};

#endif // PERSONLIST_H
