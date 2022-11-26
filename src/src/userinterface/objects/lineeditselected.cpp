/*!
 *  \file   lineeditselected.cpp
 *  \author Eva Navratilova
 */

#include "lineeditselected.h"

LineEditSelected::LineEditSelected()
{

}

void LineEditSelected::focusInEvent(QFocusEvent *e)
{
    QLineEdit::focusInEvent(e);
    QTimer::singleShot(0, this, &QLineEdit::selectAll);
}
