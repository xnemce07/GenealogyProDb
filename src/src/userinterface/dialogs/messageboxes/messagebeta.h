/*!
 *  \file   messagebeta.h
 *  \author Eva Navratilova
 */

#ifndef MESSAGEBETA_H
#define MESSAGEBETA_H

#include <QCheckBox>
#include <QSettings>

#include "messagebox.h"

class MessageBeta : public MessageBox
{
    Q_OBJECT
private:
    QCheckBox _dontShow;

public:
    MessageBeta(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    void accept() override;

private:
    void initCheckBox();
};

#endif // MESSAGEBETA_H
