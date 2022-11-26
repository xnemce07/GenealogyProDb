#-------------------------------------------------
#
# Project created by QtCreator 2018-08-08T17:59:52
#
# Author: Eva Navratilova
#         navratie@gmail.com
#
#-------------------------------------------------

QT       += core gui \
            printsupport #\
            #autoupdatercore \
            #autoupdatergui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProGenealogy
TEMPLATE = app
VERSION = 1.0.2

# Different for MAC OS !!!
win32:RC_ICONS = ProGenealogy.ico
#unix:

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES +=  QT_DEPRECATED_WARNINGS \
            QT_NO_DEBUG_OUTPUT
#            CGGEDCOM_EXPORTS


CONFIG +=   c++1z #\
            #force_debug_info \
            #static

# TRANSLATIONS
# WHEN ADDING MORE translations it is sufficient to only add the (lupdate) .ts files here,
# and the (lrelease) .qm files in the resources (to path "/translations") and specify the
# alias as QLocale::name()'s first two lowercase language characters.
TRANSLATIONS =  language/cs.ts \
                language/de.ts

# OPTIMIZATION
# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

# add the desired -O3 if not present
QMAKE_CXXFLAGS_RELEASE *= -O3
win32:QMAKE_LFLAGS = -static -static-libgcc -static-libstdc++

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#include(sourceskernel.pri)

INCLUDEPATH += $$PWD
INCLUDEPATH += $$_PRO_FILE_PWD_


RESOURCES = resources.qrc

