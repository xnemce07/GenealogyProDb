/*!
 *  \file   tablecell.cpp
 *  \author Eva Navratilova
 */

#include "tablecell.h"

TableCell::TableCell()
    : QTableWidgetItem()
{
}

Identifier TableCell::getIdentifier() const
{
    return _ref;
}

bool TableCell::operator<(const QTableWidgetItem &other) const
{
    bool ok1, ok2;
    int no1 = this->text().toInt(&ok1);
    int no2 = other.text().toInt(&ok2);
    if(ok1 && ok2)
    {
        return no1 < no2;
    }
    else
    {
        return this->text() < other.text();
    }
}
