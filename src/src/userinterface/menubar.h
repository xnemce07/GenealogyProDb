/*!
 *  \file   menubar.h
 *  \author Eva Navratilova
 */

#ifndef MENUBAR_H
#define MENUBAR_H

#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QSettings>
#include <QFileDialog>

#include "../kernel.h"
#include "menubar/menufile/actionfilenew.h"
#include "menubar/menufile/actionfilelast.h"
#include "menubar/menufile/actionfileopen.h"
#include "menubar/menufile/actionfilesave.h"
#include "menubar/menufile/actionfilesaveas.h"
#include "menubar/menufile/actioninformation.h"
#include "menubar/menuperson/actionpersonhistoryprevious.h"
#include "menubar/menuperson/actionpersonhistorynext.h"
#include "menubar/menuperson/actionpersonaddman.h"
#include "menubar/menuperson/actionpersonaddwoman.h"
#include "menubar/menuperson/actionpersondelete.h"
#include "menubar/menutree/actiontree.h"
#include "menubar/menutree/actioncustomtree.h"
#include "menubar/menutree/actiontreeexport.h"
#include "menubar/menusettings/actionsettingsenvironment.h"
#include "menubar/menusettings/actionsettingsconstraints.h"
#include "menubar/menusettings/actionsettingsdescriptionformat.h"
#include "menubar/menuhelp/actionabout.h"

#include "userinterface/dialogs/messageboxes/messagesave.h"

class MenuBar : public QMenuBar
{
    Q_OBJECT
private:
    Kernel& _kernel;
    Identifier& _proband;
    Identifier& _source;
    Identifier _family;
    IdentifierHistory &_history;
    bool _fileOpened = false;

    QMenu _menuFile;
    ActionFileNew* _menuFileNew;
    ActionFileOpen* _menuFileOpen;
    QVector<ActionFileLast*> _menuFileLast;
    ActionFileSave* _menuFileSave;
    ActionFileSaveAs* _menuFileSaveAs;
    ActionInformation* _menuFileInformation;

    QMenu _menuPerson;
    ActionPersonHistoryPrevious* _menuPersonPrevious;
    ActionPersonHistoryNext* _menuPersonNext;
    ActionPersonAddMan* _menuPersonAddMan;
    ActionPersonAddWoman* _menuPersonAddWoman;
    ActionPersonDelete* _menuPersonDelete;

    QMenu _menuTrees;
    ActionTree* _menuTreeOutletAncestral;
    ActionTree* _menuTreeOutletAgnat;
    ActionTree* _menuTreeOutletKognat;
    ActionTree* _menuTreeFamilyTree;
    ActionTree* _menuTreeRelativesTree;
    ActionCustomTree* _menuTreeCustom;
    ActionTreeExport* _menuTreeExport;

    QMenu _menuSynopses;

    QMenu _menuSettings;
    ActionSettingsEnvironment* _menuSettingsEnvironment;
    ActionSettingsConstraints* _menuSettingsConstraints;
    QMenu _submenuSettingsDescriptionFormat;
    ActionSettingsDescriptionFormat * _menuSettingsFormatTreeCellPerson;
    ActionSettingsDescriptionFormat * _menuSettingsFormatTreeCellMarriage;
    ActionSettingsDescriptionFormat * _menuSettingsFormatPerson;
    ActionSettingsDescriptionFormat * _menuSettingsFormatSource;
    ActionSettingsDescriptionFormat * _menuSettingsFormatSourceCitation;

    QMenu _menuHelp;

    ActionHelpAbout *_menuHelpAbout;

public:
    MenuBar(Kernel &k, Identifier &p, Identifier &s, IdentifierHistory &h, QWidget *parent = nullptr);
    ~MenuBar() override;

    void translate();
    void openLast();
    void setUsed(const QString &filename);
    int saveOrSaveAs();

signals:
    void probandChanged(Identifier ref);
    void sourceChanged(Identifier ref);
    void fileLoaded(QString filename);
    void fileClosed();
    void languageChanged();
    void drawTree(TreeType t);
    void drawTreeScene(TreeScene* scene);
    void exportImage(const QString& filename);

public slots:
    void update();
    int saveBeforeFlush();

private slots:
    void repopulateLastOpen();
    void deleteIndividual(Identifier ref);
    void fileWasOpened(QString filename);
    void fileWasClosed();

};

#endif // MENUBAR_H
