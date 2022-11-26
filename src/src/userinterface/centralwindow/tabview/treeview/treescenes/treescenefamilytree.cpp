/*!
 *  \file   treescenefamilytree.cpp
 *  \author Eva Navratilova
 */

#include "treescenefamilytree.h"

TreeSceneFamilyTree::TreeSceneFamilyTree(Kernel &k, Identifier p, QObject *parent)
    : TreeSceneVariables (k, p, parent)
{
    _type = TreeType::FAMILY_TREE;
}

void TreeSceneFamilyTree::setSonsOnly(bool sonsOnly)
{
    _sonsOnly = sonsOnly;
}

TreeItemPerson *TreeSceneFamilyTree::initNodeTree(const Identifier indi, const Generation gen)
{
    if(_maxGeneration == 0 || (_maxGeneration >= gen))
    {
        if(_kernel.record()->isIndividual(indi))
        {
            // Init freeX to 0 for each Generation
            if(_freeX.size() == gen)
            {
                _freeX.insert(gen, 0);
            }

            // Recursion
            QVector<Identifier> partners = _kernel.record()->getIndividualPartners(indi);
            QVector<TreeItemPerson*> nodePartners;

            for(auto partner : partners)
            {
                nodePartners.push_back(this->initFamilyNodeTree(indi, partner, gen + 1));
            }

            /*
            Identifier father = _kernel.record()->getIndividualFather(indi);
            Identifier mother = _kernel.record()->getIndividualMother(indi);

            TreeItemPerson* nodeFather = this->initNodeTree(father, gen + 1);
            TreeItemPerson* nodeMother = this->initNodeTree(mother, gen + 1);*/


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

            item->addChildren(nodePartners);

            //qDebug() << "INDI "<<indi.get()<<" F "<<father.get()<< " M "<<mother.get();

            _nodes.insertMulti(indi, item);

            if(item->getChildren().count() > 0)
            {
                bool fullLine  = true;

                TreeItemEdge *edge = emit(this->generateEdge(new TreeItemEdge(indi, item, item->getChildren(), fullLine, QString())));
                _edges.insertMulti(indi, edge);
            }

            return item;
        }
    }
    return nullptr;
}

TreeItemPerson *TreeSceneFamilyTree::initFamilyNodeTree(const Identifier indi, Identifier partner, const Generation gen)
{
    // Init freeX to 0 for each Generation
    this->initFreeX(gen);

    Identifier family = _kernel.record()->getFamilyOfCouple(indi, partner);
    auto children = _kernel.record()->getFamilyChildren(family);
    QVector<TreeItemPerson*> nodeChildren;
    for(auto child : children)
    {
        Gender childGender = _kernel.record()->getIndividualGender(child);
        if(!_sonsOnly || (childGender == Gender::MALE))
        {
            nodeChildren.push_back(this->initNodeTree(child, gen + 1));
        }
    }

    TreeItemPerson* item;
    Gender genderIndi = _kernel.record()->getIndividualGender(partner);
    QString personText = TextFormatter::getPersonTreeText(_kernel, partner);
    if(genderIndi == Gender::MALE)
    {
        item = emit(this->generateNode(new TreeItemPersonMan(partner, personText)));

    }
    else if(genderIndi == Gender::FEMALE)
    {
        item = emit(this->generateNode(new TreeItemPersonWoman(partner, personText)));
    }
    else
    {
        item = emit(this->generateNode(new TreeItemPerson(partner, personText)));
    }

    connect(item->item(), &TreeItemPerson::probandChanged, this, &TreeScene::probandChanged);

    item->addChildren(nodeChildren);

    //qDebug() << "INDI "<<indi.get()<<" F "<<father.get()<< " M "<<mother.get();

    _nodes.insertMulti(partner, item);

    if(item->getChildren().count() > 0)
    {
        QString text = TextFormatter::getMarriageTreeText(_kernel, family);
        bool married = _kernel.record()->isFamilyMarried(family);
        bool noPartner = ! _kernel.record()->isIndividual(partner);
        bool fullLine = (married || noPartner)? true : false;

        TreeItemEdge *edge = emit(this->generateEdge(new TreeItemEdge(partner, item, item->getChildren(), fullLine, text)));
        _edges.insertMulti(indi, edge);
    }

    return item;
}

void TreeSceneFamilyTree::drawNodeTree(TreeItemPerson *node, Generation gen)
{
    // Draw node's children
    auto children = node->getChildren();
    for(TreeItemPerson* child : children)
    {
        drawNodeTree(child, gen + 1);
    }
    /*qDebug() << "POSITION";
    qDebug() << "X   " << this->freeX(gen);
    qDebug() << "Y   " << individualNode->height()*gen;*/

    qreal x = this->freeX(gen);
    qreal y = this->y(gen);

    //qDebug() << " Y GEN IS "<<y;

    node->setPos(x,y);

    // Adjust position
    if(0 < children.length())
    {
        TreeItemPerson *childFirst, *childLast;
        childFirst = children.first();
        childLast = children.last();

        qreal parentWidth = childLast->right() - childFirst->left();
        qreal parentOverlap = (parentWidth - node->width()) / 2;
        qreal shift = childFirst->left() + parentOverlap;
        //int newX = parent1->left() + (parentWidth - this->width())/2;

        //qDebug() << "NAME " << node->toPlainText().left(15);
        /*qDebug() << "PWIDTH "<<parentWidth;
        qDebug() << "WIDTH " << node->width();
        qDebug() << "X "<< node->x();
        qDebug() << "pOVER "<< parentOverlap;
        qDebug() << "SHIFT "<< shift;*/

        if(shift >= node->x())
        {
            node->setX(shift);
        }
        else
        {
            qreal parentShift = node->left() - childFirst->left() - parentOverlap;
            //qDebug() << "PARENT SHIFT "<<parentShift;
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
