/*!
 *  \file   treeitemperson.cpp
 *  \author Eva Navratilova
 */

#include "treeitemperson.h"

TreeItemPerson::TreeItemPerson(Identifier indi, QString text, QGraphicsItem *parent)
    : QGraphicsTextItem (parent), _indi(indi)
{
    this->setCursor(Qt::CursorShape::ArrowCursor);
    this->setDefaultTextColor(Qt::black);
    QString htmlText = text.replace('\n', "<br>");
    this->setHtml("<center>" + htmlText + "</center>");
    this->setTextWidth(this->boundingRect().width());   // Enables center alignment + item width == text width
}

TreeItemPerson::~TreeItemPerson()
{
    qDebug()<< "Deleting "<<getIdentifier().get();
}

TreeItemPerson *TreeItemPerson::item()
{
    return this;
}

QRectF TreeItemPerson::boundingRect() const
{
    return QGraphicsTextItem::boundingRect().adjusted(-_margin,-_margin,+_margin,+_margin);
}

qreal TreeItemPerson::getRoundedRectRadius() const
{
    return 0;
}

void TreeItemPerson::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPainterPath path;
    path.addRoundedRect(this->boundingRect(), this->getRoundedRectRadius(), this->getRoundedRectRadius());

    //painter->setPen(Qt::black);
    painter->fillPath(path, _color);

    QPen pen;
    pen.setWidth(2);
    painter->setPen(pen);

    painter->drawPath(path);

    //qDebug()<<"PAINT "<<getIdentifier().get()<<(_color)<<" this " << this;

    QGraphicsTextItem::paint(painter,option,widget);
}

void TreeItemPerson::setFocus(Qt::FocusReason focusReason)
{
    Q_UNUSED(focusReason);

    _color = QColor(Qt::lightGray);
    qDebug()<<"Color gray "<<_color<<" for "<<getIdentifier().get()<<" this "<<this;
    this->update(this->boundingRect());
}

void TreeItemPerson::clearFocus()
{
    _color = QColor(Qt::transparent);
    qDebug()<<"Color transp "<<_color<<" for "<<getIdentifier().get();
    this->update(this->boundingRect());
}

void TreeItemPerson::setPos(const QPointF &pos)
{
    QGraphicsTextItem::setPos(pos);
}

void TreeItemPerson::setPos(qreal x, qreal y)
{
    QGraphicsTextItem::setPos(x, y);
}

void TreeItemPerson::setX(qreal x)
{
    QGraphicsTextItem::setX(x);
}

void TreeItemPerson::setY(qreal y)
{
    QGraphicsTextItem::setY(y);
}

qreal TreeItemPerson::x() const
{
    return QGraphicsTextItem::x();
}

qreal TreeItemPerson::y() const
{
    return QGraphicsTextItem::y();
}

qreal TreeItemPerson::center() const
{
    QRectF rect = this->boundingRect();
    return rect.width() / 2.0 + this->x();
}

qreal TreeItemPerson::top() const
{
    QRectF rect = this->boundingRect();
    return rect.top() + this->y();
}

qreal TreeItemPerson::bottom() const
{
    QRectF rect = this->boundingRect();
    return rect.bottom() + this->y();
}

qreal TreeItemPerson::right() const
{
    QRectF rect = this->boundingRect();
    return rect.right() + this->x();
}

qreal TreeItemPerson::left() const
{
    QRectF rect = this->boundingRect();
    return rect.left() + this->x();
}

qreal TreeItemPerson::height() const
{
    return this->boundingRect().height();
}

qreal TreeItemPerson::width() const
{
    return this->boundingRect().width();
}


Identifier TreeItemPerson::getIdentifier() const
{
    return _indi;
}

void TreeItemPerson::addChild(TreeItemPerson *ch)
{
    _children.push_back(ch);
}

void TreeItemPerson::addChildren(QVector<TreeItemPerson*> ch)
{
    _children.append(ch);
}

QVector<TreeItemPerson*> TreeItemPerson::getChildren() const
{
    return _children;
}

qreal TreeItemPerson::heightOfText()
{
    QFont font;
    QFontMetrics metrics(font);
    QSettings settings;
    QString text = settings.value("textformat/tree/person").toString();
    TreeItemPerson tempItem(Identifier(), text);

    return tempItem.height();
}

int TreeItemPerson::padding()
{
    QFont font;
    QFontMetrics metrics(font);

    return metrics.height();
}

int TreeItemPerson::spacing()
{
    return 2;
}

void TreeItemPerson::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    emit(this->probandChanged(_indi));
}
