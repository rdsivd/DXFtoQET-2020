#ifndef DXF_BASE_INPUT_H
#define DXF_BASE_INPUT_H

//#include <QMainWindow>
#include <QWidget>
#include <QObject>

#include "src/DXF_control/dxf_layer_control.h"
#include "src/DXF_control/dxf_ltype_control.h"
#include "src/DXF_control/dxf_text_control.h"

class dxf_base_input : public QWidget // QMainWindow
{
	Q_OBJECT
	public:
    explicit dxf_base_input(QWidget *parent = nullptr);

	QString Result;



	//QET xml var
	double QET_x;			//10
	double QET_y;			//20
	double QET_rotation;	//50
	double QET_size;	//40

	//int QET_size;
	//QString QET_rotate;

	QString QET_text;		//1
	QString QET_dxf_tag;	//2
	QString QET_color;
	QString QET_text_style;	//7
	QString QET_rotate;

	QString QET_layer;			//8
	QString QET_ltype;			//6
	QString QET_handle;			//5
	QString QET_softID;			//330


	QString QET_tag;

	QString QET_block_name;
	QString QET_block_name_id;

	QString Create_input();

	signals:

	public slots:

};

#endif // DXF_BASE_INPUT_H
