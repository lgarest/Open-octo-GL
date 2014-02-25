#ifndef MYQPUSHBUTTON_H
#define MYQPUSHBUTTON_H

#include <QtGui/QPushButton>
#include <QObject>
#include <QString>

class myQPushButton : public QPushButton
{
  Q_OBJECT
  
  Q_PROPERTY(QString lletra READ lletra WRITE setlletra)
  
  public:
  
    myQPushButton(QWidget* parent=0);
    
    QString lletra() const {return m_lletra;}
    void setlletra(QString s){m_lletra=s;}
    
  public slots:
  
    void colorBoto();
    
  signals:
  
    void clicked(const QString &);
    
  private:
    
    QString m_lletra;

};

#endif
