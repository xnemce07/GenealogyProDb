/*!
 *  \file   dialogeditabledescription.h
 *  \author Eva Navratilova
 */

#ifndef DIALOGEDITABLEDESCRIPTION_H
#define DIALOGEDITABLEDESCRIPTION_H

#include "dialogeditable.h"
#include "userinterface/objects/completerinline.h"


class DialogEditableDescription : public DialogEditable, public LabelWidthAdjuster
{
    Q_OBJECT
private:
    SubboxSimple *_subboxDescription;
    QString &_description;

    CompleterInline *_comDescription;

public:
    DialogEditableDescription(const QString title, QString &description, DateType &datetype, Date &date1, Date &date2, const QStringList& descriptions, QWidget *parent = nullptr);

private:
    void fill() override;

    int maxLabelWidth() const override;
    void setLabelsWidth(const int width) override;

private slots:
    void changeDescription(const QString& descr);
};

#endif // DIALOGEDITABLEDESCRIPTION_H
