/*!
 *  \file   individualdetail.h
 *  \author Eva Navratilova
 */

#ifndef INDIVIDUALDETAIL_H
#define INDIVIDUALDETAIL_H

#include <QWidget>
#include <QGridLayout>

#include "kernel.h"
#include "../boxes/box.h"
#include "../boxes/boxgeneral.h"
#include "../boxes/boxparents.h"
#include "../boxes/boxbirth.h"
#include "../boxes/boxdeath.h"
#include "../boxes/boxpartners.h"
#include "../boxes/boxchildren.h"
#include "../boxes/boxchristening.h"
#include "../boxes/boxburial.h"
#include "../boxes/boxoccupation.h"
#include "../boxes/boxresidence.h"
#include "../boxes/boxeducation.h"
#include "../boxes/boxreligion.h"

#include "userinterface/dialogs/data/dialogassignperson.h"

class IndividualDetail : public QWidget, public Sizer
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier &_proband;

    QGridLayout _layout;

    /// Boxes
    BoxGeneral *_boxName;
    BoxParents *_boxParents;
    BoxChildren* _boxSiblings;

    BoxBirth* _boxBirth;
    //BoxChristening* _boxChristening;
    BoxDeath* _boxDeath;
    //BoxBurial* _boxBurial;

    BoxPartners* _boxPartners;

    BoxResidence* _boxResidence;
    BoxEducation* _boxEducation;
    BoxOccupation* _boxOccupation;
    BoxReligion* _boxReligion;

    DialogAssignPerson *_dialogAddExistingPerson;

public:
    explicit IndividualDetail(Kernel &k, Identifier &p, QWidget *parent = nullptr);
    ~IndividualDetail();
    void fill();

signals:
    void probandChanged(Identifier ref);
    void sourceChanged(const Identifier &ref);
    void dataChanged();

public slots:
    void update();

    void addSiblingBoy();
    void addSiblingGirl();
    void addSiblingChild();

};

#endif // INDIVIDUALDETAIL_H
