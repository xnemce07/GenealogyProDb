/*!
 *  \file   messageexportfailed.h
 *  \author Eva Navratilova
 */

#ifndef MESSAGEEXPORTFAILED_H
#define MESSAGEEXPORTFAILED_H

#include "messagebox.h"

class MessageExportFailed : public MessageBox
{
    Q_OBJECT
public:
    MessageExportFailed(const QString &filename, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
};

#endif // MESSAGEEXPORTFAILED_H
