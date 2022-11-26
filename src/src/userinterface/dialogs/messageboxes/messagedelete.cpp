/*!
 *  \file   messagedelete.cpp
 *  \author Eva Navratilova
 */

#include "messagedelete.h"

MessageDelete::MessageDelete(QString what, QWidget *parent, Qt::WindowFlags f)
    : MessageBox(QMessageBox::Question,
                  tr("Delete %1").arg(what),
                  tr("Are you sure you want to delete %1?").arg(what),
                  QMessageBox::Ok | QMessageBox::Cancel,
                  QMessageBox::Ok,
                  parent,
                  f)
{
    this->setDefaultButton(QMessageBox::Cancel);

    connect(this->button(QMessageBox::Ok), &QAbstractButton::released, this, &MessageDelete::accept);
    connect(this->button(QMessageBox::Cancel), &QAbstractButton::released, this, &MessageDelete::reject);
}
