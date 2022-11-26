/*!
 *  \file   actionsettingsenvironment.cpp
 *  \author Eva Navratilova
 */

#include "actionsettingsenvironment.h"

ActionSettingsEnvironment::ActionSettingsEnvironment(Identifier &p, QWidget *parent)
    : Action(parent), _proband(p)
{
    //this->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_S));
}

void ActionSettingsEnvironment::translate()
{
    this->setText(tr("Environment..."));
}

void ActionSettingsEnvironment::process()
{
    // Initialize
    _dialog = new DialogSettingsEnvironment(_proband);

    connect(_dialog, &DialogSettingsEnvironment::languageChanged, this, &ActionSettingsEnvironment::languageChanged);

    // Exec
    _dialog->exec();
}
