# -------------------------------------------------
# Project created by QtCreator 2009-03-25T19:47:32
# -------------------------------------------------
include(./epdf.pri)

TARGET = epdf
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
	qoutputdev.cpp \
    myoutputdev.cpp \
	qbusybar.cpp \
	gooStub.cpp \
	goo/*.cc \
    library/*.cpp \
	xpdf/*.cc

HEADERS += mainwindow.h \
	qoutputdev.h \
    myoutputdev.h \
	qbusybar.h \
	aconf.h fixed.h UTF8.h \
	goo/*.h \
    library/*.h \
	xpdf/*.h

RESOURCES += epdf.qrc
OTHER_FILES += epdf.ini

DESTDIR	= $$BUILDDIR/app
OBJECTS_DIR	= $$BUILDDIR/obj
MOC_DIR	= $$BUILDDIR/moc
RCC_DIR = $$BUILDDIR/rcc

