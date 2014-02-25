#include <QtDesigner/QDesignerExportWidget>
#include <QLabel>
#include <QObject>

class QDESIGNER_WIDGET_EXPORT myQLabel : public QLabel
{
  Q_OBJECT
  
  public:
  
    myQLabel(QWidget* parent=0);
    
  public slots:
  
    void setTextSeguit(const QString &);
    
  signals:

};
