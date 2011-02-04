CC = gcc
CXX = g++
;LEX = flex
;YACC = bison
;QMAKE_LEXFLAGS = --c++ -o lex.lex.c
TEMPLATE = app
QT = gui core opengl
CONFIG += qt \
 warn_on \
 console \
 x86
DESTDIR = bin
OBJECTS_DIR = build
INCLUDEPATH += ./includes
MOC_DIR = build
UI_DIR = build
;LEXSOURCES = lex.l
;YACCSOURCES = parser.yy
FORMS = ui/mainwindow.ui ui/verify.ui
HEADERS = includes/mainwindowimpl.h \
 includes/globals.h \
 includes/utils.h \
 includes/passwd.h \
 includes/user.h \
 includes/user_io.h \
 includes/domain.h \
 includes/domain_io.h \
 includes/alias.h \
 includes/alias_io.h \
 includes/log.h \
 includes/linkedlist.h \
 includes/slinkedlist.h
SOURCES = src/mainwindowimpl.cpp \
 src/globals.cpp \
 src/utils.cpp \
 src/passwd.cpp \
 src/user.cpp \
 src/user_io.cpp \
 src/user_slots.cpp \
 src/domain.cpp \
 src/domain_io.cpp \
 src/domain_slots.cpp \
 src/alias.cpp \
 src/alias_io.cpp \
 src/alias_slots.cpp \
 src/log.cpp \
 src/log_slots.cpp \
 src/main.cpp
unix {

}
