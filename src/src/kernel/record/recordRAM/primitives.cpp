/*!
 *  \file   primitives.cpp
 *  \author Eva Navratilova
 */

#include "primitives.h"

uint qHash(const Identifier &key)
{
    return qHash(key.get(), 0xa03f);
}


uint qHash(const CommonEventType &key)
{
    return qHash(static_cast<int>(key), 0xa03f);
}

///////////////////////////////////////////////////////////////////////////////
