/*!
 *  \file   menubar.cpp
 *  \author Eva Navratilova
 */

#include "menubar.h"

MenuBar::MenuBar(Kernel &k, Identifier &p, Identifier &s, IdentifierHistory &h, QWidget *parent)
    : QMenuBar(parent), _kernel(k), _proband(p), _source(s), _history(h)
{
    // Initialize
    _menuFileNew = new ActionFileNew(_kernel);
    _menuFileOpen = new ActionFileOpen(_kernel);
    _menuFileSave = new ActionFileSave(_kernel);
    _menuFileSaveAs = new ActionFileSaveAs(_kernel);
    _menuFileInformation = new ActionInformation(_kernel);

    _menuPersonPrevious = new ActionPersonHistoryPrevious(_kernel, _history);
    _menuPersonNext = new ActionPersonHistoryNext(_kernel, _history);
    _menuPersonAddMan = new ActionPersonAddMan(_kernel);
    _menuPersonAddWoman = new ActionPersonAddWoman(_kernel);
    _menuPersonDelete = new ActionPersonDelete(_kernel, _proband);

    _menuTreeOutletAncestral = new ActionTree(TreeType::ANCESTRAL_OUTLET);
    _menuTreeFamilyTree = new ActionTree(TreeType::FAMILY_TREE);
    _menuTreeOutletAgnat = new ActionTree(TreeType::AGNAT_OUTLET);
    _menuTreeOutletKognat = new ActionTree(TreeType::KOGNAT_OUTLET);
    _menuTreeRelativesTree = new ActionTree(TreeType::RELATIVES_TREE);
    _menuTreeCustom = new ActionCustomTree(_kernel, _proband);
    _menuTreeExport = new ActionTreeExport();

    _menuSettingsEnvironment = new ActionSettingsEnvironment(_proband);
    _menuSettingsConstraints = new ActionSettingsConstraints();
    _menuSettingsFormatTreeCellPerson = new ActionSettingsDescriptionFormat(_kernel, _proband, FormatableText::TREE_INDIVIDUAL);
    _menuSettingsFormatTreeCellMarriage = new ActionSettingsDescriptionFormat(_kernel, _family, FormatableText::TREE_MARRIAGE);
    _menuSettingsFormatPerson = new ActionSettingsDescriptionFormat(_kernel, _proband, FormatableText::INDIVIDUAL);
    _menuSettingsFormatSource = new ActionSettingsDescriptionFormat(_kernel, _source, FormatableText::SOURCE);
    _menuSettingsFormatSourceCitation = new ActionSettingsDescriptionFormat(_kernel, _source, FormatableText::SOURCE_CITATION);

    _menuHelpAbout = new ActionHelpAbout();

    // Set menu titles
    this->translate();

    // Add items to submenus
    _menuFile.addAction(_menuFileNew);
    _menuFile.addAction(_menuFileOpen);
    _menuFile.addSeparator();
    _menuFile.addAction(_menuFileSave);
    _menuFile.addAction(_menuFileSaveAs);
    _menuFile.addSeparator();
    _menuFile.addAction(_menuFileInformation);
    _menuFile.addSeparator();

    _menuPerson.addAction(_menuPersonPrevious);
    _menuPerson.addAction(_menuPersonNext);
    _menuPerson.addSeparator();
    _menuPerson.addAction(_menuPersonAddMan);
    _menuPerson.addAction(_menuPersonAddWoman);
    _menuPerson.addAction(_menuPersonDelete);

    _menuTrees.addAction(_menuTreeOutletAncestral);
    _menuTrees.addAction(_menuTreeFamilyTree);
    _menuTrees.addAction(_menuTreeRelativesTree);
    _menuTrees.addSeparator();
    _menuTrees.addAction(_menuTreeOutletAgnat);
    _menuTrees.addAction(_menuTreeOutletKognat);
    //_menuTrees.addSeparator();
    //_menuTrees.addAction(_menuTreeCustom);
    _menuTrees.addSeparator();
    _menuTrees.addAction(_menuTreeExport);

    _menuSettings.addAction(_menuSettingsEnvironment);
    _menuSettings.addAction(_menuSettingsConstraints);
    _menuSettings.addMenu(&_submenuSettingsDescriptionFormat);
    _submenuSettingsDescriptionFormat.addAction(_menuSettingsFormatTreeCellPerson);
    _submenuSettingsDescriptionFormat.addAction(_menuSettingsFormatTreeCellMarriage);
    _submenuSettingsDescriptionFormat.addAction(_menuSettingsFormatPerson);
    _submenuSettingsDescriptionFormat.addAction(_menuSettingsFormatSource);
    _submenuSettingsDescriptionFormat.addAction(_menuSettingsFormatSourceCitation);

    _menuHelp.addAction(_menuHelpAbout);

    this->repopulateLastOpen();

    // Add items to menu
    this->addMenu(&_menuFile);
    this->addMenu(&_menuPerson);
    this->addMenu(&_menuTrees);
    this->addMenu(&_menuSettings);
    this->addMenu(&_menuHelp);

    /// Connect
    /// Connect File
    connect(_menuFileNew, &ActionFileNew::fileLoaded, this, &MenuBar::fileLoaded);
    connect(_menuFileOpen, &ActionFileOpen::fileLoaded, this, &MenuBar::fileLoaded);

    connect(this, &MenuBar::fileLoaded, this, &MenuBar::fileWasOpened);

    // Connect Proband change
    connect(_menuFileNew, &ActionFileNew::probandChanged, this, &MenuBar::probandChanged);
    connect(_menuFileOpen, &ActionFileOpen::probandChanged, this, &MenuBar::probandChanged);
    connect(_menuPersonPrevious, &ActionPersonHistoryPrevious::probandChanged, this, &MenuBar::probandChanged);
    connect(_menuPersonNext, &ActionPersonHistoryNext::probandChanged, this, &MenuBar::probandChanged);
    connect(_menuPersonAddMan, &ActionPersonAddMan::probandChanged, this, &MenuBar::probandChanged);
    connect(_menuPersonAddWoman, &ActionPersonAddWoman::probandChanged, this, &MenuBar::probandChanged);
    connect(_menuSettingsFormatPerson, &ActionSettingsDescriptionFormat::probandChanged, this, &MenuBar::probandChanged);

    // Descriptions changed
    connect(_menuSettingsFormatPerson, &ActionSettingsDescriptionFormat::probandChanged, this, &MenuBar::probandChanged);
    connect(_menuSettingsFormatSourceCitation, &ActionSettingsDescriptionFormat::probandChanged, this, &MenuBar::probandChanged);
    connect(_menuSettingsFormatSource, &ActionSettingsDescriptionFormat::sourceChanged, this, &MenuBar::sourceChanged);

    // Connect individual removed
    connect(_menuPersonDelete, &ActionPersonDelete::individualDeleted, this, &MenuBar::deleteIndividual);

    // Connect last open repopulation
    connect(_menuFileOpen, &ActionFileOpen::fileLoaded, this, &MenuBar::repopulateLastOpen);
    connect(_menuFileSaveAs, &ActionFileSaveAs::fileLoaded, this, &MenuBar::repopulateLastOpen);
    connect(_menuFileSaveAs, &ActionFileSaveAs::fileLoaded, this, &MenuBar::fileLoaded);

    // Connect new open to save
    connect(_menuFileNew, &ActionFileNew::fileSaveable, _menuFileSave, &ActionFileSave::setFileName);
    connect(_menuFileOpen, &ActionFileOpen::fileSaveable, _menuFileSave, &ActionFileSave::setFileName);
    connect(_menuFileSaveAs, &ActionFileSaveAs::fileSaveable, _menuFileSave, &ActionFileSave::setFileName);

    connect(_menuFileNew, &ActionFileNew::fileSaveable, _menuFileSaveAs, &ActionFileSaveAs::setFileName);
    connect(_menuFileOpen, &ActionFileOpen::fileSaveable, _menuFileSaveAs, &ActionFileSaveAs::setFileName);

    // Connect open file request
    connect(_menuFileNew, &ActionFileNew::fileLoadRequest, this, &MenuBar::saveBeforeFlush);
    connect(_menuFileOpen, &ActionFileOpen::fileLoadRequest, this, &MenuBar::saveBeforeFlush);

    // Connect proband changed to enable person deletion
    //connect(this, &MenuBar::probandChanged, _menuPersonDelete, &ActionPersonDelete::setEnabled);

    // Connect file loaded to enable actions
    connect(this, &MenuBar::fileLoaded, _menuFileInformation, &ActionInformation::enable);
    connect(this, &MenuBar::fileLoaded, _menuPersonAddMan, &ActionPersonAddMan::enable);
    connect(this, &MenuBar::fileLoaded, _menuPersonAddWoman, &ActionPersonAddWoman::enable);
    connect(this, &MenuBar::fileLoaded, _menuTreeOutletAncestral, &Action::enable);
    connect(this, &MenuBar::fileLoaded, _menuTreeFamilyTree, &Action::enable);
    connect(this, &MenuBar::fileLoaded, _menuTreeRelativesTree, &Action::enable);
    connect(this, &MenuBar::fileLoaded, _menuTreeOutletAgnat, &Action::enable);
    connect(this, &MenuBar::fileLoaded, _menuTreeOutletKognat, &Action::enable);
    connect(this, &MenuBar::fileLoaded, _menuTreeCustom, &Action::enable);
    connect(this, &MenuBar::fileLoaded, _menuTreeExport, &Action::enable);

    // Connect file closed to disable actions
    connect(this, &MenuBar::fileClosed, this, &MenuBar::fileWasClosed);
    connect(this, &MenuBar::fileClosed, _menuFileInformation, &ActionInformation::disable);
    connect(this, &MenuBar::fileClosed, _menuFileSave, &ActionFileSave::disable);
    connect(this, &MenuBar::fileClosed, _menuFileSaveAs, &ActionFileSaveAs::disable);
    connect(this, &MenuBar::fileClosed, _menuPersonAddMan, &ActionPersonAddMan::disable);
    connect(this, &MenuBar::fileClosed, _menuPersonAddWoman, &ActionPersonAddWoman::disable);
    connect(this, &MenuBar::fileClosed, _menuPersonDelete, &ActionPersonDelete::disable);
    connect(this, &MenuBar::fileClosed, _menuTreeOutletAncestral, &Action::disable);
    connect(this, &MenuBar::fileClosed, _menuTreeFamilyTree, &Action::disable);
    connect(this, &MenuBar::fileClosed, _menuTreeRelativesTree, &Action::disable);
    connect(this, &MenuBar::fileClosed, _menuTreeOutletAgnat, &Action::disable);
    connect(this, &MenuBar::fileClosed, _menuTreeOutletKognat, &Action::disable);
    connect(this, &MenuBar::fileClosed, _menuTreeCustom, &Action::disable);
    connect(this, &MenuBar::fileClosed, _menuTreeExport, &Action::disable);

    // Connect draw tree
    connect(_menuTreeOutletAncestral, &ActionTree::drawTree, this, &MenuBar::drawTree);
    connect(_menuTreeFamilyTree, &ActionTree::drawTree, this, &MenuBar::drawTree);
    connect(_menuTreeOutletAgnat, &ActionTree::drawTree, this, &MenuBar::drawTree);
    connect(_menuTreeOutletKognat, &ActionTree::drawTree, this, &MenuBar::drawTree);
    connect(_menuTreeRelativesTree, &ActionTree::drawTree, this, &MenuBar::drawTree);
    connect(_menuTreeCustom, &ActionCustomTree::drawTreeScene, this, &MenuBar::drawTreeScene);

    // Connect export image
    connect(_menuTreeExport, &ActionTreeExport::exportImage, this, &MenuBar::exportImage);

    /// Connect Settings
    connect(_menuSettingsEnvironment, &ActionSettingsEnvironment::languageChanged, this, &MenuBar::languageChanged);
}

