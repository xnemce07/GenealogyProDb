/*!
 *  \file   treeitempersondecorator.cpp
 *  \author Eva Navratilova
 */

#include "treeitempersondecorator.h"

TreeItemPersonDecorator::TreeItemPersonDecorator(TreeItemPerson *item, QGraphicsItem *parent)
    : TreeItemPerson (parent), _wrappee(item)
{

}

TreeItemPersonDecorator::~TreeItemPersonDecorator()
{
    _wrappee->deleteLater();
}

TreeItemPerson *TreeItemPersonDecorator::item()
{
    return _wrappee;
}

QRectF TreeItemPersonDecorator::boundingRect() const
{
    return _wrappee->boundingRect();
}

void TreeItemPersonDecorator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    _wrappee->paint(painter, option, widget);
}

void TreeItemPersonDecorator::setPos(const QPointF &pos)
{
    _wrappee->setPos(pos);
}

void TreeItemPersonDecorator::setPos(qreal x, qreal y)
{
    _wrappee->setPos(x, y);
}

void TreeItemPersonDecorator::setX(qreal x)
{
    _wrappee->setX(x);
}

void TreeItemPersonDecorator::setY(qreal y)
{
    _wrappee->setY(y);
}

qreal TreeItemPersonDecorator::x() const
{
    return _wrappee->x();
}

qreal TreeItemPersonDecorator::y() const
{
    return _wrappee->y();
}

qreal TreeItemPersonDecorator::center() const
{
    return _wrappee->center();
}

qreal TreeItemPersonDecorator::top() const
{
    return _wrappee->top();
    //return -(_wrappee->bottom());
}

qreal TreeItemPersonDecorator::bottom() const
{
    return _wrappee->bottom();
    //return -(_wrappee->top());
}

qreal TreeItemPersonDecorator::right() const
{
    return _wrappee->right();
}

qreal TreeItemPersonDecorator::left() const
{
    return _wrappee->left();
}

qreal TreeItemPersonDecorator::height() const
{
    return _wrappee->height();
}

qreal TreeItemPersonDecorator::width() const
{
    return _wrappee->width();
}

Identifier TreeItemPersonDecorator::getIdentifier() const
{
    return _wrappee->getIdentifier();
}

void TreeItemPersonDecorator::addChild(TreeItemPerson *ch)
{
    _wrappee->addChild(ch);
}

void TreeItemPersonDecorator::addChildren(QVector<TreeItemPerson *> ch)
{
    _wrappee->addChildren(ch);
}

QVector<TreeItemPerson *> TreeItemPersonDecorator::getChildren() const
{
    return _wrappee->getChildren();
}
