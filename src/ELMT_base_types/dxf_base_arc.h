#ifndef DXF_BASE_ARC_H
#define DXF_BASE_ARC_H

//#include <QMainWindow>
#include <QWidget>
#include <QObject>

#include "src/DXF_control/dxf_layer_control.h"
#include "src/DXF_control/dxf_ltype_control.h"
#include "src/DXF_control/dxf_text_control.h"
#include "src/DXF_control/dxf_corner_to_elmt.h"

class dxf_base_arc : public QWidget // QMainWindow
{
	Q_OBJECT
	public:
    explicit dxf_base_arc(QWidget *parent = nullptr);

	QString Result_arc;



	//QET xml var
	double QET_x;		//10
	double QET_y;		//20
	double QET_width;	//40*2
	double QET_height;	//40*2
	double QET_start;	//50
	double QET_end;		//51
	double QET_angle;

	QString QET_antialias;
	QString QET_style;
	QString QET_line_style;
	QString QET_line_weight;
	QString QET_filling;
	QString QET_color;

	QString QET_layer;	//8
	QString QET_ltype;	//6
	QString QET_handle;	//5
	QString QET_softID;	//330


	QString QET_block_name;
	QString QET_block_name_id;



	QString Create_arc();


	signals:

	public slots:

};

#endif // DXF_BASE_ARC_H
