/*!
 *  \file   mainwindow.cpp
 *  \author Eva Navratilova
 */

#include "mainwindow.h"
//#include "ui_mainwindow.h"


MainWindow::MainWindow(Kernel &k, QWidget *parent) :
    QMainWindow(parent), _kernel(k)
{
    /// TODO - remove!!!!
    //this->defaultSettings();

    // Initialize window according to the settings
    this->initializeSettings();

    //////////////////////////////////////////////////////////

    /// TODO - allow user to restore default settings

    this->setWindowTitle(_appName);
    this->setWindowIcon(QIcon(QString(APP_NAME) + ".ico"));


    ////////////////////////////////////////////////////////////

    this->fill();


    connect(qApp, &QApplication::screenRemoved, this, &MainWindow::ensureVisible);

#ifdef QT_DEBUG
    qApp->beep();
#endif

}

MainWindow::~MainWindow()
{

}

Identifier MainWindow::getProband() const
{
    return _proband;
}

void MainWindow::show()
{

    if(this->getMessageBetaResult())
    {
        QMainWindow::show();

        this->applySettings();
    }
    else
    {
        exit(EXIT_SUCCESS);
    }
}

void MainWindow::translate()
{
    auto currentTab = _tabView->currentTab();
    if(_menu != nullptr)
    {
        _menu->translate();
    }
    if(_tabView != nullptr)
    {
        _tabView->deleteLater();
        this->initTabView();
    }
    this->changeProband(_proband);
    this->changeSource(_source);
    _tabView->setCurrentTab(currentTab);
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event != nullptr)
    {
        if(event->type() == QEvent::LanguageChange)
        {
            //this->retranslateUi(this);
        }

        // this event is sent, if the system language changes
        else if(event->type() == QEvent::LocaleChange)
        {
            QLocale locale = QLocale::system();
            loadLanguage(locale);
        }
    }
    QMainWindow::changeEvent(event);
}

bool MainWindow::getMessageBetaResult()
{
    QSettings settings;

    if(settings.value("message/beta/dontShow").toBool())
    {
        return true;
    }

    MessageBeta messageBeta;
    return messageBeta.exec();
}

void MainWindow::changeProband(Identifier ref)
{
    // Updates through references also in widgets
    if(_kernel.record()->isIndividual(ref))
    {
        _proband = ref;
    }

    // This is probably not necessary
    /*else
    {
        _proband = _kernel.record()->getIdentifierIndividualFirst();
    }*/

    this->update();

    // Switch to person tab
    _tabView->setCurrentTab(TabViewTabs::TAB_INDI);

    // Add newly selected Identifier to History
    _history->update(ref);
}

void MainWindow::changeSource(Identifier ref)
{
    _source = ref;

    this->update();

    // Switch to source tab
    _tabView->setCurrentTab(TabViewTabs::TAB_SRC);
}

void MainWindow::readyUI(QString filename)
{
    this->setUI(filename, true);

    // Switch to Indi tab
    _tabView->setCurrentTab(TabViewTabs::TAB_INDI);
}

void MainWindow::unreadyUI()
{
    this->setUI(QString(), false);
}

void MainWindow::setUI(QString filename, bool isVisible)
{
    _uiVisible = isVisible;
    _filename = filename;

    this->centralWidget()->setVisible(_uiVisible);

    QString title = _appName;
    if(! _filename.isEmpty())
    {
        title += " - " + _filename;
    }

    this->setWindowTitle(title);

    // Reset history
    _history->reset();

    /// Clear old data from the UI
    // Clear Individual Identifier
    this->changeProband(_kernel.record()->getIdentifierIndividualFirst());
    // Clear Source Identifier
    this->changeSource(Identifier());
    // Clear tree
    _tabView->clearTree();
}

