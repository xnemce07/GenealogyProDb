/*!
 *  \file   informationfamilytree.cpp
 *  \author Eva Navratilova
 */

#include "informationfamilytree.h"

InformationFamilyTree::InformationFamilyTree(Kernel &k, QWidget *parent)
    : Dialog(parent), LabelWidthAdjuster(), _kernel(k)
{
    this->fill();

    connect(_subboxAuthor, &SubboxSimple::textChanged, this, &InformationFamilyTree::changeAuthor);
    //connect(_subboxDate, &SubboxDate::date1Changed, this, &InformationFamilyTree::changeDate);
    connect(&_textDescription, &QTextEdit::textChanged, this, &InformationFamilyTree::changeDescription);
}

void InformationFamilyTree::fill()
{
    // Initialize
    _subboxAuthor = new SubboxSimple(tr("Author"));
    //_subboxDate   = new SubboxDate(tr("Creation Date"), DateTypeAvailability::OnlySimple);
    _buttonBox    = new QDialogButtonBox(QDialogButtonBox::StandardButton::Ok |
                                         QDialogButtonBox::StandardButton::Cancel);
    connect(_buttonBox, &QDialogButtonBox::accepted, this, &InformationFamilyTree::accept);
    connect(_buttonBox, &QDialogButtonBox::rejected, this, &InformationFamilyTree::reject);

    // Set static text
    _laDescription.setText(tr("Description"));

    _subm = _kernel.record()->getIdentifierSubmitterFirst();
    if(!_kernel.record()->isSubmitter(_subm))
    {
        _subm = _kernel.record()->newSubmitter();
    }
    _author = _kernel.record()->getSubmitterName(_subm);
    _date   = _kernel.record()->getSubmitterDate(_subm);
    _description = _kernel.record()->getSubmitterNote(_subm);

    // Set layout
    _layout.addWidget(_subboxAuthor, 0, 0, 1, 2);
    //_layout.addWidget(_subboxDate, 1, 0, 1, 2);
    _layout.addWidget(&_laDescription, 2, 0);
    _layout.addWidget(&_textDescription, 2, 1);
    _layout.addWidget(_buttonBox, 3, 0, 1, 2);

    // Update values

    _subboxAuthor->update(_author);
    //_subboxDate->update(DateType::SIMPLE, _date, Date());
    _textDescription.setText(_description);

    // Adjust layout
    this->adjustLabelsWidth();
}

int InformationFamilyTree::maxLabelWidth() const
{
    QVector<int> widths;
    QFont font;
    QFontMetrics fontMetrics(font);
    widths.push_back(fontMetrics.horizontalAdvance(_laDescription.text()));
    widths.push_back(_subboxAuthor->maxLabelWidth());
    //widths.push_back(_subboxDate->maxLabelWidth());

    return *std::max_element(widths.begin(), widths.end());
}

void InformationFamilyTree::setLabelsWidth(int width)
{
    _subboxAuthor->setLabelsWidth(width);
    //_subboxDate->setLabelsWidth(width);
    _laDescription.setFixedWidth(width);
}

QString InformationFamilyTree::getAuthor() const
{
    return _author;
}

Date InformationFamilyTree::getDate() const
{
    return _date;
}

QString InformationFamilyTree::getDescription() const
{
    return _description;
}

void InformationFamilyTree::changeAuthor(QString text)
{
    _author = text;
}

void InformationFamilyTree::changeDate(const Date &date)
{
    _date = date;
}

void InformationFamilyTree::changeDescription()
{
    _description = _textDescription.toPlainText();
}
