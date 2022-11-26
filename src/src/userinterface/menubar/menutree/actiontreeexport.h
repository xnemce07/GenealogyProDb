/*!
 *  \file   actiontreeexport.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONTREEEXPORT_H
#define ACTIONTREEEXPORT_H

#include <QFileDialog>
#include <QSettings>

#include "../action.h"

class ActionTreeExport : public Action
{
    Q_OBJECT
private:
    QString _filename;

public:
    ActionTreeExport(QWidget *parent = nullptr);

    void translate() override;

private:
    void exportFile();

signals:
    void exportImage(const QString& filename);


protected slots:
    void process() override;
};

#endif // ACTIONTREEEXPORT_H
