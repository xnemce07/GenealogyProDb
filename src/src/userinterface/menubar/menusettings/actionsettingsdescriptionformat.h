/*!
 *  \file   actionsettingsdescriptionformat.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONSETTINGSDESCRIPTIONFORMAT_H
#define ACTIONSETTINGSDESCRIPTIONFORMAT_H

#include "../action.h"
#include "kernel.h"
#include "textformatter.h"
#include "userinterface/dialogs/settings/dialogsettingsdescriptionformat.h"

class ActionSettingsDescriptionFormat : public Action
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier &_ref;
    FormatableText _formattable;
    QString (*_getPreview)(Kernel&, Identifier);

    DialogSettingsDescriptionFormat *_dialog;

public:
    ActionSettingsDescriptionFormat(Kernel &k, Identifier &r, FormatableText f, QWidget *parent = nullptr);

    void translate() override;
    void process() override;

signals:
    void sourceChanged(Identifier src);
};

#endif // ACTIONSETTINGSDESCRIPTIONFORMAT_H
