/*!
 *  \file   statistics.h
 *  \author Eva Navratilova
 */

#ifndef STATISTICS_H
#define STATISTICS_H

#include "record.h"

class IdentifierAge
{
public:
    const Identifier indi;
    const Age age;

    IdentifierAge(const QPair<Identifier, Age> &data)
        : indi(data.first), age(data.second) {}
};

class MinMaxIdentifierAge
{
public:
    const IdentifierAge min;
    const IdentifierAge max;

    MinMaxIdentifierAge(const QPair< QPair<Identifier, Age>, QPair<Identifier, Age> > &data)
        : min(data.first), max(data.second) {}
};



class Statistics
{
private:
    Record &_record;

public:
    Statistics(Record &r);

    int getIndividualCount(Gender g = Gender::UNDET) const;
    int getIndividualCountAlive(Gender g = Gender::UNDET) const;
    int getGenerationCount() const;

    QPair<Identifier, Identifier> getMinmaxLifespan(bool deceased, Gender g = Gender::UNDET) const;

private:
    int getGenerationOutletCount(Identifier indi, QVector<Identifier> &checked, int currentGeneration = 0) const;
    int getGenerationFamilyCount(Identifier indi, QVector<Identifier>& checked, int currentGeneration = 0) const;
};

#endif // STATISTICS_H
