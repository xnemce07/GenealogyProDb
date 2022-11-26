/*!
 *  \file   dialogsettingsconstraints.h
 *  \author Eva Navratilova
 */

#ifndef DIALOGSETTINGSRESTRAINTS_H
#define DIALOGSETTINGSRESTRAINTS_H

#include <QDialog>
#include <QSettings>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include <QPushButton>

#include "../../../kernel.h"
#include "userinterface/dialogs/dialog.h"

class DialogSettingsConstraints : public Dialog
{
    Q_OBJECT
private:

    QLabel _laAutoDead;
    QLabel _laAutoMarried;
    QLabel _laMaxAge;
    QLabel _laMinYear;
    QLabel _laMinAgeAtChildbirth;


    QCheckBox _checkAutoDead;
    QCheckBox _checkAutoMarried;
    QSpinBox _spinMaxAge;
    QSpinBox _spinMinYear;
    QSpinBox _spinMinAgeAtChildbirth;

public:
    DialogSettingsConstraints(QWidget *parent = nullptr);
    ~DialogSettingsConstraints() override;

    void accept() override;

private:
    void fill() override;

private slots:
    void apply();
};

#endif // DIALOGSETTINGSRESTRAINTS_H
