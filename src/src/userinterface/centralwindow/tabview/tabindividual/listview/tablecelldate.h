/*!
 *  \file   tablecelldate.h
 *  \author Eva Navratilova
 */

#ifndef TABLECELLDATE_H
#define TABLECELLDATE_H


#include "tablecell.h"
#include "kernel.h"

class TableCellDate : public TableCell
{
public:
    TableCellDate() = default;
    virtual ~TableCellDate() = default;
    TableCellDate(Identifier ref, Date date);

};

#endif // TABLECELLDATE_H
