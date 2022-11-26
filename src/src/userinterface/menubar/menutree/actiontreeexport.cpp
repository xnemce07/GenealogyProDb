/*!
 *  \file   actiontreeexport.cpp
 *  \author Eva Navratilova
 */

#include "actiontreeexport.h"

ActionTreeExport::ActionTreeExport(QWidget *parent)
    : Action(parent)
{
    this->disable();
}

void ActionTreeExport::translate()
{
    this->setText(tr("Export Tree to File..."));
}

void ActionTreeExport::exportFile()
{
    /*QString ext = _filename.split(".").last().toLower();
    /// TODO - check if all are saveable - https://doc.qt.io/qt-5/qimage.html#reading-and-writing-image-files
    QStringList formats = QStringList() << "bmp"
                                        << "gif"    // Is it saveable??
                                        << "jpg"
                                        << "jpeg"
                                        << "png"
                                        << "ppm"
                                        << "xbm"
                                        << "xpm";*/
}

void ActionTreeExport::process()
{
    QSettings settings;
    QString path = settings.value("path/defaultImageDir").toString();
    /// TODO - if invalid path set to home (see mainwindow for exact definition)

    QFileDialog dialog;
    _filename = dialog.getSaveFileName(this->parentWidget(),
                                       this->text(),
                                       path,
                                       tr("PDF file (*.pdf);;"
                                          "BMP image (*.bmp);;"
                                          "JPG image (*.jpg);;"
                                          "JPEG image (*.jpeg);;"
                                          "PNG image (*.png);;"
                                          "PPM image (*.ppm);;"
                                          "XBM image (*.xbm);;"
                                          "XPM image (*.xpm)"));

    /// TODO - correct name - suffix may be missing!!!!

    if(!_filename.isEmpty())
    {
        emit(this->exportImage(_filename));
        settings.setValue("path/defaultImageDir", _filename);
    }
}
