/*!
 *  \file   tabstatistics.h
 *  \author Eva Navratilova
 */

#ifndef TABSTATISTICS_H
#define TABSTATISTICS_H

#include <QTextEdit>
#include <QString>

#include "kernel.h"
#include "textformatter.h"
#include "kernel/statistics.h"

class TabStatistics : public QTextEdit
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Statistics *_statistics = nullptr;
    static const QString _notApllicable;

public:
    explicit TabStatistics(Kernel &k, QWidget *parent = nullptr);
    ~TabStatistics() override;

public slots:
    void update();
    void show();

private:
    void fill();
    void remove();

    QString getTextIndividual(const Identifier& indi);
    QString getTextAge(const Age &age);
    QString getTextIndividualAge(const Identifier &indi, const Age &age);

signals:

public slots:
};

#endif // TABSTATISTICS_H
