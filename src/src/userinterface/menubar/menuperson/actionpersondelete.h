/*!
 *  \file   actionpersondelete.h
 *  \author Eva Navratilova
 */

#ifndef ACTIONPERSONDELETE_H
#define ACTIONPERSONDELETE_H

#include "../action.h"
#include "../../dialogs/messageboxes/messagedelete.h"
#include "../../../textformatter.h"

class ActionPersonDelete : public Action
{
    Q_OBJECT
private:
    Kernel &_kernel;
    Identifier _individualToDelete; /**< Intentionally not a refference -> can be used
                                            in a context menu in list view */
    MessageDelete *_dialogDelete;

public:
    ActionPersonDelete(Kernel &k, Identifier p, QWidget *parent = nullptr);

    void translate() override;

private:
    void process() override;

signals:
    void individualDeleted(const Identifier ref);

public slots:
    void changePerson(const Identifier ref);
};

#endif // ACTIONPERSONDELETE_H
