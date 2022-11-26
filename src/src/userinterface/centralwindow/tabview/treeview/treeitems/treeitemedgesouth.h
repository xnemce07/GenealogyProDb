/*!
 *  \file   treeitemedgesouth.h
 *  \author Eva Navratilova
 */

#ifndef TREEITEMEDGESOUTH_H
#define TREEITEMEDGESOUTH_H

#include "treeitemedgedecorator.h"

class TreeItemEdgeSouth : public TreeItemEdgeDecorator
{
public:
    TreeItemEdgeSouth(TreeItemEdge *item, QGraphicsItem *parent = nullptr);
    virtual ~TreeItemEdgeSouth() override = default;
};

#endif // TREEITEMEDGESOUTH_H
