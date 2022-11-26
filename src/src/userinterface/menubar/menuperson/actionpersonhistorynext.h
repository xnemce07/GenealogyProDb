/*!
 *  \file   actionpersonhistorynext.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONPERSONHISTORYNEXT_H
#define ACTIONPERSONHISTORYNEXT_H

#include "actionpersonhistory.h"

class ActionPersonHistoryNext : public ActionPersonHistory
{
    Q_OBJECT
public:
    ActionPersonHistoryNext(Kernel &k, IdentifierHistory &h, QWidget *parent = nullptr);

    void translate() override;

private:
    void process() override;
    void update() override;
};

#endif // ACTIONPERSONHISTORYNEXT_H
