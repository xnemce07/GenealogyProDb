/*!
 *  \file   treescenesouth.h
 *  \author Eva Navratilova
 */

#ifndef TREESCENESOUTH_H
#define TREESCENESOUTH_H

#include "../treescenedecorator.h"
#include "../treeitems/treeitemedgesouth.h"
#include "../treeitems/treeitempersonsouth.h"

class TreeSceneSouth : public TreeSceneDecorator
{
    Q_OBJECT
public:
    TreeSceneSouth(TreeScene *item, QObject *parent = nullptr);
    virtual ~TreeSceneSouth() override = default;

public slots:
    virtual TreeItemPerson* nodeGenerator(TreeItemPerson* item) const override;
    virtual TreeItemEdge* edgeGenerator(TreeItemEdge* item) const override;
};

#endif // TREESCENESOUTH_H
