TEMPLATE = lib
CONFIG += designer plugin release

HEADERS += myQLabel.h myQLabelPlugin.h
SOURCES += myQLabel.cpp myQLabelPlugin.cpp

target.path = ~/.designer/plugins/designer
INSTALLS += target
