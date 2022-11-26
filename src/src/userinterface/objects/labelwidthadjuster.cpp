/*!
 *  \file   labelwidthadjuster.cpp
 *  \author Eva Navratilova
 */

#include "labelwidthadjuster.h"

void LabelWidthAdjuster::adjustLabelsWidth()
{
    this->setLabelsWidth(this->maxLabelWidth() + 10);
}
