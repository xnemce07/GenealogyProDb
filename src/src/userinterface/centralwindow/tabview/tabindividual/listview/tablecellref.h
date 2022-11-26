/*!
 *  \file   tablecellref.h
 *  \author Eva Navratilova
 */

#ifndef INDIVIDUALITEMMODEL_H
#define INDIVIDUALITEMMODEL_H

#include "tablecell.h"
#include "kernel.h"

class TableCellRef : public TableCell
{
public:
    TableCellRef() = default;
    TableCellRef(Identifier ref);
};

#endif // INDIVIDUALITEMMODEL_H
