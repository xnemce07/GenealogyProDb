/*!
 *  \file   subboxgeneralright.h
 *  \author Eva Navratilova
 */

#ifndef SUBBOXGENERALRIGHT_H
#define SUBBOXGENERALRIGHT_H

#include <QComboBox>

#include "subbox.h"
#include "subboxsimple.h"

class SubboxGeneralRight : public Subbox
{
    Q_OBJECT
private:
    SubboxSimple *_subboxTit1;
    SubboxSimple *_subboxTit2;

    Label _laGender;
    QComboBox _comboGender;

    CompleterInline *_comTit1 = nullptr;
    CompleterInline *_comTit2 = nullptr;

public:
    SubboxGeneralRight(QWidget *parent = nullptr);
    ~SubboxGeneralRight() override;

    void update(Gender g, const QString& tit1, const QString& tit2,
                const QStringList& tit1s, const QStringList& tit2s);

    int maxLabelWidth() const override;
    void setLabelsWidth(const int width) override;
    void setGenderIndex(Gender g);

private:
    void fill() override;
    void remove();

signals:
    void changeGender(int);
    void changeNameTit1(const QString&);
    void changeNameTit2(const QString&);
};

#endif // SUBBOXGENERALRIGHT_H
