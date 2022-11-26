/*!
 *  \file   treescene.h
 *  \author Eva Navratilova
 */

#ifndef TREESCENE_H
#define TREESCENE_H

#include <QObject>
#include <QMultiHash>

#include "../../../../kernel.h"
#include "../../../../textformatter.h"
#include "treeitems/treeitemperson.h"
#include "treeitems/treeitempersonman.h"
#include "treeitems/treeitempersonwoman.h"
#include "treeitems/treeitempersonnorth.h"
#include "treeitems/treeitemedge.h"

enum class TreeType
{
    EMPTY = 0,
    ANCESTRAL_OUTLET,
    AGNAT_OUTLET,
    KOGNAT_OUTLET,
    FAMILY_TREE,
    RELATIVES_TREE  // Must be last!!!! - special tree case
};

enum class TreeDirection
{
    NORTH = 0,
    SOUTH
};

class TreeScene : public QObject
{
    Q_OBJECT
public:
    TreeScene(QObject *parent = nullptr);
    virtual ~TreeScene();

    virtual void setMaximumGeneration(Generation gen1) = 0;

    virtual QGraphicsScene* scene() = 0;

    virtual TreeScene* item();
    virtual TreeType getTreeType() const = 0;

    virtual TreeItemPerson* draw() = 0;
    virtual TreeItemPerson* drawNodeTree() = 0;
    virtual void drawEdgeTree() = 0;

    virtual TreeItemPerson* initNodeTree(Identifier person, Generation gen) = 0;
    virtual void drawNodeTree(TreeItemPerson* person, Generation gen) = 0;
    //virtual void shiftNode(TreeItemPerson* indi, Generation gen, int shift) = 0;

    virtual void shiftNode(TreeItemPerson* indi, Generation gen, qreal shift) = 0;
    virtual int nodesCount(Identifier proband) const = 0;
    virtual TreeItemPerson* getNode(Identifier indi) = 0;

    // Coordinates & space
    virtual qreal freeX(Generation gen) const = 0;

protected:
    qreal y(Generation gen) const;
    qreal spaceInterNode() const;
    qreal marginCellVertical() const;

signals:
    void probandChanged(const Identifier ref);

    TreeItemPerson* generateNode(TreeItemPerson* item);
    TreeItemEdge* generateEdge(TreeItemEdge* item);

public slots:
    virtual void changeProband(const Identifier indi) = 0;

    virtual TreeItemPerson* nodeGenerator(TreeItemPerson* item) const;
    virtual TreeItemEdge* edgeGenerator(TreeItemEdge* item) const;
};

#endif // TREESCENE_H
