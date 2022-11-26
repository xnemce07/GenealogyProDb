/*!
 *  \file   primitives.h
 *  \author Eva Navratilova
 */

#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#define APP_SH_NAME "PROGEN"
#define APP_VERS_CURR APP_VERS_1_0_2
#define APP_VERS_1_0_0 "1.0.0"
#define APP_VERS_1_0_1 "1.0.1"
#define APP_VERS_1_0_2 "1.0.2"
#define APP_NAME "ProGenealogy"
#define APP_AUTH "Eva Navrátilová"

#include <QDebug>

#include "identifier.h"
#include "event/commoneventstructure.h"


/**
 * @brief
 *
 * @param key
 * @return uint
 */
uint qHash(const Identifier &key);

uint qHash(const CommonEventType &key);



#endif // PRIMITIVES_H
