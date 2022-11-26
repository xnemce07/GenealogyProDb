/*!
 *  \file   boxchildren.cpp
 *  \author Eva Navratilova
 */

#include "boxchildren.h"

BoxChildren::BoxChildren(QString title, Kernel &k, Identifier &p, QWidget *parent)
    : Box(title, BOX_NOT_CHECKABLE, k, p, parent)
{
    this->fill();

    connect(_listChildren, &PersonList::itemChanged, this, &BoxChildren::probandChanged);
    connect(&_buAddBoy, &QPushButton::clicked, this, &BoxChildren::boyClicked);
    connect(&_buAddGirl, &QPushButton::clicked, this, &BoxChildren::girlClicked);
    connect(&_buAddChild, &QPushButton::clicked, this, &BoxChildren::childClicked);
}

void BoxChildren::update()
{
    this->remove();

    _listChildren->update(_children);
    _laCount.setText(QString::number(_children.count()));
}

void BoxChildren::remove()
{
    //_listChildren->deleteLater();
}

void BoxChildren::update(QVector<Identifier> ch)
{
    _children = ch;
    this->update();
}

void BoxChildren::boyClicked(bool checked)
{
    Q_UNUSED(checked);
    emit(this->newBoy());
}

void BoxChildren::girlClicked(bool checked)
{
    Q_UNUSED(checked);
    emit(this->newGirl());
}

void BoxChildren::childClicked(bool checked)
{
    Q_UNUSED(checked);
    emit(this->newChild());
}

void BoxChildren::fill()
{
    // Initilize
    _listChildren = new PersonList(_kernel, _proband, this);

    // Set static values
    _buAddBoy.setIcon(QIcon(":icons/man"));
    _buAddGirl.setIcon(QIcon(":icons/woman"));
    _buAddChild.setIcon(QIcon(":icons/add"));

    _buAddBoy.setToolTip(tr("Add Man"));
    _buAddGirl.setToolTip(tr("Add Woman"));
    _buAddChild.setToolTip(tr("Add Person..."));

    // Adjust items
    /*QFont font;
    QFontMetrics metrics(font);
    int buttonWidth = metrics.horizontalAdvance(_buAddBoy.text()) + 10;
    _buAddBoy.setFixedWidth(buttonWidth);
    _buAddGirl.setFixedWidth(buttonWidth);*/

    // Set layout
    _layout.addWidget(_listChildren, 0, 0, 5, 1);
    _layout.addWidget(&_buAddBoy, 0, 1);
    _layout.addWidget(&_buAddGirl, 1, 1);
    _layout.addWidget(&_buAddChild, 2, 1);
    _layout.addWidget(&_laCount, 4, 1, Qt::AlignmentFlag::AlignVCenter | Qt::AlignmentFlag::AlignRight);

    // Adjust layout
    _layout.setRowStretch(0, 1);
    _layout.setRowStretch(1, 1);
    _layout.setRowStretch(2, 1);
    _layout.setRowStretch(3, 100);
    _layout.setRowStretch(4, 1);
}
