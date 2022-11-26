/*!
 *  \file   statistics.cpp
 *  \author Eva Navratilova
 */

#include "statistics.h"

Statistics::Statistics(Record &r)
    : _record(r)
{

}

int Statistics::getIndividualCount(Gender g) const
{
    int count = 0;
    for(auto id=_record.getIdentifierIndividualFirst(); id < _record.getIdentifierIndividualLast(); _record.getIdentifierIndividualNext(id))
    {
        if(g == Gender::UNDET ||
                g == _record.getIndividualGender(id))
        {
            count++;
        }
    }
    return count;
}

int Statistics::getIndividualCountAlive(Gender g) const
{
    int count = 0;
    for(auto id=_record.getIdentifierIndividualFirst(); id < _record.getIdentifierIndividualLast(); _record.getIdentifierIndividualNext(id))
    {
        if(g == Gender::UNDET ||
                g == _record.getIndividualGender(id))
        {
            if(!_record.isIndividualDeceased(id))
            {
                count++;
            }
        }
    }
    return count;
}

int Statistics::getGenerationCount() const
{
    QVector<int> generationCount;
    QVector<Identifier> checkedIndividuals;
    generationCount.push_back(0);
    for(auto id=_record.getIdentifierIndividualFirst(); id < _record.getIdentifierIndividualLast(); _record.getIdentifierIndividualNext(id))
    {
        if(checkedIndividuals.contains(id))
            continue;

        int outletCount = this->getGenerationOutletCount(id, checkedIndividuals);
        int familyCount = this->getGenerationFamilyCount(id, checkedIndividuals);
        generationCount.push_back(outletCount + familyCount + 1);
    }
    return *(std::max_element(generationCount.begin(), generationCount.end()));
}

QPair<Identifier, Identifier> Statistics::getMinmaxLifespan(bool deceased, Gender g) const
{
    QVector<Identifier> ids;
    QVector<Age> ages;
    for(auto id=_record.getIdentifierIndividualFirst(); id < _record.getIdentifierIndividualLast(); _record.getIdentifierIndividualNext(id))
    {
        if(_record.isIndividualDeceased(id) == deceased)
        {
            if(g == Gender::UNDET || g == _record.getIndividualGender(id))
            {
                Age age = _record.getIndividualAge(id);
                if(age.isValid())
                {
                    ages.push_back(age);
                    ids.push_back(id);
                }
            }
        }
    }
    if(ages.isEmpty())
    {
        return QPair<Identifier, Identifier>(Identifier(), Identifier());
    }
    else
    {
        auto pair = std::minmax_element(ages.begin(), ages.end());
        Identifier id1=ids.at(ages.indexOf(*pair.first));
        Identifier id2=ids.at(ages.indexOf(*pair.second));
        return QPair<Identifier, Identifier>(id1, id2);
    }
}




int Statistics::getGenerationOutletCount(Identifier indi, QVector<Identifier>& checked, int currentGeneration) const
{
    if(!checked.contains(indi))
    {
        checked.push_back(indi);
    }
    QVector<int> generations;
    QVector<Identifier> parents;
    parents.push_back(_record.getIndividualFather(indi));
    parents.push_back(_record.getIndividualMother(indi));
    parents.removeAll(Identifier());
    for(auto parent=parents.begin(); parent != parents.end(); parent++)
    {
        generations.push_back(this->getGenerationOutletCount(*parent, checked, currentGeneration + 1));
    }
    if(generations.isEmpty())
    {
        return currentGeneration;
    }
    else
    {
        return *(std::max_element(generations.begin(), generations.end()));
    }
}

int Statistics::getGenerationFamilyCount(Identifier indi, QVector<Identifier>& checked, int currentGeneration) const
{
    if(!checked.contains(indi))
    {
        checked.push_back(indi);
    }
    QVector<int> generations;
    QVector<Identifier> children = _record.getChildrenOfIndividual(indi);
    children.removeAll(Identifier());
    for(auto parent=children.begin(); parent != children.end(); parent++)
    {
        generations.push_back(this->getGenerationFamilyCount(*parent, checked, currentGeneration + 1));
    }
    if(generations.isEmpty())
    {
        return currentGeneration;
    }
    else
    {
        return *(std::max_element(generations.begin(), generations.end()));
    }
}
