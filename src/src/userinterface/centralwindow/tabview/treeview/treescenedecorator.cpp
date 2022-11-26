/*!
 *  \file   treescenedecorator.cpp
 *  \author Eva Navratilova
 */

#include "treescenedecorator.h"

TreeSceneDecorator::TreeSceneDecorator(TreeScene *item, QObject *parent)
    : TreeScene (parent), _wrappee(item)
{
    connect(_wrappee, &TreeScene::generateNode, this, &TreeScene::nodeGenerator);
    connect(_wrappee, &TreeScene::generateEdge, this, &TreeScene::edgeGenerator);
    connect(_wrappee,  &TreeScene::probandChanged, this, &TreeScene::probandChanged);
}

TreeSceneDecorator::~TreeSceneDecorator()
{
    _wrappee->deleteLater();
}

QGraphicsScene *TreeSceneDecorator::scene()
{
    return _wrappee->scene();
}

TreeScene *TreeSceneDecorator::item()
{
    return _wrappee;
}

TreeType TreeSceneDecorator::getTreeType() const
{
    return _wrappee->getTreeType();
}

void TreeSceneDecorator::setMaximumGeneration(Generation gen1)
{
    this->item()->setMaximumGeneration(gen1);
}

TreeItemPerson* TreeSceneDecorator::draw()
{
    return item()->draw();
}

TreeItemPerson *TreeSceneDecorator::drawNodeTree()
{
    return item()->drawNodeTree();
}

void TreeSceneDecorator::drawEdgeTree()
{
    _wrappee->drawEdgeTree();
}

TreeItemPerson *TreeSceneDecorator::initNodeTree(Identifier person, Generation gen)
{
    return _wrappee->initNodeTree(person, gen);
}

void TreeSceneDecorator::drawNodeTree(TreeItemPerson *person, Generation gen)
{
    item()->drawNodeTree(person, gen);
}

void TreeSceneDecorator::shiftNode(TreeItemPerson *indi, Generation gen, qreal shift)
{
    item()->shiftNode(indi, gen, shift);
}

int TreeSceneDecorator::nodesCount(Identifier proband) const
{
    return _wrappee->nodesCount(proband);
}

TreeItemPerson *TreeSceneDecorator::getNode(Identifier indi)
{
    return _wrappee->getNode(indi);
}

qreal TreeSceneDecorator::freeX(Generation gen) const
{
    return _wrappee->freeX(gen);
}

void TreeSceneDecorator::changeProband(const Identifier indi)
{
    _wrappee->changeProband(indi);
}
