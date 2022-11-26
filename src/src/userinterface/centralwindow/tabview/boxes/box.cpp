/*!
 *  \file   box.cpp
 *  \author Eva Navratilova
 */

#include "box.h"

Box::Box(QString title, bool checkable, Kernel &k, Identifier &p, QWidget *parent)
    : QGroupBox(title, parent), Sizer(), _kernel(k), _proband(p), _title(title)
{    
    this->setCheckable(checkable);

    _layout.setContentsMargins(Sizer::wideSpacing(),
                               Sizer::mediumSpacing(),
                               Sizer::wideSpacing(),
                               Sizer::mediumSpacing());
    _layout.setVerticalSpacing(this->tightSpacing());
    _layout.setHorizontalSpacing(this->mediumSpacing());
    this->setLayout(&_layout);

    if(checkable)
    {
        connect(this, &Box::clicked, this, &Box::setChecked);
    }

    this->setStyleSheet("QGroupBox {font-weight: bold;}");

}

void Box::setChecked(bool checked)
{
    QGroupBox::setChecked(checked);
    for(int row = 0; row < _layout.rowCount(); row++)
    {
        for(int col = 0; col < _layout.columnCount(); col++)
        {
            auto item = _layout.itemAtPosition(row, col);
            QWidget* widget = (item ? item->widget() : nullptr);
            if(widget)
            {
                widget->setVisible(checked);
            }
        }
    }
}
