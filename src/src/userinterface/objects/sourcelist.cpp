/*!
 *  \file   sourcelist.cpp
 *  \author Eva Navratilova
 */

#include "sourcelist.h"

SourceList::SourceList(Kernel &k, Identifier &s, QWidget *parent)
    : List (k, s, parent)
{

}

ListItem *SourceList::initialize(Identifier ref)
{
    return new SourceListItem(_kernel, ref);
}
