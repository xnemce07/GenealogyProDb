/*!
 *  \file   treesceneoutletxnat.cpp
 *  \author Eva Navratilova
 */

#include "treesceneoutletxnat.h"

TreeSceneOutletXnat::TreeSceneOutletXnat(Kernel &k, Identifier p, Gender g, QObject *parent)
    : TreeSceneOutletAncestral (k, p, parent), _genderToDraw(g)
{
    if(_genderToDraw == Gender::MALE)
    {
        _type = TreeType::AGNAT_OUTLET;
    }
    else if(_genderToDraw == Gender::FEMALE)
    {
        _type = TreeType::KOGNAT_OUTLET;
    }
}

void TreeSceneOutletXnat::setSpousePresent(bool present)
{
    _drawSpouse = present;
}

TreeItemPerson *TreeSceneOutletXnat::initNodeTree(const Identifier indi, const Generation gen)
{
    if(_maxGeneration == 0 || (_maxGeneration >= gen))
    {
        if(_kernel.record()->isIndividual(indi))
        {
            // Init freeX to 0 for each Generation
            this->initFreeX(gen);

            // Construct this Individual's Node
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

            if(gen == 0 || genderIndi == _genderToDraw)
            {
                // Recursion
                Identifier father = _kernel.record()->getIndividualFather(indi);
                Identifier mother = _kernel.record()->getIndividualMother(indi);

                TreeItemPerson* nodeFather = this->initNodeTree(father, gen + 1);
                TreeItemPerson* nodeMother = this->initNodeTree(mother, gen + 1);

                // Don't draw spouse
                if(!_drawSpouse)
                {
                    if(_genderToDraw == Gender::MALE)
                    {
                        if(nodeFather != nullptr)
                            item->addChild(nodeFather);
                        if(nodeMother != nullptr)
                            delete nodeMother;
                    }
                    else if(_genderToDraw == Gender::FEMALE)
                    {
                        if(nodeMother != nullptr)
                            item->addChild(nodeMother);
                        if(nodeFather != nullptr)
                            delete nodeFather;
                    }
                    else
                    {
                        if(nodeFather != nullptr)
                            delete nodeFather;
                        if(nodeMother != nullptr)
                            delete nodeMother;
                    }
                }
                // Draw spouse
                else
                {
                    if(nodeFather != nullptr)
                        item->addChild(nodeFather);
                    if(nodeMother != nullptr)
                        item->addChild(nodeMother);
                }

            //qDebug() << "INDI "<<indi.get()<<" F "<<father.get()<< " M "<<mother.get();
            }

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
