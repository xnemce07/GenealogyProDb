/*!
 *  \file   dialogsettingsconstraints.cpp
 *  \author Eva Navratilova
 */

#include "dialogsettingsconstraints.h"

DialogSettingsConstraints::DialogSettingsConstraints(QWidget *parent)
    : Dialog(parent)
{
    this->setWindowTitle(tr("Constraints settings"));

    this->fill();

    connect(_buttonBox->button(QDialogButtonBox::StandardButton::Ok), &QPushButton::released, this, &DialogSettingsConstraints::accept);
    connect(_buttonBox->button(QDialogButtonBox::StandardButton::Cancel), &QPushButton::released, this, &DialogSettingsConstraints::reject);
}

DialogSettingsConstraints::~DialogSettingsConstraints()
{
    _buttonBox->deleteLater();
}

void DialogSettingsConstraints::accept()
{
    this->apply();

    QDialog::accept();
}

void DialogSettingsConstraints::fill()
{
    // Initialize
    _buttonBox = new QDialogButtonBox(QDialogButtonBox::StandardButton::Ok |
                                      QDialogButtonBox::StandardButton::Cancel);

    // Set static text
    _laAutoDead.setText(tr("Auto-set new individuals as deceased"));
    _laAutoMarried.setText(tr("Auto-set new partnerships as married"));
    _laMaxAge.setText(tr("Maximum age"));
    _laMinYear.setText(tr("Minimum year"));
    _laMinAgeAtChildbirth.setText(tr("Minimum age at childbirth"));

    // Adjust widgets
    _checkAutoDead.setTristate(false);
    _checkAutoMarried.setTristate(false);
    _spinMaxAge.setMinimum(50);
    _spinMaxAge.setMaximum(1000);
    _spinMinYear.setMinimum(1000);
    _spinMinYear.setMaximum(QDate::currentDate().year());
    _spinMinAgeAtChildbirth.setMinimum(1);
    _spinMinAgeAtChildbirth.setMaximum(30);

    // Set values
    QSettings settings;
    bool autoDead = settings.value("dataConstraints/autoDead").toBool();
    bool autoMarried = settings.value("dataConstraints/autoMarried").toBool();
    int maxAge = settings.value("dataConstraints/maximumAge").toInt();
    int minYear = settings.value("dataConstraints/minimumYear").toInt();
    int minAgeAtChildbirth = settings.value("dataConstraints/minimumAgeAtChildbirth").toInt();
    _checkAutoDead.setCheckState((autoDead)? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    _checkAutoMarried.setCheckState((autoMarried)? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    _spinMaxAge.setValue(maxAge);
    _spinMinYear.setValue(minYear);
    _spinMinAgeAtChildbirth.setValue(minAgeAtChildbirth);

    // Set layout
    _layout.addWidget(&_laAutoDead, 0, 0);
    _layout.addWidget(&_checkAutoDead, 0, 1);
    _layout.addWidget(&_laAutoMarried, 1, 0);
    _layout.addWidget(&_checkAutoMarried, 1, 1);
    /*_layout.addWidget(&_laMaxAge, 2, 0);
    _layout.addWidget(&_spinMaxAge, 2, 1);
    _layout.addWidget(&_laMinYear, 3, 0);
    _layout.addWidget(&_spinMinYear, 3, 1);
    _layout.addWidget(&_laMinAgeAtChildbirth, 4, 0);
    _layout.addWidget(&_spinMinAgeAtChildbirth, 4, 1);*/
    _layout.addWidget(_buttonBox, 5, 0, 1, 2);
}

void DialogSettingsConstraints::apply()
{
    bool autoDead = (_checkAutoDead.checkState() == Qt::CheckState::Checked)? true : false;
    bool autoMarried = (_checkAutoMarried.checkState() == Qt::CheckState::Checked)? true : false;
    int maxAge = _spinMaxAge.value();
    int minYear = _spinMinYear.value();
    int minAgeAtChildbirth = _spinMinAgeAtChildbirth.value();

    QSettings settings;
    settings.setValue("dataConstraints/autoDead", autoDead);
    settings.setValue("dataConstraints/autoMarried", autoMarried);
    settings.setValue("dataConstraints/maximumAge", maxAge);
    settings.setValue("dataConstraints/minimumYear", minYear);
    settings.setValue("dataConstraints/minimumAgeAtChildbirth", minAgeAtChildbirth);
}
