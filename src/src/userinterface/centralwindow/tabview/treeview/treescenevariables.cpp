/*!
 *  \file   treescenevariables.cpp
 *  \author Eva Navratilova
 */

#include "treescenevariables.h"

TreeSceneVariables::TreeSceneVariables(Kernel &k, Identifier p, QObject *parent)
    : TreeScene (parent), _kernel(k), _proband(p)
{

}

TreeSceneVariables::~TreeSceneVariables()
{

}

QGraphicsScene *TreeSceneVariables::scene()
{
    return &_scene;
}

TreeType TreeSceneVariables::getTreeType() const
{
    return _type;
}

void TreeSceneVariables::setMaximumGeneration(Generation gen1)
{
    _maxGeneration = gen1;
}

TreeItemPerson* TreeSceneVariables::draw()
{
    this->initNodeTree(_proband, 0);

    return this->drawNodeTree();
}

TreeItemPerson *TreeSceneVariables::drawNodeTree()
{
    if(_nodes.count(_proband) != 1)
        return nullptr;

    auto node = this->getNode(_proband);
    this->drawNodeTree(node, 0);

    this->drawEdgeTree();

    this->updateTreePersonActiveColor(_proband);

    return node;
}

void TreeSceneVariables::drawEdgeTree()
{
    for(auto edge : _edges)
    {
        edge->paint(nullptr, nullptr, nullptr);
        edge->setScene(&_scene);
        edge->setZValue(-1);
    }
}

void TreeSceneVariables::shiftNode(TreeItemPerson *indi, Generation gen, qreal shift)
{
    /// TODO - probably implementation can be added to base
    for(auto parent : indi->getChildren())
    {
        this->shiftNode(parent, gen + 1, shift);
    }
    indi->setX(indi->x() + shift);

    if(this->freeX(gen) < indi->right() + this->marginCellVertical())
        _freeX.insert(gen, indi->right() + this->marginCellVertical());
}

int TreeSceneVariables::nodesCount(Identifier proband) const
{
    return _nodes.count(proband);
}

TreeItemPerson *TreeSceneVariables::getNode(Identifier indi)
{
    TreeItemPerson*& item = _nodes[indi];
    return item;
}

void TreeSceneVariables::initFreeX(Generation gen)
{
    if(_freeX.size() == gen)
    {
        _freeX.insert(gen, 0);
    }
}

qreal TreeSceneVariables::freeX(Generation gen) const
{
    return _freeX.find(gen).value();
}

void TreeSceneVariables::updateTreePersonActiveColor(Identifier indi)
{
    /// TODO - getNode does not get the right instance to change background - probably only a copy - what to do?

    TreeItemPerson* node;

    // Change old proband color back to white
    node = this->getNode(_proband);
    node->clearFocus();     // reset background color
    _nodes.insert(_proband, node);

    // Change new proband color
    node = this->getNode(indi);
    node->setFocus();
    _nodes.insert(indi, node);
}

void TreeSceneVariables::changeProband(const Identifier indi)
{
    this->updateTreePersonActiveColor(indi);

    emit(this->probandChanged(indi));
}
