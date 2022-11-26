/*!
 *  \file   treescenesouth.cpp
 *  \author Eva Navratilova
 */

#include "treescenesouth.h"

TreeSceneSouth::TreeSceneSouth(TreeScene *item, QObject *parent)
    : TreeSceneDecorator (item, parent)
{

}

TreeItemPerson *TreeSceneSouth::nodeGenerator(TreeItemPerson *item) const
{
    return new TreeItemPersonSouth(item);
}

TreeItemEdge *TreeSceneSouth::edgeGenerator(TreeItemEdge *item) const
{
    return new TreeItemEdgeSouth(item);
}
