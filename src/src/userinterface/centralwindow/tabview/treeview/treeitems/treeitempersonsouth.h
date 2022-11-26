/*!
 *  \file   treeitempersonsouth.h
 *  \author Eva Navratilova
 */

#ifndef TREEITEMPERSONSOUTH_H
#define TREEITEMPERSONSOUTH_H

#include "treeitempersondecorator.h"

class TreeItemPersonSouth : public TreeItemPersonDecorator
{
public:
    TreeItemPersonSouth(TreeItemPerson* item, QGraphicsItem *parent = nullptr);
    ~TreeItemPersonSouth() override = default;
};

#endif // TREEITEMPERSONSOUTH_H
