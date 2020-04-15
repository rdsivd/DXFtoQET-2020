#include "dxf_base_input.h"

dxf_base_input::dxf_base_input(QWidget *parent) :
	QWidget(parent)
{
}


QString dxf_base_input::Create_input()
{

	/* QET_x="0";
	QET_y="10";
	QET_size="9";
	QET_rotate="true";
	QET_text="_";
	QET_tag="label"; */

	DXF_Text_control New_Text_control;

	Result.clear();

	/* <input x="3" y="1" size="9" rotate="true" text="_" tagg="label"/>
	   <input text="_" rotation="90" tagg="label" x="-20" y="-5" size="9" rotate="true"/>*/

	Result.append("     ");
	Result.append("<input");


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
	Result.append(QChar(34));

	Result.append(" dxftagg=");
	Result.append(QChar(34));
	Result.append(QET_dxf_tag);
    Result.append(QChar(34));*/

	Result.append(" x=");
	Result.append(QChar(34));
	Result.append(QString::number(QET_x,'f',2));
	Result.append(QChar(34));

	Result.append(" y=");
	Result.append(QChar(34));
	Result.append(QString::number(-QET_y,'f',2));
	Result.append(QChar(34));

	Result.append(" size=");
	Result.append(QChar(34));
	Result.append(QString::number(QET_size,'f',0));
	Result.append(QChar(34));

	Result.append(" rotation=");
	Result.append(QChar(34));
	Result.append(QString::number(QET_rotation,'f',0));
	Result.append(QChar(34));

	Result.append(" rotate=");
	Result.append(QChar(34));
	Result.append(QET_rotate);
	Result.append(QChar(34));

	Result.append(" color=");
	Result.append(QChar(34));
	Result.append(QET_color);
	Result.append(QChar(34));

	Result.append(" text=");
	Result.append(QChar(34));

	New_Text_control.TextToCheck=QET_text;
	Result.append(New_Text_control.Text_control());
	//Result.append(QET_text);
	Result.append(QChar(34));

	Result.append(" tagg=");
	Result.append(QChar(34));
	Result.append(QET_tag);
	Result.append(QChar(34));

	Result.append(" />");
	Result.append('\n');


	return Result;




}
