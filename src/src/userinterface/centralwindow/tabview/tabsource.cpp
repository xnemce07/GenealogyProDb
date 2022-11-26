/*!
 *  \file   tabsource.cpp
 *  \author Eva Navratilova
 */

#include "tabsource.h"

TabSource::TabSource(Kernel &k, Identifier &s, QWidget *parent)
    : QWidget(parent), _kernel(k), _source(s)
{
    this->setLayout(&_layout);

    this->fill();

    connect(_list, &SourceSearchList::sourceChanged, this, &TabSource::sourceChanged);
    connect(_detail, &SourceScrollArea::sourceChanged, this, &TabSource::sourceChanged);
    connect(_detail, &SourceScrollArea::dataChanged, _list, &SourceSearchList::update);
}

TabSource::~TabSource()
{
    this->remove();
}

void TabSource::update()
{
    _list->update();
    _detail->update();
}

void TabSource::defaultSettings()
{
    QSettings settings;
    int screenWidth = 1000;

    auto screens = QApplication::screens();
    if(!screens.isEmpty())
    {
        screenWidth = screens.first()->geometry().width();
    }

    int listWidth = screenWidth >> 2; // e.g. screenWidth / 4
    int detailWidth = screenWidth - listWidth;

    settings.setValue("window/srcList/width",   listWidth);
    settings.setValue("window/srcDetail/width", detailWidth); // Dummy non-zero value
}

void TabSource::saveSettings() const
{
    QSettings settings;
    settings.setValue("window/srcList/width",   _splitter.sizes()[0]);
    settings.setValue("window/srcDetail/width", _splitter.sizes()[1]);
}

void TabSource::fill()
{
    //Initialize
    _list   = new SourceSearchList(_kernel, _source, this);
    _detail = new SourceScrollArea(_kernel, _source, this);

    // Set layout
    _layout.addWidget(&_splitter);
    _splitter.addWidget(_list);
    _splitter.addWidget(_detail);

    // Adjust splitter
    QSettings settings;
    QList<int> sizes;
    sizes.push_back(settings.value("window/srcList/width").toInt());
    sizes.push_back(settings.value("window/srcDetail/width").toInt());
    _splitter.setSizes(sizes);
    _splitter.decorate();

    _splitter.setCollapsible(0, false);
    _splitter.setCollapsible(1, false);
}

void TabSource::remove()
{
    /*_list->deleteLater();
    _scrollArea->deleteLater();*/
    delete _list;
    delete _detail;
}
