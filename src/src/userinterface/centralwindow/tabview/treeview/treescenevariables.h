/*!
 *  \file   treescenevariables.h
 *  \author Eva Navratilova
 */

#ifndef TREESCENEVARIABLES_H
#define TREESCENEVARIABLES_H

#include <QGraphicsScene>

#include "treescene.h"

class TreeSceneVariables : public TreeScene
{
    Q_OBJECT
protected:
    Kernel &_kernel;
    Identifier _proband;

    QGraphicsScene _scene;

    Generation _maxGeneration = 50;
    QHash<Generation, qreal> _freeX;
    TreeType _type = TreeType::EMPTY;

    // Data
    QHash<Identifier /* indi */, TreeItemPerson*> _nodes;
    QHash<Identifier /* fam  */, TreeItemEdge*>   _edges;


public:
    TreeSceneVariables(Kernel &k, Identifier p, QObject *parent = nullptr);
    virtual ~TreeSceneVariables() override;

    QGraphicsScene* scene() override;

    virtual TreeType getTreeType() const override;
    void setMaximumGeneration(Generation gen1) override;

    TreeItemPerson* draw() override;
    virtual TreeItemPerson* drawNodeTree() override;
    virtual void drawEdgeTree() override;

    virtual TreeItemPerson* initNodeTree(Identifier person, Generation gen) override = 0;
    virtual void drawNodeTree(TreeItemPerson* person, Generation gen) override = 0;

    void shiftNode(TreeItemPerson* indi, Generation gen, qreal shift) override;
    virtual int nodesCount(Identifier proband) const override;
    virtual TreeItemPerson* getNode(Identifier indi) override;

    // Coordinates & space
    void initFreeX(Generation gen);
    qreal freeX(Generation gen) const override;

private:
    void updateTreePersonActiveColor(Identifier indi);

public slots:
    virtual void changeProband(const Identifier indi) override;
};

#endif // TREESCENEVARIABLES_H
