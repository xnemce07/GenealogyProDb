/*!
 *  \file   messageimportfailed.cpp
 *  \author Eva Navratilova
 */

#include "messageimportfailed.h"

MessageImportFailed::MessageImportFailed(const QString &filename, QWidget *parent, Qt::WindowFlags f)
    : MessageBox(QMessageBox::Critical,
                  tr("Import failed"),
                  tr("Import of the file located in %1 failed. Please check the file and try again later.").arg(filename),
                  QMessageBox::Ok,
                  QMessageBox::Ok,
                  parent,
                  f)
{

}
