/*!
 *  \file   sizer.h
 *  \author Eva Navratilova
 */

#ifndef SIZER_H
#define SIZER_H

#include <QDebug>
#include <QFont>
#include <QFontMetrics>

class Sizer
{
public:
    explicit Sizer() = default;

    int tightSpacing() const;
    int mediumSpacing() const;
    int wideSpacing() const;
    int padding() const;

private:
    int fontHeight() const;
};

#endif // SIZER_H
