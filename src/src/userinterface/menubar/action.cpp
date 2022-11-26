/*!
 *  \file   action.cpp
 *  \author Eva Navratilova
 */

#include "action.h"

Action::Action(QWidget *parent)
    : QAction(parent)
{
    this->setShortcutContext(Qt::ShortcutContext::ApplicationShortcut);
    this->setShortcutVisibleInContextMenu(true);

    connect(this, &Action::triggered, this, &Action::triggerAction);
}

void Action::enable()
{
    this->setEnabled(true);
}

void Action::disable()
{
    this->setEnabled(false);
}

void Action::triggerAction(bool checked)
{
    Q_UNUSED(checked);

    this->process();
}
