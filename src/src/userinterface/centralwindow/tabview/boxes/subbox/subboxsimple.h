/*!
 *  \file   subboxsimple.h
 *  \author Eva Navratilova
 */

#ifndef SUBBOXPLACE_H
#define SUBBOXPLACE_H

#include <QLabel>
#include <QLineEdit>

#include "subbox.h"
#include "userinterface/objects/completerinline.h"

class SubboxSimple : public Subbox
{
    Q_OBJECT
private:
    QString _textLabel;

    Label _laSimple;
    QLineEdit _lineSimple;

public:
    explicit SubboxSimple(QString title, QWidget *parent = nullptr);

    void update(QString place);
    void setEnabled(bool enabled);

    void setFocus(Qt::FocusReason reason = Qt::FocusReason::NoFocusReason);
    int maxLabelWidth() const override;
    void setLabelsWidth(int width) override;
    void setCompleter(QCompleter *completer);

signals:
    void textChanged(const QString& plac);

private slots:
    void changeText();

private:
    void fill() override;
};

#endif // SUBBOXPLACE_H
