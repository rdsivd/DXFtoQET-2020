#ifndef DXF_BASE_TERMINAL_H
#define DXF_BASE_TERMINAL_H

//#include <QMainWindow>
#include <QWidget>
#include <QObject>

class dxf_base_terminal : public QWidget // QMainWindow
{
	Q_OBJECT
	public:
    explicit dxf_base_terminal(QWidget *parent = nullptr);

	QString Result;



	//QET xml var
	double QET_x;
	double QET_y;
	QString QET_orientation;


	QString QET_layer;			//8
	QString QET_ltype;			//6
	QString QET_handle;			//5
	QString QET_softID;			//330

	QString QET_block_name;
	QString QET_block_name_id;

	QString Create_terminal();

	signals:

	public slots:

};

#endif // DXF_BASE_TERMINAL_H
