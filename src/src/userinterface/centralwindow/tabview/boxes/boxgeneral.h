/*!
 *  \file   boxgeneral.h
 *  \author Eva Navratilova
 */

#ifndef BOXNAME_H
#define BOXNAME_H

#include <QGroupBox>
#include <QGridLayout>
#include <QStringList>

#include "../../../../kernel.h"
#include "box.h"
#include "../../../dialogs/messageboxes/messagebox.h"
#include "userinterface/objects/completerinline.h"
#include "subbox/subboxgeneralleft.h"
#include "subbox/subboxgeneralright.h"


/// TODO - change parent to Box

class BoxGeneral : public Box
{
    Q_OBJECT
private:
    SubboxGeneralLeft *_subboxGeneralLeft;
    SubboxGeneralRight *_subboxGeneralRight;

public:
    BoxGeneral(QString title, Kernel &k, Identifier &p, QWidget *parent = nullptr);

    void update() override;

private:
    void fill() override;

signals:
    void dataChanged();

private slots:
    void genderChanged(int index);
    void nameGivenChanged(const QString &str);
    void nameMarnameChanged(const QString &str);
    void nameBirthnameChanged(const QString &str);
    void nameTit1Changed(const QString &str);
    void nameTit2Changed(const QString &str);
};

#endif // BOXNAME_H
