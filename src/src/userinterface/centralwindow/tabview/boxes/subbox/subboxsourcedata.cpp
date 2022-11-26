/*!
 *  \file   subboxsourcedata.cpp
 *  \author Eva Navratilova
 */

#include "subboxsourcedata.h"

SubboxSourceData::SubboxSourceData(Kernel &k, Identifier &s, CommonEventType t, unsigned int index, int row, QGridLayout &layout, QWidget* parent)
    : QWidget (parent), _kernel(k), _source(s), _type(t), _index(index), _row(row), _layout(layout)
{
    this->fill();

    connect(_subboxPlace, &SubboxSimple::textChanged, this, &SubboxSourceData::placeChanged);
    connect(_subboxDate1, &SubboxDate::date1Changed, this, &SubboxSourceData::date1Changed);
    connect(_subboxDate2, &SubboxDate::date1Changed, this, &SubboxSourceData::date2Changed);
    connect(_subboxPage1, &SubboxSimple::textChanged, this, &SubboxSourceData::page1Changed);
    connect(_subboxPage2, &SubboxSimple::textChanged, this, &SubboxSourceData::page2Changed);
    connect(_subboxUrl, &SubboxWeb::urlChanged, this, &SubboxSourceData::urlChanged);
    connect(&_buDelete, &NarrowButton::clicked, this, &SubboxSourceData::deleteClicked);
}

SubboxSourceData::~SubboxSourceData()
{
    /*_layout.removeWidget(_subboxPlace);
    _layout.removeWidget(_subboxDate1);
    _layout.removeWidget(_subboxDate2);
    _layout.removeWidget(_subboxPage1);
    _layout.removeWidget(_subboxPage2);
    _layout.removeWidget(_subboxUrl);*/


    _subboxPlace->deleteLater();
    _subboxDate1->deleteLater();
    _subboxDate2->deleteLater();
    _subboxPage1->deleteLater();
    _subboxPage2->deleteLater();
    _subboxUrl->deleteLater();
}

void SubboxSourceData::update()
{
    _subboxPlace->update(_kernel.record()->getSourceDataPlac(_source, _type, _index));
    _subboxDate1->update(DateType::SIMPLE, _kernel.record()->getSourceDataDateFrom(_source, _type, _index), Date());
    _subboxDate2->update(DateType::SIMPLE, _kernel.record()->getSourceDataDateTo(_source, _type, _index), Date());
    _subboxPage1->update(_kernel.record()->getSourceDataPage1(_source, _type, _index));
    _subboxPage2->update(_kernel.record()->getSourceDataPage2(_source, _type, _index));
    _subboxUrl->update(_kernel.record()->getSourceDataUrl(_source, _type, _index));
}

void SubboxSourceData::setFocus()
{
    _subboxPlace->setFocus();
}

void SubboxSourceData::fill()
{
    // Initialize
    _subboxPlace = new SubboxSimple(tr(""));
    _subboxDate1 = new SubboxDate("", DateTypeAvailability::OnlySimple);
    _subboxDate2 = new SubboxDate(tr("-"), DateTypeAvailability::OnlySimple);
    _subboxPage1 = new SubboxSimple(tr(""));
    _subboxPage2 = new SubboxSimple(tr("-"));
    _subboxUrl = new SubboxWeb(tr(""));
    _buDelete.setIcon(QIcon(":icons/delete"));
    _buDelete.setToolTip(tr("Remove source record data"));
    _buDelete.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // Set layout
    _layout.addWidget(_subboxPlace, _row, 0, 1, 2);
    _layout.addWidget(_subboxDate1, _row, 2);
    _layout.addWidget(_subboxDate2, _row, 3);
    _layout.addWidget(_subboxPage1, _row, 4);
    _layout.addWidget(_subboxPage2, _row, 5);
    _layout.addWidget(_subboxUrl, _row, 6);
    _layout.addWidget(&_buDelete, _row, 7);
}

void SubboxSourceData::placeChanged(const QString &place)
{
    _kernel.record()->setSourceDataPlac(_source, _type, _index, place);
}

void SubboxSourceData::date1Changed(const Date &date)
{
    _kernel.record()->setSourceDataDateFrom(_source, _type, _index, date);
}

void SubboxSourceData::date2Changed(const Date &date)
{
    _kernel.record()->setSourceDataDateTo(_source, _type, _index, date);
}

void SubboxSourceData::page1Changed(const QString &page)
{
    _kernel.record()->setSourceDataPage1(_source, _type, _index, page);
}

void SubboxSourceData::page2Changed(const QString &page)
{
    _kernel.record()->setSourceDataPage2(_source, _type, _index, page);
}

void SubboxSourceData::urlChanged(const QString &url)
{
    _kernel.record()->setSourceDataUrl(_source, _type, _index, url);
}

void SubboxSourceData::deleteClicked(bool checked)
{
    Q_UNUSED(checked);

    MessageDelete dialog(tr("this data of source record"));
    if(dialog.exec())
    {
        _kernel.record()->removeSourceData(_source, _type, _index);
        emit(this->dataChanged());
    }
}
