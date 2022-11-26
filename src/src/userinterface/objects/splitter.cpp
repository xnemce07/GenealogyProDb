/*!
 *  \file   splitter.cpp
 *  \author Eva Navratilova
 */

#include "splitter.h"

Splitter::Splitter(QWidget *parent)
    : QSplitter (parent)
{

}

Splitter::~Splitter()
{
    /// TODO - resolve deleting
    /*for(auto line : _lines)
    {
        delete line;
    }
    for(auto handle : _handles)
    {
        delete handle;
    }
    for(auto layout: _layouts)
    {
        delete layout;
    }*/

    _lines.clear();
    _layouts.clear();
    _handles.clear();
}

void Splitter::decorate()
{
    const int count = this->count();
    QFrame::Shape shape = (this->orientation() == Qt::Orientation::Horizontal)? QFrame::Shape::VLine : QFrame::Shape::HLine;

    for(int i = 0; i < count; i++)
    {
        QSplitterHandle* handle = this->handle(i);
        QVBoxLayout* layout = new QVBoxLayout(handle);
        layout->setSpacing(0);
        layout->setMargin(0);

        QFrame* line = new QFrame(handle);
        line->setFrameShape(shape);
        line->setFrameShadow(QFrame::Sunken);
        layout->addWidget(line);

        _layouts.push_back(layout);
        _handles.push_back(handle);
        _lines.push_back(line);
    }
}
