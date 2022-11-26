/*!
 *  \file   sourcedetail.cpp
 *  \author Eva Navratilova
 */

#include "sourcedetail.h"

SourceDetail::SourceDetail(Kernel &k, Identifier &source, QWidget *parent)
    : QWidget(parent), _kernel(k), _source(source)
{
    this->setLayout(&_layout);

    this->fill();

    connect(_subboxArchive, &SubboxSimple::textChanged, this, &SourceDetail::changeArchive);
    connect(_subboxSignature, &SubboxSimple::textChanged, this, &SourceDetail::changeSignature);
    connect(_subboxOriginator, &SubboxSimple::textChanged, this, &SourceDetail::changeOriginator);
    connect(_subboxUrl, &SubboxWeb::urlChanged, this, &SourceDetail::changeUrl);
}

SourceDetail::~SourceDetail()
{
    /*_subboxArchive->deleteLater();
    _subboxSignature->deleteLater();
    _subboxOriginator->deleteLater();
    _subboxUrl->deleteLater();

    _boxSourceBirth->deleteLater();
    _boxSourceMarriage->deleteLater();
    _boxSourceDeath->deleteLater();*/

    delete _subboxArchive;
    delete _subboxSignature;
    delete _subboxOriginator;
    delete _subboxUrl;

    delete _boxSourceBirth;
    delete _boxSourceMarriage;
    delete _boxSourceDeath;
}

void SourceDetail::update()
{
    _subboxArchive->update(_kernel.record()->getSourceArchive(_source));
    _subboxSignature->update(_kernel.record()->getSourceTitle(_source));
    _subboxOriginator->update(_kernel.record()->getSourceOriginator(_source));
    _subboxUrl->update(_kernel.record()->getSourceUrl(_source));

    _boxSourceBirth->update();
    _boxSourceMarriage->update();
    _boxSourceDeath->update();

    connect(_boxSourceBirth, &BoxSource::dataChanged, this, &SourceDetail::dataChanged);
    connect(_boxSourceMarriage, &BoxSource::dataChanged, this, &SourceDetail::dataChanged);
    connect(_boxSourceDeath, &BoxSource::dataChanged, this, &SourceDetail::dataChanged);

    if(_kernel.record()->isSource(_source))
    {
        _subboxArchive->show();
        _subboxSignature->show();
        _subboxOriginator->show();
        _subboxUrl->show();

        _boxSourceBirth->show();
        _boxSourceMarriage->show();
        _boxSourceDeath->show();
    }
    else
    {
        _subboxArchive->hide();
        _subboxSignature->hide();
        _subboxOriginator->hide();
        _subboxUrl->hide();

        _boxSourceBirth->hide();
        _boxSourceMarriage->hide();
        _boxSourceDeath->hide();
    }
}

void SourceDetail::fill()
{
    _subboxArchive = new SubboxSimple(tr("Archive"));
    _subboxSignature = new SubboxSimple(tr("Signature"));
    _subboxOriginator = new SubboxSimple(tr("Originator"));
    _subboxUrl = new SubboxWeb();

    _boxSourceBirth = new BoxSource(tr("Birth Records"), _kernel, _source, CommonEventType::BIRT);
    _boxSourceMarriage = new BoxSource(tr("Marriage Records"), _kernel, _source, CommonEventType::MARR);
    _boxSourceDeath = new BoxSource(tr("Death Records"), _kernel, _source, CommonEventType::DEAT);

    _spacer = new QSpacerItem(1, 1, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

    // Set layout
    _layout.addWidget(_subboxArchive, 0, 0);
    _layout.addWidget(_subboxSignature, 1, 0);
    _layout.addWidget(_subboxOriginator, 2, 0);
    _layout.addWidget(_subboxUrl, 3, 0);

    _layout.addWidget(_boxSourceBirth, 4, 0);
    _layout.addWidget(_boxSourceMarriage, 5, 0);
    _layout.addWidget(_boxSourceDeath, 6, 0);

    _layout.addItem(_spacer, 7, 0);

    // Adjust
    this->adjustLabelsWidth();
}

int SourceDetail::maxLabelWidth() const
{
    QVector<int> widths;

    widths.push_back(_subboxArchive->maxLabelWidth());
    widths.push_back(_subboxSignature->maxLabelWidth());
    widths.push_back(_subboxOriginator->maxLabelWidth());
    widths.push_back(_subboxUrl->maxLabelWidth());

    return *std::max_element(widths.begin(), widths.end());
}

void SourceDetail::setLabelsWidth(int width)
{
    _subboxArchive->setLabelsWidth(width);
    _subboxSignature->setLabelsWidth(width);
    _subboxOriginator->setLabelsWidth(width);
    _subboxUrl->setLabelsWidth(width);
}

void SourceDetail::changeArchive(const QString text)
{
    _kernel.record()->setSourceArchive(_source, text);
    emit(this->dataChanged());
}

void SourceDetail::changeSignature(const QString text)
{
    _kernel.record()->setSourceTitle(_source, text);
    emit(this->dataChanged());
}

void SourceDetail::changeOriginator(const QString text)
{
    _kernel.record()->setSourceOriginator(_source, text);
    emit(this->dataChanged());
}

void SourceDetail::changeUrl(const QString text)
{
    _kernel.record()->setSourceUrl(_source, text);
    emit(this->dataChanged());
}
