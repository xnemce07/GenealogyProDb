/*!
 *  \file   subboxgeneralleft.h
 *  \author Eva Navratilova
 */

#ifndef SUBBOXGENERALLEFT_H
#define SUBBOXGENERALLEFT_H

#include <QTimer>

#include "subbox.h"
#include "subboxsimple.h"

class SubboxGeneralLeft : public Subbox
{
    Q_OBJECT
private:
    SubboxSimple *_subboxNameGiven;
    SubboxSimple *_subboxNameMarname;
    SubboxSimple *_subboxNameBirthname;
    CompleterInline *_comNameGiven = nullptr;
    CompleterInline *_comNameMarname = nullptr;
    CompleterInline *_comNameBirthname = nullptr;

public:
    SubboxGeneralLeft(QWidget *parent = nullptr);
    ~SubboxGeneralLeft() override;

    void update(const QString& given, const QString& marname, const QString& birthname,
                const QStringList& givens, const QStringList& marnames, const QStringList& birthnames);

    int maxLabelWidth() const override;
    void setLabelsWidth(const int width) override;

private:
    void fill() override;
    void remove();

signals:
    void changeNameGiven(const QString& name);
    void changeNameMarname(const QString& name);
    void changeNameBirthname(const QString& name);

public slots:
    void setFocus(Qt::FocusReason reason = Qt::FocusReason::NoFocusReason);
};

#endif // SUBBOXGENERALLEFT_H
