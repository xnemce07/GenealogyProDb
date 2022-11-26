/*!
 *  \file   sourcescrollarea.cpp
 *  \author Eva Navratilova
 */

#include "sourcescrollarea.h"

SourceScrollArea::SourceScrollArea(Kernel &k, Identifier &source, QWidget *parent)
    : QScrollArea (parent), _kernel(k), _source(source)
{
    this->fill();

    connect(_sourceDetail, &SourceDetail::sourceChanged, this, &SourceScrollArea::sourceChanged);
    connect(_sourceDetail, &SourceDetail::dataChanged, this, &SourceScrollArea::dataChanged);
}

void SourceScrollArea::update()
{
    this->takeWidget();
    _sourceDetail->update();
    this->setWidget(_sourceDetail);
}

void SourceScrollArea::fill()
{
    // Initialize
    _sourceDetail = new SourceDetail(_kernel, _source);
    this->setWidgetResizable(true);

    this->setWidget(_sourceDetail);
}
