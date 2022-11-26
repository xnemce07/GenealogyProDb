/*!
 *  \file   place.h
 *  \author Eva Navratilova
 */

#ifndef PLACE_H
#define PLACE_H


#include <QVector>
#include <QString>

#include "date.h"

//#include "../record.h"


/**
 * @brief
 *
 */
class Place
{
private:
    QString _name; /**< Place name */
    QString _hier; /**< Place hierarchy */
    QString _latit; /**< Map latitude */
    QString _longit; /**< Map longitude */

public:
    /**
     * @brief Default constructor
     *
     */
    Place() = default;
    ~Place() = default;

    // Getters

    QString getName() const;
    QString getHier() const;
    QString getLatit() const;
    QString getLongit() const;


    // Setters

    void setName(const QString n);
    void setHier(const QString h);
    void setLatit(const QString l);
    void setLongit(const QString l);




};

#endif // PLACE_H
