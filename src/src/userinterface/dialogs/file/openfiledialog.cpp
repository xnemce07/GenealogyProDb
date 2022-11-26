/*!
 *  \file   openfiledialog.cpp
 *  \author Eva Navratilova
 */

#include "openfiledialog.h"

OpenFileDialog::OpenFileDialog(QWidget *parent)
    : QFileDialog(parent)
{
    this->setAcceptMode(QFileDialog::AcceptOpen);
    this->setFileMode(QFileDialog::ExistingFile);
    this->setOption(QFileDialog::ReadOnly, true);
    this->setOption(QFileDialog::HideNameFilterDetails, false);
    this->setViewMode(QFileDialog::Detail);
}

QString OpenFileDialog::getOpenFileName()
{
    QSettings settings;
    QString dir = settings.value("path/defaultDir").toString();
    QFileInfo dirInfo(dir);
    if((!dirInfo.exists()) || (!dirInfo.isDir()) || (!dirInfo.isWritable()))
    {
        dir = QDir::homePath();
        settings.setValue("path/defaultDir", dir);
    }
    QString filter = tr("Gedcom") + " (*.ged)";
    this->setDefaultSuffix("ged");
    return QFileDialog::getOpenFileName(this, tr("Open File"), dir, filter);
}

void OpenFileDialog::deleteLater()
{
    this->QFileDialog::deleteLater();
}
