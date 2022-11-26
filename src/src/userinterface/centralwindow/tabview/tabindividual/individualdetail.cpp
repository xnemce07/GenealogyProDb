/*!
 *  \file   individualdetail.cpp
 *  \author Eva Navratilova
 */

#include "individualdetail.h"

IndividualDetail::IndividualDetail(Kernel &k, Identifier &p, QWidget *parent)
  : QWidget(parent), Sizer(), _kernel(k), _proband(p)
{
    this->setLayout(&_layout);

    this->fill();

    /// TODO - connect also children, spouses, priests, witnesses and godparents
    // Connect proband changed
    connect(_boxParents, &BoxParents::probandChanged, this, &IndividualDetail::probandChanged);
    connect(_boxSiblings, &BoxChildren::probandChanged, this, &IndividualDetail::probandChanged);
    connect(_boxBirth, &BoxBirth::probandChanged, this, &IndividualDetail::probandChanged);
    connect(_boxDeath, &BoxDeath::probandChanged, this, &IndividualDetail::probandChanged);
    connect(_boxPartners, &BoxPartners::probandChanged, this, &IndividualDetail::probandChanged);

    // Connect Add sibling
    /// TODO - add sibling family construction not working properly
    connect(_boxSiblings, &BoxChildren::newBoy, this, &IndividualDetail::addSiblingBoy);
    connect(_boxSiblings, &BoxChildren::newGirl, this, &IndividualDetail::addSiblingGirl);
    connect(_boxSiblings, &BoxChildren::newChild, this, &IndividualDetail::addSiblingChild);

    // Connect Data changed -> update list
    connect(_boxName, &BoxGeneral::dataChanged, this, &IndividualDetail::dataChanged);
    connect(_boxBirth, &BoxBirth::dataChanged, this, &IndividualDetail::dataChanged);

    // Connect source changed
    connect(_boxBirth, &BoxBirth::sourceChanged, this, &IndividualDetail::sourceChanged);
    connect(_boxDeath, &BoxDeath::sourceChanged, this, &IndividualDetail::sourceChanged);
    connect(_boxPartners, &BoxPartners::sourceChanged, this, &IndividualDetail::sourceChanged);
}

IndividualDetail::~IndividualDetail()
{
    _boxName->deleteLater();
    _boxParents->deleteLater();
    _boxSiblings->deleteLater();

    _boxBirth->deleteLater();
    _boxDeath->deleteLater();

    _boxPartners->deleteLater();

    _boxResidence->deleteLater();
    _boxOccupation->deleteLater();
    _boxEducation->deleteLater();
    _boxReligion->deleteLater();
}

void IndividualDetail::fill()
{
    QSettings settings;

    // Initialize
    _layout.setHorizontalSpacing(this->tightSpacing());
    _layout.setContentsMargins(this->mediumSpacing(),this->mediumSpacing(),this->mediumSpacing(),0);

    // Boxes init
    _boxName = new BoxGeneral(tr("General"), _kernel, _proband, this);
    _boxParents = new BoxParents(tr("Parents"), _kernel, _proband, this);
    _boxSiblings = new BoxChildren(tr("Siblings"), _kernel, _proband, this);

    _boxBirth = new BoxBirth(tr("Birth"), _kernel, _proband, this);
    //_boxChristening = new BoxChristening(tr("Christening"), _kernel, _proband);
    _boxDeath = new BoxDeath(tr("Death"), _kernel, _proband, this);
    //_boxBurial = new BoxBurial(tr("Burial"), _kernel, _proband);

    _boxPartners = new BoxPartners(tr("Partners"), _kernel, _proband, this);

    _boxResidence = new BoxResidence(_kernel, _proband, this);
    _boxEducation = new BoxEducation(_kernel, _proband, this);
    _boxOccupation = new BoxOccupation(_kernel, _proband, this);
    _boxReligion = new BoxReligion(_kernel, _proband, this);

    // Set layout
    _layout.addWidget(_boxName, 0, 0, 1, 2);
    _layout.addWidget(_boxParents, 0, 2, 1, 1);
    _layout.addWidget(_boxSiblings, 0, 3, 1, 1);
    _layout.addWidget(_boxBirth, 1, 0, 1, 2);
    _layout.addWidget(_boxDeath, 1, 2, 1, 2);
    //_layout.addWidget(_boxChristening, 2, 0, 1, 3);
    //_layout.addWidget(_boxBurial, 2, 3, 1, 3);
    _layout.addWidget(_boxPartners, 2, 0, 1, 4);
    _layout.addWidget(_boxResidence, 3, 0, 1, 1);
    _layout.addWidget(_boxEducation, 3, 1, 1, 1);
    _layout.addWidget(_boxOccupation, 3, 2, 1, 1);
    _layout.addWidget(_boxReligion, 3, 3, 1, 1);

    // Adjust widgets in layout
    _layout.setColumnStretch(0, 1);
    _layout.setColumnStretch(1, 1);
    _layout.setColumnStretch(2, 1);
    _layout.setColumnStretch(3, 1);

    _layout.setRowStretch(0, 10);
    _layout.setRowStretch(1, 1);
    _layout.setRowStretch(2, 100);
    _layout.setRowStretch(3, 100);
}

