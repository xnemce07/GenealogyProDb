/*!
 *  \file   boxchristening.cpp
 *  \author Eva Navratilova
 */

#include "boxchristening.h"

BoxChristening::BoxChristening(QString title, Kernel &k, Identifier &p, QWidget *parent)
    : Box(title, BOX_NOT_CHECKABLE, k, p, parent)
{
    this->fill();

    // Connect proband changed
    connect(_subboxPriest, &SubboxPersonRef::probandChanged, this, &BoxChristening::probandChanged);
    connect(_subboxGodfather, &SubboxPersonRef::probandChanged, this, &BoxChristening::probandChanged);
    connect(_subboxGodmother, &SubboxPersonRef::probandChanged, this, &BoxChristening::probandChanged);

    // Connect data changed
    connect(_subboxDate, &SubboxDate::dateTypeChanged, this, &BoxChristening::changeDatetype);
    connect(_subboxDate, &SubboxDate::date1Changed, this, &BoxChristening::changeDate1);
    connect(_subboxDate, &SubboxDate::date2Changed, this, &BoxChristening::changeDate2);

    // Connect Subbox button clicked
    connect(_subboxPriest, &SubboxPersonRef::addClicked, this, &BoxChristening::addPriest);
    connect(_subboxPriest, &SubboxPersonRef::removeClicked, this, &BoxChristening::removePriest);
    connect(_subboxGodfather, &SubboxPersonRef::addClicked, this, &BoxChristening::addGodfather);
    connect(_subboxGodfather, &SubboxPersonRef::removeClicked, this, &BoxChristening::removeGodfather);
    connect(_subboxGodmother, &SubboxPersonRef::addClicked, this, &BoxChristening::addGodmother);
    connect(_subboxGodmother, &SubboxPersonRef::removeClicked, this, &BoxChristening::removeGodmother);
}

void BoxChristening::update()
{
    // Get data
    DateType datetype = _kernel.record()->getIndividualChristeningDateType(_proband);
    Date date1 = _kernel.record()->getIndividualChristeningDate1(_proband);
    Date date2 = _kernel.record()->getIndividualChristeningDate2(_proband);
    Identifier priest = _kernel.record()->getIndividualChristeningPriest(_proband);
    Identifier godfather = _kernel.record()->getIndividualChristeningGodfather(_proband);
    Identifier godmother = _kernel.record()->getIndividualChristeningGodmother(_proband);

    // Update
    _subboxDate->update(datetype, date1, date2);
    _subboxPriest->update(priest);
    _subboxGodfather->update(godfather);
    _subboxGodmother->update(godmother);
}

void BoxChristening::fill()
{
    _subboxDate = new SubboxDate(tr("Date of Christening"), DateTypeAvailability::NoPeriod, this);
    _subboxPriest = new SubboxPersonRef(_strPriest, _kernel, this);
    _subboxGodfather = new SubboxPersonRef(_strGodfather, _kernel, this);
    _subboxGodmother = new SubboxPersonRef(_strGodmother, _kernel, this);

    // Set layout
    _layout.addWidget(_subboxDate, 0, 0);
    _layout.addWidget(_subboxPriest, 1, 0);
    _layout.addWidget(_subboxGodfather, 2, 0);
    _layout.addWidget(_subboxGodmother, 3, 0);

    // Adjust
    this->adjustLabelsWidth();
}

int BoxChristening::maxLabelWidth() const
{
    int width = _subboxDate->maxLabelWidth();
    if(width < _subboxPriest->maxLabelWidth())
    {
        width = _subboxPriest->maxLabelWidth();
    }
    if(width < _subboxGodfather->maxLabelWidth())
    {
        width = _subboxGodfather->maxLabelWidth();
    }
    if(width < _subboxGodmother->maxLabelWidth())
    {
        width = _subboxGodmother->maxLabelWidth();
    }
    return width;
}

void BoxChristening::setLabelsWidth(int width)
{
    _subboxDate->setLabelsWidth(width);
    _subboxPriest->setLabelsWidth(width);
    _subboxGodfather->setLabelsWidth(width);
    _subboxGodmother->setLabelsWidth(width);
}

void BoxChristening::changeDatetype(const DateType datetype)
{
    _kernel.record()->setIndividualChristeningDateType(_proband, datetype);
}

void BoxChristening::changeDate1(const Date date)
{
    _kernel.record()->setIndividualChristeningDate1(_proband, date);
}

void BoxChristening::changeDate2(const Date date)
{
    _kernel.record()->setIndividualChristeningDate2(_proband, date);
}

