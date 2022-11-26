/*!
 *  \file   treeitemedgedecorator.h
 *  \author Eva Navratilova
 */

#ifndef TREEITEMEDGEDECORATOR_H
#define TREEITEMEDGEDECORATOR_H

#include "treeitemedge.h"

class TreeItemEdgeDecorator : public TreeItemEdge
{
    friend class TreeItemEdge;
private:
    TreeItemEdge* _wrappee;

public:
    TreeItemEdgeDecorator(TreeItemEdge *item, QGraphicsItem *parent = nullptr);
    virtual ~TreeItemEdgeDecorator() override;

    virtual TreeItemEdge* item() override;

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual void setScene(QGraphicsScene *scene) override;

    virtual Identifier getIdentifier() const override;

private:
    virtual QPen getPen() const override;
    virtual QLineF getLine(QGraphicsLineItem* item) const override;
    virtual void setLine(qreal x1, qreal y1, qreal x2, qreal y2) override;
};

#endif // TREEITEMEDGEDECORATOR_H
