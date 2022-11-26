/*!
 *  \file   treeitemedgedecorator.cpp
 *  \author Eva Navratilova
 */

#include "treeitemedgedecorator.h"

TreeItemEdgeDecorator::TreeItemEdgeDecorator(TreeItemEdge *item, QGraphicsItem *parent)
    : TreeItemEdge (parent), _wrappee(item)
{

}

TreeItemEdgeDecorator::~TreeItemEdgeDecorator()
{
    delete _wrappee;
}

TreeItemEdge *TreeItemEdgeDecorator::item()
{
    return _wrappee;
}

QRectF TreeItemEdgeDecorator::boundingRect() const
{
    return _wrappee->boundingRect();
}

void TreeItemEdgeDecorator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);

    this->draw();
}

void TreeItemEdgeDecorator::setScene(QGraphicsScene *scene)
{
    _wrappee->item()->setScene(scene);
}

Identifier TreeItemEdgeDecorator::getIdentifier() const
{
    return _wrappee->getIdentifier();
}

QPen TreeItemEdgeDecorator::getPen() const
{
    return _wrappee->getPen();
}

QLineF TreeItemEdgeDecorator::getLine(QGraphicsLineItem *item) const
{
    return item->line();
}

void TreeItemEdgeDecorator::setLine(qreal x1, qreal y1, qreal x2, qreal y2)
{
    item()->setLine(x1, y1, x2, y2);
}
