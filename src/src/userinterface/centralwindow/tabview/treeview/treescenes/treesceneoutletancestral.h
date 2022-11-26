/*!
 *  \file   treesceneoutletancestral.h
 *  \author Eva Navratilova
 */

#ifndef TREESCENEOUTLETANCESTRAL_H
#define TREESCENEOUTLETANCESTRAL_H

#include "../treescenevariables.h"
#include "../treeitems/treeitemedgenorth.h"

class TreeSceneOutletAncestral : public TreeSceneVariables
{
    Q_OBJECT
public:
    TreeSceneOutletAncestral(Kernel &k, Identifier p, QObject *parent = nullptr);
    virtual ~TreeSceneOutletAncestral() override = default;

    // Tree draw
    TreeItemPerson* initNodeTree(const Identifier indi, const Generation gen) override;
    void drawNodeTree(TreeItemPerson* node, Generation gen) override;
};

#endif // TREESCENEOUTLETANCESTRAL_H
