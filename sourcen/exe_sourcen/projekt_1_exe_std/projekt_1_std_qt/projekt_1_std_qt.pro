#-------------------------------------------------
#
# Project created by QtCreator 2015-10-09T19:12:15
#
#-------------------------------------------------

QT       -= gui

TARGET = projekt_1_std_vc
TEMPLATE = lib

DEFINES += projekt_1_STD_QT_LIBRARY

SOURCES += \
    ../sourcen/std_sourcen/Function.c \
    ../sourcen/std_sourcen/IbvStudioCommonFunctions.c \
    ../sourcen/std_sourcen/IbvStudioDllEntry.c

HEADERS += \
    ../sourcen/projekt_1_main.h \
    ../sourcen/schalter.h \
    ../sourcen/std_sourcen/DllFunctionInfo.h \
    ../sourcen/std_sourcen/Function.h \
    ../sourcen/std_sourcen/GlobalDefs.h \
    ../sourcen/std_sourcen/IbvStudioCommonFunctions.h \
    ../sourcen/std_sourcen/qt_debug_bug.h

LIBS += -L"i:/vorlagen/sys_dlls/" -libv_dll_d
LIBS += -L"i:/vorlagen/sys_dlls/" -lparam_parser_lib_dll_d

unix {
    target.path = /usr/lib
    INSTALLS += target
}
