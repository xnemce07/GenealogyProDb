/*!
 *  \file   tablecelldate.cpp
 *  \author Eva Navratilova
 */

#include "tablecelldate.h"

TableCellDate::TableCellDate(Identifier ref, Date date)
{
    this->_ref = ref;
    int year = date.year();
    QString text;
    if(year != 0)
        text = QString::number(year);
    this->setText(text);
}

