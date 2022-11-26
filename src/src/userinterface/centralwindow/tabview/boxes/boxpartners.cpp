/*!
 *  \file   boxpartners.cpp
 *  \author Eva Navratilova
 */

#include "boxpartners.h"

BoxPartners::BoxPartners(QString title, Kernel &k, Identifier &p, QWidget *parent)
    : Box(title, BOX_NOT_CHECKABLE, k, p, parent)
{
    _layout.setHorizontalSpacing(this->tightSpacing());
    _layout.setContentsMargins(0, this->mediumSpacing(), 0, 0);

    this->fill();

    connect(_tabsWidget, &PartnersTabWidget::probandChanged, this, &BoxPartners::probandChanged);
    connect(_tabsWidget, &PartnersTabWidget::sourceChanged, this, &BoxPartners::sourceChanged);
}

void BoxPartners::update()
{
    _tabsWidget->update();
}

void BoxPartners::fill()
{
    // Initialize
    _tabsWidget = new PartnersTabWidget(_kernel, _proband, this);

    // Set static values

    // Set layout
    _layout.addWidget(_tabsWidget, 0, 0);
}