SOURCES += \
    kernel.cpp \
    kernel/importer.cpp \
    3rd-party/cgGedcom/anselcodec.cpp \
    3rd-party/cgGedcom/gedcomnode.cpp \
    3rd-party/cgGedcom/gedcomparser.cpp \
    kernel/exporter.cpp \
    kernel/importer/importergedcom.cpp \
    kernel/record.cpp \
    kernel/record/recordram.cpp \
    kernel/record/recordRAM\place.cpp \
    kernel/record/recordRAM\family.cpp \
    kernel/record/recordRAM\individual.cpp \
    kernel/record/recordRAM\eventdetail.cpp \
    kernel/record/recordRAM\address.cpp \
    kernel/record/recordRAM\head.cpp \
    kernel/record/recordRAM\identifier\identifierfactory.cpp \
    kernel/record/recordRAM\identifier.cpp \
    kernel/record/recordRAM\event\commoneventstructure.cpp \
    kernel/record/recordRAM/individual/personalnamepieces.cpp \
    kernel/record/recordRAM/submitter.cpp \
    kernel/record/recordRAM/sourcerecord.cpp \
    kernel/record/recordRAM/source/sourcecitation.cpp \
    kernel/record/recordRAM/source/eventrecorded.cpp \
    kernel/exporter/exportergedcom.cpp \
    kernel/importer/importernewproject.cpp \
    kernel/record/recordRAM/primitives.cpp \
    main.cpp \
    userinterface/centralwindow/tabview/boxes/subbox/subboxgeneralleft.cpp \
    userinterface/centralwindow/tabview/boxes/subbox/subboxgeneralright.cpp \
    userinterface/centralwindow/tabview/tabindividual/individuallist.cpp \
    userinterface/centralwindow/tabview/treeview.cpp \
    userinterface/dialogs/data/dialogassignperson.cpp \
    userinterface/dialogs/import/dialogprogress.cpp \
    userinterface/dialogs/messageboxes/messagesave.cpp \
    userinterface/dialogs/settings/dialogsettingsconstraints.cpp \
    userinterface/mainwindow.cpp \
    userinterface/menubar.cpp \
    userinterface/centralwindow/tabview/tabindividual.cpp \
    userinterface/centralwindow/tabview.cpp \
    userinterface/centralwindow/tabview/boxes/boxparents.cpp \
    textformatter.cpp \
    userinterface/centralwindow/tabview/boxes/boxbirth.cpp \
    userinterface/centralwindow/tabview/boxes/box.cpp \
    userinterface/centralwindow/tabview/boxes/boxgeneral.cpp \
    userinterface/centralwindow/tabview/boxes/subbox/subboxdate.cpp \
    userinterface/centralwindow/tabview/boxes/subbox/subbox.cpp \
    userinterface/centralwindow/tabview/boxes/boxdeath.cpp \
    userinterface/centralwindow/tabview/boxes/boxpartners.cpp \
    userinterface/centralwindow/tabview/boxes/boxmarriage.cpp \
    userinterface/centralwindow/tabview/boxes/boxchildren.cpp \
    userinterface/centralwindow/tabview/boxes/boxdivorce.cpp \
    userinterface/dialogs/messageboxes/messagebeta.cpp \
    userinterface/centralwindow/tabview/boxes/boxchristening.cpp \
    userinterface/centralwindow/tabview/boxes/subbox/subboxpersonref.cpp \
    userinterface/centralwindow/tabview/boxes/boxburial.cpp \
    userinterface/centralwindow/tabview/boxes/boxeditablelist.cpp \
    userinterface/centralwindow/tabview/boxes/boxoccupation.cpp \
    userinterface/centralwindow/tabview/boxes/boxresidence.cpp \
    userinterface/centralwindow/tabview/boxes/boxeducation.cpp \
    userinterface/centralwindow/tabview/boxes/boxreligion.cpp \
    kernel/record/recordRAM/date.cpp \
    userinterface/dialogs/messageboxes/messageimportfailed.cpp \
    userinterface/dialogs/messageboxes/messagedelete.cpp \
    userinterface/menubar/menufile/actionfilenew.cpp \
    userinterface/menubar/menufile/actionfilelast.cpp \
    userinterface/dialogs/messageboxes/messageexportfailed.cpp \
    userinterface/menubar/menufile/actionfile.cpp \
    userinterface/menubar/menufile/actionfileopen.cpp \
    userinterface/menubar/menufile/actionfilesaveas.cpp \
    userinterface/menubar/menufile/actionfilesave.cpp \
    userinterface/dialogs/messageboxes/messagebox.cpp \
    userinterface/centralwindow/tabview/boxes/subbox/subboxsimple.cpp \
    userinterface/dialogs/data/dialogeditable.cpp \
    userinterface/dialogs/data/dialogeditabledescription.cpp \
    userinterface/dialogs/data/dialogeditableresidence.cpp \
    userinterface/dialogs/file/openfiledialog.cpp \
    userinterface/dialogs/file/savefiledialog.cpp \
    userinterface/dialogs/settings/dialogsettingsevnironment.cpp \
    userinterface/menubar/menuhelp/actionabout.cpp \
    userinterface/menubar/menusettings/actionsettingsenvironment.cpp \
    userinterface/menubar/menusettings/actionsettingsconstraints.cpp \
    userinterface/identifierhistory.cpp \
    userinterface/menubar/menuperson/actionpersonadd.cpp \
    userinterface/menubar/action.cpp \
    userinterface/menubar/menuperson/actionpersonaddman.cpp \
    userinterface/menubar/menuperson/actionpersonaddwoman.cpp \
    userinterface/menubar/menuperson/actionpersondelete.cpp \
    userinterface/menubar/menuperson/actionpersonhistory.cpp \
    userinterface/menubar/menuperson/actionpersonhistorynext.cpp \
    userinterface/menubar/menuperson/actionpersonhistoryprevious.cpp \
    userinterface/centralwindow/tabview/treeview/treescene.cpp \
    userinterface/centralwindow/tabview/treeview/treescenes/treesceneoutletancestral.cpp \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitemperson.cpp \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitemedge.cpp \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitempersonman.cpp \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitempersonwoman.cpp \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitempersondecorator.cpp \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitempersonnorth.cpp \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitemedgedecorator.cpp \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitemedgenorth.cpp \
    userinterface/centralwindow/tabview/treeview/treescenes/treescenenorth.cpp \
    userinterface/centralwindow/tabview/treeview/treescenevariables.cpp \
    userinterface/centralwindow/tabview/treeview/treescenedecorator.cpp \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitempersonsouth.cpp \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitemedgesouth.cpp \
    userinterface/centralwindow/tabview/treeview/treescenes/treescenesouth.cpp \
    userinterface/centralwindow/tabview/treeview/treescenes/treescenefamilytree.cpp \
    userinterface/centralwindow/tabview/treeview/treescenes/treesceneoutletxnat.cpp \
    userinterface/menubar/menutree/actiontree.cpp \
    userinterface/centralwindow/tabview/treeview/treescenes/treescenerelativestree.cpp \
    userinterface/centralwindow/tabview/tabsource.cpp \
    userinterface/centralwindow/tabview/tabsource/sourcedetail.cpp \
    userinterface/centralwindow/tabview/boxes/boxsource.cpp \
    userinterface/dialogs/data/informationfamilytree.cpp \
    userinterface/menubar/menufile/actioninformation.cpp \
    userinterface/centralwindow/tabview/tabsource/sourcesearchlist.cpp \
    userinterface/centralwindow/tabview/boxes/subbox/subboxweb.cpp \
    userinterface/centralwindow/tabview/boxes/subbox/subboxcitation.cpp \
    userinterface/centralwindow/tabview/boxes/subbox/subboxsourcedata.cpp \
    userinterface/centralwindow/tabview/tabsource/sourcescrollarea.cpp \
    userinterface/dialogs/tree/dialogtreecustom.cpp \
    userinterface/menubar/menutree/actioncustomtree.cpp \
    userinterface/centralwindow/tabview/boxes/boxtree.cpp \
    userinterface/centralwindow/tabview/treeview/treescenes/treesceneuniversal.cpp \
    userinterface/centralwindow/tabview/treeview/treescenes/treescenedoubletree.cpp \
    userinterface/menubar/menutree/actiontreeexport.cpp \
    kernel/statistics.cpp \
    userinterface/dialogs/settings/dialogsettingsdescriptionformat.cpp \
    userinterface/menubar/menusettings/actionsettingsdescriptionformat.cpp \
    userinterface/dialogs/dialog.cpp \
    userinterface/centralwindow/tabview/tabstatistics.cpp \
    userinterface/objects/comboboxnarrow.cpp \
    userinterface/objects/completerinline.cpp \
    userinterface/objects/datelineedit.cpp \
    userinterface/objects/datevalidator.cpp \
    userinterface/objects/elidebutton.cpp \
    userinterface/objects/label.cpp \
    userinterface/objects/labelwidthadjuster.cpp \
    userinterface/objects/lineeditselected.cpp \
    userinterface/objects/list.cpp \
    userinterface/objects/listitem.cpp \
    userinterface/objects/narrowbutton.cpp \
    userinterface/objects/personlist.cpp \
    userinterface/objects/personlistitem.cpp \
    userinterface/objects/sizer.cpp \
    userinterface/objects/sourcelist.cpp \
    userinterface/objects/sourcelistitem.cpp \
    userinterface/objects/splitter.cpp \
    userinterface/centralwindow/tabview/tabindividual/individualdetail.cpp \
    userinterface/centralwindow/tabview/tabindividual/layoutindividual.cpp \
    userinterface/centralwindow/tabview/boxes/partners/partneroverview.cpp \
    userinterface/centralwindow/tabview/boxes/partners/partnerstabwidget.cpp \
    userinterface/centralwindow/tabview/boxes/partners/partnerwidget.cpp \
    userinterface/centralwindow/tabview/tabindividual/listview/tablecell.cpp \
    userinterface/centralwindow/tabview/tabindividual/listview/tablecelldate.cpp \
    userinterface/centralwindow/tabview/tabindividual/listview/tablecellref.cpp \
    userinterface/centralwindow/tabview/tabindividual/listview/tablecelltext.cpp \
    userinterface/centralwindow/tabview/tabnote.cpp \
    userinterface/objects/translatableobject.cpp

