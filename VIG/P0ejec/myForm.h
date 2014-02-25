#include "ui_form.h"

class myForm:public QWidget{

	Q_OBJECT
	
	public:
		myForm(QWidget* parent=0);
	
	private:
		Ui::myForm ui;
};
