/*!
 *  \file   address.h
 *  \author Eva Navratilova
 */

#ifndef ADDRESS_H
#define ADDRESS_H

#include <QString>


/**
 * @brief
 *
 */
class Address
{
private:
    QString address; /**< Address */
    QString city; /**< City */
    QString state; /**< State */
    QString phone; /**< Phone number */
    QString email; /**< E-mail address */
    QString www; /**< Web address */


public:
    /**
     * @brief
     *
     */
    Address() = default;
    ~Address() = default;

    // Getters
    /**
     * @brief
     *
     * @return QString
     */
    QString getAddress() const;
    /**
     * @brief
     *
     * @return QString
     */
    QString getCity() const;
    /**
     * @brief
     *
     * @return QString
     */
    QString getState() const;
    /**
     * @brief
     *
     * @return QString
     */
    QString getPhone() const;
    /**
     * @brief
     *
     * @return QString
     */
    QString getEmail() const;
    /**
     * @brief
     *
     * @return QString
     */
    QString getWww() const;

    // Setters
    /**
     * @brief
     *
     * @param str
     */
    void setAddress(QString str);
    /**
     * @brief
     *
     * @param str
     */
    void setCity(QString str);
    /**
     * @brief
     *
     * @param str
     */
    void setState(QString str);
    /**
     * @brief
     *
     * @param str
     */
    void setPhone(QString str);
    /**
     * @brief
     *
     * @param str
     */
    void setEmail(QString str);
    /**
     * @brief
     *
     * @param str
     */
    void setWww(QString str);

};

#endif // ADDRESS_H
