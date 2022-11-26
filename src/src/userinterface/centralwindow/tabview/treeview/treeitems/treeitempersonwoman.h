/*!
 *  \file   treeitempersonwoman.h
 *  \author Eva Navratilova
 */

#ifndef TREEITEMPERSONWOMAN_H
#define TREEITEMPERSONWOMAN_H

#include "treeitemperson.h"

class TreeItemPersonWoman : public TreeItemPerson
{
public:
    TreeItemPersonWoman(Identifier indi, QString text, QGraphicsItem *parent = nullptr);
    ~TreeItemPersonWoman() = default;

    qreal getRoundedRectRadius() const override;
};

#endif // TREEITEMPERSONWOMAN_H
