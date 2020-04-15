#ifndef DXF_BASE_POLYLINE_H
#define DXF_BASE_POLYLINE_H

//#include <QMainWindow>
#include <QWidget>
#include <QObject>

#include "src/DXF_control/dxf_layer_control.h"
#include "src/DXF_control/dxf_ltype_control.h"
#include "src/DXF_control/dxf_text_control.h"

class dxf_base_polyline : public QWidget // QMainWindow
{
	Q_OBJECT
	public:
    explicit dxf_base_polyline(QWidget *parent = nullptr);

	QString Result_polyline;

	QString QET_line_style;
	QString QET_line_weight;
	QString QET_filling;
	QString QET_color;
	QString QET_closed;
	QString QET_antialias;

	QString QET_layer;			//8
	QString QET_ltype;			//6
	QString QET_handle;			//5
	QString QET_softID;			//330

	double QET_x[QET_L_POLYLINE];
	double QET_y[QET_L_POLYLINE];

	int count_segments;
	int segments;

	QString QET_block_name;
	QString QET_block_name_id;


	QString Create_polyline();

	signals:

	public slots:

};

#endif // DXF_BASE_POLYLINE_H
