#ifndef ELMT_BLOCKS_H
#define ELMT_BLOCKS_H

#include <QWidget>
#include <QObject>


#include "data.h"
#include "src/dxf_load.h"
#include "db/dbmanager.h"

#include "src/DXF_control/dxf_layer_control.h"
#include "src/DXF_control/dxf_ltype_control.h"
#include "src/DXF_control/dxf_text_control.h"
#include "src/ELMT_base_types/dxf_base_line.h"
#include "src/ELMT_base_types/dxf_base_circle.h"
#include "src/ELMT_base_types/dxf_base_arc.h"
#include "src/ELMT_base_types/dxf_base_text.h"
#include "src/ELMT_base_types/dxf_base_input.h"
#include "src/ELMT_base_types/dxf_base_terminal.h"
#include "src/ELMT_base_types/dxf_base_ellipse.h"
#include "src/ELMT_base_types/dxf_base_rectangel.h"
#include "src/ELMT_base_types/dxf_base_polyline.h"
#include "src/ELMT_steps/elmt_block_level2.h"

class elmt_blocks : public QWidget
{
	Q_OBJECT
	public:
    explicit elmt_blocks(QWidget *parent = nullptr);

	int end_block;
	int end_seqend;
	int end_lwpoly;

	int read_error1;
	int readrecord;
    int32_t stringsize;

	int32_t count_vertex;
	int32_t xcount;
	int32_t rowcount;
	int32_t max_vertex;
	int32_t Block_count;

	int32_t Block_recod_count;


	QString Logtext;
	QString Recordvalue;
    QString Recordvalue2;
	QString ELMT_ID_instruction;

	QString Rec_Command;
	QString Rec_Blocknaam;

	QString QET_layer;	//8
	QString QET_ltype;	//6
	QString QET_handle;	//5
	QString QET_softID;	//330

	QString QET_block_name;
	QString QET_block_name_id;

	QString filename1;

	QString FromBlock;

	QString QsqlString1;

    double hatchx;
    double hatchy;

	double Block_X;				//10
	double Block_Y;				//20
	double Block_scale_x;		//41
	double Block_scale_y;		//42
	double Block_rotation;		//50

	QString Block_name;			//2
	QString Block_layer;		//8
	QString Block_ltype;		//6
	QString Block_handle;		//5
	QString Block_softID;		//330

	QString QET_antialias;
	QString QET_line_style;
	QString QET_line_weight;
	QString QET_filling;
	QString QET_color;

	QString DXF_Block_Value;
	QString DXF_Block_Name;

	QString Signal_waarde1;
    QString Signal_log1;

    QString Insert_Block_1();

	signals:

	void Signal1 (const QString &Waarde1);
	void send_log(const QString &Waarde2);
	void send_elmt(const QString &Waarde3);
	void send_process(const QString &Waarde4);

	public slots:

};

#endif // ELMT_BLOCKS_H
