/*!
 *  \file   sourcesearchlist.cpp
 *  \author Eva Navratilova
 */

#include "sourcesearchlist.h"

SourceSearchList::SourceSearchList(Kernel &k, Identifier &s, QWidget *parent)
    : QWidget(parent), _kernel(k), _source(s)
{
    this->setLayout(&_layout);

    this->fill();

    _lineSearch.setFocus();

    // Connect buttons
    connect(&_buAdd, &NarrowButton::clicked, this, &SourceSearchList::sourceAddClicked);
    connect(&_buDelete, &NarrowButton::clicked, this, &SourceSearchList::sourceRemoveClicked);

    // Connect search list
    connect(&_lineSearch, &QLineEdit::textEdited, _table, &SourceList::selectLine);
    connect(_table, &SourceList::itemChanged, this, &SourceSearchList::sourceChanged);
    connect(_table, &SourceList::selectedChanged, this, &SourceSearchList::sourceChanged);
}

void SourceSearchList::update()
{
    this->remove();

    for(auto src = _kernel.record()->getIdentifierSourceFirst(); src < _kernel.record()->getIdentifierSourceLast(); _kernel.record()->getIdentifierSourceNext(src))
    {
        if(_kernel.record()->isSource(src))
        {
            _sources.push_back(src);
        }
    }

    _buDelete.setEnabled(_kernel.record()->isSource(_source));

    _table->update(_sources);

    _table->selectLine(_lineSearch.text());

}

void SourceSearchList::fill()
{
    // Initialize
    _table = new SourceList(_kernel, _source);

    // Set static text
    _buAdd.setIcon(QIcon(":icons/add"));
    _buDelete.setIcon(QIcon(":icons/delete"));
    _buAdd.setToolTip(tr("Add Source"));
    _buDelete.setToolTip(tr("Delete Source"));
    _buDelete.setEnabled(false);

    // Set layout
    _layout.addWidget(&_buAdd, 0, 0);
    _layout.addWidget(&_buDelete, 0, 1);
    _layout.addWidget(&_lineSearch, 1, 0, 1, 3);
    _layout.addWidget(_table, 2, 0, 1, 3);

    // Adjust layout
    _layout.setColumnStretch(0, 1);
    _layout.setColumnStretch(1, 1);
    _layout.setColumnStretch(2, 1000);
}

void SourceSearchList::remove()
{
    _sources.clear();
}

void SourceSearchList::sourceAddClicked(bool checked)
{
    Q_UNUSED(checked);

    Identifier source = _kernel.record()->newSource();
    emit(this->sourceChanged(source));
}

void SourceSearchList::sourceRemoveClicked(bool checked)
{
    Q_UNUSED(checked);

    MessageDelete dialog(tr("this source record"));
    if(dialog.exec())
    {
        _kernel.record()->deleteSource(_source);
        emit(this->sourceChanged(_kernel.record()->getIdentifierSourceFirst()));
    }
}
