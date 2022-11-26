/*!
 *  \file   sizer.cpp
 *  \author Eva Navratilova
 */

#include "sizer.h"

int Sizer::tightSpacing() const
{
    return fontHeight() / 12;
}

int Sizer::mediumSpacing() const
{
    return fontHeight() / 4;
}

int Sizer::wideSpacing() const
{
    return fontHeight() / 2;
}

int Sizer::padding() const
{
    return fontHeight() / 2;
}

int Sizer::fontHeight() const
{
    return QFontMetrics(QFont()).height();
}
