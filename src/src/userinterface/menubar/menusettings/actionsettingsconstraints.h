/*!
 *  \file   actionsettingsconstraints.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONSETTINGSCONSTRAINTS_H
#define ACTIONSETTINGSCONSTRAINTS_H

#include "../action.h"
#include "../../dialogs/settings/dialogsettingsconstraints.h"

class ActionSettingsConstraints : public Action
{
    Q_OBJECT
private:
    DialogSettingsConstraints *_dialog;

public:
    ActionSettingsConstraints(QWidget *parent = nullptr);

    void translate() override;

    void process() override;
};

#endif // ACTIONSETTINGSCONSTRAINTS_H
