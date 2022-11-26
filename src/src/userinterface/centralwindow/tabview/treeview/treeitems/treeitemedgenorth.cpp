/*!
 *  \file   treeitemedgenorth.cpp
 *  \author Eva Navratilova
 */

#include "treeitemedgenorth.h"

TreeItemEdgeNorth::TreeItemEdgeNorth(TreeItemEdge *item, QGraphicsItem *parent)
    : TreeItemEdgeDecorator (item, parent)
{

}

QLineF TreeItemEdgeNorth::getLine(QGraphicsLineItem *item) const
{
    QLineF line = item->line();
    qreal x1 = line.x1();
    qreal y1 = line.y1();
    qreal x2 = line.x2();
    qreal y2 = line.y2();
    line.setLine(x1, -y2, x2, -y1);
    return line;
}

void TreeItemEdgeNorth::setLine(qreal x1, qreal y1, qreal x2, qreal y2)
{
    /// TODO - check
    item()->setLine(x1, -y2, x2, -y1);
}

qreal TreeItemEdgeNorth::getDescriptionYPos()
{
    return - (item()->_children.first()->top() - gapGeneration());
}
