/*!
 *  \file   partneroverview.h
 *  \author Eva Navratilova
 */

#ifndef PARTNEROVERVIEW_H
#define PARTNEROVERVIEW_H

#include <QWidget>
#include <QGridLayout>

#include "../../../../../kernel.h"
#include "../boxchildren.h"
#include "userinterface/objects/sizer.h"
#include "userinterface/dialogs/messageboxes/messagebox.h"
#include "userinterface/dialogs/data/dialogassignperson.h"

class PartnerOverview : public QWidget, Sizer
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier &_proband;
    QVector<Identifier> _families;

    QGridLayout _layout;

    BoxChildren* _boxChildren;

    DialogAssignPerson *_dialogAddExistingPerson;

public:
    explicit PartnerOverview(Kernel &k, Identifier &p, QVector<Identifier> f, QWidget *parent = nullptr);

    void update(const QVector<Identifier> &families);

signals:
    void probandChanged(Identifier ref);

private slots:
    bool isAddChildValid();
    void addSon();
    void addDaughter();
    void addChild();

private:
    void fill();
    void remove();

};

#endif // PARTNEROVERVIEW_H
