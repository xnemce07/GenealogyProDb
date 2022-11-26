/*!
 *  \file   boxparents.cpp
 *  \author Eva Navratilova
 */

#include "boxparents.h"

BoxParents::BoxParents(QString title, Kernel &k, Identifier &p, QWidget *parent)
    : Box(title, BOX_NOT_CHECKABLE, k, p, parent)
{
    this->fill();

    // Connect proband changed
    connect(_subboxFather, &SubboxPersonRef::probandChanged, this, &BoxParents::probandChanged);
    connect(_subboxMother, &SubboxPersonRef::probandChanged, this, &BoxParents::probandChanged);

    // Connect person button clicked
    connect(_subboxFather, &SubboxPersonRef::addClicked, this, &BoxParents::addFather);
    connect(_subboxFather, &SubboxPersonRef::removeClicked, this, &BoxParents::removeFather);
    connect(_subboxMother, &SubboxPersonRef::addClicked, this, &BoxParents::addMother);
    connect(_subboxMother, &SubboxPersonRef::removeClicked, this, &BoxParents::removeMother);
}

void BoxParents::update()
{
    Identifier father = _kernel.record()->getIndividualFather(_proband);
    Identifier mother = _kernel.record()->getIndividualMother(_proband);
    _subboxFather->update(father);
    _subboxMother->update(mother);
}

void BoxParents::fill()
{
    // Initialize
    _subboxFather = new SubboxPersonRef(tr("Father"), _kernel, this);
    _subboxMother = new SubboxPersonRef(tr("Mother"), _kernel, this);

    // Set layout
    _layout.addWidget(_subboxFather, 0, 0);
    _layout.addWidget(_subboxMother, 1, 0);

    // Adjust
    this->adjustLabelsWidth();
}

int BoxParents::maxLabelWidth() const
{
    int width = _subboxFather->maxLabelWidth();
    if(width < _subboxMother->maxLabelWidth())
    {
        width = _subboxMother->maxLabelWidth();
    }
    return width;
}

void BoxParents::setLabelsWidth(int width)
{
    _subboxFather->setLabelsWidth(width);
    _subboxMother->setLabelsWidth(width);
}

void BoxParents::addFather()
{
    Identifier father;
    QVector<Identifier> pers;
    QVector<Identifier> children = _kernel.record()->getIndividualDescendants(_proband);

    Identifier first = _kernel.record()->getIdentifierIndividualFirst();
    Identifier last  = _kernel.record()->getIdentifierIndividualLast();
    for(Identifier current = first; current < last; _kernel.record()->getIdentifierIndividualNext(current))
    {
        if(current == _proband)
            continue;
        if(children.contains(current))
            continue;

        Gender genderCurrent = _kernel.record()->getIndividualGender(current);
        /// TODO - probably add alive check?
        if(genderCurrent == Gender::MALE)
        {
            pers.push_front(current);
        }
    }

    _dialogAddExistingPerson = new DialogAssignPerson(_kernel, pers);
    int result = _dialogAddExistingPerson->getSelectedId(father);
    if(_kernel.record()->isIndividual(father))
    {
        _kernel.record()->setIndividualFather(_proband, father);
        _subboxFather->update(father);
    }
    else if(result == DialogAssignPerson::Accepted
            && !_kernel.record()->isIndividual(father))
    {
        QSettings settings;
        father = _kernel.record()->newIndividual();
        _kernel.record()->setIndividualDeceased(father, settings.value("dataConstraints/autoDead").toBool());
        _kernel.record()->setIndividualGender(father, Gender::MALE);
        _kernel.record()->setIndividualFather(_proband, father);
        if(_kernel.record()->getIndividualGender(_proband) == Gender::MALE)
        {
            QString surname = _kernel.record()->getIndividualNameSurnameMarriedBirth(_proband);
            _kernel.record()->setIndividualNameSurname(father, surname);
            _kernel.record()->setIndividualNameMarname(father, surname);
        }
        emit(this->probandChanged(father));
    }
}

void BoxParents::removeFather()
{
    _kernel.record()->setIndividualFather(_proband, Identifier());
    _subboxFather->update(Identifier());
}

void BoxParents::addMother()
{
    Identifier mother;
    QVector<Identifier> pers;
    QVector<Identifier> children = _kernel.record()->getIndividualDescendants(_proband);

    Identifier first = _kernel.record()->getIdentifierIndividualFirst();
    Identifier last  = _kernel.record()->getIdentifierIndividualLast();
    for(Identifier current = first; current < last; _kernel.record()->getIdentifierIndividualNext(current))
    {
        if(current == _proband)
            continue;
        if(children.contains(current))
            continue;

        Gender genderCurrent = _kernel.record()->getIndividualGender(current);
        /// TODO - probably add alive check?
        if(genderCurrent == Gender::FEMALE)
        {
            pers.push_front(current);
        }
    }

    _dialogAddExistingPerson = new DialogAssignPerson(_kernel, pers);
    int result = _dialogAddExistingPerson->getSelectedId(mother);
    if(_kernel.record()->isIndividual(mother))
    {
        _kernel.record()->setIndividualMother(_proband, mother);
        _subboxMother->update(mother);
    }
    else if(result == DialogAssignPerson::Accepted
            && !_kernel.record()->isIndividual(mother))
    {
        QSettings settings;
        mother = _kernel.record()->newIndividual();
        _kernel.record()->setIndividualDeceased(mother, settings.value("dataConstraints/autoDead").toBool());
        _kernel.record()->setIndividualGender(mother, Gender::FEMALE);
        _kernel.record()->setIndividualMother(_proband, mother);
        if(_kernel.record()->getIndividualGender(_proband) == Gender::FEMALE)
        {
            QString surname = _kernel.record()->getIndividualNameSurnameBirth(_proband);
            _kernel.record()->setIndividualNameMarname(mother, surname);
        }
        emit(this->probandChanged(mother));
    }
}

void BoxParents::removeMother()
{
    _kernel.record()->setIndividualMother(_proband, Identifier());
    _subboxMother->update(Identifier());
}

