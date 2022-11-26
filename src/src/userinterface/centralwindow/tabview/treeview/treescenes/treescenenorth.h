/*!
 *  \file   treescenenorth.h
 *  \author Eva Navratilova
 */

#ifndef TREESCENENORTH_H
#define TREESCENENORTH_H

#include "../treescenedecorator.h"
#include "../treeitems/treeitemedgenorth.h"
#include "../treeitems/treeitempersonnorth.h"

class TreeSceneNorth : public TreeSceneDecorator
{
    Q_OBJECT
public:
    TreeSceneNorth(TreeScene *item, QObject *parent = nullptr);
    virtual ~TreeSceneNorth() override = default;

public slots:
    virtual TreeItemPerson* nodeGenerator(TreeItemPerson* item) const override;
    virtual TreeItemEdge* edgeGenerator(TreeItemEdge* item) const override;
};

#endif // TREESCENENORTH_H
