/*!
 *  \file   boxsource.cpp
 *  \author Eva Navratilova
 */

#include "boxsource.h"

BoxSource::BoxSource(QString title, Kernel &k, Identifier &src, CommonEventType t, QWidget *parent)
    : Box(title, BOX_NOT_CHECKABLE, k, src, parent), _source(src), _type(t)
{
    this->fill();

    connect(&_buAdd, &NarrowButton::clicked, this, &BoxSource::addSourceClicked);
}

BoxSource::~BoxSource()
{
    //this->remove();

    for(auto it = _subboxesSourceData.begin(); it != _subboxesSourceData.end(); it++)
    {
        delete *it;
    }

    _subboxesSourceData.clear();
}

void BoxSource::update()
{
    this->remove();

    bool wasPlaced = false;

    const unsigned int count = _kernel.record()->getSourceDataCount(_source, _type);
    for(unsigned int index = 0; index < count; index++)
    {
        wasPlaced = true;

        int row = static_cast<int>(index) + 2;

        auto subboxSourceData = new SubboxSourceData(_kernel, _source, _type, index, row, _layout);
        subboxSourceData->update();
        connect(subboxSourceData, &SubboxSourceData::dataChanged, this, &BoxSource::update);
        connect(subboxSourceData, &SubboxSourceData::dataChanged, this, &BoxSource::dataChanged);
        _subboxesSourceData.push_back(subboxSourceData);
    }

    if(wasPlaced)
    {
        _laDates.show();
        _laPlaces.show();
        _laPages.show();
        _laUrls.show();
    }
    else
    {
        _laDates.hide();
        _laPlaces.hide();
        _laPages.hide();
        _laUrls.hide();
    }
}

void BoxSource::fill()
{
    // Set static text
    _laDates.setText(tr("Time period"));
    _laPlaces.setText(tr("Place"));
    _laPages.setText(tr("Page scope"));
    _laUrls.setText(tr("Url"));
    _buAdd.setIcon(QIcon(":icons/source"));
    _buAdd.setToolTip(tr("Add record"));

    // Adjust widgets
    _layout.setHorizontalSpacing(Sizer::mediumSpacing());
    _layout.setVerticalSpacing(Sizer::tightSpacing());

    // Set layout
    _layout.addWidget(&_buAdd, 0, 0);
    _layout.addWidget(&_laPlaces, 1, 0, 1, 2);
    _layout.addWidget(&_laDates, 1, 2, 1, 2);
    _layout.addWidget(&_laPages, 1, 4, 1, 2);
    _layout.addWidget(&_laUrls, 1, 6);

    _layout.setColumnStretch(0, 1);
    _layout.setColumnStretch(1, 10);
    _layout.setColumnStretch(2, 1);
    _layout.setColumnStretch(3, 1);
    _layout.setColumnStretch(4, 2);
    _layout.setColumnStretch(5, 2);
    _layout.setColumnStretch(6, 4);
}

void BoxSource::remove()
{
    for(auto it = _subboxesSourceData.begin(); it != _subboxesSourceData.end(); it++)
    {
        (*it)->deleteLater();
    }

    _subboxesSourceData.clear();
}

void BoxSource::addSourceClicked(bool checked)
{
    Q_UNUSED(checked);

    unsigned int index = _kernel.record()->setSourceData(_source, _type);
    if(index > 0)
    {
        Date dateFrom = _kernel.record()->getSourceDataDateFrom(_source, _type, index - 1);
        Date dateTo = _kernel.record()->getSourceDataDateTo(_source, _type, index - 1);
        QString page1 = _kernel.record()->getSourceDataPage1(_source, _type, index - 1);
        QString page2 = _kernel.record()->getSourceDataPage2(_source, _type, index - 1);
        QString url = _kernel.record()->getSourceDataUrl(_source, _type, index - 1);

        _kernel.record()->setSourceDataDateFrom(_source, _type, index, dateFrom);
        _kernel.record()->setSourceDataDateTo(_source, _type, index, dateTo);
        _kernel.record()->setSourceDataPage1(_source, _type, index, page1);
        _kernel.record()->setSourceDataPage2(_source, _type, index, page2);
        _kernel.record()->setSourceDataUrl(_source, _type, index, url);
    }
    this->update();

    // Update source list
    emit(this->dataChanged());

    // Focus on newly added line
    _subboxesSourceData.last()->setFocus();

}
