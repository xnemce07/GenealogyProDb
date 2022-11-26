/*!
 *  \file   actionsettingsconstraints.cpp
 *  \author Eva Navratilova
 */

#include "actionsettingsconstraints.h"

ActionSettingsConstraints::ActionSettingsConstraints(QWidget *parent)
    : Action(parent)
{
    //this->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
}

void ActionSettingsConstraints::translate()
{
    this->setText(tr("Constraints..."));
}

void ActionSettingsConstraints::process()
{
    _dialog = new DialogSettingsConstraints();
    _dialog->exec();
}