void MainWindow::adjustLanguage()
{
    QSettings settings;
    QLocale locale = settings.value("locale").toLocale();
    this->loadLanguage(locale);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(_uiVisible)
    {
        /// TODO - Prompt to save data
        auto result = _menu->saveBeforeFlush();
        if(result == MessageBox::Accepted)
        {
            this->saveSettings();
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }

    //QMainWindow::closeEvent(event);
}

void MainWindow::applySettings()
{
    QSettings settings;

    // Setting window position
    this->resize(settings.value("window/size").toSize());
    this->move(settings.value("window/pos").toPoint());
    this->setWindowState(static_cast<Qt::WindowState>((settings.value("window/maximized")).toInt()));

    // Adjusting window position
    this->ensureVisible();

    // Opening last file if set so
    if(settings.value("accessibility/autoOpenLastFile").toBool())
    {
        _menu->openLast();
    }
}

void MainWindow::initializeSettings() const
{
    QSettings settings;
    if(settings.value("initialized").isNull())
    {
        this->defaultSettings();

        // Init done
        settings.setValue("initialized", true);
    }

    this->updateSettings();
}

void MainWindow::defaultSettings() const
{
    QSettings settings;

    // App version
    settings.setValue("version", APP_VERS_CURR);

    // Window position
    settings.setValue("window/maximized", Qt::WindowState::WindowMaximized);
    settings.setValue("window/size", this->size());
    settings.setValue("window/pos", QPoint(0,0));

    // Widget position and size
    TabView::defaultSettings();

    // Application language
    QLocale* locale = new QLocale();

    // Is Locale within valid implemented locales
    bool isLocaleValid = false;
    QStringList supportedLanguageList = QDir(":/translations").entryList();
    for(QString language : supportedLanguageList)
    {
        isLocaleValid = language == locale->name().section('_', 0, 0);
        if(isLocaleValid)
            break;
    }

    // If not within locales -> set English
    if(! isLocaleValid)
    {
        delete locale;
        locale = new QLocale(QLocale::English);
    }
    settings.setValue("locale", *locale);

    // Paths
    settings.setValue("path/defaultDir", QDir::homePath());
    settings.setValue("path/recentFiles", QStringList());
    settings.setValue("path/defaultImageDir", QDir::homePath() + "/*.png");

    // Message boxes
    settings.setValue("message/beta/dontShow", false);

    TextFormatter::defaultSettings();

    // Accessibility
    settings.setValue("accessibility/autoOpenLastFile", true);

    // Settings for data constraints
    settings.setValue("dataConstraints/autoDead", false);
    settings.setValue("dataConstraints/autoMarried", false);
    settings.setValue("dataConstraints/maximumAge", 100);
    settings.setValue("dataConstraints/minimumYear", 1500);
    settings.setValue("dataConstraints/minimumAgeAtChildbirth", 15);

    // Settings for the direction of tree drawing
    settings.setValue("treeDirection/outlet", static_cast<int>(TreeDirection::NORTH));
    settings.setValue("treeDirection/family", static_cast<int>(TreeDirection::SOUTH));
    settings.setValue("treeDirection/relatives", static_cast<int>(TreeDirection::SOUTH));
}

void MainWindow::saveSettings() const
{
    QSettings settings;

    // App version
    settings.setValue("version", APP_VERS_CURR);

    // Window position
    settings.setValue("window/maximized", static_cast<int>(this->windowState()));
    settings.setValue("window/size", this->size());
    settings.setValue("window/pos", this->pos());

    _tabView->saveSettings();

    // QLocale saved in Environment dialog
    //settings.setValue("locale", QLocale());
}

void MainWindow::updateSettings() const
{
    QSettings settings;
    if(settings.value("version").toString().isEmpty())  // == APP_VERS_1_0_0
    {
        // Update settings after new version release
        // Repair bug in window layout

        _tabView->defaultSettings();
    }
}

void MainWindow::fill()
{
    _history = new IdentifierHistory(MEMORY_SIZE);
    _menu = new MenuBar(_kernel, _proband, _source, *_history, this);
    this->setMenuBar(_menu);

    this->initTabView();

    // Adjust application language according to the settings
    this->adjustLanguage();

    // Connect proband changed
    connect(_history, &IdentifierHistory::probandChanged, this, &MainWindow::changeProband);
    connect(_menu, &MenuBar::probandChanged, this, &MainWindow::changeProband);
    connect(_menu, &MenuBar::languageChanged, this, &MainWindow::adjustLanguage);

    // Connect change source
    connect(_menu, &MenuBar::sourceChanged, this, &MainWindow::changeSource);


    // Connect file loaded
    connect(_menu, &MenuBar::fileLoaded, this, &MainWindow::readyUI);

    // Connect file closed
    connect(_menu, &MenuBar::fileClosed, this, &MainWindow::unreadyUI);
}

void MainWindow::initTabView()
{
    _tabView = new TabView(_kernel, _proband, _source);
    this->setCentralWidget(_tabView);

    // No file loaded yet - disable UI
    this->centralWidget()->setVisible(_uiVisible);

    // Connect proband changed
    connect(_tabView, &TabView::probandChanged, this, &MainWindow::changeProband);
    // Connect source changed
    connect(_tabView, &TabView::sourceChanged, this, &MainWindow::changeSource);

    // Connect draw tree
    connect(_menu, &MenuBar::drawTree, _tabView, &TabView::drawTree);
    connect(_menu, &MenuBar::drawTreeScene, _tabView, &TabView::drawTreeScene);

    // Connect export tree image
    connect(_menu, &MenuBar::exportImage, _tabView, &TabView::exportImage);
}

void MainWindow::loadLanguage(QLocale &locale)
{
    QLocale::setDefault(locale);
    qApp->removeTranslator(&_translatorQt);
    qApp->removeTranslator(&_translatorApp);

    // If locale is not supported, set system locale;
    bool isLocaleValid = false;
    QStringList supportedLanguageList = QDir(":/translations").entryList();
    supportedLanguageList.append(QLocale(QLocale::English).name().section('_', 0, 0));
    for(QString language : supportedLanguageList)
    {
        isLocaleValid = (language == locale.name().section('_', 0, 0));
        if(isLocaleValid)
            break;
    }

    if(! isLocaleValid)
    {
        locale = QLocale(QLocale::English);
    }


    if(_translatorQt.load(":/translations/qtbase_" + locale.name().section('_', 0, 0)))
    {
        qApp->installTranslator(&_translatorQt);
    }

    if(_translatorApp.load(":/translations/" + locale.name().section('_', 0, 0)))
    {
        qApp->installTranslator(&_translatorApp);
    }
    this->translate();
}

void MainWindow::update()
{
    _tabView->update();
    _menu->update();
}

void MainWindow::ensureVisible(QScreen *screen)
{
    Q_UNUSED(screen);

    bool drawn = false;
    QSize size = this->size();
    QPoint pos = this->pos();

    auto screens = QApplication::screens();
    for(auto iteratorScreen = screens.begin(); iteratorScreen != screens.end(); iteratorScreen++)
    {
        QScreen* screen = *iteratorScreen;
        QRect screenRect = screen->geometry();
        if((screenRect.left() <= pos.x() && pos.x() + size.width() < screenRect.right()) &&
           (screenRect.top() <= pos.y() && pos.y() + size.height() < screenRect.bottom()))
        {
            drawn=true;
            break;
        }
    }
    if(!drawn)
    {
        if(screens.length() > 0)
        {
            QScreen* screen = screens.first();
            this->move(screen->geometry().topLeft());
            if(size.width() > screen->size().width())
            {
                this->resize(screen->size().width(), size.height());
            }
            if(size.height() > screen->size().height())
            {
                this->resize(size.width(), screen->size().height());
            }
        }
    }
}

