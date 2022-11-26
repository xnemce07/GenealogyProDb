/*!
 *  \file   actionfilenew.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONFILENEW_H
#define ACTIONFILENEW_H

#include "actionfile.h"
#include "userinterface/dialogs/import/dialogprogress.h"

class ActionFileNew : public ActionFile
{
    Q_OBJECT
public:
    ActionFileNew(Kernel &k);
    ~ActionFileNew() override;

    void translate() override;

private slots:
    void process() override;
};

#endif // ACTIONFILENEW_H
