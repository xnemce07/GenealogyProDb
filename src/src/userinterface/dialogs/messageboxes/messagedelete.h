/*!
 *  \file   messagedelete.h
 *  \author Eva Navratilova
 */

#ifndef MESSAGEDELETE_H
#define MESSAGEDELETE_H

#include <QAbstractButton>

#include "messagebox.h"

class MessageDelete : public MessageBox
{
    Q_OBJECT
public:
    MessageDelete(QString what = tr("this item"), QWidget *parent = nullptr, Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
};

#endif // MESSAGEDELETE_H
