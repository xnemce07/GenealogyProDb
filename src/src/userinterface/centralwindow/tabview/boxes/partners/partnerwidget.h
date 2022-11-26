/*!
 *  \file   partnerwidget.h
 *  \author Eva Navratilova
 */

#ifndef PARTNERWIDGET_H
#define PARTNERWIDGET_H

#include <QWidget>
#include <QGridLayout>

#include "../../../../../kernel.h"
#include "../boxmarriage.h"
#include "../boxdivorce.h"
#include "../boxchildren.h"
#include "userinterface/dialogs/data/dialogassignperson.h"

class PartnerWidget : public QWidget, private Sizer
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier &_proband;
    Identifier &_family;

    QGridLayout _layout;

    BoxChildren* _boxChildren;
    BoxMarriage* _boxMarriage;
    BoxDivorce* _boxDivorce;

    DialogAssignPerson *_dialogAddExistingPerson;

public:
    explicit PartnerWidget(Kernel &k, Identifier &p, Identifier &f, QWidget *parent = nullptr);

    void update();
    Identifier getPartnerIdentifier() const;
    Identifier getFamilyIdentifier() const;

signals:
    void probandChanged(Identifier ref);
    void sourceChanged(const Identifier &ref);

private slots:
    void addSon();
    void addDaughter();
    void addChild();

private:
    void fill();
};

#endif // PARTNERWIDGET_H
