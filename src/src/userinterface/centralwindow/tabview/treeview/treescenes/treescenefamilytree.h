/*!
 *  \file   treescenefamilytree.h
 *  \author Eva Navratilova
 */

#ifndef TREESCENEFAMILYTREE_H
#define TREESCENEFAMILYTREE_H

#include "../treescenevariables.h"

class TreeSceneFamilyTree : public TreeSceneVariables
{
    Q_OBJECT
private:
    bool _sonsOnly = false;

public:
    TreeSceneFamilyTree(Kernel &k, Identifier p, QObject *parent = nullptr);
    ~TreeSceneFamilyTree() override = default;

    void setSonsOnly(bool sonsOnly);

    // Tree draw
    TreeItemPerson* initNodeTree(const Identifier indi, const Generation gen) override;
    TreeItemPerson* initFamilyNodeTree(const Identifier indi, Identifier partner, const Generation gen);
    void drawNodeTree(TreeItemPerson* node, Generation gen) override;
};

#endif // TREESCENEFAMILYTREE_H
