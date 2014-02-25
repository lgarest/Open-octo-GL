#include "myQLabel.h"
#include <iostream>

using namespace std;
    
myQLabel::myQLabel(QWidget* parent) : QLabel(parent) 
{
}


void myQLabel::setTextSeguit(const QString & s)
{
    QString t = this->text();
    if(t.size() != 10){
        t.append(s);
        setText(t);
    }
    else{
        this->clear();
        emit setText(s);
    }
}
