/*!
 *  \file   boxbirth.cpp
 *  \author Eva Navratilova
 */

#include "boxbirth.h"

/// TODO - on update date and place adjust source combobox - BUT DON'T DELETE current
/// source! -> that could lead to user being flabbergasted
/// same for !!!!!!!!!! DEATH & MARRIAGE !!!!!!!!!!

BoxBirth::BoxBirth(QString title, Kernel &k, Identifier &p, QWidget *parent)
    : Box(title, BOX_NOT_CHECKABLE, k, p, parent)
{
    this->fill();

    // Connect proband changed
    connect(_subboxObstetrix, &SubboxPersonRef::probandChanged, this, &BoxBirth::probandChanged);
    connect(_boxChristening, &BoxChristening::probandChanged, this, &BoxBirth::probandChanged);

    // Connect add/goto source
    connect(_subboxSource, &SubboxCitation::addSource, this, &BoxBirth::addSource);
    connect(_subboxSource, &SubboxCitation::gotoSource, this, &BoxBirth::sourceChanged);

    // Connect Data changed
    connect(_subboxDate, &SubboxDate::dateTypeChanged, this, &BoxBirth::changeDatetype);
    connect(_subboxDate, &SubboxDate::date1Changed, this, &BoxBirth::changeDate1);
    connect(_subboxDate, &SubboxDate::date2Changed, this, &BoxBirth::changeDate2);
    connect(_subboxPlace, &SubboxSimple::textChanged, this, &BoxBirth::changePlace);
    connect(_subboxSource, &SubboxCitation::sourceChanged, this, &BoxBirth::changeSourceRef);
    connect(_subboxSource, &SubboxCitation::pageChanged, this, &BoxBirth::changeSourcePage);
    connect(_subboxSource, &SubboxCitation::urlChanged, this, &BoxBirth::changeSourceUrl);

    // Connect Subbox button clicked
    connect(_subboxObstetrix, &SubboxPersonRef::addClicked, this, &BoxBirth::addObstetrix);
    connect(_subboxObstetrix, &SubboxPersonRef::removeClicked, this, &BoxBirth::removeObstetrix);

    // Connect update combo
    connect(_subboxSource, &SubboxCitation::updateCombo, this, &BoxBirth::update);
}

void BoxBirth::update()
{
    this->remove();

    // Initialize
    _comPlace = new CompleterInline(_kernel.record()->getStringsPlaces());

    // Get data
    DateType datetype = _kernel.record()->getIndividualBirthDateType(_proband);
    Date date1 = _kernel.record()->getIndividualBirthDate1(_proband);
    Date date2 = _kernel.record()->getIndividualBirthDate2(_proband);
    QString place = _kernel.record()->getIndividualBirthPlaceName(_proband);
    QVector<Identifier> sources = _kernel.record()->getSourceRefs(CommonEventType::BIRT, date1, place);
    Identifier sourceRef = _kernel.record()->getIndividualBirthSourceRef(_proband);
    QString page = _kernel.record()->getIndividualBirthSourceCitationPage(_proband);
    QString url = _kernel.record()->getIndividualBirthSourceCitationUrl(_proband);
    Identifier obstetrix = _kernel.record()->getIndividualBirthObstetrix(_proband);

    // Update
    _subboxDate->update(datetype, date1, date2);
    _subboxPlace->update(place);
    _subboxPlace->setCompleter(_comPlace);
    _subboxSource->update(_kernel, CommonEventType::BIRT, place, sources, sourceRef, page, url);
    _subboxObstetrix->update(obstetrix);

    _boxChristening->update();

    this->setSourceEnabled();
}

int BoxBirth::maxLabelWidth() const
{
    int width = _subboxDate->maxLabelWidth();
    if(width < _subboxPlace->maxLabelWidth())
    {
        width = _subboxPlace->maxLabelWidth();
    }
    if(width < _subboxObstetrix->maxLabelWidth())
    {
        width = _subboxObstetrix->maxLabelWidth();
    }
    return width;

}

void BoxBirth::setLabelsWidth(int width)
{
    _subboxDate->setLabelsWidth(width);
    _subboxPlace->setLabelsWidth(width);
    _subboxObstetrix->setLabelsWidth(width);
}

void BoxBirth::setSourceEnabled()
{
    DateType datetype = _kernel.record()->getIndividualBirthDateType(_proband);
    Date date1 = _kernel.record()->getIndividualBirthDate1(_proband);
    QString place = _kernel.record()->getIndividualBirthPlaceName(_proband);

    bool exactDate = (datetype == DateType::SIMPLE) && date1.isValid();
    bool enabled = exactDate && !place.isEmpty();

    _subboxSource->setEnabled(enabled);
}

