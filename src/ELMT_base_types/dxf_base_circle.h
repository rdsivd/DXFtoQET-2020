#ifndef DXF_BASE_CIRCLE_H
#define DXF_BASE_CIRCLE_H

//#include <QMainWindow>
#include <QWidget>
#include <QObject>

#include "src/DXF_control/dxf_layer_control.h"
#include "src/DXF_control/dxf_ltype_control.h"
#include "src/DXF_control/dxf_text_control.h"

class dxf_base_circle : public QWidget // QMainWindow
{
	Q_OBJECT
	public:
    explicit dxf_base_circle(QWidget *parent = nullptr);

	QString Result_circle;

	//DXF var
	double QET_x;				//10
	double QET_y;				//20
	double QET_diameter;		//40 radius

	QString QET_layer;			//8
	QString QET_ltype;			//6
	QString QET_handle;			//5
	QString QET_softID;			//330

	//QET xml var
	QString QET_antialias;
	QString QET_line_style;
	QString QET_line_weight;
	QString QET_filling;
	QString QET_color;
	QString QET_block_name;
	QString QET_block_name_id;


	QString Create_circle();

	signals:

	public slots:

};

#endif // DXF_BASE_CIRCLE_H
