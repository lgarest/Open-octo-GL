#include "myQPushButton.h"
#include <iostream>

using namespace std;
    
myQPushButton::myQPushButton(QWidget* parent) : QPushButton(parent) 
{
}


void myQPushButton::colorBoto()
{
    QString s; 
    //s = this->objectName();
    s=this->lletra();
       
    emit clicked(s);
}
