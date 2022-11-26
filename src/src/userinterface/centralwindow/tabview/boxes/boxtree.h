/*!
 *  \file   boxtree.h
 *  \author Eva Navratilova
 */

#ifndef BOXTREE_H
#define BOXTREE_H

#include <QCheckBox>
#include <QSpinBox>

#include "box.h"
#include "userinterface/objects/label.h"
#include "userinterface/objects/comboboxnarrow.h"
#include "../treeview/treescene.h"

class BoxTree : public Box
{
    Q_OBJECT
private:
    Label _laTreeType;
    ComboBoxNarrow _comboTreeType;
    Label _laGenerationCount;
    QCheckBox _checkGenerationCount;
    QSpinBox _spinGenerationCount;

    /// Tree Type dependent
    // Outlet kognat & agnat
    Label _laSpousePresent;
    QCheckBox _checkSpousePresent;
    // Outlet & Relative Tree
    Label _laSonsOnly;
    QCheckBox _checkSonsOnly;

public:
    BoxTree(QString title, Kernel &k, Identifier &p, QWidget *parent = nullptr);

    void update();

private:
    void fill();
    void remove();

signals:
    void changeTreeType(TreeType type);
    void changeGenerationCount(int count);
    void changeSpousePresent(bool present);
    void changeSonsOnly(bool sonsOnly);

private slots:
    void setChecked(bool checked);
    void treeTypeChanged(int type);
    void checkGenerationClicked(bool checked);

};

#endif // BOXTREE_H
