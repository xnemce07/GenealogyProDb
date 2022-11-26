/*!
 *  \file   dialogsettingsdescriptionformat.cpp
 *  \author Eva Navratilova
 */

#include "dialogsettingsdescriptionformat.h"

DialogSettingsDescriptionFormat::DialogSettingsDescriptionFormat(Kernel &k, Identifier &r, FormatableText f, QWidget *parent)
    : Dialog(parent), _kernel(k), _ref(r), _formatable(f)
{
    this->setWindowTitle(tr("Set Description Format ..."));

    this->fill();

    connect(_buttonBox->button(QDialogButtonBox::StandardButton::Ok), &QPushButton::released, this, &DialogSettingsDescriptionFormat::accept);
    connect(_buttonBox->button(QDialogButtonBox::StandardButton::Cancel), &QPushButton::released, this, &DialogSettingsDescriptionFormat::reject);
    connect(_buttonBox->button(QDialogButtonBox::StandardButton::RestoreDefaults), &QPushButton::released, this, &DialogSettingsDescriptionFormat::restoreDefaults);
}

void DialogSettingsDescriptionFormat::fill()
{
    QSettings settings;

    // Initialize
    _buttonBox = new QDialogButtonBox(QDialogButtonBox::StandardButton::Ok |
                                      QDialogButtonBox::StandardButton::Cancel |
                                      QDialogButtonBox::StandardButton::RestoreDefaults);
    _spacer = new QSpacerItem(1, 1, QSizePolicy::Fixed, QSizePolicy::Expanding);

    // Set static text
    _laLegend.setText("<b>" + tr("Legend") + "</b>");
    _laFormat.setText("<b>" + tr("Description Format") + "</b>");
    _laPreview.setText("<b>" + tr("Text Preview") + "</b>");

    // Get values
    _legend  = TextFormatter::getHtmlString(_formatable);
    _legend += TextFormatter::getDictionaryString(_formatable);
    _getPreview = TextFormatter::getTextGetter(_formatable);
    _settingsKey = TextFormatter::getSettingsKey(_formatable);
    _settingsBackup = settings.value(_settingsKey).toString();

    // Set values
    _textLegend.setPlainText(_legend);
    this->changePreview(_settingsBackup);

    // Adjust widgets
    _splitter.setChildrenCollapsible(false);
    _textLegend.setReadOnly(true);
    _textLegend.setWordWrapMode(QTextOption::NoWrap);
    _laPreviewText.setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    // Set layout
    _layout.addWidget(&_splitter, 0, 0);
    _layout.addWidget(_buttonBox, 1, 0);

    _splitter.addWidget(&_left);
    _splitter.addWidget(&_right);
    _left.setLayout(&_layoutLeft);
    _right.setLayout(&_layoutRight);

    _layoutLeft.addWidget(&_laLegend, 0, 0);
    _layoutLeft.addWidget(&_textLegend, 1, 0);

    _layoutRight.addWidget(&_laFormat, 0, 0);
    switch(_formatable)
    {
    case FormatableText::TREE_MARRIAGE:
    case FormatableText::TREE_INDIVIDUAL:
        _layoutRight.addWidget(&_textFormat, 1, 0);
        break;
    case FormatableText::INDIVIDUAL:
    case FormatableText::SOURCE:
    case FormatableText::SOURCE_CITATION:
        _layoutRight.addWidget(&_lineFormat, 1, 0);
        break;
    case FormatableText::EMPTY:
        break;
    }
    this->lineTextFormatFromSettings();
    _layoutRight.addWidget(&_laPreview, 2, 0);
    _layoutRight.addWidget(&_laPreviewText, 3, 0);
    _layoutRight.addWidget(&_laPreviewText, 4, 0);
    _layoutRight.addItem(_spacer, 5, 0);

    // Adjust after insert
    _splitter.decorate();

    // Connect change preview
    connect(&_lineFormat, &QLineEdit::textChanged, this, &DialogSettingsDescriptionFormat::changePreviewLine);
    connect(&_textFormat, &QTextEdit::textChanged, this, &DialogSettingsDescriptionFormat::changePreviewText);

    // Connect en/disable Ok button
    connect(&_lineFormat, &QLineEdit::textChanged, this, &DialogSettingsDescriptionFormat::checkEmptyLine);
    connect(&_textFormat, &QTextEdit::textChanged, this, &DialogSettingsDescriptionFormat::checkEmptyText);
}

void DialogSettingsDescriptionFormat::changePreview(const QString &text)
{
    QSettings settings;
    settings.setValue(_settingsKey, text);

    // Preview text or write no data if no data available
    QString preview = _getPreview(_kernel, _ref);
    QString nodata = tr("There is no data available for preview.");
    switch(_formatable)
    {
    case FormatableText::INDIVIDUAL:
    case FormatableText::TREE_INDIVIDUAL:
        if(!_kernel.record()->isIndividual(_ref))
        {
            preview = nodata;
        }
        break;
    case FormatableText::TREE_MARRIAGE:
        if(!_kernel.record()->isFamily(_ref))
        {
            preview = nodata;
        }
        break;
    case FormatableText::SOURCE:
    case FormatableText::SOURCE_CITATION:
        if(!_kernel.record()->isSource(_ref))
        {
            preview = nodata;
        }
        break;
    case FormatableText::EMPTY:
        break;
    }

    _laPreviewText.setText(preview);
}

void DialogSettingsDescriptionFormat::lineTextFormatFromSettings()
{
    switch(_formatable)
    {
    case FormatableText::TREE_MARRIAGE:
    case FormatableText::TREE_INDIVIDUAL:
        _textFormat.setPlainText(_settingsBackup);
        break;
    case FormatableText::INDIVIDUAL:
    case FormatableText::SOURCE:
    case FormatableText::SOURCE_CITATION:
        _lineFormat.setText(_settingsBackup);
        break;
    case FormatableText::EMPTY:
        break;
    }
}

void DialogSettingsDescriptionFormat::changePreviewText()
{
    this->changePreview(_textFormat.toPlainText());
}

void DialogSettingsDescriptionFormat::changePreviewLine(const QString &text)
{
    this->changePreview(text);
}

void DialogSettingsDescriptionFormat::checkEmptyText()
{
    _buttonBox->button(QDialogButtonBox::StandardButton::Ok)->setEnabled(!_textFormat.toPlainText().isEmpty());
}

void DialogSettingsDescriptionFormat::checkEmptyLine(const QString &text)
{
    _buttonBox->button(QDialogButtonBox::StandardButton::Ok)->setEnabled(!text.isEmpty());
}

void DialogSettingsDescriptionFormat::accept()
{
    // Emit signal to reload ui
    Dialog::accept();
}

void DialogSettingsDescriptionFormat::reject()
{
    QSettings settings;
    settings.setValue(_settingsKey, _settingsBackup);

    Dialog::reject();
}

void DialogSettingsDescriptionFormat::restoreDefaults()
{
    QSettings settings;
    TextFormatter::defaultSettings(_formatable);
    _settingsBackup = settings.value(_settingsKey).toString();
    this->lineTextFormatFromSettings();
}
