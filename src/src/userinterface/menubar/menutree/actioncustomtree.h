/*!
 *  \file   actioncustomtree.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONCUSTOMTREE_H
#define ACTIONCUSTOMTREE_H

#include "../action.h"
#include "../../dialogs/tree/dialogtreecustom.h"

class ActionCustomTree : public Action
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier &_proband;

    DialogTreeCustom* _dialog;

public:
    ActionCustomTree(Kernel &k, Identifier &p);

    void translate() override;

signals:
    void drawTreeScene(TreeScene *scene);

protected slots:
    virtual void process();
};

#endif // ACTIONCUSTOMTREE_H
