/*!
 *  \file   sourcescrollarea.h
 *  \author Eva Navratilova
 */

#ifndef SOURCESCROLLAREA_H
#define SOURCESCROLLAREA_H

#include <QScrollArea>
#include <QGridLayout>

#include "../../../../kernel.h"
#include "sourcedetail.h"

class SourceScrollArea : public QScrollArea
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier &_source;

    SourceDetail *_sourceDetail;

public:
    SourceScrollArea(Kernel &k, Identifier &source, QWidget *parent = nullptr);

    void update();

private:
    void fill();

signals:
    void sourceChanged(Identifier ref);
    void dataChanged();

};

#endif // SOURCESCROLLAREA_H
