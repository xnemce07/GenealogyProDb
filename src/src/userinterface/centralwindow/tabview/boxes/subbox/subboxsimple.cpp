/*!
 *  \file   subboxsimple.cpp
 *  \author Eva Navratilova
 */

#include "subboxsimple.h"

SubboxSimple::SubboxSimple(QString title, QWidget *parent)
    : Subbox (parent)
{
    _textLabel = title;

    this->fill();

    connect(&_lineSimple, &QLineEdit::textChanged, this, &SubboxSimple::changeText);
}

void SubboxSimple::update(QString place)
{
    _lineSimple.setText(place);
}

void SubboxSimple::setEnabled(bool enabled)
{
    _laSimple.setEnabled(enabled);
    _lineSimple.setEnabled(enabled);
}

void SubboxSimple::setFocus(Qt::FocusReason reason)
{
    Q_UNUSED(reason);
    _lineSimple.setFocus();
}

void SubboxSimple::fill()
{
    // Set static text
    _laSimple.setText(_textLabel);

    // Set layout
    _layout.addWidget(&_laSimple, 0, 0);
    _layout.addWidget(&_lineSimple, 0, 1);
}

int SubboxSimple::maxLabelWidth() const
{
    QFont font;
    QFontMetrics fontMetrics(font);
    int width = fontMetrics.horizontalAdvance(_laSimple.text());
    return width;
}

void SubboxSimple::setLabelsWidth(int width)
{
    _laSimple.setFixedWidth(width);
}

void SubboxSimple::setCompleter(QCompleter *completer)
{
    _lineSimple.setCompleter(completer);
    connect(completer, SIGNAL(activated(const QString&)), &_lineSimple, SLOT(setText(const QString&)));
}

void SubboxSimple::changeText()
{
    emit(this->textChanged(_lineSimple.text()));
}
