/*!
 *  \file   sourcedetail.h
 *  \author Eva Navratilova
 */

#ifndef SOURCEDETAIL_H
#define SOURCEDETAIL_H

#include <QWidget>
#include <QGridLayout>

#include "../../../../kernel.h"
#include "userinterface/objects/labelwidthadjuster.h"
#include "../boxes/subbox/subboxsimple.h"
#include "../boxes/subbox/subboxweb.h"
#include "../../tabview/boxes/boxsource.h"

class SourceDetail : public QWidget, public LabelWidthAdjuster
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier &_source;

    QGridLayout _layout;

    SubboxSimple *_subboxArchive = nullptr;
    SubboxSimple *_subboxSignature = nullptr;
    SubboxSimple *_subboxOriginator = nullptr;
    SubboxWeb    *_subboxUrl = nullptr;

    BoxSource* _boxSourceBirth = nullptr;
    BoxSource* _boxSourceMarriage = nullptr;
    BoxSource* _boxSourceDeath = nullptr;

    QSpacerItem *_spacer;

public:
    explicit SourceDetail(Kernel &k, Identifier &source, QWidget *parent = nullptr);
    ~SourceDetail() override;

    void update();

private:
    void fill();

    int maxLabelWidth() const override;
    void setLabelsWidth(int width) override;

signals:
    void sourceChanged(Identifier ref);
    void dataChanged();

private slots:
    void changeArchive(const QString text);
    void changeSignature(const QString text);
    void changeOriginator(const QString text);
    void changeUrl(const QString text);

};

#endif // SOURCEDETAIL_H
