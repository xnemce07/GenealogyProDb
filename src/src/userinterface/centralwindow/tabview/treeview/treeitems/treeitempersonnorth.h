/*!
 *  \file   treeitempersonnorth.h
 *  \author Eva Navratilova
 */

#ifndef TREEITEMPERSONNORTH_H
#define TREEITEMPERSONNORTH_H

#include "treeitempersondecorator.h"

class TreeItemPersonNorth : public TreeItemPersonDecorator
{
public:
    TreeItemPersonNorth(TreeItemPerson* item, QGraphicsItem *parent = nullptr);
    ~TreeItemPersonNorth() override = default;

    void setPos(const QPointF & pos) override;
    void setPos(qreal x, qreal y) override;

    qreal top() const override;
    qreal bottom() const override;

    virtual void setY(qreal y) override;
    virtual qreal y() const override;
};

#endif // TREEITEMPERSONNORTH_H
