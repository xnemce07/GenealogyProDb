/*!
 *  \file   tabnote.cpp
 *  \author Eva Navratilova
 */

#include "tabnote.h"

TabNote::TabNote(Kernel &k, Identifier &p, QWidget *parent)
    : QWidget(parent), _kernel(k), _proband(p)
{
    this->setLayout(&_layout);

    fill();

    connect(&_textNote, &QTextEdit::textChanged, this, &TabNote::noteChanged);
}

void TabNote::fill()
{
    // Set static text
    _laNote.setText(tr("Notes"));

    // Set layout
    _layout.addWidget(&_laNote, 0, 0);
    _layout.addWidget(&_textNote, 1, 0);
}

void TabNote::update()
{
    _textNote.setText(_kernel.record()->getIndividualNote(_proband));
}

void TabNote::noteChanged()
{
    _kernel.record()->setIndividualNote(_proband, _textNote.toPlainText());
}
