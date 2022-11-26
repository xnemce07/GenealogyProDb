/*!
 *  \file   treescenerelativestree.h
 *  \author Eva Navratilova
 */

#ifndef TREESCENERELATIVESTREE_H
#define TREESCENERELATIVESTREE_H

#include "treesceneoutletancestral.h"
#include "treescenefamilytree.h"
#include "treescenenorth.h"
#include "treescenesouth.h"

class TreeSceneRelativesTree : public TreeSceneVariables
{
    Q_OBJECT
private:
    TreeScene* _sceneNorth = nullptr;
    TreeScene* _sceneSouth = nullptr;

public:
    TreeSceneRelativesTree(Kernel &k, Identifier p, QObject *parent = nullptr);
    virtual ~TreeSceneRelativesTree() override = default;

    virtual TreeItemPerson* getNode(Identifier indi) override;

    virtual TreeItemPerson* drawNodeTree() override;

    // Tree draw
    TreeItemPerson* initNodeTree(const Identifier indi, const Generation gen) override;
    void drawNodeTree(TreeItemPerson* node, Generation gen) override;
};

#endif // TREESCENERELATIVESTREE_H
