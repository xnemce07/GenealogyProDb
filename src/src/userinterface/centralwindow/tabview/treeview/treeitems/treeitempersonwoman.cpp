/*!
 *  \file   treeitempersonwoman.cpp
 *  \author Eva Navratilova
 */

#include "treeitempersonwoman.h"

TreeItemPersonWoman::TreeItemPersonWoman(Identifier indi, QString text, QGraphicsItem *parent)
    : TreeItemPerson (indi, text, parent)
{

}

qreal TreeItemPersonWoman::getRoundedRectRadius() const
{
    return 10;
}
