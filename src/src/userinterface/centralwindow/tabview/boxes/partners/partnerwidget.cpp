/*!
 *  \file   partnerwidget.cpp
 *  \author Eva Navratilova
 */

#include "partnerwidget.h"

PartnerWidget::PartnerWidget(Kernel &k, Identifier &p, Identifier &f, QWidget *parent)
    : QWidget(parent), Sizer(), _kernel(k), _proband(p), _family(f)
{
    _layout.setHorizontalSpacing(this->tightSpacing());
    _layout.setContentsMargins(0, this->mediumSpacing(), 0, 0);
    this->setLayout(&_layout);

    this->fill();

    // Connect add children
    connect(_boxChildren, &BoxChildren::newBoy, this, &PartnerWidget::addSon);
    connect(_boxChildren, &BoxChildren::newGirl, this, &PartnerWidget::addDaughter);
    connect(_boxChildren, &BoxChildren::newChild, this, &PartnerWidget::addChild);

    // Connect proband changed
    connect(_boxChildren, &BoxChildren::probandChanged, this, &PartnerWidget::probandChanged);
    connect(_boxMarriage, &BoxMarriage::probandChanged, this, &PartnerWidget::probandChanged);
    connect(_boxMarriage, &BoxMarriage::sourceChanged, this, &PartnerWidget::sourceChanged);
}

void PartnerWidget::update()
{
    auto children = _kernel.record()->getFamilyChildren(_family);
    _boxMarriage->update();
    _boxDivorce->update();
    _boxChildren->update(children);
}

Identifier PartnerWidget::getPartnerIdentifier() const
{
    // Partner is wife
    if(_kernel.record()->getIndividualGender(_proband) == Gender::MALE)
    {
        return _kernel.record()->getFamilyWife(_family);
    }
    // Partner is husband
    else
    {
        return _kernel.record()->getFamilyHusband(_family);
    }
}

Identifier PartnerWidget::getFamilyIdentifier() const
{
    return _family;
}

void PartnerWidget::addSon()
{
    QSettings settings;
    Identifier son = _kernel.record()->newIndividual();
    _kernel.record()->setIndividualDeceased(son, settings.value("dataConstraints/autoDead").toBool());
    _kernel.record()->setIndividualGender(son, Gender::MALE);
    Identifier father = _kernel.record()->getFamilyHusband(_family);
    QString lastname = _kernel.record()->getIndividualNameSurnameMarriedBirth(father);
    _kernel.record()->setIndividualNameSurname(son, lastname);
    _kernel.record()->setIndividualNameMarname(son, lastname);
    _kernel.record()->setFamilyChild(_family, son);
    emit(this->probandChanged(son));
}

void PartnerWidget::addDaughter()
{
    QSettings settings;
    Identifier daughter = _kernel.record()->newIndividual();
    _kernel.record()->setIndividualDeceased(daughter, settings.value("dataConstraints/autoDead").toBool());
    _kernel.record()->setIndividualGender(daughter, Gender::FEMALE);
    Identifier mother = _kernel.record()->getFamilyWife(_family);
    QString surname = _kernel.record()->getIndividualNameSurnameMarried(mother);
    _kernel.record()->setIndividualNameSurname(daughter, surname);
    _kernel.record()->setFamilyChild(_family, daughter);
    emit(this->probandChanged(daughter));
}

void PartnerWidget::addChild()
{
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
        _kernel.record()->setFamilyChild(_family, child);
        _boxChildren->update(_kernel.record()->getChildrenOfIndividual(_proband));
    }
    else if(result == DialogAssignPerson::Accepted
            && !_kernel.record()->isIndividual(child))
    {
        QSettings settings;
        child = _kernel.record()->newIndividual();
        _kernel.record()->setIndividualDeceased(child, settings.value("dataConstraints/autoDead").toBool());
        _kernel.record()->setFamilyChild(_family, child);
        emit(this->probandChanged(child));
    }
}

void PartnerWidget::fill()
{
    // Initialize
    _boxChildren = new BoxChildren(tr("Children"), _kernel, _proband);
    _boxMarriage = new BoxMarriage(tr("Married"), _kernel, _proband, _family);
    _boxDivorce = new BoxDivorce(tr("Divorced"), _kernel, _proband, _family);

    // Set static values

    // Set layout
    _layout.addWidget(_boxChildren, 0, 0);
    _layout.addWidget(_boxMarriage, 0, 1);
    _layout.addWidget(_boxDivorce, 0, 2);

    // Adjust layout positions
    _layout.setColumnStretch(0, 10);
    _layout.setColumnStretch(1, 15);
    _layout.setColumnStretch(2, 1);
}
