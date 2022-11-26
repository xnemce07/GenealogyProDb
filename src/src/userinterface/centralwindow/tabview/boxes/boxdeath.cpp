/*!
 *  \file   boxdeath.cpp
 *  \author Eva Navratilova
 */

#include "boxdeath.h"

BoxDeath::BoxDeath(QString title, Kernel &k, Identifier &p, QWidget *parent)
    : Box(title, BOX_CHECKABLE, k, p, parent)
{
    this->fill();

    // Connect proband changed
    connect(_boxBurial, &BoxBurial::probandChanged, this, &BoxDeath::probandChanged);

    // Connect add/goto source
    connect(_subboxSource, &SubboxCitation::addSource, this, &BoxDeath::addSource);
    connect(_subboxSource, &SubboxCitation::gotoSource, this, &BoxDeath::sourceChanged);

    // Connect data changed
    connect(this, &BoxDeath::clicked, this, &BoxDeath::changeDeathState);

    connect(_subboxDate, &SubboxDate::dateTypeChanged, this, &BoxDeath::changeDatetype);
    connect(_subboxDate, &SubboxDate::date1Changed, this, &BoxDeath::changeDate1);
    connect(_subboxDate, &SubboxDate::date2Changed, this, &BoxDeath::changeDate2);
    connect(_subboxPlace, &SubboxSimple::textChanged, this, &BoxDeath::changePlace);
    connect(_subboxCause, &SubboxSimple::textChanged, this, &BoxDeath::changeCause);
    connect(_subboxSource, &SubboxCitation::sourceChanged, this, &BoxDeath::changeSourceRef);
    connect(_subboxSource, &SubboxCitation::pageChanged, this, &BoxDeath::changeSourcePage);
    connect(_subboxSource, &SubboxCitation::urlChanged, this, &BoxDeath::changeSourceUrl);

    // Connect update combo
    connect(_subboxSource, &SubboxCitation::updateCombo, this, &BoxDeath::update);
}

void BoxDeath::update()
{
    this->remove();

    // Initialize
    _comPlace = new CompleterInline(_kernel.record()->getStringsPlaces());
    _comCause = new CompleterInline(_kernel.record()->getStringsDeathCause());

    // Get data
    DateType datetype = _kernel.record()->getIndividualDeathDateType(_proband);
    Date date1 = _kernel.record()->getIndividualDeathDate1(_proband);
    Date date2 = _kernel.record()->getIndividualDeathDate2(_proband);
    QString place = _kernel.record()->getIndividualDeathPlaceName(_proband);
    QString cause = _kernel.record()->getIndividualDeathCause(_proband);
    QVector<Identifier> sources = _kernel.record()->getSourceRefs(CommonEventType::DEAT, date1, place);
    Identifier sourceRef = _kernel.record()->getIndividualDeathSourceRef(_proband);
    QString page = _kernel.record()->getIndividualDeathSourceCitationPage(_proband);
    QString url = _kernel.record()->getIndividualDeathSourceCitationUrl(_proband);

    // Update
    this->setChecked(_kernel.record()->isIndividualDeceased(_proband));
    _subboxDate->update(datetype, date1, date2);
    _subboxPlace->update(place);
    _subboxPlace->setCompleter(_comPlace);
    _subboxCause->update(cause);
    _subboxCause->setCompleter(_comCause);
    _subboxSource->update(_kernel, CommonEventType::DEAT, place, sources, sourceRef, page, url);

    //_lineCause.setText(_kernel.record()->getIndividualDeathCause(_proband));
    //_lineCause.setCompleter(_comCause);

    _boxBurial->update();

    this->setSourceEnabled();
}

int BoxDeath::maxLabelWidth() const
{
    QFont font;
    QFontMetrics fontMetrics(font);
    int width = _subboxCause->maxLabelWidth();
    if(width < _subboxDate->maxLabelWidth())
    {
        width = _subboxDate->maxLabelWidth();
    }
    if(width < _subboxPlace->maxLabelWidth())
    {
        width = _subboxPlace->maxLabelWidth();
    }
    return width;
}

