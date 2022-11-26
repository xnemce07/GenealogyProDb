/*!
 *  \file   subbox.cpp
 *  \author Eva Navratilova
 */

#include "subbox.h"

Subbox::Subbox(QWidget *parent)
    : QWidget(parent), Sizer()
{
    _layout.setVerticalSpacing(0);
    _layout.setHorizontalSpacing(this->mediumSpacing());
    _layout.setMargin(0);
    _layout.setContentsMargins(0,0,0,0);
    this->setLayout(&_layout);
}
