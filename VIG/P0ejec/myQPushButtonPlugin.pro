TEMPLATE = lib
CONFIG += designer plugin release

HEADERS += myQPushButton.h myQPushButtonPlugin.h
SOURCES += myQPushButton.cpp myQPushButtonPlugin.cpp

target.path = ~/.designer/plugins/designer
INSTALLS += target
