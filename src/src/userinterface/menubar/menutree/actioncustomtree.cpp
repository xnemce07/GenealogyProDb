/*!
 *  \file   actioncustomtree.cpp
 *  \author Eva Navratilova
 */

#include "actioncustomtree.h"

ActionCustomTree::ActionCustomTree(Kernel &k, Identifier &p)
    : Action (), _kernel(k), _proband(p)
{
    this->setShortcut(QKeySequence(Qt::SHIFT | Qt::Key_F7));
    this->disable();
}

void ActionCustomTree::translate()
{
    this->setText(tr("Custom Tree..."));
}

void ActionCustomTree::process()
{
    _dialog = new DialogTreeCustom(_kernel, _proband);
    auto scene = _dialog->getTreeScene();

    emit(this->drawTreeScene(scene));
}
