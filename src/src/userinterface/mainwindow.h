/*!
 *  \file   mainwindow.h
 *  \author Eva Navratilova
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define MEMORY_SIZE 50

#include <QMainWindow>
#include <QTranslator>
#include <QListView>
#include <QTabWidget>
#include <QCloseEvent>
#include <QList>
#include <QLibraryInfo>
#include <QApplication>
#include <QScreen>

#include "identifierhistory.h"
#include "menubar.h"
#include "../textformatter.h"
#include "centralwindow/tabview.h"
#include "dialogs/messageboxes/messagebeta.h"
#include "objects/translatableobject.h"


namespace Ui {
class MainWindow;
}

/**
 * @brief
 *
 */
class MainWindow : public QMainWindow, public TranslatableObject
{
    Q_OBJECT
private:
    Kernel& _kernel;
    QTranslator _translatorQt;
    QTranslator _translatorApp;
    Identifier _proband;
    Identifier _source;

    IdentifierHistory* _history = nullptr; /**< History of probands */

    const QString _appName = APP_NAME + QString(" ") + APP_VERS_CURR;
    QString _filename;
    bool _uiVisible = false;

    MenuBar *_menu = nullptr;
    TabView *_tabView = nullptr;    // TabView is central widget

public:
    /**
     * @brief
     *
     * @param parent
     */
    explicit MainWindow(Kernel &k, QWidget *parent = nullptr);
    /**
     * @brief
     *
     */
    ~MainWindow() override;

    Identifier getProband() const;
    void show();
    void translate() override;

protected:
    void changeEvent(QEvent *event) override;

private:
    bool getMessageBetaResult();

    void applySettings();
    void initializeSettings() const;
    void defaultSettings() const;
    void saveSettings() const;
    void updateSettings() const;

    void fill();
    void initTabView();

    void loadLanguage(QLocale &locale);

public slots:
    void update();

private slots:
    void changeProband(Identifier ref);
    void changeSource(Identifier ref);

    void readyUI(QString filename);
    void unreadyUI();
    void setUI(QString filename, bool isVisible);
    void closeEvent(QCloseEvent *event) override;
    void adjustLanguage();
    void ensureVisible(QScreen *screen = nullptr);
};

#endif // MAINWINDOW_H
