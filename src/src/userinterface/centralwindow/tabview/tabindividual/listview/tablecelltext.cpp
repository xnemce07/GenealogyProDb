/*!
 *  \file   tablecelltext.cpp
 *  \author Eva Navratilova
 */

#include "tablecelltext.h"

TableCellText::TableCellText(Identifier ref, QString text)
{
    this->_ref = ref;
    this->setText(text);
}
