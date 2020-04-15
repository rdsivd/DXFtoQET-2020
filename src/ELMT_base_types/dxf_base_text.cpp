#include "dxf_base_text.h"

dxf_base_text::dxf_base_text(QWidget *parent) :
	QWidget(parent)
{
}

QString dxf_base_text::Create_text()

{
	/*  <text x="-11" y="3" size="6" rotation="90" text="Vcc"/>
		<text x="-7" y="-8" size="3" text="HC-SR04"/>
		<text x="-50" y="-45" text="Test" color="white" size="9"/>*/

	Result_text.clear();

	DXF_Text_control New_Text_control;



	Result_text.append("     ");
	Result_text.append("<text");


    /*Result_text.append(" dxfelmt=");
	Result_text.append(QChar(34));
	Result_text.append(QET_block_name);
	Result_text.append(QChar(34));

	Result_text.append(" dxfelmtid=");
	Result_text.append(QChar(34));
	Result_text.append(QET_block_name_id);
	Result_text.append(QChar(34));

	Result_text.append(" dxfid=");
	Result_text.append(QChar(34));
	Result_text.append(QET_handle);
    Result_text.append(QChar(34));*/

	Result_text.append(" x=");
	Result_text.append(QChar(34));
	Result_text.append(QString::number(QET_x,'f',2));
	Result_text.append(QChar(34));

	Result_text.append(" y=");
	Result_text.append(QChar(34));
	Result_text.append(QString::number(-QET_y,'f',2));
	Result_text.append(QChar(34));

	Result_text.append(" size=");
	Result_text.append(QChar(34));
	Result_text.append(QString::number(QET_size,'f',0));
	Result_text.append(QChar(34));

	Result_text.append(" rotation=");
	Result_text.append(QChar(34));
	Result_text.append(QString::number(QET_rotation,'f',0));
	Result_text.append(QChar(34));

	Result_text.append(" color=");
	Result_text.append(QChar(34));
	Result_text.append(QET_color);
	Result_text.append(QChar(34));

	Result_text.append(" text=");
	Result_text.append(QChar(34));
	New_Text_control.TextToCheck=QET_text;
	Result_text.append(New_Text_control.Text_control());
	Result_text.append(QChar(34));



	Result_text.append(" />");
	Result_text.append('\n');

	return Result_text;

}
