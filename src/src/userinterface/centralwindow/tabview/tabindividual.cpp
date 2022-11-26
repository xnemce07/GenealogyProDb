/*!
 *  \file   tabindividual.cpp
 *  \author Eva Navratilova
 */

#include "tabindividual.h"

TabIndividual::TabIndividual(Kernel &k, Identifier &p, QWidget *parent)
  : QWidget(parent), _kernel(k), _proband(p)
{
    this->setLayout(&_layout);

    this->fill();

    /// TODO - connect also children, spouses, priests, witnesses and godparents
    // Connect proband changed
    connect(_listView, &IndividualList::probandChanged, this, &TabIndividual::probandChanged);
    connect(_detail, &IndividualDetail::probandChanged, this, &TabIndividual::probandChanged);
    // Connect source changed
    connect(_detail, &IndividualDetail::sourceChanged, this, &TabIndividual::sourceChanged);
    // On data change update the list
    connect(_detail, &IndividualDetail::dataChanged, _listView, &IndividualList::update);
    connect(_detail, &IndividualDetail::dataChanged, this, &TabIndividual::dataChanged);
}

TabIndividual::~TabIndividual()
{
    if(_listView != nullptr)
    {
        _listView->deleteLater();
        _listView = nullptr;
    }
    if(_detail != nullptr)
    {
        _detail->deleteLater();
        _detail = nullptr;
    }
}

void TabIndividual::fill()
{
    QSettings settings;

    // Initialize
    _listView = new IndividualList(_kernel, _proband, this);
    _detail = new IndividualDetail(_kernel, _proband, this);

    // Set layout
    _layout.addWidget(&_splitter);
    _splitter.addWidget(_listView);
    _splitter.addWidget(_detail);

    // Adjust widgets in layout
    _layout.setMargin(0);
    _layout.setContentsMargins(0, 0, 0, 0);
    _splitter.decorate();

    QList<int> sizes;
    sizes.push_back(settings.value("window/indiList/width").toInt());
    sizes.push_back(settings.value("window/indiDetail/width").toInt());
    _splitter.setSizes(sizes);

    _splitter.setCollapsible(0, true);
    _splitter.setCollapsible(1, false);

    _splitter.setStretchFactor(0,0);
    _splitter.setStretchFactor(1,1);
}

void TabIndividual::update()
{
    _listView->update();
    _detail->update();
}

void TabIndividual::defaultSettings()
{
    IndividualList::defaultSettings();

    QSettings settings;
    QScrollBar scrollBar;
    int listWidth = 0;
    listWidth += settings.value("window/indiList/idCol").toInt();
    listWidth += settings.value("window/indiList/surnameCol").toInt();
    listWidth += settings.value("window/indiList/nameCol").toInt();
    listWidth += settings.value("window/indiList/birthCol").toInt();
    listWidth += 10;    // Approximation of slider width
    int detailWidth = listWidth*6;  // Non-zero dummy value (in case no screen will be detected)

    auto screens = QApplication::screens();
    if(!screens.isEmpty())
    {
        int screenWidth = screens.first()->geometry().width();
        detailWidth = screenWidth - listWidth;
    }

    settings.setValue("window/indiList/width",   listWidth);
    settings.setValue("window/indiDetail/width", detailWidth); // Dummy non-zero value
}

void TabIndividual::saveSettings() const
{
    QSettings settings;
    settings.setValue("window/indiList/width",   _splitter.sizes()[0]);
    settings.setValue("window/indiDetail/width", _splitter.sizes()[1]);

    _listView->saveSettings();
}
