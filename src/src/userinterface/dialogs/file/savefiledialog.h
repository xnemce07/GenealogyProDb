/*!
 *  \file   savefiledialog.h
 *  \author Eva Navratilova
 */

#ifndef SAVEFILEDIALOG_H
#define SAVEFILEDIALOG_H

#include <QFileDialog>
#include <QSettings>

class SaveFileDialog : protected QFileDialog
{
    Q_OBJECT
public:
    SaveFileDialog(QWidget *parent = nullptr);

    QString getSaveFileName(QString filename);

    void deleteLater();
};

#endif // SAVEFILEDIALOG_H
