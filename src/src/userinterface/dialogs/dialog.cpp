/*!
 *  \file   dialog.cpp
 *  \author Eva Navratilova
 */

#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog (parent)
{
    this->setLayout(&_layout);
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}
