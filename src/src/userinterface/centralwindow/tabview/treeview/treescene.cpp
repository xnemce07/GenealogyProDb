/*!
 *  \file   treescene.cpp
 *  \author Eva Navratilova
 */

#include "treescene.h"

TreeScene::TreeScene(QObject *parent)
    : QObject (parent)
{
    connect(this, &TreeScene::generateNode, this, &TreeScene::nodeGenerator);
    connect(this, &TreeScene::generateEdge, this, &TreeScene::edgeGenerator);
}

TreeScene::~TreeScene()
{

}

TreeScene *TreeScene::item()
{
    return this;
}

qreal TreeScene::y(Generation gen) const
{
    qreal nodeHeight = TreeItemPerson::heightOfText();

    return gen * (nodeHeight + this->spaceInterNode());
}

qreal TreeScene::spaceInterNode() const
{
    qreal marriageHeight = TreeItemEdge::heightOfText();
    return TreeItemEdge::gapGeneration() * 2 + marriageHeight;
}

qreal TreeScene::marginCellVertical() const
{
    return 10;
}

TreeItemPerson *TreeScene::nodeGenerator(TreeItemPerson *item) const
{
    return  item;
}

TreeItemEdge *TreeScene::edgeGenerator(TreeItemEdge *item) const
{
    return item;
}

