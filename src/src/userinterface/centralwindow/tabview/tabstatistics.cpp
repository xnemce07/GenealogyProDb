/*!
 *  \file   tabstatistics.cpp
 *  \author Eva Navratilova
 */

#include "tabstatistics.h"

const QString TabStatistics::_notApllicable = QT_TR_NOOP("N/A");


TabStatistics::TabStatistics(Kernel &k, QWidget *parent)
    : QTextEdit(parent), _kernel(k)
{
    this->fill();
}

TabStatistics::~TabStatistics()
{
    this->remove();
}

void TabStatistics::update()
{
    this->show();
}

void TabStatistics::show()
{
    QTextEdit::show();

    this->clear();

    QString text;

    /*this->insertHtml("<b>" + tr("Statistics:") + "</b><br>");
    this->insertHtml("<br>");*/

    this->insertHtml(tr("Number of Persons: %1").arg(_statistics->getIndividualCount()) + "<br>");
    this->insertHtml(tr("Number of Men: %1").arg(_statistics->getIndividualCount(Gender::MALE)) + "<br>");
    this->insertHtml(tr("Number of Women: %1").arg(_statistics->getIndividualCount(Gender::FEMALE)) + "<br>");
    this->insertHtml("<br>");

    this->insertHtml(tr("Number of Living Persons: %1").arg(_statistics->getIndividualCountAlive()) + "<br>");
    this->insertHtml(tr("Number of Living Men: %1").arg(_statistics->getIndividualCountAlive(Gender::MALE)) + "<br>");
    this->insertHtml(tr("Number of Living Women: %1").arg(_statistics->getIndividualCountAlive(Gender::FEMALE)) + "<br>");
    this->insertHtml("<br>");

    this->insertHtml(tr("Number of Generations: %1").arg(_statistics->getGenerationCount()) + "<br>");
    this->insertHtml("<br>");

    this->insertHtml("<b>" + tr("Everyone:") + "</b><br>");
    auto lifespanIdentifierDeceasedAll = _statistics->getMinmaxLifespan(true);
    auto lifespanIdentifierDeceasedAllMin = lifespanIdentifierDeceasedAll.first;
    auto lifespanIdentifierDeceasedAllMax = lifespanIdentifierDeceasedAll.second;
    auto lifespanAgeDeceasedAllMin = _kernel.record()->getIndividualAge(lifespanIdentifierDeceasedAllMin);
    auto lifespanAgeDeceasedAllMax = _kernel.record()->getIndividualAge(lifespanIdentifierDeceasedAllMax);

    Q_UNUSED(lifespanAgeDeceasedAllMin);

    this->insertHtml(tr("The longest life span of the deceased: %1")
                 .arg(this->getTextIndividualAge(lifespanIdentifierDeceasedAllMax, lifespanAgeDeceasedAllMax)) + "<br>");



    //this->setHtml(text);

}

void TabStatistics::fill()
{
    // Initialize
    _statistics = new Statistics(*_kernel.record());

    // Adjust widgets
    this->setReadOnly(true);
}

void TabStatistics::remove()
{
    if(_statistics != nullptr)
    {
        delete _statistics;
        _statistics = nullptr;
    }
}

QString TabStatistics::getTextIndividual(const Identifier &indi)
{
    if(_kernel.record()->isIndividual(indi))
    {
        return TextFormatter::getPersonLineText(_kernel, indi);
    }
    else
    {
        return QString();
    }
}

QString TabStatistics::getTextAge(const Age &age)
{
    QString text;
    if(age.isValid())
    {
        text = tr("%1 days (%2 years, %3 months, %4 days)")
                .arg(age.daysBetween())
                .arg(age.years())
                .arg(age.months())
                .arg(age.days());
    }
    else
    {
        text = _notApllicable;
    }
    return text;
}

QString TabStatistics::getTextIndividualAge(const Identifier &indi, const Age &age)
{
    QString text;
    if(_kernel.record()->isIndividual(indi))
    {
        text = tr("%1: age %2")
                .arg(this->getTextIndividual(indi))
                .arg(getTextAge(age));
    }
    else
    {
        text = _notApllicable;
    }
    return text;
}
