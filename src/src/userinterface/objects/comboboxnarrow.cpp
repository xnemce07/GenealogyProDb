/*!
 *  \file   comboboxnarrow.cpp
 *  \author Eva Navratilova
 */

#include "comboboxnarrow.h"

ComboBoxNarrow::ComboBoxNarrow(QWidget *parent)
    :QComboBox (parent)
{
    //QFont font;
    //QFontMetrics metrics(font);
    //_comboView = new QTableView(parent);
    //_comboView->horizontalHeader()->setVisible(false);
    //_comboView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //_comboView->verticalHeader()->setVisible(false);
    //_comboView->verticalHeader()->setDefaultSectionSize(metrics.height());
    //this->setView(_comboView);

    this->initializeCompleter();
    this->setInsertPolicy(NoInsert);
    this->setEditable(false);
}

//void ComboBoxNarrow::addItem(const QString &text, const Identifier ref)
//{
//    QComboBox::addItem(text, ref.get());
//}

//void ComboBoxNarrow::setItemIdentifier(int index, const Identifier ref)
//{
//    QComboBox::setItemData(index, ref.get());
//}

//Identifier ComboBoxNarrow::itemIdentifier(int index)
//{
//    return Identifier::fromString(QComboBox::itemData(index).toString());
//}

void ComboBoxNarrow::updateWidth()
{
    QFont font;
    QFontMetrics fontMetrics(font);
    _minWidth = 2 * margin();
    int minimumComboWidth = minItemLength() + 2*margin();
    int minimumViewWidth = maxItemLength() + margin();
    this->setMinimumWidth(minimumComboWidth);
    /// TODO - also set maximum width?
    this->view()->setMinimumWidth(minimumViewWidth);
}

int ComboBoxNarrow::margin() const
{
    QFont font;
    QFontMetrics fontMetrics(font);
    return fontMetrics.height();
}

int ComboBoxNarrow::minItemLength() const
{
    QFont font;
    QFontMetrics fontMetrics(font);
    int width = _minWidth;

    for(int i = 0; i < this->count(); i++)
    {
        int newWidth = fontMetrics.horizontalAdvance(this->itemText(i));
        if(width > newWidth)
        {
            width = newWidth;
        }
    }
    return width;
}

int ComboBoxNarrow::maxItemLength() const
{
    QFont font;
    QFontMetrics fontMetrics(font);
    int width = _minWidth;

    for(int i = 0; i < this->count(); i++)
    {
        int newWidth = fontMetrics.horizontalAdvance(this->itemText(i));
        if(width < newWidth)
        {
            width = newWidth;
        }
    }
    return width + 10;
}

void ComboBoxNarrow::initializeCompleter()
{
    _completer.setCaseSensitivity(Qt::CaseInsensitive);
    _completer.setCompletionMode(QCompleter::InlineCompletion);
    this->setCompleter(&_completer);

}

void ComboBoxNarrow::showPopup()
{
    emit(this->updateCombo());
    QComboBox::showPopup();
}
