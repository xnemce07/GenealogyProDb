/*!
 *  \file   actionabout.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONABOUT_H
#define ACTIONABOUT_H

#include "../action.h"
#include "userinterface/dialogs/messageboxes/messagebox.h"

class ActionHelpAbout : public Action
{
    Q_OBJECT
private:
    MessageBox* _message = nullptr;
    static const char* _aboutText;

public:
    ActionHelpAbout(QWidget *parent = nullptr);
    void translate() override;

protected slots:
    void process() override;
};

#endif // ACTIONABOUT_H
