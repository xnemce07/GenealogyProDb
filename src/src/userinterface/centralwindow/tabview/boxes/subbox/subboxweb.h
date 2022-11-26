/*!
 *  \file   subboxweb.h
 *  \author Eva Navratilova
 */

#ifndef SUBBOXWEB_H
#define SUBBOXWEB_H

#include <QDesktopServices>
#include <QIcon>

#include "subbox.h"
#include "userinterface/objects/lineeditselected.h"
#include "userinterface/objects/narrowbutton.h"

class SubboxWeb : public Subbox
{
    Q_OBJECT
private:
    QString _textLabel;

    Label _laUrl;
    LineEditSelected _lineUrl;
    NarrowButton _buUrl;
    QUrl _url;

public:
    SubboxWeb(QString title = tr("Web"), QWidget *parent = nullptr);
    ~SubboxWeb() override = default;

    void update(const QString& url);
    void setEnabled(bool enabled);

    int maxLabelWidth() const override;
    void setLabelsWidth(int width) override;

private:
    void fill() override;

signals:
    void urlChanged(const QString text);

private slots:
    void changeUrl();
    void changeUrlButtonState(const QString &text);

    void openUrl(bool checked);
};

#endif // SUBBOXWEB_H
