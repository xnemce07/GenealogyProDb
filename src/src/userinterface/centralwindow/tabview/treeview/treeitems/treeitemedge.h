/*!
 *  \file   treeitemedge.h
 *  \author Eva Navratilova
 */

#ifndef TREEITEMEDGE_H
#define TREEITEMEDGE_H

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QVector>
#include <QRectF>
#include <QPointF>
#include <QFont>
#include <QFontMetrics>
#include <QPen>
#include <QSettings>

#include "../../../../../kernel.h"
#include "treeitemperson.h"

class TreeItemEdgeDecorator;

class TreeItemEdge : protected QGraphicsItem
{
    friend class TreeItemEdgeNorth;
    friend class TreeItemEdgeSouth;
    friend class TreeItemEdgeDecorator;
protected:
    Identifier _ref;
    bool _fullLine;

    QVector<QGraphicsLineItem*> _edges;
    QGraphicsTextItem* _description = nullptr;

    // Pointers to related nodes
    TreeItemPerson* _parent = nullptr;
    QVector<TreeItemPerson*> _children;


public:
    TreeItemEdge(Identifier indiOrFam, TreeItemPerson *p, const QVector<TreeItemPerson *> &ch, bool fullLine, QString text = QString(), QGraphicsItem *parent = nullptr);
    TreeItemEdge(QGraphicsItem *parent = nullptr);
    virtual ~TreeItemEdge() override;

    virtual TreeItemEdge* item();

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    virtual void setScene(QGraphicsScene *scene);
    virtual void setZValue(qreal z);

    virtual Identifier getIdentifier() const;

    static qreal heightOfText();

    static int gapGeneration();

    virtual void draw();

    virtual QPen getPen() const;
    virtual QLineF getLine(QGraphicsLineItem* item) const;
    virtual void setLine(qreal x1, qreal y1, qreal x2, qreal y2);
    virtual qreal getDescriptionYPos();

};

#endif // TREEITEMEDGE_H
