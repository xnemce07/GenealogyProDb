/*!
 *  \file   treeitemperson.h
 *  \author Eva Navratilova
 */

#ifndef TREEITEMPERSON_H
#define TREEITEMPERSON_H

#include <QGraphicsTextItem>
#include <QFont>
#include <QFontMetrics>
#include <QSettings>
#include <QPointF>
#include <QPainter>
#include <QCursor>

#include "../../../../../kernel.h"
#include "generation.h"

class TreeItemPerson : public QGraphicsTextItem
{
    Q_OBJECT
protected:
    Identifier _indi;
    QVector<TreeItemPerson*> _children;

    int _margin = 0;
    QColor _color = QColor(Qt::transparent);

public:
    TreeItemPerson(QGraphicsItem *parent = nullptr) : QGraphicsTextItem(parent) {}
    TreeItemPerson(Identifier indi, QString text, QGraphicsItem *parent = nullptr);
    virtual ~TreeItemPerson() override;

    virtual TreeItemPerson* item();

    virtual QRectF boundingRect() const override;
    virtual qreal getRoundedRectRadius() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    virtual void setFocus(Qt::FocusReason focusReason = Qt::OtherFocusReason);
    virtual void clearFocus();

    virtual void setPos(const QPointF & pos);
    virtual void setPos(qreal x, qreal y);

    virtual void setX(qreal x);
    virtual void setY(qreal y);
    virtual qreal x() const;
    virtual qreal y() const;

    virtual qreal center() const;
    virtual qreal top() const;
    virtual qreal bottom() const;
    virtual qreal right() const;
    virtual qreal left() const;
    virtual qreal height() const;
    virtual qreal width() const;

    virtual Identifier getIdentifier() const;

    virtual void addChild(TreeItemPerson* ch);
    virtual void addChildren(QVector<TreeItemPerson*> ch);

    virtual QVector<TreeItemPerson*> getChildren() const;

    static qreal heightOfText();

protected:
    static int padding();
    static int spacing();

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void probandChanged(const Identifier ref);

};

#endif // TREEITEMPERSON_H
