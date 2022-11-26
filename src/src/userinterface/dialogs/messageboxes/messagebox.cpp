/*!
 *  \file   messagebox.cpp
 *  \author Eva Navratilova
 */

#include "messagebox.h"

MessageBox::MessageBox(Icon icon, const QString &title, const QString &text, StandardButtons buttons, StandardButtons acceptButtons, QWidget *parent, Qt::WindowFlags f)
    : QMessageBox (icon, title, text, buttons, parent, f), _acceptButtons(acceptButtons)
{
    this->setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}

int MessageBox::exec()
{
    auto pressedButton = QMessageBox::exec();
    if(_acceptButtons & pressedButton)
    {
        return MessageBox::Accepted;
    }
    else
    {
        return MessageBox::Rejected;
    }
}