void BoxChristening::addPriest()
{
    QVector<Identifier> pers;
    Identifier first = _kernel.record()->getIdentifierIndividualFirst();
    Identifier last  = _kernel.record()->getIdentifierIndividualLast();
    Identifier midwife = _kernel.record()->getIndividualBirthObstetrix(_proband);
    for(Identifier current = first; current < last; _kernel.record()->getIdentifierIndividualNext(current))
    {
        if(current == _proband)
            continue;

        Gender genderCurrent = _kernel.record()->getIndividualGender(current);
        /// TODO - probably add alive check?
        if(genderCurrent == Gender::MALE)
        {
            pers.push_front(current);
        }
    }
    if(_kernel.record()->isIndividual(midwife))
    {
        pers.push_front(midwife);
    }

    _dialogAddExistingPerson = new DialogAssignPerson(_kernel, pers);
    Identifier priest;
    int result = _dialogAddExistingPerson->getSelectedId(priest);
    if(_kernel.record()->isIndividual(priest))
    {
        _kernel.record()->setIndividualChristeningPriest(_proband, priest);
        _subboxPriest->update(priest);
    }
    else if(result == DialogAssignPerson::Accepted
            && !_kernel.record()->isIndividual(priest))
    {
        QSettings settings;
        priest = _kernel.record()->newIndividual();
        _kernel.record()->setIndividualDeceased(priest, settings.value("dataConstraints/autoDead").toBool());
        _kernel.record()->setIndividualGender(priest, Gender::MALE);
        _kernel.record()->setIndividualChristeningPriest(_proband, priest);
        emit(this->probandChanged(priest));
    }
}

void BoxChristening::removePriest()
{
    _kernel.record()->setIndividualChristeningPriest(_proband, Identifier());
    _subboxPriest->update(Identifier());
}

void BoxChristening::addGodfather()
{
    QVector<Identifier> pers;
    Identifier first = _kernel.record()->getIdentifierIndividualFirst();
    Identifier last  = _kernel.record()->getIdentifierIndividualLast();
    Identifier godmother = _kernel.record()->getIndividualChristeningGodmother(_proband);
    for(Identifier current = first; current < last; _kernel.record()->getIdentifierIndividualNext(current))
    {
        if(current == _proband)
            continue;
        if(current == godmother)
            continue;

        /// TODO - probably add alive check?
        pers.push_front(current);
    }

    _dialogAddExistingPerson = new DialogAssignPerson(_kernel, pers);
    Identifier godfather;
    int result = _dialogAddExistingPerson->getSelectedId(godfather);
    if(_kernel.record()->isIndividual(godfather))
    {
        _kernel.record()->setIndividualChristeningGodfather(_proband, godfather);
        _subboxGodfather->update(godfather);
    }
    else if(result == DialogAssignPerson::Accepted
            && !_kernel.record()->isIndividual(godfather))
    {
        QSettings settings;
        godfather = _kernel.record()->newIndividual();
        _kernel.record()->setIndividualDeceased(godfather, settings.value("dataConstraints/autoDead").toBool());
        _kernel.record()->setIndividualGender(godfather, Gender::MALE);
        _kernel.record()->setIndividualChristeningGodfather(_proband, godfather);
        emit(this->probandChanged(godfather));
    }
}

void BoxChristening::removeGodfather()
{
    _kernel.record()->setIndividualChristeningGodfather(_proband, Identifier());
    _subboxGodfather->update(Identifier());
}

void BoxChristening::addGodmother()
{
    QVector<Identifier> pers;
    Identifier first = _kernel.record()->getIdentifierIndividualFirst();
    Identifier last  = _kernel.record()->getIdentifierIndividualLast();
    Identifier godfather = _kernel.record()->getIndividualChristeningGodfather(_proband);
    for(Identifier current = first; current < last; _kernel.record()->getIdentifierIndividualNext(current))
    {
        if(current == _proband)
            continue;
        if(current == godfather)
            continue;

        /// TODO - probably add alive check?
        pers.push_front(current);
    }

    _dialogAddExistingPerson = new DialogAssignPerson(_kernel, pers);
    Identifier godmother;
    int result = _dialogAddExistingPerson->getSelectedId(godmother);
    if(_kernel.record()->isIndividual(godmother))
    {
        _kernel.record()->setIndividualChristeningGodmother(_proband, godmother);
        _subboxGodmother->update(godmother);
    }
    else if(result == DialogAssignPerson::Accepted
            && !_kernel.record()->isIndividual(godmother))
    {
        QSettings settings;
        godmother = _kernel.record()->newIndividual();
        _kernel.record()->setIndividualDeceased(godmother, settings.value("dataConstraints/autoDead").toBool());
        _kernel.record()->setIndividualGender(godmother, Gender::FEMALE);
        _kernel.record()->setIndividualChristeningGodmother(_proband, godmother);
        emit(this->probandChanged(godmother));
    }
}

void BoxChristening::removeGodmother()
{
    _kernel.record()->setIndividualChristeningGodmother(_proband, Identifier());
    _subboxGodmother->update(Identifier());
}

