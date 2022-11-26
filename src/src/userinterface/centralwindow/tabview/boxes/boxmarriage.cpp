/*!
 *  \file   boxmarriage.cpp
 *  \author Eva Navratilova
 */

#include "boxmarriage.h"

BoxMarriage::BoxMarriage(QString title, Kernel &k, Identifier &p, Identifier &f, QWidget *parent)
    : Box(title, BOX_CHECKABLE, k, p, parent), _family(f)
{
    this->fill();

    // Connect proband changed
    connect(_subboxPriest, &SubboxPersonRef::probandChanged, this, &BoxMarriage::probandChanged);
    connect(_subboxWitness1, &SubboxPersonRef::probandChanged, this, &BoxMarriage::probandChanged);
    connect(_subboxWitness2, &SubboxPersonRef::probandChanged, this, &BoxMarriage::probandChanged);

    // Connect add/goto source
    connect(_subboxSource, &SubboxCitation::addSource, this, &BoxMarriage::addSource);
    connect(_subboxSource, &SubboxCitation::gotoSource, this, &BoxMarriage::sourceChanged);

    // Connect data changed
    connect(this, &BoxMarriage::clicked, this, &BoxMarriage::changeMarriageState);

    connect(_subboxDate, &SubboxDate::dateTypeChanged, this, &BoxMarriage::changeDatetype);
    connect(_subboxDate, &SubboxDate::date1Changed, this, &BoxMarriage::changeDate1);
    connect(_subboxDate, &SubboxDate::date2Changed, this, &BoxMarriage::changeDate2);
    connect(_subboxPlace, &SubboxSimple::textChanged, this, &BoxMarriage::changePlace);
    connect(_subboxSource, &SubboxCitation::sourceChanged, this, &BoxMarriage::changeSourceRef);
    connect(_subboxSource, &SubboxCitation::pageChanged, this, &BoxMarriage::changeSourcePage);
    connect(_subboxSource, &SubboxCitation::urlChanged, this, &BoxMarriage::changeSourceUrl);

    // Connect Subbox button clicked
    connect(_subboxPriest, &SubboxPersonRef::addClicked, this, &BoxMarriage::addPriest);
    connect(_subboxPriest, &SubboxPersonRef::removeClicked, this, &BoxMarriage::removePriest);
    connect(_subboxWitness1, &SubboxPersonRef::addClicked, this, &BoxMarriage::addWitness1);
    connect(_subboxWitness1, &SubboxPersonRef::removeClicked, this, &BoxMarriage::removeWitness1);
    connect(_subboxWitness2, &SubboxPersonRef::addClicked, this, &BoxMarriage::addWitness2);
    connect(_subboxWitness2, &SubboxPersonRef::removeClicked, this, &BoxMarriage::removeWitness2);

    // Connect update combo
    connect(_subboxSource, &SubboxCitation::updateCombo, this, &BoxMarriage::update);
}

void BoxMarriage::update()
{
    this->remove();

    // Initialize
    _comPlace = new CompleterInline(_kernel.record()->getStringsPlaces());

    // Initialize values
    bool married = _kernel.record()->isFamilyMarried(_family);
    DateType datetype = _kernel.record()->getFamilyMarriageDateType(_family);
    Date date1 = _kernel.record()->getFamilyMarriageDate1(_family);
    Date date2 = _kernel.record()->getFamilyMarriageDate2(_family);
    QString place = _kernel.record()->getFamilyMarriagePlaceName(_family);
    QVector<Identifier> sources = _kernel.record()->getSourceRefs(CommonEventType::MARR, date1, place);
    Identifier sourceRef = _kernel.record()->getFamilyMarriageSourceRef(_family);
    QString page = _kernel.record()->getFamilyMarriageSourceCitationPage(_family);
    QString url = _kernel.record()->getFamilyMarriageSourceCitationUrl(_family);
    Identifier priest = _kernel.record()->getFamilyMarriagePriest(_family);
    Identifier witness1 = _kernel.record()->getFamilyMarriageWitness1(_family);
    Identifier witness2 = _kernel.record()->getFamilyMarriageWitness2(_family);

    // Set new values
    this->setChecked(married);
    _subboxDate->update(datetype, date1, date2);
    _subboxPlace->update(place);
    _subboxPlace->setCompleter(_comPlace);
    _subboxSource->update(_kernel, CommonEventType::MARR, place, sources, sourceRef, page, url);
    _subboxPriest->update(priest);
    _subboxWitness1->update(witness1);
    _subboxWitness2->update(witness2);

    this->setSourceEnabled();
}

