#include "dxf_base_circle.h"

dxf_base_circle::dxf_base_circle(QWidget *parent) :
	QWidget(parent)
{
}

QString dxf_base_circle::Create_circle()
{
	/* <circle x="-28" y="-8" antialias="true"
	 * style="line-style:normal;line-weight:thin;filling:none;color:black"
	 * diameter="22"/> */

	Result_circle.clear();

	DXF_layer_control New_Layer_Control;
	DXF_Ltype_control New_LType_Control;

	New_Layer_Control.layer_to_find=QET_layer;

	New_LType_Control.FindLT=New_Layer_Control.dxf_layer_ltype();

	QET_line_style=New_LType_Control.Ltype_control();


	Result_circle="     ";

	Result_circle.append("<ellipse");


    /*Result_circle.append(" dxfelmt=");
	Result_circle.append(QChar(34));
	Result_circle.append(QET_block_name);
	Result_circle.append(QChar(34));

	Result_circle.append(" dxfelmtid=");
	Result_circle.append(QChar(34));
	Result_circle.append(QET_block_name_id);
	Result_circle.append(QChar(34));

	Result_circle.append(" dxfid=");
	Result_circle.append(QChar(34));
	Result_circle.append(QET_handle);
    Result_circle.append(QChar(34));*/

	Result_circle.append(" x=");
	Result_circle.append(QChar(34));
	Result_circle.append(QString::number (QET_x-QET_diameter ,'f',2));
	Result_circle.append(QChar(34));

	Result_circle.append(" y=");
	Result_circle.append(QChar(34));
	Result_circle.append(QString::number (-(QET_y+QET_diameter) ,'f',2));
	Result_circle.append(QChar(34));

	Result_circle.append(" antialias=");
	Result_circle.append(QChar(34));
	Result_circle.append(QET_antialias);
	Result_circle.append(QChar(34));

	Result_circle.append(" height=");
	Result_circle.append(QChar(34));
	Result_circle.append(QString::number (QET_diameter*2 ,'f',2));
	Result_circle.append(QChar(34));

	Result_circle.append(" width=");
	Result_circle.append(QChar(34));
	Result_circle.append(QString::number (QET_diameter*2 ,'f',2));
	Result_circle.append(QChar(34));

	Result_circle.append(" style=");
	Result_circle.append(QChar(34));
	Result_circle.append("line-style:");
	Result_circle.append(QET_line_style);
	Result_circle.append(";");
	Result_circle.append("line-weight:");
	Result_circle.append(QET_line_weight);
	Result_circle.append(";");
	Result_circle.append("filling:");
	Result_circle.append(QET_filling);
	Result_circle.append(";");
	Result_circle.append("color:");
	Result_circle.append(QET_color);
	Result_circle.append(";");
	Result_circle.append(QChar(34));


	Result_circle.append(" />");
	Result_circle.append('\n');

	return Result_circle;
}
