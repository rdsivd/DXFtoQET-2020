#include "dxf_base_terminal.h"

dxf_base_terminal::dxf_base_terminal(QWidget *parent) :
	QWidget(parent)
{
}

QString dxf_base_terminal::Create_terminal()
{

	/*QET_x="0";
	QET_y="0";
	QET_orientation="n";*/

	 /* <terminal x="-10" y="-20" orientation="n"/> */

	Result.clear();

	Result.append("     ");
	Result.append("<terminal");


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

	Result.append(" x=");
	Result.append(QChar(34));
	Result.append(QString::number(QET_x,'f',2));
	Result.append(QChar(34));
	Result.append(" y=");
	Result.append(QChar(34));
	Result.append(QString::number(-QET_y,'f',2));
	Result.append(QChar(34));
	Result.append(" orientation=");

	Result.append(QChar(34));
	Result.append("s");
	Result.append(QChar(34));

	Result.append(" />");
	Result.append('\n');

	return Result;

}
