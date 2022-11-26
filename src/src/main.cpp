/*!
 *  \file   main.cpp
 *  \author Eva Navratilova
 */

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QLocale>
#include <QStyleFactory>
#include <QSettings>

#include "kernel.h"
#include "textformatter.h"
#include "userinterface/mainwindow.h"

#include "userinterface/dialogs/messageboxes/messagebeta.h"

void initializeSettingsData()
{
    QCoreApplication::setOrganizationName("Eva Navratilova");
    QCoreApplication::setOrganizationDomain("");
    QCoreApplication::setApplicationName(APP_NAME);
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{    
    initializeSettingsData();

    Q_INIT_RESOURCE(resources);

    QApplication app(argc, argv);

    #ifdef __linux__
        auto keys = QStyleFactory::keys();
        //app.setStyle(QStyleFactory::create(keys.first()));
        QFont font;
        font.setPixelSize(12);
        app.setFont(font);

    #endif


    Kernel kernel;
    MainWindow mainWindow(kernel);

    mainWindow.show();
    return app.exec();
}
