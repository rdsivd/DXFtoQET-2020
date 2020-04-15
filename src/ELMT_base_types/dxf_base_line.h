#ifndef DXF_BASE_LINE_H
#define DXF_BASE_LINE_H

//#include <QMainWindow>
#include <QWidget>
#include <QObject>

#include "src/DXF_control/dxf_layer_control.h"
#include "src/DXF_control/dxf_ltype_control.h"
#include "src/DXF_control/dxf_text_control.h"

class dxf_base_line : public QWidget //QMainWindow
{
	Q_OBJECT
	public:
    explicit dxf_base_line(QWidget *parent = nullptr);


	//DXF var

	double QET_x1;				//10
	double QET_x2;				//11
	double QET_y1;				//20
	double QET_y2;				//21

	QString QET_layer;			//8
	QString QET_ltype;			//6
	QString QET_handle;			//5
	QString QET_softID;			//330

	//int16_t color;			//62

	//QET xml var
	double QET_lenght1;
	double QET_lenght2;
	QString QET_antialias;
	QString QET_end1;
	QString QET_end2;
	QString QET_line_style;
	QString QET_line_weight;
	QString QET_filling;
	QString QET_color;

	QString QET_block_name;
	QString QET_block_name_id;

	QString Result;


	QString CreateElmt();

	signals:

	public slots:

};

#endif // DXF_BASE_LINE_H
