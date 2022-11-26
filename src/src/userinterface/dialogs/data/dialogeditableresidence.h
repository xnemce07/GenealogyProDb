/*!
 *  \file   dialogeditableresidnece.h
 *  \author Eva Navratilova
 */

#ifndef DIALOGEDITABLERESIDENCE_H
#define DIALOGEDITABLERESIDENCE_H

#include "dialogeditable.h"
#include "userinterface/objects/completerinline.h"

class DialogEditableResidence : public DialogEditable, public LabelWidthAdjuster
{
    Q_OBJECT
private:
    SubboxSimple *_subboxCity;
    SubboxSimple *_subboxAddress;

    CompleterInline *_comCity = nullptr;
    CompleterInline *_comAddr = nullptr;

    QString &_city;
    QString &_address;

public:
    DialogEditableResidence(const QString title, QString &city, QString &address, DateType &datetype, Date &date1, Date &date2, const QStringList &cities, const QStringList& addresses, QWidget *parent = nullptr);
    ~DialogEditableResidence() override;

private:
    void fill() override;
    int maxLabelWidth() const override;
    void setLabelsWidth(const int width) override;

private slots:
    void changeCity(const QString city);
    void changeAddress(const QString addr);
};

#endif // DIALOGEDITABLERESIDENCE_H
