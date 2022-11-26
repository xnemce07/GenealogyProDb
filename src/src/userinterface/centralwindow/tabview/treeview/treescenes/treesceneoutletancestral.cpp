/*!
 *  \file   treesceneoutletancestral.cpp
 *  \author Eva Navratilova
 */

#include "treesceneoutletancestral.h"

TreeSceneOutletAncestral::TreeSceneOutletAncestral(Kernel &k, Identifier p, QObject *parent)
    : TreeSceneVariables (k, p, parent)
{
    _type = TreeType::ANCESTRAL_OUTLET;
}

TreeItemPerson *TreeSceneOutletAncestral::initNodeTree(const Identifier indi, const Generation gen)
{
    if(_maxGeneration == 0 || (_maxGeneration >= gen))
    {
        if(_kernel.record()->isIndividual(indi))
        {
            // Init freeX to 0 for each Generation
            this->initFreeX(gen);

            // Recursion
            Identifier father = _kernel.record()->getIndividualFather(indi);
            Identifier mother = _kernel.record()->getIndividualMother(indi);

            TreeItemPerson* nodeFather = this->initNodeTree(father, gen + 1);
            TreeItemPerson* nodeMother = this->initNodeTree(mother, gen + 1);

            TreeItemPerson *item;
            Gender genderIndi = _kernel.record()->getIndividualGender(indi);
            QString personText = TextFormatter::getPersonTreeText(_kernel, indi);
            if(genderIndi == Gender::MALE)
            {
                item = emit(this->generateNode(new TreeItemPersonMan(indi, personText)));

            }
            else if(genderIndi == Gender::FEMALE)
            {
                item = emit(this->generateNode(new TreeItemPersonWoman(indi, personText)));
            }
            else
            {
                item = emit(this->generateNode(new TreeItemPerson(indi, personText)));
            }

            connect(item->item(), &TreeItemPerson::probandChanged, this, &TreeScene::changeProband);

            if(nodeFather != nullptr)
                item->addChild(nodeFather);
            if(nodeMother != nullptr)
                item->addChild(nodeMother);

            _nodes.insertMulti(indi, item);

            if(item->getChildren().count() > 0)
            {
                Identifier fam = _kernel.record()->getIndividualParentalFamily(indi);
                bool hasFather = _kernel.record()->getFamilyHusband(fam).isValid();
                bool hasMother = _kernel.record()->getFamilyMarriageWitness1(fam).isValid();
                bool married   = _kernel.record()->isFamilyMarried(fam);
                bool fullLine  = married || (!hasFather || !hasMother);

                TreeItemEdge *edge = emit(this->generateEdge(new TreeItemEdge(fam, item, item->getChildren(), fullLine, TextFormatter::getMarriageTreeText(_kernel, fam))));
                _edges.insertMulti(fam, edge);
            }

            return item;
        }
    }
    return nullptr;
}

void TreeSceneOutletAncestral::drawNodeTree(TreeItemPerson *node, Generation gen)
{
    // Draw node's parents
    auto parents = node->getChildren();
    for(TreeItemPerson* parent : parents)
    {
        drawNodeTree(parent, gen + 1);
    }

    qreal x = this->freeX(gen);
    qreal y = this->y(gen);

    node->setPos(x,y);

    // Adjust position
    auto children = node->getChildren();
    if(0 < children.length() && children.length() <= 2)
    {
        TreeItemPerson *parent1, *parent2;
        parent1 = children.first();
        parent2 = children.last();

        qreal parentWidth = parent2->right() - parent1->left();
        qreal parentOverlap = (parentWidth - node->width()) / 2;
        qreal shift = parent1->left() + parentOverlap;

        if(shift >= node->x())
        {
            node->setX(shift);
        }
        else
        {
            qreal parentShift = node->left() - parent1->left() - parentOverlap;
            for(auto parent : node->getChildren())
            {
                this->shiftNode(parent, gen + 1, parentShift);
            }
        }
    }

    // Update free space in current generation
    _freeX.insert(gen, node->right() + this->marginCellVertical());

    // Add item to the scene and paint
    //node->paint(nullptr, nullptr, nullptr);
    _scene.addItem(node->item());
}
