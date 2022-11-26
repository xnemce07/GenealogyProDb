/*!
 *  \file   openfiledialog.h
 *  \author Eva Navratilova
 */

#ifndef OPENFILEDIALOG_H
#define OPENFILEDIALOG_H

#include <QFileInfo>
#include <QFileDialog>
#include <QSettings>

class OpenFileDialog : protected QFileDialog
{
    Q_OBJECT
public:
    OpenFileDialog(QWidget *parent = nullptr);

    QString getOpenFileName();
    void deleteLater();
};

#endif // OPENFILEDIALOG_H
