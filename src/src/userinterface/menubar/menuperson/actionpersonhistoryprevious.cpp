/*!
 *  \file   actionpersonhistoryprevious.cpp
 *  \author Eva Navratilova
 */

#include "actionpersonhistoryprevious.h"

ActionPersonHistoryPrevious::ActionPersonHistoryPrevious(Kernel &k, IdentifierHistory &h, QWidget *parent)
    : ActionPersonHistory (k, h, parent)
{
    this->setIcon(QIcon(":icons/arrow-left"));
    this->setShortcut(QKeySequence(Qt::Key_F3));
    this->disable();
}

void ActionPersonHistoryPrevious::translate()
{
    this->setText(tr("Previous"));
}

void ActionPersonHistoryPrevious::process()
{
    _history.previous();
}

void ActionPersonHistoryPrevious::update()
{
    this->setEnabled(_history.isPreviousAvailable());
}
