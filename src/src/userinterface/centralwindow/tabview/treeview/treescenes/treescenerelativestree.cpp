/*!
 *  \file   treescenerelativestree.cpp
 *  \author Eva Navratilova
 */

#include "treescenerelativestree.h"

TreeSceneRelativesTree::TreeSceneRelativesTree(Kernel &k, Identifier p, QObject *parent)
    : TreeSceneVariables(k, p, parent)
{
    _type = TreeType::RELATIVES_TREE;

    QSettings settings;
    TreeDirection direction = static_cast<TreeDirection>(settings.value("treeDirection/relatives").toInt());
    direction = TreeDirection::SOUTH;
    TreeScene* outlet = new TreeSceneOutletAncestral(k, p, parent);
    TreeScene* family = new TreeSceneFamilyTree(k, p, parent);
    if(direction == TreeDirection::NORTH)
    {
        _sceneNorth = new TreeSceneSouth(outlet);
        _sceneSouth = new TreeSceneNorth(family);
    }
    else if(direction == TreeDirection::SOUTH)
    {
        _sceneNorth = new TreeSceneNorth(outlet);
        _sceneSouth = new TreeSceneSouth(family);
    }

    connect(_sceneNorth, &TreeScene::probandChanged, this, &TreeScene::probandChanged);
    connect(_sceneSouth, &TreeScene::probandChanged, this, &TreeScene::probandChanged);
}

TreeItemPerson *TreeSceneRelativesTree::getNode(Identifier indi)
{
    QVector<TreeItemPerson*> nodes;
    nodes.push_back(_sceneNorth->getNode(indi));
    nodes.push_back(_sceneSouth->getNode(indi));
    nodes.removeAll(nullptr);
    if(nodes.isEmpty())
    {
        return nullptr;
    }
    else
    {
        return nodes.first();
    }
}

TreeItemPerson *TreeSceneRelativesTree::drawNodeTree()
{
    if(_sceneNorth->nodesCount(_proband) != 1)
        return nullptr;
    if(_sceneSouth->nodesCount(_proband) != 1)
        return nullptr;

    auto node1 = _sceneNorth->getNode(_proband);
    _sceneNorth->drawNodeTree(node1, 0);
    auto node2 = _sceneSouth->getNode(_proband);
    _sceneSouth->drawNodeTree(node2, 0);

    this->drawNodeTree(node1, 0);

    return node2;
}

TreeItemPerson *TreeSceneRelativesTree::initNodeTree(const Identifier indi, const Generation gen)
{
    TreeItemPerson* retval1, *retval2;

    Q_UNUSED(retval2);

    retval1 = _sceneNorth->initNodeTree(indi, gen);
    retval2 = _sceneSouth->initNodeTree(indi, gen);

    return retval1;
}

void TreeSceneRelativesTree::drawNodeTree(TreeItemPerson *node, Generation gen)
{
    Q_UNUSED(node);
    Q_UNUSED(gen);

    auto nodeOutlet = _sceneNorth->getNode(_proband);
    auto nodeFamily = _sceneSouth->getNode(_proband);

    qreal xOutlet = nodeOutlet->x();
    qreal xFamily = nodeFamily->x();

    qreal shift = xOutlet - xFamily;

    if(shift < 0)
    {
        _sceneNorth->shiftNode(nodeOutlet, 0, -shift);
    }
    else
    {
        _sceneSouth->shiftNode(nodeFamily, 0, shift);
    }


    _sceneNorth->drawEdgeTree();
    _sceneSouth->drawEdgeTree();


    for(auto item : _sceneNorth->scene()->items())
    {
        if(item == node)
            continue;
        this->scene()->addItem(item);
    }
    for(auto item : _sceneSouth->scene()->items())
    {
        if(item == node)
            continue;
        this->scene()->addItem(item);
    }
}
