/*!
 *  \file   treescenenorth.cpp
 *  \author Eva Navratilova
 */

#include "treescenenorth.h"

TreeSceneNorth::TreeSceneNorth(TreeScene *item, QObject *parent)
    : TreeSceneDecorator (item, parent)
{

}

TreeItemPerson *TreeSceneNorth::nodeGenerator(TreeItemPerson *item) const
{
    return new TreeItemPersonNorth(item);
}

TreeItemEdge *TreeSceneNorth::edgeGenerator(TreeItemEdge *item) const
{
    return new TreeItemEdgeNorth(item);
}
