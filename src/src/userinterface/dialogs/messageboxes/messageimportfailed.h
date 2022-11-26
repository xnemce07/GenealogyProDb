/*!
 *  \file   messageimportfailed.h
 *  \author Eva Navratilova
 */

#ifndef MESSAGEIMPORTFAILED_H
#define MESSAGEIMPORTFAILED_H

#include "messagebox.h"

class MessageImportFailed : public MessageBox
{
    Q_OBJECT
public:
    MessageImportFailed(const QString &filename, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
};

#endif // MESSAGEIMPORTFAILED_H
