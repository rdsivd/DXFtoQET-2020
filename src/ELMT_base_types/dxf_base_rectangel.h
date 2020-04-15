#ifndef DXF_BASE_RECTANGEL_H
#define DXF_BASE_RECTANGEL_H

//#include <QMainWindow>
#include <QWidget>
#include <QObject>

#include "src/DXF_control/dxf_layer_control.h"
#include "src/DXF_control/dxf_ltype_control.h"
#include "src/DXF_control/dxf_text_control.h"

class dxf_base_rectangel : public QWidget // QMainWindow
{
	Q_OBJECT
	public:
    explicit dxf_base_rectangel(QWidget *parent = nullptr);

	//QET xml var
	double QET_x;				//10
	double QET_y;				//20
	double QET_width;
	double QET_height;
	double QET_start;
	double QET_angle;

	QString QET_layer;			//8
	QString QET_ltype;			//6
	QString QET_handle;			//5
	QString QET_softID;			//330

	QString QET_antialias;
	QString QET_style;
	QString QET_line_style;
	QString QET_line_weight;
	QString QET_filling;
	QString QET_color;

	QString Result_rect;

	QString QET_block_name;
	QString QET_block_name_id;

	QString Create_rectangel();



	signals:

	public slots:

};

#endif // DXF_BASE_RECTANGEL_H
