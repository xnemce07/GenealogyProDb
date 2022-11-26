/*!
 *  \file   dialogsettingsenvironment.cpp
 *  \author Eva Navratilova
 */

#include "dialogsettingsevnironment.h"

DialogSettingsEnvironment::DialogSettingsEnvironment(Identifier &p, QWidget *parent)
    : Dialog (parent), _proband(p)
{
    this->setWindowTitle(tr("Environment settings"));

    this->fill();

    connect(_buttonBox->button(QDialogButtonBox::StandardButton::Ok), &QPushButton::released, this, &DialogSettingsEnvironment::accept);
    connect(_buttonBox->button(QDialogButtonBox::StandardButton::Cancel), &QPushButton::released, this, &DialogSettingsEnvironment::reject);
}

void DialogSettingsEnvironment::accept()
{
    this->apply();

    QDialog::accept();
}

void DialogSettingsEnvironment::fill()
{
    QSettings settings;

    // Initialize
    _buttonBox = new QDialogButtonBox(QDialogButtonBox::StandardButton::Ok |
                                      QDialogButtonBox::StandardButton::Cancel);

    // Set static text
    _laLanguage.setText(tr("Language"));
    _laAutoOpen.setText(tr("Open last file at startup"));

    // Get values
    QLocale locale = settings.value("locale").toLocale();
    bool autoOpen =  settings.value("accessibility/autoOpenLastFile").toBool();
    Qt::CheckState state = (autoOpen)? Qt::CheckState::Checked : Qt::CheckState::Unchecked;

    // Set values
    this->fillComboLanguage();
    this->blockSignals(true);
    _comboLanguage.setCurrentText(this->getFormatedLanguageName(locale));
    this->blockSignals(false);
    _checkAutoOpen.setCheckState(state);

    // Adjust widgets
    _checkAutoOpen.setTristate(false);

    // Set layout
    _layout.addWidget(&_laLanguage, 0, 0);
    _layout.addWidget(&_comboLanguage, 0, 1);
    _layout.addWidget(&_laAutoOpen, 1, 0);
    _layout.addWidget(&_checkAutoOpen, 1, 1);
    _layout.addWidget(_buttonBox, 2, 0, 1, 2);
}

void DialogSettingsEnvironment::fillComboLanguage()
{
    QLocale english(QLocale::Language::English);
    _comboLanguage.addItem(this->getFormatedLanguageName(english), english);
    QVector<QLocale> languages;
    QStringList supportedLanguageList = QDir(":/translations").entryList();

    for(int language = QLocale::Language::AnyLanguage; language <= QLocale::Language::UncodedLanguages; language++)
    {
        QLocale::Language castedLanguage = static_cast<QLocale::Language>(language);
        // Here is a weird bug - even though castedLanguage value is ok,
        //   language locale is initilized as QLocale(). This is the reason
        //   the additional check to "if" inside the "fors" was added
        QLocale languageLocale = QLocale(castedLanguage);
        for(auto supportedLanguage : supportedLanguageList)
        {
            if((languageLocale.name().section('_', 0, 0) == supportedLanguage) &&
               (languageLocale.language() == castedLanguage)) // DO NOT DELETE ADDITIONAL CONDITION - See the explaining comment above
            {
                _comboLanguage.addItem(this->getFormatedLanguageName(languageLocale), languageLocale);
            }
        }
    }
}

QString DialogSettingsEnvironment::getFormatedLanguageName(const QLocale &language) const
{
    QString languageName = language.nativeLanguageName();
    QString languageNameLowerLast = language.toLower(languageName);
    QString languageNameUpperFirst = language.toUpper(languageName);
    languageNameLowerLast.remove(0, 1);
    languageNameUpperFirst.truncate(1);
    return languageNameUpperFirst + languageNameLowerLast;
}

void DialogSettingsEnvironment::apply()
{
    // Get values
    QSettings settings;
    QLocale locale = _comboLanguage.currentData().toLocale();
    bool isChecked = (_checkAutoOpen.checkState() == Qt::CheckState::Checked)? true : false;

    // Save values to settings
    if(locale != settings.value("locale").toLocale())
    {
        //QLocale::setDefault(locale);
        settings.setValue("locale", locale);
        emit(this->languageChanged());
    }
    settings.setValue("accessibility/autoOpenLastFile", isChecked);
}