int BoxMarriage::maxLabelWidth() const
{
    QFont font;
    QFontMetrics fontMetrics(font);
    int width = fontMetrics.horizontalAdvance(_subboxDate->maxLabelWidth());
    if(width < _subboxPlace->maxLabelWidth())
    {
        width = _subboxPlace->maxLabelWidth();
    }
    if(width < _subboxPriest->maxLabelWidth())
    {
        width = _subboxPriest->maxLabelWidth();
    }
    if(width < _subboxWitness1->maxLabelWidth())
    {
        width = _subboxWitness1->maxLabelWidth();
    }
    if(width < _subboxWitness2->maxLabelWidth())
    {
        width = _subboxWitness2->maxLabelWidth();
    }
    return width;
}

void BoxMarriage::setLabelsWidth(int width)
{
    _subboxDate->setLabelsWidth(width);
    _subboxPlace->setLabelsWidth(width);
    _subboxPriest->setLabelsWidth(width);
    _subboxWitness1->setLabelsWidth(width);
    _subboxWitness2->setLabelsWidth(width);
}

void BoxMarriage::fill()
{
    // Initialize
    _subboxDate = new SubboxDate(tr("Wedding Date"), DateTypeAvailability::NoPeriod, this);
    _subboxPlace = new SubboxSimple(tr("Wedding Place"), this);
    _subboxSource = new SubboxCitation(this);
    _subboxPriest = new SubboxPersonRef(_strPriest, _kernel, this);
    _subboxWitness1 = new SubboxPersonRef(_strWitness1, _kernel, this);
    _subboxWitness2 = new SubboxPersonRef(_strWitness2, _kernel, this);

    _spacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);

    // Set static values

    // Set layout
    _layout.addWidget(_subboxDate, 0, 0);
    _layout.addWidget(_subboxPlace, 1, 0);
    _layout.addWidget(_subboxPriest, 2, 0);
    _layout.addWidget(_subboxWitness1, 3, 0);
    _layout.addWidget(_subboxWitness2, 4, 0);
    _layout.addItem(_spacer, 5, 0);
    _layout.addWidget(_subboxSource, 0, 1, 6, 1);

    // Adjust widgets
    this->adjustLabelsWidth();
    _layout.setColumnStretch(0, 1);
    _layout.setColumnStretch(1, 1);
}

void BoxMarriage::remove()
{
    if(_comPlace != nullptr)
    {
        _comPlace->deleteLater();
        _comPlace = nullptr;
    }
}

void BoxMarriage::setSourceEnabled()
{
    DateType datetype = _kernel.record()->getFamilyMarriageDateType(_family);
    Date date1 = _kernel.record()->getFamilyMarriageDate1(_family);
    QString place = _kernel.record()->getFamilyMarriagePlaceName(_family);

    bool exactDate = (datetype == DateType::SIMPLE) && date1.isValid();
    _subboxSource->setEnabled(exactDate && !place.isEmpty());
}

void BoxMarriage::changeMarriageState(bool checked)
{
    _kernel.record()->setFamilyMarried(_family, checked);
}

void BoxMarriage::changeDatetype(const DateType datetype)
{
    _kernel.record()->setFamilyMarriageDateType(_family, datetype);
    this->setSourceEnabled();
}

void BoxMarriage::changeDate1(const Date date)
{
    _kernel.record()->setFamilyMarriageDate1(_family, date);
    this->setSourceEnabled();
}

void BoxMarriage::changeDate2(const Date date)
{
    _kernel.record()->setFamilyMarriageDate2(_family, date);
}

