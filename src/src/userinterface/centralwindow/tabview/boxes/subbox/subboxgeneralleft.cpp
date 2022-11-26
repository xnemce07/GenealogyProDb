/*!
 *  \file   subboxgeneralleft.cpp
 *  \author Eva Navratilova
 */

#include "subboxgeneralleft.h"

SubboxGeneralLeft::SubboxGeneralLeft(QWidget *parent)
    : Subbox (parent)
{
    this->fill();

    connect(_subboxNameGiven, &SubboxSimple::textChanged, this, &SubboxGeneralLeft::changeNameGiven);
    connect(_subboxNameBirthname, &SubboxSimple::textChanged, this, &SubboxGeneralLeft::changeNameBirthname);
    connect(_subboxNameMarname, &SubboxSimple::textChanged, this, &SubboxGeneralLeft::changeNameMarname);
}

SubboxGeneralLeft::~SubboxGeneralLeft()
{

}

void SubboxGeneralLeft::update(const QString &given, const QString &marname, const QString &birthname,
                               const QStringList &givens, const QStringList &marnames, const QStringList &birthnames)
{
    this->remove();

    _subboxNameGiven->update(given);
    _subboxNameMarname->update(marname);
    _subboxNameBirthname->update(birthname);

    _comNameGiven     = new CompleterInline(givens);
    _comNameMarname   = new CompleterInline(marnames);
    _comNameBirthname = new CompleterInline(birthnames);

    // Initialize

    _subboxNameGiven->setCompleter(_comNameGiven);
    _subboxNameMarname->setCompleter(_comNameMarname);
    _subboxNameBirthname->setCompleter(_comNameBirthname);
}

int SubboxGeneralLeft::maxLabelWidth() const
{
    QVector<int> widths;
    widths.push_back(_subboxNameGiven->maxLabelWidth());
    widths.push_back(_subboxNameMarname->maxLabelWidth());
    widths.push_back(_subboxNameBirthname->maxLabelWidth());
    return *std::max_element(widths.begin(), widths.end());
}

void SubboxGeneralLeft::setLabelsWidth(const int width)
{
    _subboxNameGiven->setLabelsWidth(width);
    _subboxNameMarname->setLabelsWidth(width);
    _subboxNameBirthname->setLabelsWidth(width);
}

void SubboxGeneralLeft::fill()
{
    // Initialize
    _subboxNameGiven     = new SubboxSimple(tr("Name"));
    _subboxNameMarname   = new SubboxSimple(tr("Married name"));
    _subboxNameBirthname = new SubboxSimple(tr("Birth name"));

    // Set layout
    // // Column 0
    _layout.addWidget(_subboxNameGiven, 0, 0);
    _layout.addWidget(_subboxNameMarname, 1, 0);
    _layout.addWidget(_subboxNameBirthname, 2, 0);

    // Adjust widgets
    this->adjustLabelsWidth();
}

void SubboxGeneralLeft::remove()
{
    if(_comNameGiven != nullptr)
    {
        _comNameGiven->deleteLater();
        _comNameGiven = nullptr;
    }
    if(_comNameMarname != nullptr)
    {
        _comNameMarname->deleteLater();
        _comNameMarname = nullptr;
    }
    if(_comNameBirthname != nullptr)
    {
        _comNameBirthname->deleteLater();
        _comNameBirthname = nullptr;
    }
}

void SubboxGeneralLeft::setFocus(Qt::FocusReason reason)
{
    Q_UNUSED(reason);
    _subboxNameGiven->setFocus();
}
