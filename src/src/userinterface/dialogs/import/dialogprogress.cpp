/*!
 *  \file   dialogprogress.cpp
 *  \author Eva Navratilova
 */

#include "dialogprogress.h"

const char* DialogProgress::_progressText = QT_TR_NOOP("Importing structure %1 of %2");

DialogProgress::DialogProgress(Kernel &k, QWidget *parent)
    : Dialog (parent)
{
    this->setWindowTitle(tr("Import in progress..."));
    // Hide all dialog buttons
    this->setWindowFlags(Qt::Dialog | Qt::Desktop);

    this->fill();

    connect(&k, &Kernel::objectsToImport, this, &DialogProgress::objectsToImport);
    connect(&k, &Kernel::objectImported, this, &DialogProgress::objectImported);
    connect(&k, &Kernel::importDone, this, &DialogProgress::importDone);

    QCoreApplication::processEvents();
}

void DialogProgress::fill()
{
    // Initialize
    // No button box available

    // Set static values
    _progressBar.setMinimum(0);
    _label.setText(tr("Initializing import..."));

    // Set layout
    _layout.addWidget(&_label, 0, 0);
    _layout.addWidget(&_progressBar, 1, 0);

    QCoreApplication::processEvents();
}

void DialogProgress::objectsToImport(int count)
{
    _progressBar.setMaximum(count);
    _progressBar.setValue(_progressBar.minimum());
    _label.setText(tr(_progressText).arg(_progressBar.value()).arg(_progressBar.maximum()));

    QCoreApplication::processEvents();
}

void DialogProgress::objectImported()
{
    _progressBar.setValue(_progressBar.value() + 1);
    _label.setText(tr(_progressText).arg(_progressBar.value()).arg(_progressBar.maximum()));

    QCoreApplication::processEvents();
}

void DialogProgress::importDone()
{
    this->accept();
}
