#include "dxf_base_arc.h"

dxf_base_arc::dxf_base_arc(QWidget *parent) :
	QWidget(parent)
{
}

QString dxf_base_arc::Create_arc()
{

/*  <arc width="20" x="-15" y="-8" antialias="true"
 *  height="38" style="line-style:normal;
 *  line-weight:normal;filling:none;color:black"
 *  start="-30" angle="-299"/> */

	Result_arc.clear();

	DXF_layer_control New_Layer_Control;
	DXF_Ltype_control New_LType_Control;
	dxf_corner_to_elmt New_corner_control;

	New_corner_control.start_angle=QET_start;
	New_corner_control.end_angle=QET_end;

	QET_start=New_corner_control.QET_start_angle();

	QET_end=New_corner_control.QET_end_angle();

	New_corner_control.begin2=New_corner_control.begin0;
	New_corner_control.einde2=New_corner_control.einde0;
	New_corner_control.start_angle2=New_corner_control.start_angle;
	New_corner_control.end_angle2=New_corner_control.end_angle;

	QET_angle=New_corner_control.QET_corner_angle();

	New_Layer_Control.layer_to_find=QET_layer;

	New_LType_Control.FindLT=New_Layer_Control.dxf_layer_ltype();

	QET_line_style=New_LType_Control.Ltype_control();

	Result_arc.append("     ");
	Result_arc.append("<arc");


    /*Result_arc.append(" dxfelmt=");
	Result_arc.append(QChar(34));
	Result_arc.append(QET_block_name);
	Result_arc.append(QChar(34));

	Result_arc.append(" dxfelmtid=");
	Result_arc.append(QChar(34));
	Result_arc.append(QET_block_name_id);
	Result_arc.append(QChar(34));

	Result_arc.append(" dxfid=");
	Result_arc.append(QChar(34));
	Result_arc.append(QET_handle);
    Result_arc.append(QChar(34));*/

	Result_arc.append(" width=");
	Result_arc.append(QChar(34));
	Result_arc.append(QString::number(QET_width,'f',2));
	Result_arc.append(QChar(34));

	Result_arc.append(" x=");
	Result_arc.append(QChar(34));
	Result_arc.append(QString::number(QET_x,'f',2));
	Result_arc.append(QChar(34));

	Result_arc.append(" y=");
	Result_arc.append(QChar(34));
	Result_arc.append(QString::number(-QET_y,'f',2));
	Result_arc.append(QChar(34));

	Result_arc.append(" antialias=");
	Result_arc.append(QChar(34));
	Result_arc.append(QET_antialias);
	Result_arc.append(QChar(34));

	Result_arc.append(" height=");
	Result_arc.append(QChar(34));
	Result_arc.append(QString::number(QET_height,'f',2));
	Result_arc.append(QChar(34));

	Result_arc.append(" style=");
	Result_arc.append(QChar(34));
	Result_arc.append("line-style:");
	Result_arc.append(QET_line_style);
	Result_arc.append(";");
	Result_arc.append("line-weight:");
	Result_arc.append(QET_line_weight);
	Result_arc.append(";");
	Result_arc.append("filling:");
	Result_arc.append(QET_filling);
	Result_arc.append(";");
	Result_arc.append("color:");
	Result_arc.append(QET_color);
	Result_arc.append(QChar(34));

	Result_arc.append(" start=");
	Result_arc.append(QChar(34));
	Result_arc.append(QString::number(QET_start,'f',0));
	Result_arc.append(QChar(34));

	Result_arc.append(" angle=");
	Result_arc.append(QChar(34));
	Result_arc.append(QString::number(QET_angle,'f',0));
	Result_arc.append(QChar(34));

	Result_arc.append(" />");
	Result_arc.append('\n');

	return Result_arc;
}
