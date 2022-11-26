
ROOT_DIRECTORY = $$PWD
APP_DIRECTORY = $$PWD/src
BUILD_DIRECTORY = $${ROOT_DIRECTORY}/build



SOURCES += \
    src/kernel.cpp \
    src/kernel/importer.cpp \
    src/kernel/importer/importergedcom.cpp \
    src/3rd-party/cgGedcom/anselcodec.cpp \
    src/3rd-party/cgGedcom/gedcomnode.cpp \
    src/3rd-party/cgGedcom/gedcomparser.cpp \
    src/kernel/exporter.cpp \
    src/kernel/record.cpp \
    src/kernel/record/recordram.cpp \
    src/kernel/record/recordRAM\date.cpp \
    src/kernel/record/recordRAM\place.cpp \
    src/kernel/record/recordRAM\family.cpp \
    src/kernel/record/recordRAM\individual.cpp \
    src/kernel/record/recordRAM\eventdetail.cpp \
    src/kernel/record/recordRAM\address.cpp \
    src/kernel/record/recordRAM\head.cpp \
    src/kernel/record/recordRAM\identifier\identifierfactory.cpp \
    src/kernel/record/recordRAM\identifier.cpp \
    src/kernel/record/recordRAM\event\commoneventstructure.cpp \
    src/kernel/record/recordRAM/individual/personalnamepieces.cpp \
    src/kernel/record/recordRAM/submitter.cpp \
    src/kernel/record/recordRAM/sourcerecord.cpp \
    src/kernel/record/recordRAM/source/sourcecitation.cpp \
    src/kernel/record/recordRAM/source/eventrecorded.cpp \
    src/kernel/exporter/exportergedcom.cpp \
    src/kernel/importer/importernewproject.cpp \
    src/kernel/record/recordRAM/primitives.cpp

HEADERS += \
    src/kernel.h \
    src/kernel/importer.h \
    src/3rd-party/cgGedcom/anselcodec.h \
    src/3rd-party/cgGedcom/cggedcom.h \
    src/3rd-party/cgGedcom/gedcomnode.h \
    src/3rd-party/cgGedcom/gedcomparser.h \
    src/kernel/exporter.h \
    src/kernel/record.h \
    src/kernel/record/recordram.h \
    src/kernel/record/recordRAM\date.h \
    src/kernel/record/recordRAM\place.h \
    src/kernel/record/recordRAM\family.h \
    src/kernel/record/recordRAM\individual.h \
    src/kernel/record/recordRAM\primitives.h \
    src/kernel/record/recordRAM\eventdetail.h \
    src/kernel/record/recordRAM\address.h \
    src/kernel/record/recordRAM\head.h \
    src/kernel/record/recordRAM\identifier\identifierfactory.h \
    src/kernel/record/recordRAM\identifier.h \
    src/kernel/record/recordRAM\identifier\identifiertype.h \
    src/kernel/record/recordRAM\event\commoneventstructure.h \
    src/kernel/record/recordRAM/individual/personalnamepieces.h \
    src/kernel/record/recordRAM/submitter.h \
    src/kernel/record/recordRAM/sourcerecord.h \
    src/kernel/record/recordRAM/source/sourcecitation.h \
    src/kernel/record/recordRAM/source/eventrecorded.h \
    src/kernel/importer/importergedcom.h \
    src/kernel/exporter/exportergedcom.h \
    src/kernel/importer/importernewproject.h

