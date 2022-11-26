/*!
 *  \file   subboxgeneralright.cpp
 *  \author Eva Navratilova
 */

#include "subboxgeneralright.h"

SubboxGeneralRight::SubboxGeneralRight(QWidget *parent)
    : Subbox (parent)
{
    this->fill();

    connect(&_comboGender, SIGNAL(currentIndexChanged(int)), this, SIGNAL(changeGender(int)));
    connect(_subboxTit1, &SubboxSimple::textChanged, this, &SubboxGeneralRight::changeNameTit1);
    connect(_subboxTit2, &SubboxSimple::textChanged, this, &SubboxGeneralRight::changeNameTit2);
}

SubboxGeneralRight::~SubboxGeneralRight()
{

}

void SubboxGeneralRight::update(Gender g, const QString &tit1, const QString &tit2, const QStringList &tit1s, const QStringList &tit2s)
{
    this->remove();

    _subboxTit1->update(tit1);
    _subboxTit2->update(tit2);

    _comTit1 = new CompleterInline(tit1s);
    _comTit2 = new CompleterInline(tit2s);

    // Initialize
    _subboxTit1->setCompleter(_comTit1);
    _subboxTit2->setCompleter(_comTit2);

    this->blockSignals(true);
    _comboGender.setCurrentIndex(static_cast<int>(g));
    this->blockSignals(false);
}

int SubboxGeneralRight::maxLabelWidth() const
{
    QVector<int> widths;
    widths.push_back(_subboxTit1->maxLabelWidth());
    widths.push_back(_subboxTit2->maxLabelWidth());
    return *std::max_element(widths.begin(), widths.end());
}

void SubboxGeneralRight::setLabelsWidth(const int width)
{
    _laGender.setFixedWidth(width);
    _subboxTit1->setLabelsWidth(width);
    _subboxTit2->setLabelsWidth(width);
}

void SubboxGeneralRight::setGenderIndex(Gender g)
{
    _comboGender.setCurrentIndex(toUnderlying(g));
}

void SubboxGeneralRight::fill()
{
    // Initialize
    _subboxTit1        = new SubboxSimple(tr("Title in front"));
    _subboxTit2        = new SubboxSimple(tr("Title after"));

    // Set static text
    _laGender.setText(tr("Gender"));

    _comboGender.addItems(QStringList() << tr("Male") << tr("Female") << tr("Undetermined"));

    // Set layout
    _layout.addWidget(&_laGender, 0, 0, Qt::AlignVCenter | Qt::AlignRight);
    _layout.addWidget(&_comboGender, 0, 1);
    _layout.addWidget(_subboxTit1, 1, 0, 1, 2);
    _layout.addWidget(_subboxTit2, 2, 0, 1, 2);

    // Adjust widgets
    this->adjustLabelsWidth();
}

void SubboxGeneralRight::remove()
{
    if(_comTit1 != nullptr)
    {
        _comTit1->deleteLater();
        _comTit1 = nullptr;
    }
    if(_comTit2 != nullptr)
    {
        _comTit2->deleteLater();
        _comTit2 = nullptr;
    }
}
