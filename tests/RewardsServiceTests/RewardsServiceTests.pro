QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

INCDIR = ../../src
INCLUDEPATH += $$INCDIR
HEADERS += $$INCDIR/eligibilityservice.h $$INCDIR/eligibilityserviceimpl.h $$INCDIR/rewardsservice.h $$INCDIR/rewardsserviceimpl.h
SOURCES += $$INCDIR/rewardsserviceimpl.cpp $$INCDIR/eligibilityserviceimpl.cpp


SOURCES +=  tst_rewardsservicetests.cpp
