/*!
 *  \file   informationfamilytree.h
 *  \author Eva Navratilova
 */

#ifndef INFORMATIONFAMILYTREE_H
#define INFORMATIONFAMILYTREE_H

#include <QDialog>
#include <QGridLayout>
#include <QTextEdit>
#include <QDialogButtonBox>

#include "kernel.h"
#include "userinterface/dialogs/dialog.h"
#include "userinterface/objects/label.h"
#include "userinterface/objects/labelwidthadjuster.h"

#include "../../centralwindow/tabview/boxes/subbox/subboxdate.h"
#include "../../centralwindow/tabview/boxes/subbox/subboxsimple.h"

class InformationFamilyTree : public Dialog, public LabelWidthAdjuster
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier _subm;

    SubboxSimple *_subboxAuthor;
    //SubboxDate   *_subboxDate;
    Label _laDescription;
    QTextEdit _textDescription;

    QString _author;
    Date _date;
    QString _description;

public:
    InformationFamilyTree(Kernel &k, QWidget *parent = nullptr);

    QString getAuthor() const;
    Date getDate() const;
    QString getDescription() const;

private:
    void fill() override;

    int maxLabelWidth() const override;
    void setLabelsWidth(int width) override;

private slots:
    void changeAuthor(QString text);
    void changeDate(const Date& date);
    void changeDescription();

};

#endif // INFORMATIONFAMILYTREE_H
