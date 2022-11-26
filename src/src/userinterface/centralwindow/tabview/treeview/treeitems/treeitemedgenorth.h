/*!
 *  \file   treeitemedgenorth.h
 *  \author Eva Navratilova
 */

#ifndef TREEITEMEDGENORTH_H
#define TREEITEMEDGENORTH_H

#include "treeitemedgedecorator.h"

class TreeItemEdgeNorth : public TreeItemEdgeDecorator
{
public:
    TreeItemEdgeNorth(TreeItemEdge *item, QGraphicsItem *parent = nullptr);
    virtual ~TreeItemEdgeNorth() override = default;

private:
    virtual QLineF getLine(QGraphicsLineItem* item) const override;
    virtual void setLine(qreal x1, qreal y1, qreal x2, qreal y2) override;
    virtual qreal getDescriptionYPos() override;

};

#endif // TREEITEMEDGENORTH_H
