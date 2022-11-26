/*!
 *  \file   exporter.h
 *  \author Eva Navratilova
 */

#ifndef EXPORTER_H
#define EXPORTER_H

#include <QString>

#include "record.h"


/**
 * @brief
 *
 */
class Exporter
{
public:
    /**
     * @brief
     *
     */
    Exporter();
    /**
     * @brief
     *
     */
    virtual ~Exporter();
    // not copyable
    /**
     * @brief
     *
     * @param
     */
    Exporter(const Exporter&) = delete;
    /**
     * @brief
     *
     * @param
     * @return Exporter &operator
     */
    Exporter& operator=(const Exporter&) = delete;

    /**
     * @brief
     *
     * @param filename
     * @param record
     * @return bool
     */
    virtual bool exportFile(QString filename, Record &record) = 0;
};




#endif // EXPORTER_H
