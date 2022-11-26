INCLUDEPATH += $$PWD/..
VPATH += $$PWD/..

include(../BuildKernel.pri)

QT += core testlib
QT -= gui

TARGET = ProGenealogyTest

DESTDIR = $${BUILD_DIRECTORY}_tests
OBJECTS_DIR = $${BUILD_DIRECTORY}_tests
MOC_DIR = $${BUILD_DIRECTORY}_tests

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

VPATH += $${APP_DIRECTORY}

TEMPLATE = app

SOURCES +=  tst_testkernel.cpp

HEADERS +=  tst_testkernel.h



