#ifndef DXF_BASE_TEXT_H
#define DXF_BASE_TEXT_H

//#include <QMainWindow>
#include <QWidget>
#include <QObject>

#include "src/DXF_control/dxf_layer_control.h"
#include "src/DXF_control/dxf_ltype_control.h"
#include "src/DXF_control/dxf_text_control.h"

class dxf_base_text : public QWidget // QMainWindow
{
	Q_OBJECT
	public:
    explicit dxf_base_text(QWidget *parent = nullptr);

	//QET xml var
	double QET_x;			//10
	double QET_y;			//20
	double QET_size;		//40
	double QET_rotation;	//50


	QString QET_text;		//1
	QString QET_color;
	QString QET_text_style;	//7

	QString QET_layer;			//8
	QString QET_ltype;			//6
	QString QET_handle;			//5
	QString QET_softID;			//330

	QString Result_text;

	QString QET_block_name;
	QString QET_block_name_id;

	QString Create_text();

	signals:

	public slots:

};

#endif // DXF_BASE_TEXT_H