MenuBar::~MenuBar()
{

}

void MenuBar::translate()
{
    _menuFileNew->translate();
    _menuFileOpen->translate();
    _menuFileSave->translate();
    _menuFileSaveAs->translate();
    _menuFileInformation->translate();

    _menuPersonPrevious->translate();
    _menuPersonNext->translate();
    _menuPersonAddMan->translate();
    _menuPersonAddWoman->translate();
    _menuPersonDelete->translate();

    _menuTreeOutletAncestral->translate();
    _menuTreeFamilyTree->translate();
    _menuTreeOutletAgnat->translate();
    _menuTreeOutletKognat->translate();
    _menuTreeRelativesTree->translate();
    _menuTreeCustom->translate();
    _menuTreeExport->translate();

    _menuSettingsEnvironment->translate();
    _menuSettingsConstraints->translate();
    _menuSettingsFormatTreeCellPerson->translate();
    _menuSettingsFormatTreeCellMarriage->translate();
    _menuSettingsFormatPerson->translate();
    _menuSettingsFormatSource->translate();
    _menuSettingsFormatSourceCitation->translate();

    _menuHelpAbout->translate();

    // Set menu titles
    _menuFile.setTitle(tr("File"));
    _menuPerson.setTitle((tr("Person")));
    _menuTrees.setTitle((tr("Tree")));
    _menuSettings.setTitle(tr("Settings"));
    _menuHelp.setTitle(tr("Help"));

    _submenuSettingsDescriptionFormat.setTitle(tr("Description Format"));
}

