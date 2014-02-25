#ifndef CUSTOMWIDGETPLUGINMEMORY_H
#define CUSTOMWIDGETPLUGINMEMORY_H


#include <QDesignerCustomWidgetInterface>

class myQPushButtonPlugin: public QObject, public QDesignerCustomWidgetInterface
{
  Q_OBJECT
  Q_INTERFACES(QDesignerCustomWidgetInterface)

  public:

    myQPushButtonPlugin(QObject *parent=0);
    bool isContainer() const;
    bool isInitialized() const;
    QIcon icon() const;
    QString domXml() const;
    QString group() const;
    QString includeFile() const;
    QString name() const;
    QString toolTip() const;
    QString whatsThis() const;
    QWidget *createWidget(QWidget *parent);
    void initialize(QDesignerFormEditorInterface *core);

  private:
  
    bool initialized;
};

#endif