void BoxMarriage::changePlace(const QString plac)
{
    _kernel.record()->setFamilyMarriagePlaceName(_family, plac);
    this->setSourceEnabled();
}

void BoxMarriage::changeSourceRef(const Identifier src)
{
    _kernel.record()->setFamilyMarriageSourceCitationRef(_family, src);
    this->update();
}

void BoxMarriage::changeSourcePage(const QString page)
{
    _kernel.record()->setFamilyMarriageSourceCitationPage(_family, page);
}

void BoxMarriage::changeSourceUrl(const QString url)
{
    _kernel.record()->setFamilyMarriageSourceCitationUrl(_family, url);
}

void BoxMarriage::addPriest()
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
        _kernel.record()->setFamilyMarriagePriest(_family, priest);
        _subboxPriest->update(priest);
    }
    else if(result == DialogAssignPerson::Accepted
            && !_kernel.record()->isIndividual(priest))
    {
        QSettings settings;
        priest = _kernel.record()->newIndividual();
        _kernel.record()->setIndividualDeceased(priest, settings.value("dataConstraints/autoDead").toBool());
        _kernel.record()->setIndividualGender(priest, Gender::MALE);
        _kernel.record()->setFamilyMarriagePriest(_family, priest);
        emit(this->probandChanged(priest));
    }
}

void BoxMarriage::removePriest()
{
    _kernel.record()->setFamilyMarriagePriest(_family, Identifier());
    _subboxPriest->update(Identifier());
}

void BoxMarriage::addWitness1()
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
    Identifier witness1;
    int result = _dialogAddExistingPerson->getSelectedId(witness1);
    if(_kernel.record()->isIndividual(witness1))
    {
        _kernel.record()->setFamilyMarriageWitness1(_family, witness1);
        _subboxWitness1->update(witness1);
    }
    else if(result == DialogAssignPerson::Accepted
            && !_kernel.record()->isIndividual(witness1))
    {
        QSettings settings;
        witness1 = _kernel.record()->newIndividual();
        _kernel.record()->setIndividualDeceased(witness1, settings.value("dataConstraints/autoDead").toBool());
        _kernel.record()->setIndividualGender(witness1, Gender::MALE);
        _kernel.record()->setFamilyMarriageWitness1(_family, witness1);
        emit(this->probandChanged(witness1));
    }
}

void BoxMarriage::removeWitness1()
{
    _kernel.record()->setFamilyMarriageWitness1(_family, Identifier());
    _subboxWitness1->update(Identifier());
}

void BoxMarriage::addWitness2()
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
    Identifier witness2;
    int result = _dialogAddExistingPerson->getSelectedId(witness2);
    if(_kernel.record()->isIndividual(witness2))
    {
        _kernel.record()->setFamilyMarriageWitness2(_family, witness2);
        _subboxWitness2->update(witness2);
    }
    else if(result == DialogAssignPerson::Accepted
            && !_kernel.record()->isIndividual(witness2))
    {
        QSettings settings;
        witness2 = _kernel.record()->newIndividual();
        _kernel.record()->setIndividualDeceased(witness2, settings.value("dataConstraints/autoDead").toBool());
        _kernel.record()->setIndividualGender(witness2, Gender::MALE);
        _kernel.record()->setFamilyMarriageWitness2(_family, witness2);
        emit(this->probandChanged(witness2));
    }
}

void BoxMarriage::removeWitness2()
{
    _kernel.record()->setFamilyMarriageWitness2(_family, Identifier());
    _subboxWitness2->update(Identifier());
}

void BoxMarriage::addSource()
{
    Identifier src = _kernel.record()->newSource();
    QString plac = _kernel.record()->getFamilyMarriagePlaceName(_proband);
    _kernel.record()->setSourceData(src, CommonEventType::MARR);
    _kernel.record()->setSourceDataPlac(src, CommonEventType::MARR, 0, plac);

    _kernel.record()->setFamilyMarriageSourceCitationRef(_family, src);
    emit(this->sourceChanged(src));
}

