/*!
 *  \file   messagebox.h
 *  \author Eva Navratilova
 */

#ifndef MESSAGEBOX_H
#define MESSAGEBOX_H

#include <QMessageBox>

class MessageBox : public QMessageBox
{
    Q_OBJECT
private:
    StandardButtons _acceptButtons;

public:
    MessageBox(Icon icon, const QString &title, const QString &text, StandardButtons buttons = NoButton, StandardButtons acceptButtons = NoButton, QWidget *parent = nullptr, Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
    virtual ~MessageBox() override = default;

public slots:
    virtual int exec() override;
};

#endif // MESSAGEBOX_H
