#include "dxf_base_line.h"

dxf_base_line::dxf_base_line(QWidget *parent) :
	QWidget(parent)
{
}

QString dxf_base_line::CreateElmt()
{

	Result.clear();

	DXF_layer_control New_Layer_Control;
	DXF_Ltype_control New_LType_Control;

	New_Layer_Control.layer_to_find=QET_layer;

	New_LType_Control.FindLT=New_Layer_Control.dxf_layer_ltype();

	QET_line_style=New_LType_Control.Ltype_control();

	/*<line length1="1.5" length2="1.5" antialias="false"
	 * end1="none" end2="none"
	 * style="line-style:normal;line-weight:normal;filling:none;color:black"
	 * y1="-20" x1="10" y2="-10" x2="10"/>*/


	/* create qet elmt code */

	Result.append("     ");
	Result.append("<line");

    /*Result.append(" dxfelmt=");
	Result.append(QChar(34));
	Result.append(QET_block_name);
	Result.append(QChar(34));

	Result.append(" dxfelmtid=");
	Result.append(QChar(34));
	Result.append(QET_block_name_id);
	Result.append(QChar(34));

	Result.append(" dxfid=");
	Result.append(QChar(34));
	Result.append(QET_handle);
    Result.append(QChar(34));*/

	Result.append(" lenght1=");
	Result.append(QChar(34));
	Result.append(QString::number(QET_lenght1,'f',2));
	Result.append(QChar(34));

	Result.append(" lenght2=");
	Result.append(QChar(34));
	Result.append(QString::number(QET_lenght2,'f',2));
	Result.append(QChar(34));

	Result.append(" antialias=");
	Result.append(QChar(34));
	Result.append(QET_antialias);
	Result.append(QChar(34));

	Result.append(" end1=");
	Result.append(QChar(34));
	Result.append(QET_end1);
	Result.append(QChar(34));

	Result.append(" end2=");
	Result.append(QChar(34));
	Result.append(QET_end2);
	Result.append(QChar(34));

	Result.append(" style=");
	Result.append(QChar(34));
	Result.append("line-style:");
	Result.append(QET_line_style);
	Result.append(";");
	Result.append("line-weight:");
	Result.append(QET_line_weight);
	Result.append(";");
	Result.append("filling:");
	Result.append(QET_filling);
	Result.append(";");
	Result.append("color:");
	Result.append(QET_color);
	Result.append(QChar(34));

	Result.append(" x1=");
	Result.append(QChar(34));
	Result.append(QString::number(QET_x1,'f',2));
	Result.append(QChar(34));

	Result.append(" y1=");
	Result.append(QChar(34));
	Result.append(QString::number(-QET_y1,'f',2));
	Result.append(QChar(34));

	Result.append(" x2=");
	Result.append(QChar(34));
	Result.append(QString::number(QET_x2,'f',2));
	Result.append(QChar(34));

	Result.append(" y2=");
	Result.append(QChar(34));
	Result.append(QString::number(-QET_y2,'f',2));
	Result.append(QChar(34));

	Result.append(" />");
	Result.append('\n');




	return Result;
}
