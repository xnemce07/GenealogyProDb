/*!
 *  \file   treescenedoubletree.h
 *  \author Eva Navratilova
 */

#ifndef TREESCENEDOUBLETREE_H
#define TREESCENEDOUBLETREE_H

#include "treesceneuniversal.h"
#include "treescenenorth.h"
#include "treescenesouth.h"

class TreeSceneDoubleTree : public TreeSceneVariables
{
    Q_OBJECT
private:
    TreeScene* _sceneNorth = nullptr;
    TreeScene* _sceneSouth = nullptr;

public:
    TreeSceneDoubleTree(Kernel &k, Identifier p, QObject *parent = nullptr);
    virtual ~TreeSceneDoubleTree() override;

    void setSceneNorth(TreeScene* scene);
    void setSceneSouth(TreeScene* scene);

    virtual TreeItemPerson* drawNodeTree() override;

    // Tree draw
    TreeItemPerson* initNodeTree(const Identifier indi, const Generation gen) override;
    void drawNodeTree(TreeItemPerson* node, Generation gen) override;

private:
    TreeScene** getCurrentScene(TreeDirection dir);

    void drawNodeSubTree(TreeDirection dir, TreeItemPerson *node);

public slots:
    /*void changeNorthTreeType(TreeType type);
    void changeNorthMaximumGeneration(Generation gen);
    void changeNorthSpousePresent(bool present);
    void changeNorthSonsOnly(bool sonsOnly);*/

    void changeTreeType(TreeDirection dir, TreeType type);
    void changeMaximumGeneration(TreeDirection dir, Generation gen);
    void changeSpousePresent(TreeDirection dir, bool present);
    void changeSonsOnly(TreeDirection dir, bool sonsOnly);

};

#endif // TREESCENEDOUBLETREE_H
