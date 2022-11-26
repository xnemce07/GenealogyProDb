/*!
 *  \file   openfiledialog.cpp
 *  \author Eva Navratilova
 */

#include "savefiledialog.h"

SaveFileDialog::SaveFileDialog(QWidget *parent)
    : QFileDialog(parent)
{
    this->setAcceptMode(QFileDialog::AcceptSave);
    this->setFileMode(QFileDialog::AnyFile);
    this->setOption(QFileDialog::ReadOnly, false);
    this->setViewMode(QFileDialog::Detail);
}

QString SaveFileDialog::getSaveFileName(QString filename)
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
    return QFileDialog::getSaveFileName(this, tr("Save File"), dir + "/" + filename, filter);
}

void SaveFileDialog::deleteLater()
{
    this->QFileDialog::deleteLater();
}
