/*!
 *  \file   partneroverview.cpp
 *  \author Eva Navratilova
 */

#include "partneroverview.h"

PartnerOverview::PartnerOverview(Kernel &k, Identifier &p, QVector<Identifier> f, QWidget *parent)
    : QWidget(parent), Sizer(), _kernel(k), _proband(p), _families(f)
{
    _layout.setHorizontalSpacing(this->tightSpacing());
    _layout.setContentsMargins(0, this->mediumSpacing(), 0, 0);
    this->setLayout(&_layout);

    this->fill();

    // Connect add children
    connect(_boxChildren, &BoxChildren::newBoy, this, &PartnerOverview::addSon);
    connect(_boxChildren, &BoxChildren::newGirl, this, &PartnerOverview::addDaughter);
    connect(_boxChildren, &BoxChildren::newChild, this, &PartnerOverview::addChild);

    // Connect proband changed
    connect(_boxChildren, &BoxChildren::probandChanged, this, &PartnerOverview::probandChanged);
}

void PartnerOverview::update(const QVector<Identifier> &families)
{
    this->remove();

    _families = families;

    QVector<Identifier> children;
    for(auto f = _families.begin(); f != _families.end(); f++)
    {
        children.append(_kernel.record()->getFamilyChildren(*f));
    }
    _boxChildren->update(children);
}

bool PartnerOverview::isAddChildValid()
{
    if(_kernel.record()->getIndividualGender(_proband) == Gender::UNDET)
    {
        MessageBox message(MessageBox::Icon::Warning,
                           tr("Adding a child to an individual with undetermined gender"),
                           tr("You are adding a child to an individual with undetermined gender.\n"
                              "Please set the individual's gender and repeat the action."),
                           MessageBox::StandardButton::Ok);
        message.exec();
        return false;
    }
    else
    {
        MessageBox message(MessageBox::Icon::Question,
                           tr("Adding a child to single parent"),
                           tr("You are adding a child to a single parent %1.\n"
                              "Do you want to continue?").arg(TextFormatter::getPersonLineText(_kernel, _proband)),
                           MessageBox::StandardButton::Yes | MessageBox::StandardButton::No,
                           MessageBox::StandardButton::Yes);
        return (message.exec() == MessageBox::Accepted)? true : false;
    }
}

void PartnerOverview::addSon()
{
    if(!this->isAddChildValid())
        return;

    QSettings settings;
    Identifier family = _kernel.record()->getFamilyOfCouple(_proband, Identifier());
    if(!_kernel.record()->isFamily(family))
    {
        family = _kernel.record()->newFamily();
        _kernel.record()->setFamilySpouse(family, _proband);
    }
    Identifier son = _kernel.record()->newIndividual();
    _kernel.record()->setIndividualDeceased(son, settings.value("dataConstraints/autoDead").toBool());
    _kernel.record()->setIndividualGender(son, Gender::MALE);
    Identifier father = _kernel.record()->getFamilyHusband(family);
    QString lastname = _kernel.record()->getIndividualNameSurnameMarriedBirth(father);
    _kernel.record()->setIndividualNameSurname(son, lastname);
    _kernel.record()->setIndividualNameMarname(son, lastname);
    _kernel.record()->setFamilyChild(family, son);
    emit(this->probandChanged(son));
}

void PartnerOverview::addDaughter()
{
    if(!this->isAddChildValid())
        return;

    Identifier family = _kernel.record()->getFamilyOfCouple(_proband, Identifier());
    if(!_kernel.record()->isFamily(family))
    {
        family = _kernel.record()->newFamily();
        _kernel.record()->setFamilySpouse(family, _proband);
    }
    QSettings settings;
    Identifier daughter = _kernel.record()->newIndividual();
    _kernel.record()->setIndividualDeceased(daughter, settings.value("dataConstraints/autoDead").toBool());
    _kernel.record()->setIndividualGender(daughter, Gender::FEMALE);
    Identifier mother = _kernel.record()->getFamilyWife(family);
    QString surname = _kernel.record()->getIndividualNameSurnameBirth(mother);
    _kernel.record()->setIndividualNameSurname(daughter, surname);
    _kernel.record()->setFamilyChild(family, daughter);
    emit(this->probandChanged(daughter));
}

void PartnerOverview::addChild()
{
    if(!this->isAddChildValid())
        return;

    QVector<Identifier> pers;
    QVector<Identifier> ancestors = _kernel.record()->getIndividualAncestors(_proband);
    QVector<Identifier> children = _kernel.record()->getChildrenOfIndividual(_proband);
    Identifier first = _kernel.record()->getIdentifierIndividualFirst();
    Identifier last  = _kernel.record()->getIdentifierIndividualLast();
    for(Identifier current = first; current < last; _kernel.record()->getIdentifierIndividualNext(current))
    {
        if(current == _proband)
            continue;
        if(ancestors.contains(current))
            continue;
        if(children.contains(current))
            continue;

        /// TODO - probably add alive check?
        pers.push_front(current);
    }

    _dialogAddExistingPerson = new DialogAssignPerson(_kernel, pers);
    Identifier child;
    int result = _dialogAddExistingPerson->getSelectedId(child);
    if(_kernel.record()->isIndividual(child))
    {
        Identifier family = _kernel.record()->getFamilyOfCouple(Identifier(), _proband);
        if(!_kernel.record()->isFamily(family))
        {
            family = _kernel.record()->newFamily();
            _kernel.record()->setFamilySpouse(family, _proband);
        }
        _kernel.record()->setFamilyChild(family, child);
        _boxChildren->update(_kernel.record()->getChildrenOfIndividual(_proband));
    }
    else if(result == DialogAssignPerson::Accepted
            && !_kernel.record()->isIndividual(child))
    {
        QSettings settings;
        child = _kernel.record()->newIndividual();
        _kernel.record()->setIndividualDeceased(child, settings.value("dataConstraints/autoDead").toBool());
        Identifier family = _kernel.record()->getFamilyOfCouple(Identifier(), _proband);
        if(!_kernel.record()->isFamily(family))
        {
            family = _kernel.record()->newFamily();
            _kernel.record()->setFamilySpouse(family, _proband);
        }
        _kernel.record()->setFamilyChild(family, child);
        emit(this->probandChanged(child));
    }
}

void PartnerOverview::fill()
{
    // Initialize
    _boxChildren = new BoxChildren(tr("Children"), _kernel, _proband);

    // Set static values

    // Set layout
    _layout.addWidget(_boxChildren, 0, 0);

    // Adjust layout positions
    _layout.setColumnStretch(0, 1);
}

void PartnerOverview::remove()
{
    _families.clear();
}
