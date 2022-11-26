/*!
 *  \file   label.cpp
 *  \author Eva Navratilova
 */

#include "label.h"

Label::Label()
{
    //this->setFixedWidth(75);
    this->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
}

void Label::setText(const QString &text)
{
    this->QLabel::setText(text);
    QFont font;
    QFontMetrics fontMetrics(font);
    int width = fontMetrics.horizontalAdvance(text);
    this->setFixedWidth(width);
}