HEADERS += \
    kernel.h \
    kernel/importer.h \
    3rd-party/cgGedcom/anselcodec.h \
    3rd-party/cgGedcom/cggedcom.h \
    3rd-party/cgGedcom/gedcomnode.h \
    3rd-party/cgGedcom/gedcomparser.h \
    kernel/exporter.h \
    kernel/importer/importergedcom.h \
    kernel/record.h \
    kernel/record/recordram.h \
    kernel/record/recordRAM\place.h \
    kernel/record/recordRAM\family.h \
    kernel/record/recordRAM\individual.h \
    kernel/record/recordRAM\primitives.h \
    kernel/record/recordRAM\eventdetail.h \
    kernel/record/recordRAM\address.h \
    kernel/record/recordRAM\head.h \
    kernel/record/recordRAM\identifier\identifierfactory.h \
    kernel/record/recordRAM\identifier.h \
    kernel/record/recordRAM\identifier\identifiertype.h \
    kernel/record/recordRAM\event\commoneventstructure.h \
    kernel/record/recordRAM/individual/personalnamepieces.h \
    kernel/record/recordRAM/submitter.h \
    kernel/record/recordRAM/sourcerecord.h \
    kernel/record/recordRAM/source/sourcecitation.h \
    kernel/record/recordRAM/source/eventrecorded.h \
    kernel/exporter/exportergedcom.h \
    kernel/importer/importernewproject.h \
    userinterface/centralwindow/tabview/boxes/subbox/subboxgeneralleft.h \
    userinterface/centralwindow/tabview/boxes/subbox/subboxgeneralright.h \
    userinterface/centralwindow/tabview/tabindividual/individuallist.h \
    userinterface/centralwindow/tabview/treeview.h \
    userinterface/dialogs/data/dialogassignperson.h \
    userinterface/dialogs/import/dialogprogress.h \
    userinterface/dialogs/messageboxes/messagesave.h \
    userinterface/dialogs/settings/dialogsettingsconstraints.h \
    userinterface/mainwindow.h \
    userinterface/menubar.h \
    userinterface/centralwindow/tabview/tabindividual.h \
    userinterface/centralwindow/tabview.h \
    userinterface/centralwindow/tabview/boxes/boxparents.h \
    textformatter.h \
    userinterface/centralwindow/tabview/boxes/boxbirth.h \
    userinterface/centralwindow/tabview/boxes/box.h \
    userinterface/centralwindow/tabview/boxes/boxgeneral.h \
    userinterface/centralwindow/tabview/boxes/subbox/subboxdate.h \
    userinterface/centralwindow/tabview/boxes/subbox/subbox.h \
    userinterface/centralwindow/tabview/boxes/boxdeath.h \
    userinterface/centralwindow/tabview/boxes/boxpartners.h \
    userinterface/centralwindow/tabview/boxes/boxmarriage.h \
    userinterface/centralwindow/tabview/boxes/boxchildren.h \
    userinterface/centralwindow/tabview/boxes/boxdivorce.h \
    userinterface/dialogs/messageboxes/messagebeta.h \
    userinterface/centralwindow/tabview/boxes/boxchristening.h \
    userinterface/centralwindow/tabview/boxes/subbox/subboxpersonref.h \
    userinterface/centralwindow/tabview/boxes/boxburial.h \
    userinterface/centralwindow/tabview/boxes/boxeditablelist.h \
    userinterface/centralwindow/tabview/boxes/boxoccupation.h \
    userinterface/centralwindow/tabview/boxes/boxresidence.h \
    userinterface/centralwindow/tabview/boxes/boxeducation.h \
    userinterface/centralwindow/tabview/boxes/boxreligion.h \
    kernel/record/recordRAM/date.h \
    userinterface/dialogs/messageboxes/messageimportfailed.h \
    userinterface/dialogs/messageboxes/messagedelete.h \
    userinterface/menubar/menufile/actionfilenew.h \
    userinterface/menubar/menufile/actionfilelast.h \
    userinterface/dialogs/messageboxes/messageexportfailed.h \
    userinterface/menubar/menufile/actionfile.h \
    userinterface/menubar/menufile/actionfileopen.h \
    userinterface/menubar/menufile/actionfilesaveas.h \
    userinterface/menubar/menufile/actionfilesave.h \
    userinterface/dialogs/messageboxes/messagebox.h \
    userinterface/centralwindow/tabview/boxes/subbox/subboxsimple.h \
    userinterface/dialogs/data/dialogeditable.h \
    userinterface/dialogs/data/dialogeditabledescription.h \
    userinterface/dialogs/data/dialogeditableresidence.h \
    userinterface/dialogs/file/openfiledialog.h \
    userinterface/dialogs/file/savefiledialog.h \
    userinterface/dialogs/settings/dialogsettingsevnironment.h \
    userinterface/menubar/menuhelp/actionabout.h \
    userinterface/menubar/menusettings/actionsettingsenvironment.h \
    userinterface/menubar/menusettings/actionsettingsconstraints.h \
    userinterface/identifierhistory.h \
    userinterface/menubar/menuperson/actionpersonadd.h \
    userinterface/menubar/action.h \
    userinterface/menubar/menuperson/actionpersonaddman.h \
    userinterface/menubar/menuperson/actionpersonaddwoman.h \
    userinterface/menubar/menuperson/actionpersondelete.h \
    userinterface/menubar/menuperson/actionpersonhistory.h \
    userinterface/menubar/menuperson/actionpersonhistorynext.h \
    userinterface/menubar/menuperson/actionpersonhistoryprevious.h \
    userinterface/centralwindow/tabview/treeview/treescene.h \
    userinterface/centralwindow/tabview/treeview/treescenes/treesceneoutletancestral.h \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitemperson.h \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitemedge.h \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitempersonman.h \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitempersonwoman.h \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitempersondecorator.h \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitempersonnorth.h \
    userinterface/centralwindow/tabview/treeview/treeitems/generation.h \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitemedgedecorator.h \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitemedgenorth.h \
    userinterface/centralwindow/tabview/treeview/treescenes/treescenenorth.h \
    userinterface/centralwindow/tabview/treeview/treescenevariables.h \
    userinterface/centralwindow/tabview/treeview/treescenedecorator.h \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitempersonsouth.h \
    userinterface/centralwindow/tabview/treeview/treeitems/treeitemedgesouth.h \
    userinterface/centralwindow/tabview/treeview/treescenes/treescenesouth.h \
    userinterface/centralwindow/tabview/treeview/treescenes/treescenefamilytree.h \
    userinterface/centralwindow/tabview/treeview/treescenes/treesceneoutletxnat.h \
    userinterface/menubar/menutree/actiontree.h \
    userinterface/centralwindow/tabview/treeview/treescenes/treescenerelativestree.h \
    userinterface/centralwindow/tabview/tabsource.h \
    userinterface/centralwindow/tabview/tabsource/sourcedetail.h \
    userinterface/centralwindow/tabview/boxes/boxsource.h \
    userinterface/dialogs/data/informationfamilytree.h \
    userinterface/menubar/menufile/actioninformation.h \
    userinterface/centralwindow/tabview/tabsource/sourcesearchlist.h \
    userinterface/centralwindow/tabview/boxes/subbox/subboxweb.h \
    userinterface/centralwindow/tabview/boxes/subbox/subboxcitation.h \
    userinterface/centralwindow/tabview/boxes/subbox/subboxsourcedata.h \
    userinterface/centralwindow/tabview/tabsource/sourcescrollarea.h \
    userinterface/dialogs/tree/dialogtreecustom.h \
    userinterface/menubar/menutree/actioncustomtree.h \
    userinterface/centralwindow/tabview/boxes/boxtree.h \
    userinterface/centralwindow/tabview/treeview/treescenes/treesceneuniversal.h \
    userinterface/centralwindow/tabview/treeview/treescenes/treescenedoubletree.h \
    userinterface/menubar/menutree/actiontreeexport.h \
    kernel/statistics.h \
    userinterface/dialogs/settings/dialogsettingsdescriptionformat.h \
    userinterface/menubar/menusettings/actionsettingsdescriptionformat.h \
    userinterface/dialogs/dialog.h \
    userinterface/centralwindow/tabview/tabstatistics.h \
    userinterface/objects/comboboxnarrow.h \
    userinterface/objects/completerinline.h \
    userinterface/objects/datelineedit.h \
    userinterface/objects/datevalidator.h \
    userinterface/objects/elidebutton.h \
    userinterface/objects/label.h \
    userinterface/objects/labelwidthadjuster.h \
    userinterface/objects/lineeditselected.h \
    userinterface/objects/list.h \
    userinterface/objects/listitem.h \
    userinterface/objects/narrowbutton.h \
    userinterface/objects/personlist.h \
    userinterface/objects/personlistitem.h \
    userinterface/objects/sizer.h \
    userinterface/objects/sourcelist.h \
    userinterface/objects/sourcelistitem.h \
    userinterface/objects/splitter.h \
    userinterface/centralwindow/tabview/tabindividual/individualdetail.h \
    userinterface/centralwindow/tabview/tabindividual/layoutindividual.h \
    userinterface/centralwindow/tabview/boxes/partners/partneroverview.h \
    userinterface/centralwindow/tabview/boxes/partners/partnerstabwidget.h \
    userinterface/centralwindow/tabview/boxes/partners/partnerwidget.h \
    userinterface/centralwindow/tabview/tabindividual/listview/tablecell.h \
    userinterface/centralwindow/tabview/tabindividual/listview/tablecelldate.h \
    userinterface/centralwindow/tabview/tabindividual/listview/tablecellref.h \
    userinterface/centralwindow/tabview/tabindividual/listview/tablecelltext.h \
    userinterface/centralwindow/tabview/tabnote.h \
    userinterface/objects/translatableobject.h
