/*!
 *  \file   dialogsettingsenvironment.h
 *  \author Eva Navratilova
 */

#ifndef DIALOGSETTINGSEVNIRONMENT_H
#define DIALOGSETTINGSEVNIRONMENT_H

#include <QDialog>
#include <QSettings>
#include <QDir>
#include <QLocale>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QPushButton>

#include "../../../kernel.h"
#include "userinterface/dialogs/dialog.h"

class DialogSettingsEnvironment : public Dialog
{
    Q_OBJECT
private:
    Identifier &_proband;

    QLabel _laLanguage;
    QLabel _laAutoOpen;

    QComboBox _comboLanguage;
    QCheckBox _checkAutoOpen;

public:
    DialogSettingsEnvironment(Identifier &p, QWidget *parent = nullptr);

    void accept() override;

private:
    void fill() override;
    void fillComboLanguage();
    QString getFormatedLanguageName(const QLocale &language) const;

signals:
    void languageChanged();

private slots:
    void apply();
};

#endif // DIALOGSETTINGSEVNIRONMENT_H
