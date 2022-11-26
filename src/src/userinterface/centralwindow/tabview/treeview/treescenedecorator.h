/*!
 *  \file   treescenedecorator.h
 *  \author Eva Navratilova
 */

#ifndef TREESCENEDECORATOR_H
#define TREESCENEDECORATOR_H

#include "treescene.h"
#include "treescenevariables.h"

class TreeSceneDecorator : public TreeScene
{
    Q_OBJECT
private:
    TreeScene* _wrappee;

public:
    TreeSceneDecorator(TreeScene *item, QObject *parent = nullptr);
    virtual ~TreeSceneDecorator() override;

    QGraphicsScene* scene() override;

    virtual TreeScene* item() override;

    virtual TreeType getTreeType() const override;
    virtual void setMaximumGeneration(Generation gen1) override;

    virtual TreeItemPerson* draw() override;
    virtual TreeItemPerson* drawNodeTree() override;
    virtual void drawEdgeTree() override;

    virtual TreeItemPerson* initNodeTree(Identifier person, Generation gen) override;
    virtual void drawNodeTree(TreeItemPerson* person, Generation gen) override;

    virtual void shiftNode(TreeItemPerson* indi, Generation gen, qreal shift) override;
    virtual int nodesCount(Identifier proband) const override;
    virtual TreeItemPerson* getNode(Identifier indi) override;

protected:
    // Coordinates & space
    virtual qreal freeX(Generation gen) const override;

public slots:
    virtual TreeItemPerson* nodeGenerator(TreeItemPerson* item) const override = 0;
    virtual TreeItemEdge* edgeGenerator(TreeItemEdge* item) const override = 0;

    virtual void changeProband(const Identifier indi) override;

};

#endif // TREESCENEDECORATOR_H
