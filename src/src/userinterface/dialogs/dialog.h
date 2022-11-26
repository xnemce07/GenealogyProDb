/*!
 *  \file   dialog.h
 *  \author Eva Navratilova
 */

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QPushButton>

class Dialog : public QDialog
{
    Q_OBJECT
protected:
    QGridLayout _layout;

    QDialogButtonBox *_buttonBox;

public:
    Dialog(QWidget *parent = nullptr);
    virtual ~Dialog() override = default;

protected:
    virtual void fill() = 0;
};

#endif // DIALOG_H
