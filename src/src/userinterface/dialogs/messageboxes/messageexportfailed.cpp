/*!
 *  \file   messageexportfailed.cpp
 *  \author Eva Navratilova
 */

#include "messageexportfailed.h"

MessageExportFailed::MessageExportFailed(const QString &filename, QWidget *parent, Qt::WindowFlags f)
    : MessageBox(QMessageBox::Critical,
                  tr("Export failed"),
                  tr("Export of the file to the location %1 failed.").arg(filename),
                  QMessageBox::Ok,
                  QMessageBox::Ok,
                  parent,
                  f)
{

}
