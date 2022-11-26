/*!
 *  \file   elidebutton.cpp
 *  \author Eva Navratilova
 */

#include "elidebutton.h"

ElideButton::ElideButton(QWidget *parent)
    : NarrowButton(parent)
{

}

void ElideButton::setText(const QString &text)
{
    _content = text.simplified();
    this->update();
}

void ElideButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    const QFontMetrics fontMetrics = painter.fontMetrics();
    const int usableWidth = qRound(0.9 * this->width());

    const QString elidedText = fontMetrics.elidedText(_content, Qt::ElideRight, usableWidth);
    _elided = (elidedText != _content);
    NarrowButton::setText(elidedText);
    QPushButton::paintEvent(event);
}
