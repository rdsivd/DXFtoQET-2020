#include "dxf_base_rectangel.h"

dxf_base_rectangel::dxf_base_rectangel(QWidget *parent) :
	QWidget(parent)
{
}

QString dxf_base_rectangel::Create_rectangel()
{

	/* <rect width="61" x="-30" y="-12"
	 * antialias="false" height="36"
	 * style="line-style:normal;line-weight:normal;filling:none;color:black"/> */



	Result_rect.clear();

	DXF_layer_control New_Layer_Control;
	DXF_Ltype_control New_LType_Control;

	New_Layer_Control.layer_to_find=QET_layer;

	New_LType_Control.FindLT=New_Layer_Control.dxf_layer_ltype();

	QET_line_style=New_LType_Control.Ltype_control();


	Result_rect.append("     ");
	Result_rect.append("<rect");


    /*Result_rect.append(" dxfelmt=");
	Result_rect.append(QChar(34));
	Result_rect.append(QET_block_name);
	Result_rect.append(QChar(34));

	Result_rect.append(" dxfelmtid=");
	Result_rect.append(QChar(34));
	Result_rect.append(QET_block_name_id);
	Result_rect.append(QChar(34));

	Result_rect.append(" dxfid=");
	Result_rect.append(QChar(34));
	Result_rect.append(QET_handle);
    Result_rect.append(QChar(34));*/

	Result_rect.append(" width=");
	Result_rect.append(QChar(34));
	Result_rect.append(QString::number(QET_width,'f',2));
	Result_rect.append(QChar(34));

	Result_rect.append(" x=");
	Result_rect.append(QChar(34));
	Result_rect.append(QString::number(QET_x,'f',2));
	Result_rect.append(QChar(34));

	Result_rect.append(" y=");
	Result_rect.append(QChar(34));
	Result_rect.append(QString::number(-QET_y,'f',2));
	Result_rect.append(QChar(34));

	Result_rect.append(" antialias=");
	Result_rect.append(QChar(34));
	Result_rect.append(QET_antialias);
	Result_rect.append(QChar(34));

	Result_rect.append(" height=");
	Result_rect.append(QChar(34));
	Result_rect.append(QString::number(QET_height,'f',2));
	Result_rect.append(QChar(34));

	Result_rect.append(" style=");
	Result_rect.append(QChar(34));
	Result_rect.append("line-style:");
	Result_rect.append(QET_line_style);
	Result_rect.append(";");
	Result_rect.append("line-weight:");
	Result_rect.append(QET_line_weight);
	Result_rect.append(";");
	Result_rect.append("filling:");
	Result_rect.append(QET_filling);
	Result_rect.append(";");
	Result_rect.append("color:");
	Result_rect.append(QET_color);
	Result_rect.append(QChar(34));



	Result_rect.append(" />");
	Result_rect.append('\n');



	return Result_rect;

}
