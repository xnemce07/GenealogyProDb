/*!
 *  \file   dialogprogress.h
 *  \author Eva Navratilova
 */

#ifndef DIALOGPROGRESS_H
#define DIALOGPROGRESS_H

#include <QProgressBar>
#include <QCoreApplication>

#include "kernel.h"
#include "../dialog.h"
#include "userinterface/objects/label.h"

class DialogProgress : public Dialog
{
    Q_OBJECT
private:
    Label _label;
    QProgressBar _progressBar;
    static const char* _progressText;

public:
    DialogProgress(Kernel &k, QWidget *parent = nullptr);

private:
    void fill();

public slots:
    void objectsToImport(int count);
    void objectImported();
    void importDone();


};

#endif // DIALOGPROGRESS_H
