/*!
 *  \file   tablecell.h
 *  \author Eva Navratilova
 */

#ifndef TABLECELL_H
#define TABLECELL_H

#include <QTableWidgetItem>

#include "kernel.h"

class TableCell : public QTableWidgetItem
{
protected:
    Identifier _ref;

public:
    TableCell();
    virtual ~TableCell() = default;

    Identifier getIdentifier() const;

    bool operator<(const QTableWidgetItem &other) const;
};

#endif // TABLECELL_H
