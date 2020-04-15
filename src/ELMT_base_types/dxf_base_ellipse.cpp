#include "dxf_base_ellipse.h"

dxf_base_ellipse::dxf_base_ellipse(QWidget *parent) :
	QWidget(parent)
{
}

QString dxf_base_ellipse::Create_ellipse()
{
	/* <ellipse width="38"
	 * x="-15" y="34"
	 * antialias="true"
	 * height="13"
	 * style="line-style:normal;line-weight:normal;filling:none;color:black"/>*/
	Result_ellipse.clear();

	DXF_layer_control New_Layer_Control;
	DXF_Ltype_control New_LType_Control;

	New_Layer_Control.layer_to_find=QET_layer;

	New_LType_Control.FindLT=New_Layer_Control.dxf_layer_ltype();

	QET_line_style=New_LType_Control.Ltype_control();

	QET_width=QET_major_radius_x*2;
	QET_height=QET_major_radius_x*2*QET_ratio_minor_axis;

	//QET_x=QET_center_x-(QET_width/2);
	//QET_y=(QET_center_y-(QET_height/2));

	QET_x=QET_center_x;
	QET_y=QET_center_y;

	// radians to degrees
	start_angle=(180*(QET_Start_parameter/3.141592654));
	end_angle=(180*(QET_end_parameter/3.141592654));

	QET_angle=end_angle-start_angle;
	QET_start=start_angle;


	Result_ellipse.append("     ");
	Result_ellipse.append("<arc");


    /*Result_ellipse.append(" dxfelmt=");
	Result_ellipse.append(QChar(34));
	Result_ellipse.append(QET_block_name);
	Result_ellipse.append(QChar(34));

	Result_ellipse.append(" dxfelmtid=");
	Result_ellipse.append(QChar(34));
	Result_ellipse.append(QET_block_name_id);
	Result_ellipse.append(QChar(34));

	Result_ellipse.append(" dxfid=");
	Result_ellipse.append(QChar(34));
	Result_ellipse.append(QET_handle);
    Result_ellipse.append(QChar(34));*/

	Result_ellipse.append(" width=");
	Result_ellipse.append(QChar(34));
	Result_ellipse.append(QString::number(QET_width,'f',2));
	Result_ellipse.append(QChar(34));

	Result_ellipse.append(" x=");
	Result_ellipse.append(QChar(34));
	Result_ellipse.append(QString::number(QET_x,'f',2));
	Result_ellipse.append(QChar(34));

	Result_ellipse.append(" y=");
	Result_ellipse.append(QChar(34));
	Result_ellipse.append(QString::number(-QET_y,'f',2));
	Result_ellipse.append(QChar(34));

	Result_ellipse.append(" antialias=");
	Result_ellipse.append(QChar(34));
	Result_ellipse.append(QET_antialias);
	Result_ellipse.append(QChar(34));

	Result_ellipse.append(" height=");
	Result_ellipse.append(QChar(34));
	Result_ellipse.append(QString::number(QET_height,'f',2));
	Result_ellipse.append(QChar(34));

	Result_ellipse.append(" style=");
	Result_ellipse.append(QChar(34));
	Result_ellipse.append("line-style:");
	Result_ellipse.append(QET_line_style);
	Result_ellipse.append(";");
	Result_ellipse.append("line-weight:");
	Result_ellipse.append(QET_line_weight);
	Result_ellipse.append(";");
	Result_ellipse.append("filling:");
	Result_ellipse.append(QET_filling);
	Result_ellipse.append(";");
	Result_ellipse.append("color:");
	Result_ellipse.append(QET_color);
	Result_ellipse.append(QChar(34));

	Result_ellipse.append(" start=");
	Result_ellipse.append(QChar(34));
	Result_ellipse.append(QString::number(QET_start,'f',0));
	Result_ellipse.append(QChar(34));

	Result_ellipse.append(" angle=");
	Result_ellipse.append(QChar(34));
	Result_ellipse.append(QString::number(QET_angle,'f',0));
	Result_ellipse.append(QChar(34));

	Result_ellipse.append(" />");
	Result_ellipse.append('\n');

	return Result_ellipse;
}


