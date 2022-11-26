/*!
 *  \file   treeitempersondecorator.h
 *  \author Eva Navratilova
 */

#ifndef TREEITEMPERSONDECORATOR_H
#define TREEITEMPERSONDECORATOR_H

#include "treeitemperson.h"

class TreeItemPersonDecorator : public TreeItemPerson
{
private:
    TreeItemPerson* _wrappee;

public:
    TreeItemPersonDecorator(TreeItemPerson* item, QGraphicsItem *parent = nullptr);
    virtual ~TreeItemPersonDecorator() override;

    virtual TreeItemPerson* item() override;

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual void setPos(const QPointF & pos) override;
    virtual void setPos(qreal x, qreal y) override;

    virtual qreal center() const override;
    virtual qreal top() const override;
    virtual qreal bottom() const override;
    virtual qreal right() const override;
    virtual qreal left() const override;
    virtual qreal height() const override;
    virtual qreal width() const override;

    virtual void setX(qreal x) override;
    virtual void setY(qreal y) override;
    virtual qreal x() const override;
    virtual qreal y() const override;

    virtual Identifier getIdentifier() const override;

    virtual void addChild(TreeItemPerson* ch) override;
    virtual void addChildren(QVector<TreeItemPerson*> ch) override;

    virtual QVector<TreeItemPerson*> getChildren() const override;
};

#endif // TREEITEMPERSONDECORATOR_H
