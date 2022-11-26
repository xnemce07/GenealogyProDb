/*!
 *  \file   personlist.cpp
 *  \author Eva Navratilova
 */

#include "personlist.h"

PersonList::PersonList(Kernel &k, Identifier &p, QWidget *parent)
    : List(k, p, parent)
{

}

ListItem *PersonList::initialize(Identifier ref)
{
    return new PersonListItem(_kernel, ref);
}
