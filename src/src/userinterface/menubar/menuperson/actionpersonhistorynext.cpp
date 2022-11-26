/*!
 *  \file   actionpersonhistorynext.cpp
 *  \author Eva Navratilova
 */

#include "actionpersonhistorynext.h"

ActionPersonHistoryNext::ActionPersonHistoryNext(Kernel &k, IdentifierHistory &h, QWidget *parent)
    : ActionPersonHistory (k, h, parent)
{
    this->setIcon(QIcon(":icons/arrow-right"));
    this->setShortcut(QKeySequence(Qt::Key_F4));
    this->disable();
}

void ActionPersonHistoryNext::translate()
{
    this->setText(tr("Next"));
}

void ActionPersonHistoryNext::process()
{
    _history.next();
}

void ActionPersonHistoryNext::update()
{
    this->setEnabled(_history.isNextAvailable());
}
