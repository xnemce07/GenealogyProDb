/*!
 *  \file   subboxpersonref.cpp
 *  \author Eva Navratilova
 */

#include "subboxpersonref.h"

SubboxPersonRef::SubboxPersonRef(const QString title, Kernel &k, QWidget *parent)
    : Subbox (parent), _kernel(k)
{
    _textLabel = title;

    this->fill();

    connect(&_buPerson, &QPushButton::clicked, this, &SubboxPersonRef::clickPerson);
    connect(&_buRemove, &QPushButton::clicked, this, &SubboxPersonRef::clickRemove);
}

void SubboxPersonRef::update(Identifier ref)
{
    this->remove();

    QString text;
    QString tooltip;
    QIcon icon;
    _ref = ref;
    bool validPerson = _kernel.record()->isIndividual(_ref);

    if(validPerson)
    {
        text = TextFormatter::getPersonLineText(_kernel, _ref);
    }
    else
    {
        icon = QIcon(":icons/add");
        tooltip = tr("Add person...");
    }
    _buPerson.setText(text);
    _buPerson.setToolTip(tooltip);
    _buPerson.setIcon(icon);
    _buRemove.setHidden(!validPerson);
}

int SubboxPersonRef::maxLabelWidth() const
{
    QFont font;
    QFontMetrics fontMetrics(font);
    int width = fontMetrics.horizontalAdvance(_laPerson.text());
    return width;
}

void SubboxPersonRef::setLabelsWidth(int width)
{
    _laPerson.setFixedWidth(width);
}

void SubboxPersonRef::fill()
{
    // Set static text
    _laPerson.setText(_textLabel);
    _buPerson.setCursor(Qt::CursorShape::PointingHandCursor);
    _buRemove.setIcon(QIcon(":icons/delete"));
    _buRemove.setToolTip(tr("Remove link to person"));
    _buRemove.setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // Adjust widgets
    _laPerson.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _buPerson.setStyleSheet("padding-left: 4px; padding-right: 2px; padding-top: 2px; padding-bottom: 2px; Text-align:left;");

    // Set layout
    _layout.addWidget(&_laPerson, 0, 0);
    _layout.addWidget(&_buPerson, 0, 1);
    _layout.addWidget(&_buRemove, 0, 2);

    // Adjust layout
    _layout.setColumnStretch(0, 100);
    _layout.setColumnStretch(1, 1000);
    _layout.setColumnStretch(2, 1);
}

void SubboxPersonRef::remove()
{
    _individuals.clear();
}

void SubboxPersonRef::clickPerson(bool checked)
{
    Q_UNUSED(checked);

    if(_kernel.record()->isIndividual(_ref))
    {
        emit(this->probandChanged(_ref));
    }
    else
    {
        emit(this->addClicked());
    }
}

void SubboxPersonRef::clickRemove(bool checked)
{
    Q_UNUSED(checked);

    _dialogDelete = new MessageDelete(tr("this link to person"));
    int r = _dialogDelete->exec();

    if(r == MessageDelete::Accepted)
    {
        emit(this->removeClicked());
    }
}
