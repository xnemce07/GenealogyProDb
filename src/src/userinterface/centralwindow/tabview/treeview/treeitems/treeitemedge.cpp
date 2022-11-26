/*!
 *  \file   treeitemedge.cpp
 *  \author Eva Navratilova
 */

#include "treeitemedge.h"

TreeItemEdge::TreeItemEdge(Identifier indiOrFam, TreeItemPerson *p, const QVector<TreeItemPerson *> &ch, bool fullLine, QString text, QGraphicsItem *parent)
    : QGraphicsItem (parent), _ref(indiOrFam), _parent(p), _children(ch)
{
    _fullLine = fullLine;
    if(! text.isEmpty())
    {
        item()->_description = new QGraphicsTextItem();
        item()->_description->setHtml("<div style='background-color:#ffffff;'>" + text + "</div>");
    }
}

TreeItemEdge::TreeItemEdge(QGraphicsItem *parent)
    : QGraphicsItem (parent)
{

}

TreeItemEdge::~TreeItemEdge()
{
    if(_description != nullptr)
    {
        _description->deleteLater();
    }
    for(QGraphicsLineItem* edge : _edges)
    {
        delete edge;
    }
    _edges.clear();
}

TreeItemEdge *TreeItemEdge::item()
{
    return this;
}

QRectF TreeItemEdge::boundingRect() const
{
    QPointF topLeft, bottomRight;

    for(auto edge : _edges)
    {
        QLineF line = this->getLine(edge);
        qreal x1 = line.x1();
        qreal y1 = line.y1();
        qreal x2 = line.x2();
        qreal y2 = line.y2();

        if(x1 > x2)
        {
            std::swap(x1, x2);
        }
        if(y1 > y2)
        {
            std::swap(y1, y2);
        }

        if(edge == _edges.first())
        {
            topLeft.setX(x1);
            topLeft.setY(y1);
            bottomRight.setX(x2);
            bottomRight.setY(y2);
        }
        else
        {
            if(topLeft.x() > x1)
                topLeft.setX(x1);
            if(topLeft.y() > y1)
                topLeft.setY(y1);
            if(bottomRight.x() < x2)
                bottomRight.setX(x2);
            if(bottomRight.y() < y2)
                bottomRight.setY(y2);
        }
    }

    return QRectF(topLeft, bottomRight);
}

void TreeItemEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);

    item()->draw();
}

void TreeItemEdge::setScene(QGraphicsScene *scene)
{
    // Place items
    for(QGraphicsLineItem* edge : item()->_edges)
    {
        scene->addItem(edge);
    }

    if(item()->_description != nullptr)
    {
        scene->addItem(item()->_description);
    }
}

void TreeItemEdge::setZValue(qreal z)
{
    for(auto edge : item()->_edges)
    {
        edge->setZValue(z);
    }
}

void TreeItemEdge::setLine(qreal x1, qreal y1, qreal x2, qreal y2)
{
    QGraphicsLineItem *line = new QGraphicsLineItem();
    line->setPen(this->getPen());
    line->setLine(x1, y1, x2, y2);

    item()->_edges.push_back(line);
}

qreal TreeItemEdge::getDescriptionYPos()
{
    return item()->_children.first()->top() - gapGeneration() - heightOfText();
}

void TreeItemEdge::draw()
{

    qreal heightOverlap = this->heightOfText();

    //
    int count = item()->_children.size();
    if(item()->_parent != nullptr)
    {
        count++;
    }

    // If less than two people in the family - nothing to draw -> probably messed up initialization
    if(count < 2)
    {
        qDebug() << "FATAL - Wrong Tree Edge Initialization";
        return;
    }

    // Exactly one parent and one child - single line is enough
    if(item()->_parent != nullptr && count == 2)
    {
        qreal pX = item()->_parent->center();
        qreal pY = item()->_parent->bottom();
        qreal chY = item()->_children.first()->top();
        // One line connecting single parent with his single child
        this->setLine(pX, pY, pX, chY);
    }
    // Init all lines for more children
    else
    {
        for(auto child : item()->_children)
        {
            qreal chX = child->center();
            qreal chY = child->top();
            // Line for each child connecting it to horizontal line
            this->setLine(chX, chY, chX, chY - gapGeneration() - heightOverlap);
        }

        // Connect the children together if there are more than 1
        if(item()->_children.size() > 1)
        {
            qreal chX1 = item()->_children.first()->center();
            qreal chX2 = item()->_children.last()->center();
            qreal chY  = item()->_children.first()->top() - this->gapGeneration() - heightOverlap;
            // Horizontal line to connect all children lines
            this->setLine(chX1, chY, chX2, chY);
        }

        if(item()->_parent != nullptr)
        {
            qreal pX = item()->_parent->center();
            qreal pY = item()->_parent->bottom();
            qreal chY = item()->_children.first()->top() - gapGeneration() - heightOverlap;
            // Line from parent to horizontal children line
            this->setLine(pX, pY, pX, chY);
        }
    }

    // Description settings
    if(item()->_description != nullptr)
    {
        if(item()->_parent != nullptr)
        {
            qreal widthOverlap = item()->_description->boundingRect().width() / 2;
            qreal posX = item()->_parent->center() - widthOverlap;
            qreal posY = this->getDescriptionYPos();
            item()->_description->setPos(posX, posY);
        }
        else
        {
            qDebug() << "FATAL - parent missing but marriage to be written";
            item()->_description->setPos(0, 0);
        }
    }
}

Identifier TreeItemEdge::getIdentifier() const
{
    return _ref;
}

QPen TreeItemEdge::getPen() const
{
    QPen pen;
    pen.setWidth(2);
    if(! _fullLine)
        pen.setStyle(Qt::DashLine);
    return pen;
}

QLineF TreeItemEdge::getLine(QGraphicsLineItem *item) const
{
    return item->line();
}

qreal TreeItemEdge::heightOfText()
{
    QFont font;
    QFontMetrics metrics(font);
    QSettings settings;
    QString text = settings.value("textformat/tree/marriage").toString();
    QGraphicsTextItem tempItem(text);

    return tempItem.boundingRect().height();
}

int TreeItemEdge::gapGeneration()
{
    return 15;
}

