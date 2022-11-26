/*!
 *  \file   messagesave.h
 *  \author Eva Navratilova
 */

#ifndef MESSAGESAVE_H
#define MESSAGESAVE_H

#include <QAbstractButton>
#include <QMessageBox>

//#include "userinterface/menubar.h"

class MessageSave : public QMessageBox
{
    Q_OBJECT
public:
    MessageSave(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

};

#endif // MESSAGESAVE_H
