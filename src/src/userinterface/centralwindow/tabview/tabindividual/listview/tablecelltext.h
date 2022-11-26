/*!
 *  \file   tablecelltext.h
 *  \author Eva Navratilova
 */

#ifndef TABLECELLTEXT_H
#define TABLECELLTEXT_H

#include <QString>

#include "tablecell.h"
#include "kernel.h"


class TableCellText : public TableCell
{
public:
    TableCellText() = default;
    TableCellText(Identifier ref, QString text);
};

#endif // TABLECELLTEXT_H
