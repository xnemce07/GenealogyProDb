/*!
 *  \file   actiontree.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONTREEOUTLETANCESTRAL_H
#define ACTIONTREEOUTLETANCESTRAL_H

#include "../../../kernel.h"
#include "../action.h"
#include "../../centralwindow/tabview/treeview.h"

class ActionTree : public Action
{
    Q_OBJECT
private:
    TreeType _type;

public:
    ActionTree(TreeType type, QWidget *parent = nullptr);

    void translate() override;

signals:
    void drawTree(TreeType t);

protected slots:
    virtual void process() override;
};

#endif // ACTIONTREEOUTLETANCESTRAL_H
