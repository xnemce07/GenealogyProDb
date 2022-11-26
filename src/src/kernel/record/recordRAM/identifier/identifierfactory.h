/*!
 *  \file   identifierfactory.h
 *  \author Eva Navratilova
 */

#ifndef IDENTIFIERFACTORY_H
#define IDENTIFIERFACTORY_H

#include <QString>
#include <QVector>
#include <QDebug>

#include "../../../record.h"
#include "identifiertype.h"
#include "../identifier.h"

class Identifier;
class RecordRAM;


/**
 * @brief
 *
 */
class IdentifierFactory
{
    friend class Identifier;
private:
    const IdentifierType _type; /**< Type of Identifiers that will be produced by the factory */

    unsigned long long int _nextNumber; /**< Number to give to the next constructed Identifier */
    QVector<unsigned long long int> _freeNumbers;

public:

    /**
     * @brief Initializes a new IdentifierFactory
     *
     * @param t     Type of Identifiers, which will be produced by the new Factory
     */
    IdentifierFactory(IdentifierType t);
    /**
     * @brief Constructs a new Identifier of type consistent with Factory type
     *
     * @return Identifier   Newly constructed Identifier
     */
    Identifier newIdentifier();

    /**
     * @brief Imports an identifier of current type
     *
     * Creates all free numbers or incremets nextNumber.
     * Returns Invalid Identifier if the number requested
     * has already been used.
     *
     * @param ref   Identifier to import
     * @return      Returns imported identifier (== ref) or Invalid in case of problems
     */
    Identifier importIdentifier(Identifier ref);

    /**
     * @brief Frees an Identifier of deleted entity to further use
     * @param ref   Identifier to be freed
     */
    void freeIdentifier(Identifier ref);

    /**
     * @brief Returns first identifier of Factory type
     * @return  First Identifier of Factory type
     */
    Identifier firstIdentifier() const;

    /**
     * @brief Returns next Identifier of Factory type to be generated
     * @return  Next to-be-generated Identifier of Factory type
     */
    Identifier lastIdentifier() const;

    Identifier nextIdentifier(Identifier &ref) const;

    /**
     * @brief Resets Identifier factory to a state, where it hasn't produced any Identifiers yet
     *
     */
    void reset();

};

#endif // IDENTIFIERFACTORY_H
