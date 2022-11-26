/*!
 *  \file   box.h
 *  \author Eva Navratilova
 */

#ifndef BOX_H
#define BOX_H

#include <QGroupBox>
#include <QGridLayout>

#include "userinterface/objects/label.h"
#include "userinterface/objects/sizer.h"
#include "../../../../kernel.h"
#include "../../../../textformatter.h"

#define BOX_CHECKABLE       1
#define BOX_NOT_CHECKABLE   0


class Box : public QGroupBox, public Sizer
{

    Q_OBJECT

protected:
    Kernel &_kernel;
    Identifier &_proband;

    QGridLayout _layout;
    QString _title;

    const QString _strPriest = tr("Priest");
    const QString _strMidwife = tr("Midwife");
    const QString _strGodfather = tr("Godparent 1");
    const QString _strGodmother = tr("Godparent 2");
    const QString _strWitness1 = tr("Witness 1");
    const QString _strWitness2 = tr("Witness 2");


public:
    Box(QString title, bool checkable, Kernel &k, Identifier &p, QWidget *parent = nullptr);
    virtual ~Box() = default;

    virtual void update() = 0;

protected:
    virtual void fill() = 0;

signals:
    void probandChanged(Identifier ref);
    void sourceChanged(const Identifier &src);

public slots:
    void setChecked(bool checked);

};

#endif // BOX_H
