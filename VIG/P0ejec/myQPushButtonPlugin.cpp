#include "myQPushButton.h"
#include "myQPushButtonPlugin.h"
#include <QtPlugin>

myQPushButtonPlugin :: myQPushButtonPlugin(QObject *parent): QObject(parent)
{
  initialized = false;
}

void myQPushButtonPlugin ::initialize(QDesignerFormEditorInterface * core)
{
  if (initialized) return;
  initialized = true;
}

bool myQPushButtonPlugin ::isInitialized() const
{
  return initialized;
}

QWidget * myQPushButtonPlugin ::createWidget(QWidget *parent)
{
  return new myQPushButton(parent); // Construir el Widget
}

QString myQPushButtonPlugin ::name() const
{
  return "myQPushButton"; // El nom de la classe del Widget
}

QString myQPushButtonPlugin ::group() const
{
  return "Display Widgets [Examples]";
}

QIcon myQPushButtonPlugin ::icon() const
{
  return QIcon();
}

QString myQPushButtonPlugin ::toolTip() const
{
  return "";
}

QString myQPushButtonPlugin ::whatsThis() const
{
  return "";
}

bool myQPushButtonPlugin ::isContainer() const
{
  return false;
}

QString myQPushButtonPlugin ::domXml() const
{
  return "<widget class=\"myQPushButton\" name=\"myQPushButton_obj\">\n"
  " <property name=\"geometry\">\n"
  " <rect>\n"
  " <x>0</x>\n"
  " <y>0</y>\n"
  " <width>100</width>\n"
  " <height>100</height>\n"
  " </rect>\n"
  " </property>\n"
  "</widget>\n";
}

QString myQPushButtonPlugin ::includeFile() const
{
  return "myQPushButton.h";
}

// Q_EXPORT_PLUGIN2 ( ClassName, PluginName )

Q_EXPORT_PLUGIN2(myQPushButton,myQPushButtonPlugin)
