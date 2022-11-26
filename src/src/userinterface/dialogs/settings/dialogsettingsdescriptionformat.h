/*!
 *  \file   dialogsettingsdescriptionformat.h
 *  \author Eva Navratilova
 */

#ifndef DIALOGSETTINGSDESCRIPTIONFORMAT_H
#define DIALOGSETTINGSDESCRIPTIONFORMAT_H

#include <QSettings>
#include <QSpacerItem>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>

#include "kernel.h"
#include "textformatter.h"
#include "userinterface/dialogs/dialog.h"
#include "userinterface/objects/splitter.h"

class DialogSettingsDescriptionFormat : public Dialog
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier &_ref;
    FormatableText _formatable;
    QString _settingsKey;
    QString _settingsBackup;
    QString _legend;
    std::function<QString (Kernel&, Identifier)> _getPreview;

    Splitter _splitter;
    QWidget _left, _right;
    QGridLayout _layoutLeft, _layoutRight;

    QLabel _laLegend;
    QTextEdit _textLegend;

    QLabel _laFormat;
    QLineEdit _lineFormat;
    QTextEdit _textFormat;

    QLabel _laPreview;
    QLabel _laPreviewText;

    QSpacerItem *_spacer;

public:
    DialogSettingsDescriptionFormat(Kernel &k, Identifier &r, FormatableText f, QWidget* parent = nullptr);

private:
    void fill() override;
    void changePreview(const QString& text);
    void lineTextFormatFromSettings();

private slots:
    void changePreviewText();
    void changePreviewLine(const QString& text);
    void checkEmptyText();
    void checkEmptyLine(const QString& text);

    virtual void accept() override;
    virtual void reject() override;
    void restoreDefaults();
};

#endif // DIALOGSETTINGSDESCRIPTIONFORMAT_H
