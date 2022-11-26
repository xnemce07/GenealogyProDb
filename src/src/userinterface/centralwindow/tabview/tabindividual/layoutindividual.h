/*!
 *  \file   layoutindividual.h
 *  \author Eva Navratilova
 */

#ifndef LAYOUTINDIVIDUAL_H
#define LAYOUTINDIVIDUAL_H

#include <QGridLayout>
#include "kernel.h"

class LayoutIndividual : public QGridLayout
{
public:
    LayoutIndividual(Kernel &k, Identifier &p);

private:
    Kernel &_kernel;
    Identifier &_proband;
};

#endif // LAYOUTINDIVIDUAL_H