void BoxBirth::changeDatetype(const DateType datetype)
{
    _kernel.record()->setIndividualBirthDateType(_proband, datetype);
    this->setSourceEnabled();
}

void BoxBirth::changeDate1(const Date date)
{
    _kernel.record()->setIndividualBirthDate1(_proband, date);
    // For the update of the ListView
    emit(this->dataChanged());
    this->setSourceEnabled();
}

void BoxBirth::changeDate2(const Date date)
{
    _kernel.record()->setIndividualBirthDate2(_proband, date);
}

void BoxBirth::changePlace(const QString plac)
{
    _kernel.record()->setIndividualBirthPlaceName(_proband, plac);
    this->setSourceEnabled();
}

void BoxBirth::changeSourceRef(const Identifier src)
{
    _kernel.record()->setIndividualBirthSourceCitationRef(_proband, src);
    this->update();
}

void BoxBirth::changeSourcePage(const QString page)
{
    _kernel.record()->setIndividualBirthSourceCitationPage(_proband, page);
}

void BoxBirth::changeSourceUrl(const QString url)
{
    _kernel.record()->setIndividualBirthSourceCitationUrl(_proband, url);
}

void BoxBirth::addObstetrix()
{
    QVector<Identifier> pers;
    Identifier first = _kernel.record()->getIdentifierIndividualFirst();
    Identifier last  = _kernel.record()->getIdentifierIndividualLast();
    for(Identifier current = first; current < last; _kernel.record()->getIdentifierIndividualNext(current))
    {
        if(current == _proband)
            continue;

        Gender genderCurrent = _kernel.record()->getIndividualGender(current);
        /// TODO - probably add alive check?
        if(genderCurrent == Gender::FEMALE)
        {
            pers.push_front(current);
        }
    }

    _dialogAddExistingPerson = new DialogAssignPerson(_kernel, pers);
    Identifier obst;
    int result = _dialogAddExistingPerson->getSelectedId(obst);
    if(_kernel.record()->isIndividual(obst))
    {
        _kernel.record()->setIndividualBirthObstetrix(_proband, obst);
        _subboxObstetrix->update(obst);
    }
    else if(result == DialogAssignPerson::Accepted
            && !_kernel.record()->isIndividual(obst))
    {
        QSettings settings;
        obst = _kernel.record()->newIndividual();
        _kernel.record()->setIndividualDeceased(obst, settings.value("dataConstraints/autoDead").toBool());
        _kernel.record()->setIndividualGender(obst, Gender::FEMALE);
        _kernel.record()->setIndividualBirthObstetrix(_proband, obst);
        emit(this->probandChanged(obst));
    }
}

void BoxBirth::removeObstetrix()
{
    _kernel.record()->setIndividualBirthObstetrix(_proband, Identifier());
    _subboxObstetrix->update(_kernel.record()->getIndividualBirthObstetrix(_proband));
}

void BoxBirth::addSource()
{
    Identifier src = _kernel.record()->newSource();
    QString plac = _kernel.record()->getIndividualBirthPlaceName(_proband);
    _kernel.record()->setSourceData(src, CommonEventType::BIRT);
    _kernel.record()->setSourceDataPlac(src, CommonEventType::BIRT, 0, plac);

    _kernel.record()->setIndividualBirthSourceCitationRef(_proband, src);
    emit(this->sourceChanged(src));
}

void BoxBirth::fill()
{
    // Initialize items
    _subboxDate = new SubboxDate(tr("Date of Birth"), DateTypeAvailability::NoPeriod, this);
    _subboxPlace = new SubboxSimple(tr("Place of Birth"), this);
    _subboxSource = new SubboxCitation(this);
    _subboxObstetrix = new SubboxPersonRef(_strMidwife, _kernel, this);

    _boxChristening = new BoxChristening(tr("Christening"), _kernel, _proband, this);

    _spacer = new QSpacerItem(0, this->mediumSpacing(), QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Set static text

    // Set layout
    _layout.addWidget(_subboxDate, 0, 0);
    _layout.addWidget(_subboxPlace, 1, 0);
    _layout.addWidget(_subboxObstetrix, 2, 0);
    _layout.addWidget(_subboxSource, 0, 1, 3, 1);
    _layout.addItem(_spacer, 3, 0, 1, 2);
    _layout.addWidget(_boxChristening, 4, 0, 1, 2);

    // Adjust
    this->adjustLabelsWidth();
    _layout.setColumnStretch(0, 1);
    _layout.setColumnStretch(1, 1);
}

void BoxBirth::remove()
{
    if(_comPlace != nullptr)
    {
        _comPlace->deleteLater();
        _comPlace = nullptr;
    }
}