void MenuBar::openLast()
{
    if(_menuFileLast.length() > 0)
        emit(_menuFileLast.first()->triggered());
}

void MenuBar::setUsed(const QString &filename)
{
    _menuFileSave->setFileName(filename);
    _menuFileSaveAs->setFileName(filename);
}

int MenuBar::saveOrSaveAs()
{
    if(_menuFileSave->isEnabled())
    {
        _menuFileSave->trigger();
    }
    else
    {
        _menuFileSaveAs->trigger();
        // Dialog was canceled -> reject
        if(_menuFileSaveAs->getFileName().isEmpty())
        {
            return QMessageBox::Rejected;
        }
    }
    return QMessageBox::Accepted;
}

void MenuBar::update()
{
    _menuPersonDelete->changePerson(_proband);

    auto families = _kernel.record()->getFamiliesOfIndividualParent(_proband);
    _family = (families.isEmpty())? Identifier() : families.first();
}

int MenuBar::saveBeforeFlush()
{
    int retval;
    if(_fileOpened)
    {
        MessageSave messageSave;
        auto result = messageSave.exec();
        switch(result)
        {
        case MessageSave::StandardButton::Yes:
            retval = this->saveOrSaveAs();
            break;
        case MessageSave::StandardButton::No:
            retval = MessageBox::Accepted;
            break;
        default: // && Cancel
            retval = MessageBox::Rejected;
            break;
        }
    }
    else
    {
        // Accept close or new file load if nothing opened
        retval = MessageBox::Accepted;
    }
    if(_fileOpened && retval == MessageBox::Accepted)
    {
        emit(this->fileClosed());
    }
    return retval;
}

