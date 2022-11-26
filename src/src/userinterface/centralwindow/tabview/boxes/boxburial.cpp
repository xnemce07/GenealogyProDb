/*!
 *  \file   boxburial.cpp
 *  \author Eva Navratilova
 */

#include "boxburial.h"

BoxBurial::BoxBurial(QString title, Kernel &k, Identifier &p, QWidget *parent)
    : Box(title, BOX_NOT_CHECKABLE, k, p, parent)
{
    this->fill();

    // Connect proband changed
    connect(_subboxPriest, &SubboxPersonRef::probandChanged, this, &BoxBurial::probandChanged);

    // Connect data changed
    connect(_subboxDate, &SubboxDate::dateTypeChanged, this, &BoxBurial::changeDatetype);
    connect(_subboxDate, &SubboxDate::date1Changed, this, &BoxBurial::changeDate1);
    connect(_subboxDate, &SubboxDate::date2Changed, this, &BoxBurial::changeDate2);
    connect(_subboxPlace, &SubboxSimple::textChanged, this, &BoxBurial::changePlace);

    // Connect Subbox button clicked
    connect(_subboxPriest, &SubboxPersonRef::addClicked, this, &BoxBurial::addPriest);
    connect(_subboxPriest, &SubboxPersonRef::removeClicked, this, &BoxBurial::removePriest);
}

void BoxBurial::update()
{
    this->remove();

    // Initialize
    _comPlace = new CompleterInline(_kernel.record()->getStringsPlaces());

    // Get data
    DateType datetype = _kernel.record()->getIndividualBurialDateType(_proband);
    Date date1 = _kernel.record()->getIndividualBurialDate1(_proband);
    Date date2 = _kernel.record()->getIndividualBurialDate2(_proband);
    QString place = _kernel.record()->getIndividualBurialPlaceName(_proband);
    Identifier priest = _kernel.record()->getIndividualBurialPriest(_proband);

    // Update
    _subboxDate->update(datetype, date1, date2);
    _subboxPlace->update(place);
    _subboxPlace->setCompleter(_comPlace);
    _subboxPriest->update(priest);
}

void BoxBurial::fill()
{
    // Initialize items
    _subboxDate = new SubboxDate(tr("Date of Burial"), DateTypeAvailability::NoPeriod, this);
    _subboxPlace = new SubboxSimple(tr("Place of Burial"), this);
    _subboxPriest = new SubboxPersonRef(_strPriest, _kernel, this);

    // Set static text

    // Set layout
    _layout.addWidget(_subboxDate, 0, 0);
    _layout.addWidget(_subboxPlace, 1, 0);
    _layout.addWidget(_subboxPriest, 2, 0);

    // Adjust
    this->adjustLabelsWidth();
}

void BoxBurial::remove()
{
    if(_comPlace != nullptr)
    {
        _comPlace->deleteLater();
        _comPlace = nullptr;
    }
}

int BoxBurial::maxLabelWidth() const
{
    int width = _subboxDate->maxLabelWidth();
    if(width < _subboxPlace->maxLabelWidth())
    {
        width = _subboxPlace->maxLabelWidth();
    }
    if(width < _subboxPriest->maxLabelWidth())
    {
        width = _subboxPriest->maxLabelWidth();
    }
    return width;
}

void BoxBurial::setLabelsWidth(int width)
{
    _subboxDate->setLabelsWidth(width);
    _subboxPlace->setLabelsWidth(width);
    _subboxPriest->setLabelsWidth(width);
}

void BoxBurial::changeDatetype(const DateType datetype)
{
    _kernel.record()->setIndividualBurialDateType(_proband, datetype);
}

void BoxBurial::changeDate1(const Date date)
{
    _kernel.record()->setIndividualBurialDate1(_proband, date);
}

void BoxBurial::changeDate2(const Date date)
{
    _kernel.record()->setIndividualBurialDate2(_proband, date);
}

void BoxBurial::changePlace(const QString plac)
{
    _kernel.record()->setIndividualBurialPlaceName(_proband, plac);
}

void BoxBurial::addPriest()
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
        if(genderCurrent == Gender::MALE)
        {
            pers.push_front(current);
        }
    }

    _dialogAddExistingPerson = new DialogAssignPerson(_kernel, pers);
    Identifier priest;
    int result = _dialogAddExistingPerson->getSelectedId(priest);
    if(_kernel.record()->isIndividual(priest))
    {
        _kernel.record()->setIndividualBurialPriest(_proband, priest);
        _subboxPriest->update(priest);
    }
    else if(result == DialogAssignPerson::Accepted
            && !_kernel.record()->isIndividual(priest))
    {
        QSettings settings;
        priest = _kernel.record()->newIndividual();
        _kernel.record()->setIndividualDeceased(priest, settings.value("dataConstraints/autoDead").toBool());
        _kernel.record()->setIndividualGender(priest, Gender::MALE);
        _kernel.record()->setIndividualBurialPriest(_proband, priest);
        emit(this->probandChanged(priest));
    }
}

void BoxBurial::removePriest()
{
    _kernel.record()->setIndividualBurialPriest(_proband, Identifier());
    _subboxPriest->update(Identifier());
}
