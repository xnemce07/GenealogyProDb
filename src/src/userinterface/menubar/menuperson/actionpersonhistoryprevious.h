/*!
 *  \file   actionpersonhistoryprevious.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONPERSONPREVIOUS_H
#define ACTIONPERSONPREVIOUS_H

#include "actionpersonhistory.h"
#include "../../identifierhistory.h"

class ActionPersonHistoryPrevious : public ActionPersonHistory
{
    Q_OBJECT
public:
    ActionPersonHistoryPrevious(Kernel &k, IdentifierHistory &h, QWidget *parent = nullptr);

    void translate() override;

private:
    void process() override;
    void update() override;
};

#endif // ACTIONPERSONPREVIOUS_H
