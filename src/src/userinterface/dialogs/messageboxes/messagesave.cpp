/*!
 *  \file   messagesave.cpp
 *  \author Eva Navratilova
 */

#include "messagesave.h"

MessageSave::MessageSave(QWidget *parent, Qt::WindowFlags f)
    : QMessageBox (Icon::Question,
                  tr("Do you want to save?"),
                  tr("Do you want to save the file before exiting?"),
                  StandardButton::Yes | StandardButton::No | StandardButton::Cancel,
                  parent,
                  f)
{
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
    this->setDefaultButton(QMessageBox::Cancel);
}
