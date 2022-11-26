/*!
 *  \file   treeitempersonnorth.cpp
 *  \author Eva Navratilova
 */

#include "treeitempersonnorth.h"

TreeItemPersonNorth::TreeItemPersonNorth(TreeItemPerson *item, QGraphicsItem *parent)
    : TreeItemPersonDecorator(item, parent)
{

}

void TreeItemPersonNorth::setPos(const QPointF &pos)
{
    qreal x = pos.x();
    qreal y = - pos.y();

    QPointF point(x, y);

    TreeItemPersonDecorator::setPos(point);

    //qDebug() << "SETTING POS " << pos;
}

void TreeItemPersonNorth::setPos(qreal x, qreal y)
{
    TreeItemPersonDecorator::setPos(x, -y);

    //qDebug()<<"CALLING POS";
}

qreal TreeItemPersonNorth::top() const
{
    return - TreeItemPersonDecorator::bottom();
}

qreal TreeItemPersonNorth::bottom() const
{
    return - TreeItemPersonDecorator::top();
}

void TreeItemPersonNorth::setY(qreal y)
{
    TreeItemPersonDecorator::setY(-y);
}

qreal TreeItemPersonNorth::y() const
{
    return - TreeItemPersonDecorator::y();
}
