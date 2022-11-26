/*!
 *  \file   actionsettingsenvironment.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONSETTINGSENVIRONMENT_H
#define ACTIONSETTINGSENVIRONMENT_H

#include "../action.h"
#include "../../../kernel.h"
#include "../../dialogs/settings/dialogsettingsevnironment.h"

class ActionSettingsEnvironment : public Action
{
    Q_OBJECT
private:
    Identifier &_proband;

    DialogSettingsEnvironment *_dialog;

public:
    ActionSettingsEnvironment(Identifier &p, QWidget *parent = nullptr);

    void translate() override;
    void process() override;

signals:
    void languageChanged();
};

#endif // ACTIONSETTINGSENVIRONMENT_H
