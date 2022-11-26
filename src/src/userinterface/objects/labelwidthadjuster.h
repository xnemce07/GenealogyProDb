/*!
 *  \file   labelwidthadjuster.h
 *  \author Eva Navratilova
 */

#ifndef DESIGNER_H
#define DESIGNER_H

#include <QWidget>

class LabelWidthAdjuster
{
public:
    explicit LabelWidthAdjuster() = default;
    virtual ~LabelWidthAdjuster() = default;

    void adjustLabelsWidth();
    virtual int maxLabelWidth() const = 0;
    virtual void setLabelsWidth(const int width) = 0;
};

#endif // DESIGNER_H
