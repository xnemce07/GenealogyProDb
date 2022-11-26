/*!
 *  \file   treeitempersonman.h
 *  \author Eva Navratilova
 */

#ifndef TREEITEMPERSONMAN_H
#define TREEITEMPERSONMAN_H

#include "treeitemperson.h"

class TreeItemPersonMan : public TreeItemPerson
{
public:
    TreeItemPersonMan(Identifier indi, QString text, QGraphicsItem *parent = nullptr);
    ~TreeItemPersonMan() = default;

};

#endif // TREEITEMPERSONMAN_H