void BoxDeath::setLabelsWidth(int width)
{
    //_laCause.setFixedWidth(width);
    _subboxDate->setLabelsWidth(width);
    _subboxPlace->setLabelsWidth(width);
    _subboxCause->setLabelsWidth(width);
}

void BoxDeath::fill()
{
    // Initialization
    _subboxDate = new SubboxDate(tr("Date of Death"), DateTypeAvailability::NoPeriod, this);
    _subboxPlace = new SubboxSimple(tr("Place of Death"), this);
    _subboxCause = new SubboxSimple(tr("Cause of Death"), this);
    _subboxSource = new SubboxCitation(this);

    _boxBurial = new BoxBurial(tr("Burial"), _kernel, _proband, this);
    _spacer = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);

    // Set static text
    //_laCause.setText(tr("Cause of Death"));

    // Set layout
    _layout.addWidget(_subboxDate, 0, 0);
    _layout.addWidget(_subboxPlace, 1, 0);
    //_layout.addWidget(&_laCause, 2, 0);
    //_layout.addWidget(&_lineCause, 2, 1);
    _layout.addWidget(_subboxCause, 2, 0);
    _layout.addWidget(_subboxSource, 0, 1, 3, 1);
    _layout.addItem(_spacer, 3, 0, 1, 2);
    _layout.addWidget(_boxBurial, 4, 0, 1, 2);

    // Adjust widgets
    this->adjustLabelsWidth();
    _layout.setColumnStretch(0, 1);
    _layout.setColumnStretch(1, 1);
}

void BoxDeath::remove()
{
    if(_comPlace != nullptr)
    {
        _comPlace->deleteLater();
        _comPlace = nullptr;
    }
    if(_comCause != nullptr)
    {
        _comCause->deleteLater();
        _comCause = nullptr;
    }
}

void BoxDeath::setSourceEnabled()
{
    DateType datetype = _kernel.record()->getIndividualDeathDateType(_proband);
    Date date1 = _kernel.record()->getIndividualDeathDate1(_proband);
    QString place = _kernel.record()->getIndividualDeathPlaceName(_proband);

    bool exactDate = (datetype == DateType::SIMPLE) && date1.isValid();
    _subboxSource->setEnabled(exactDate && !place.isEmpty());
}

void BoxDeath::changeDeathState(bool checked)
{
    _kernel.record()->setIndividualDeceased(_proband, checked);
}

void BoxDeath::changeDatetype(const DateType datetype)
{
    _kernel.record()->setIndividualDeathDateType(_proband, datetype);
    this->setSourceEnabled();
}

void BoxDeath::changeDate1(const Date date)
{
    _kernel.record()->setIndividualDeathDate1(_proband, date);
    this->setSourceEnabled();
}

void BoxDeath::changeDate2(const Date date)
{
    _kernel.record()->setIndividualDeathDate2(_proband, date);
}

void BoxDeath::changePlace(const QString plac)
{
    _kernel.record()->setIndividualDeathPlaceName(_proband, plac);
    this->setSourceEnabled();
}

void BoxDeath::changeCause(const QString caus)
{
    _kernel.record()->setIndividualDeathCause(_proband, caus);
}

void BoxDeath::changeSourceRef(const Identifier src)
{
    _kernel.record()->setIndividualDeathSourceCitationRef(_proband, src);
    this->update();
}

void BoxDeath::changeSourcePage(const QString page)
{
    _kernel.record()->setIndividualDeathSourceCitationPage(_proband, page);
}

void BoxDeath::changeSourceUrl(const QString url)
{
    _kernel.record()->setIndividualDeathSourceCitationUrl(_proband, url);
}

void BoxDeath::addSource()
{
    Identifier src = _kernel.record()->newSource();
    QString plac = _kernel.record()->getIndividualDeathPlaceName(_proband);
    _kernel.record()->setSourceData(src, CommonEventType::DEAT);
    _kernel.record()->setSourceDataPlac(src, CommonEventType::DEAT, 0, plac);

    _kernel.record()->setIndividualDeathSourceCitationRef(_proband, src);
    emit(this->sourceChanged(src));
}
