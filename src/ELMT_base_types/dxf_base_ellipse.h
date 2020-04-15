#ifndef DXF_BASE_ELLIPSE_H
#define DXF_BASE_ELLIPSE_H

//#include <QMainWindow>
#include <QWidget>
#include <QObject>

#include "src/DXF_control/dxf_layer_control.h"
#include "src/DXF_control/dxf_ltype_control.h"
#include "src/DXF_control/dxf_text_control.h"

class dxf_base_ellipse : public QWidget // QMainWindow
{
	Q_OBJECT
	public:
    explicit dxf_base_ellipse(QWidget *parent = nullptr);

	QString Result_ellipse;
	/* <ellipse width="38"
	 * x="-15" y="34"
	 * antialias="true"
	 * height="13"
	 * style="line-style:normal;line-weight:normal;filling:none;color:black"/>*/

	//QET xml var
	double QET_x;
	double QET_y;
	double QET_center_x;			//10
	double QET_center_y;			//20
	double QET_major_radius_x;		//11
	double QET_major_radius_y;		//21
	double QET_width;
	double QET_height;
	double QET_start;
	double QET_angle;
	double QET_ratio_minor_axis;	//40
	double QET_Start_parameter;		//41
	double QET_end_parameter;		//42

	//double QET_diameter;


	QString QET_antialias;

	QString QET_line_style;
	QString QET_line_weight;
	QString QET_filling;
	QString QET_color;

	QString QET_layer;			//8
	QString QET_ltype;			//6
	QString QET_handle;			//5
	QString QET_softID;			//330

	double major_lenght;
	double minor_lenght;
	double start_angle;
	double end_angle;

	QString QET_block_name;
	QString QET_block_name_id;




	QString Create_ellipse();



	signals:

	public slots:

};

#endif // DXF_BASE_ELLIPSE_H
