/*!
 *  \file   translatableobject.h
 *  \author Eva Navratilova
 */

#ifndef TRANSLATABLEOBJECT_H
#define TRANSLATABLEOBJECT_H


class TranslatableObject
{
public:
    TranslatableObject() = default;
    virtual ~TranslatableObject() = default;

    virtual void translate() = 0;

};

#endif // TRANSLATABLEOBJECT_H
