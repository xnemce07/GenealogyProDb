/*!
 *  \file   dialogtreecustom.h
 *  \author Eva Navratilova
 */

#ifndef DIALOGTREECUSTOM_H
#define DIALOGTREECUSTOM_H

#include <QDialog>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QListView>
#include <QSpinBox>
#include <QCheckBox>
#include <QSettings>

#include "kernel.h"
#include "userinterface/dialogs/dialog.h"
#include "../../centralwindow/tabview/treeview/treescenes/treesceneuniversal.h"
#include "userinterface/centralwindow/tabview/treeview/treescenes/treescenedoubletree.h"
#include "../../centralwindow/tabview/treeview/treescenes/treescenenorth.h"
#include "../../centralwindow/tabview/treeview/treescenes/treescenesouth.h"
#include "userinterface/objects/label.h"
#include "../../centralwindow/tabview/boxes/boxtree.h"
#include "../../centralwindow/tabview/treeview.h"

class DialogTreeCustom : public Dialog
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier &_proband;

    TreeSceneDoubleTree *_scene;

    TreeType _northType;
    Generation _northMaxGen;
    bool _northSpousePresent = false;
    bool _northSonsOnly = false;
    TreeType _southType;
    Generation _southMaxGen;
    bool _southSpousePresent = false;
    bool _southSonsOnly = false;

    QLabel _laRecent;
    QListView _listRecent;

    BoxTree* _boxTreeCrown;
    BoxTree* _boxTreeRoots;

    TreeView *_treeView;

public:
    DialogTreeCustom(Kernel &k, Identifier &p, QWidget *parent = nullptr);

    TreeScene* getTreeScene();

private:
    //int exec();

    void fill();

private slots:
    void changeNorthTreeType(TreeType type);
    void changeNorthGenerationCount(int count);
    void changeNorthSpousePresent(bool present);
    void changeNorthSonsOnly(bool sonsOnly);

    void changeSouthTreeType(TreeType type);
    void changeSouthGenerationCount(int count);
    void changeSouthSpousePresent(bool present);
    void changeSouthSonsOnly(bool sonsOnly);

    void changeTreeType(TreeDirection dir, TreeType type);
    void changeGenerationCount(TreeDirection dir, int count);
    void changeSpousePresent(TreeDirection dir, bool present);
    void changeSonsOnly(TreeDirection dir, bool sonsOnly);

    void updatePreview();

};

#endif // DIALOGTREECUSTOM_H
