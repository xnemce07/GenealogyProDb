/*!
 *  \file   treescenedoubletree.cpp
 *  \author Eva Navratilova
 */

#include "treescenedoubletree.h"
#include "treescenedoubletree.h"

TreeSceneDoubleTree::TreeSceneDoubleTree(Kernel &k, Identifier p, QObject *parent)
    : TreeSceneVariables(k, p, parent)
{
    _type = TreeType::EMPTY;
}

TreeSceneDoubleTree::~TreeSceneDoubleTree()
{

}

void TreeSceneDoubleTree::setSceneNorth(TreeScene *scene)
{
    auto scenePtr = this->getCurrentScene(TreeDirection::NORTH);

    if(*scenePtr != nullptr)
    {
        (*scenePtr)->deleteLater();
    }
    *scenePtr = scene;
}

void TreeSceneDoubleTree::setSceneSouth(TreeScene *scene)
{
    auto scenePtr = this->getCurrentScene(TreeDirection::SOUTH);

    if(*scenePtr != nullptr)
    {
        (*scenePtr)->deleteLater();
    }
    *scenePtr = scene;
}

TreeItemPerson *TreeSceneDoubleTree::drawNodeTree()
{
    TreeItemPerson* node1, *node2;
    node1 = node2 = nullptr;

    if(_sceneNorth != nullptr)
    {
        if(_sceneNorth->nodesCount(_proband) != 1)
            return nullptr;
        node1 = _sceneNorth->getNode(_proband);
        _sceneNorth->drawNodeTree(node1, 0);
    }

    if(_sceneSouth != nullptr)
    {
        if(_sceneSouth->nodesCount(_proband) != 1)
            return nullptr;
        node2 = _sceneSouth->getNode(_proband);
        _sceneSouth->drawNodeTree(node2, 0);
    }

    if(node1 != nullptr)
    {
        this->drawNodeTree(node1, 0);
    }

    return node1;
}

TreeItemPerson *TreeSceneDoubleTree::initNodeTree(const Identifier indi, const Generation gen)
{
    TreeItemPerson* retval1, *retval2;
    retval1 = retval2 = nullptr;

    if(_sceneNorth != nullptr)
    {
        retval1 = _sceneNorth->initNodeTree(indi, gen);
    }

    if(_sceneSouth != nullptr)
    {
        retval2 = _sceneSouth->initNodeTree(indi, gen);
    }

    return retval1;
}

void TreeSceneDoubleTree::drawNodeTree(TreeItemPerson *node, Generation gen)
{
    Q_UNUSED(node);
    Q_UNUSED(gen);

    TreeItemPerson *nodeNorth, *nodeSouth;
    nodeNorth = nodeSouth = nullptr;

    if(_sceneNorth != nullptr && _sceneSouth != nullptr)
    {
        nodeNorth = _sceneNorth->getNode(_proband);
        nodeSouth = _sceneSouth->getNode(_proband);

        qreal xNorth = nodeNorth->x();
        qreal xSouth = nodeSouth->x();

        qreal shift = xNorth - xSouth;

        if(shift < 0)
        {
            _sceneNorth->shiftNode(nodeNorth, 0, -shift);
        }
        else
        {
            _sceneSouth->shiftNode(nodeSouth, 0, shift);
        }
    }

    if(nodeNorth != nullptr)
    {
        this->drawNodeSubTree(TreeDirection::NORTH, nodeNorth);
    }
    if(nodeSouth != nullptr)
    {
        this->drawNodeSubTree(TreeDirection::SOUTH, nodeSouth);
    }
}

TreeScene **TreeSceneDoubleTree::getCurrentScene(TreeDirection dir)
{
    TreeScene **current = nullptr;
    switch(dir)
    {
    case TreeDirection::NORTH:
        current = &_sceneNorth;
        break;
    case TreeDirection::SOUTH:
        current = &_sceneSouth;
        break;
    }
    return current;
}

void TreeSceneDoubleTree::drawNodeSubTree(TreeDirection dir, TreeItemPerson *node)
{
    auto current = this->getCurrentScene(dir);

    if(current != nullptr && (*current) != nullptr)
    {
        (*current)->drawEdgeTree();

        for(auto item : (*current)->scene()->items())
        {
            if(item == node)
                continue;
            this->scene()->addItem(item);
        }
    }
}

void TreeSceneDoubleTree::changeTreeType(TreeDirection dir, TreeType type)
{
    TreeScene** current = getCurrentScene(dir);

    if(current != nullptr && (*current) != nullptr && type != (*current)->getTreeType())
    {
        if(*current != nullptr)
        {
            _scene.clear();

            (*current)->deleteLater();
            //*current = nullptr;
        }

        switch(dir)
        {
        case TreeDirection::NORTH:
            *current = new TreeSceneNorth(TreeSceneUniversal::sceneForType(_kernel, _proband, type));
            break;
        case TreeDirection::SOUTH:
            *current = new TreeSceneSouth(TreeSceneUniversal::sceneForType(_kernel, _proband, type));
            break;
        }

        connect(*current, &TreeScene::probandChanged, this, &TreeScene::probandChanged);
    }
}

void TreeSceneDoubleTree::changeMaximumGeneration(TreeDirection dir, Generation gen)
{
    auto current = this->getCurrentScene(dir);
    if(current != nullptr && (*current) != nullptr)
    {
        (*current)->setMaximumGeneration(gen);
    }
}

void TreeSceneDoubleTree::changeSpousePresent(TreeDirection dir, bool present)
{
    auto current = this->getCurrentScene(dir);
    if(current != nullptr && (*current) != nullptr)
    {
        static_cast<TreeSceneOutletXnat*>(*current)->setSpousePresent(present);
    }
}

void TreeSceneDoubleTree::changeSonsOnly(TreeDirection dir, bool sonsOnly)
{
    auto current = this->getCurrentScene(dir);
    if(current != nullptr && (*current) != nullptr)
    {
        static_cast<TreeSceneFamilyTree*>(*current)->setSonsOnly(sonsOnly);
    }
}
