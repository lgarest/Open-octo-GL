#include "myQLabel.h"
#include "myQLabelPlugin.h"
#include <QtPlugin>

myQLabelPlugin :: myQLabelPlugin(QObject *parent): QObject(parent)
{
  initialized = false;
}

void myQLabelPlugin ::initialize(QDesignerFormEditorInterface * core)
{
  if (initialized) return;
  initialized = true;
}

bool myQLabelPlugin ::isInitialized() const
{
  return initialized;
}

QWidget * myQLabelPlugin ::createWidget(QWidget *parent)
{
  return new myQLabel(parent); // Construir el Widget
}

QString myQLabelPlugin ::name() const
{
  return "myQLabel"; // El nom de la classe del Widget
}

QString myQLabelPlugin ::group() const
{
  return "Display Widgets [Examples]";
}

QIcon myQLabelPlugin ::icon() const
{
  return QIcon();
}

QString myQLabelPlugin ::toolTip() const
{
  return "";
}

QString myQLabelPlugin ::whatsThis() const
{
  return "";
}

bool myQLabelPlugin ::isContainer() const
{
  return false;
}

QString myQLabelPlugin ::domXml() const
{
  return "<widget class=\"myQLabel\" name=\"myQLabel_obj\">\n"
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

QString myQLabelPlugin ::includeFile() const
{
  return "myQLabel.h";
}

// Q_EXPORT_PLUGIN2 ( ClassName, PluginName )

Q_EXPORT_PLUGIN2(myQLabel,myQLabelPlugin)