void MenuBar::repopulateLastOpen()
{

    QSettings settings;
    QStringList files = settings.value("path/recentFiles").toStringList();

    // Clear old menu
    auto menuFileToRemove = _menuFileLast.begin();
    while(menuFileToRemove != _menuFileLast.end())
    {
        _menuFile.removeAction(*menuFileToRemove);
        //delete *menuFileToRemove;
        menuFileToRemove = _menuFileLast.erase(menuFileToRemove);
    }
    _menuFileLast.clear();

    // Re-populate
    for(auto file=files.begin(); file != files.end(); file++)
    {
        _menuFileLast.push_back(new ActionFileLast(_kernel, *file));
        _menuFile.addAction(_menuFileLast.last());
        connect(_menuFileLast.last(), &ActionFileLast::probandChanged, this, &MenuBar::probandChanged);
        connect(_menuFileLast.last(), &ActionFileLast::fileLoaded, this, &MenuBar::repopulateLastOpen);
        connect(_menuFileLast.last(), &ActionFileLast::fileSaveable, _menuFileSave, &ActionFileSave::setFileName);
        connect(_menuFileLast.last(), &ActionFileLast::fileSaveable, _menuFileSaveAs, &ActionFileSaveAs::setFileName);
        connect(_menuFileLast.last(), &ActionFileLast::fileLoaded, this, &MenuBar::fileLoaded);
        connect(_menuFileLast.last(), &ActionFileLast::fileLoadRequest, this, &MenuBar::saveBeforeFlush);
    }
}

void MenuBar::deleteIndividual(Identifier ref)
{
    _history.remove(ref);
}

void MenuBar::fileWasOpened(QString filename)
{
    Q_UNUSED(filename);

    _fileOpened = true;
}

void MenuBar::fileWasClosed()
{
    _fileOpened = false;
}


