/*!
 *  \file   narrowbutton.cpp
 *  \author Eva Navratilova
 */

#include "narrowbutton.h"

NarrowButton::NarrowButton(QWidget *parent)
    : QPushButton(parent)
{
    this->setStyleSheet("padding: 1px");
    this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void NarrowButton::setText(const QString &text)
{
    this->QPushButton::setText(text);

    QFont font;
    QFontMetrics metrics(font);
    int width = metrics.horizontalAdvance(text) + 10;
    this->setMinimumWidth(width);
}