void IndividualDetail::update()
{
    auto siblings = _kernel.record()->getIndividualSiblings(_proband);

    _boxName->update();
    _boxParents->update();
    _boxSiblings->update(siblings);

    _boxBirth->update();
    //_boxChristening->update();
    _boxDeath->update();
    //_boxBurial->update();

    _boxPartners->update();

    _boxResidence->update();
    _boxEducation->update();
    _boxOccupation->update();
    _boxReligion->update();

    this->setEnabled(_kernel.record()->isIndividual(_proband));
}
void IndividualDetail::addSiblingBoy()
{
    QSettings settings;
    Identifier boy = _kernel.record()->newIndividual();
    _kernel.record()->setIndividualDeceased(boy, settings.value("dataConstraints/autoDead").toBool());
    _kernel.record()->setIndividualGender(boy, Gender::MALE);
    Identifier family = _kernel.record()->getIndividualParentalFamily(_proband);
    if(!_kernel.record()->isFamily(family))
    {
        family = _kernel.record()->newFamily();
        _kernel.record()->setFamilyChild(family, _proband);
    }
    _kernel.record()->setFamilyChild(family, boy);
    QString surname;
    if(Gender::MALE == _kernel.record()->getIndividualGender(_proband))
    {
        surname = _kernel.record()->getIndividualNameSurnameBirthMarried(_proband);
    }
    else
    {
        Identifier father = _kernel.record()->getFamilyHusband(family);
        surname = _kernel.record()->getIndividualNameSurnameMarriedBirth(father);
    }
    _kernel.record()->setIndividualNameSurname(boy, surname);
    _kernel.record()->setIndividualNameMarname(boy, surname);
    emit(this->probandChanged(boy));
}

void IndividualDetail::addSiblingGirl()
{
    QSettings settings;
    Identifier girl = _kernel.record()->newIndividual();
    _kernel.record()->setIndividualDeceased(girl, settings.value("dataConstraints/autoDead").toBool());
    _kernel.record()->setIndividualGender(girl, Gender::FEMALE);
    Identifier family = _kernel.record()->getIndividualParentalFamily(_proband);
    if(!_kernel.record()->isFamily(family))
    {
        family = _kernel.record()->newFamily();
        _kernel.record()->setFamilyChild(family, _proband);
    }
    _kernel.record()->setFamilyChild(family, girl);
    QString surname;
    if(Gender::FEMALE == _kernel.record()->getIndividualGender(_proband))
    {
        surname = _kernel.record()->getIndividualNameSurnameBirth(_proband);
    }
    else
    {
        Identifier mother = _kernel.record()->getFamilyWife(family);
        if(_kernel.record()->isFamilyMarried(family))
        {
            surname = _kernel.record()->getIndividualNameSurnameMarried(mother);
        }
        else
        {
            surname = _kernel.record()->getIndividualNameSurnameBirth(mother);
        }
    }
    _kernel.record()->setIndividualNameSurname(girl, surname);
    emit(this->probandChanged(girl));
}

void IndividualDetail::addSiblingChild()
{
    QVector<Identifier> pers;
    QVector<Identifier> ancestors = _kernel.record()->getIndividualAncestors(_proband);
    QVector<Identifier> siblings = _kernel.record()->getIndividualSiblings(_proband);
    QVector<Identifier> descendants = _kernel.record()->getIndividualDescendants(_proband);
    Identifier first = _kernel.record()->getIdentifierIndividualFirst();
    Identifier last  = _kernel.record()->getIdentifierIndividualLast();
    for(Identifier current = first; current < last; _kernel.record()->getIdentifierIndividualNext(current))
    {
        if(current == _proband)
            continue;
        if(ancestors.contains(current))
            continue;
        if(siblings.contains(current))
            continue;
        if(descendants.contains(current))
            continue;

        /// TODO - probably add alive check?
        pers.push_front(current);
    }

    _dialogAddExistingPerson = new DialogAssignPerson(_kernel, pers);
    Identifier child;
    int result = _dialogAddExistingPerson->getSelectedId(child);Identifier family = _kernel.record()->getIndividualParentalFamily(_proband);
    if(!_kernel.record()->isFamily(family))
    {
        family = _kernel.record()->newFamily();
        _kernel.record()->setFamilyChild(family, _proband);
    }
    if(_kernel.record()->isIndividual(child))
    {
        _kernel.record()->setFamilyChild(family, child);
        _boxSiblings->update(_kernel.record()->getIndividualSiblings(_proband));
    }
    else if(result == DialogAssignPerson::Accepted
            && !_kernel.record()->isIndividual(child))
    {
        QSettings settings;
        child = _kernel.record()->newIndividual();
        _kernel.record()->setIndividualDeceased(child, settings.value("dataConstraints/autoDead").toBool());
        _kernel.record()->setFamilyChild(family, child);
        emit(this->probandChanged(child));
    }
}



