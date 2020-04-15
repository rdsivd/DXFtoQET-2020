#include "dxf_base_polyline.h"

dxf_base_polyline::dxf_base_polyline(QWidget *parent) :
	QWidget(parent)
{
}

QString dxf_base_polyline::Create_polyline()
{
	/* creation of the xml code for a polygon */


	/* <polygon style="line-style:normal;
	 * line-weight:thin;filling:none;color:black"
	 * closed="false"
	 * y1="-100" y2="-90" y3="0" y4="65" y5="75" y6="-20"
	 * antialias="false"
	 * y7="-30" x1="-140" y8="15" x2="0" y9="10" x3="60"
	 * x4="15" x5="-125" x6="-125" x7="-60" x8="-60"
	 * x9="-5" y10="-75" x10="-20" y11="-75" x11="-20"/>*/

	/* <polygon style="line-style:normal;
	 * line-weight:thin;filling:none;color:black"
	 * closed="false"
	 * antialias="false"
	 * x1="107" y1="-179" x2="107" y2="-179"
	 * x3="107" y3="-179" x4="107" y4="-179" /> */

	Result_polyline.clear();

	DXF_layer_control New_Layer_Control;
	DXF_Ltype_control New_LType_Control;

	New_Layer_Control.layer_to_find=QET_layer;

	New_LType_Control.FindLT=New_Layer_Control.dxf_layer_ltype();

	QET_line_style=New_LType_Control.Ltype_control();

	/* create qet elmt code */

	Result_polyline.append("     ");
	Result_polyline.append("<polygon");


    /*Result_polyline.append(" dxfelmt=");
	Result_polyline.append(QChar(34));
	Result_polyline.append(QET_block_name);
	Result_polyline.append(QChar(34));

	Result_polyline.append(" dxfelmtid=");
	Result_polyline.append(QChar(34));
	Result_polyline.append(QET_block_name_id);
	Result_polyline.append(QChar(34));

	Result_polyline.append(" dxfid=");
	Result_polyline.append(QChar(34));
	Result_polyline.append(QET_handle);
    Result_polyline.append(QChar(34));*/

	Result_polyline.append(" style=");

	Result_polyline.append(QChar(34));
	Result_polyline.append("line-style:");
	Result_polyline.append(QET_line_style);
	Result_polyline.append(";");


	Result_polyline.append("line-weight:");
	Result_polyline.append(QET_line_weight);
	Result_polyline.append(";");

	Result_polyline.append("filling:");
	Result_polyline.append(QET_filling);
	Result_polyline.append(";");

	Result_polyline.append("color:");
	Result_polyline.append(QET_color);
	Result_polyline.append(QChar(34));

	Result_polyline.append(" closed=");
	Result_polyline.append(QChar(34));
	Result_polyline.append(QET_closed);
	Result_polyline.append(QChar(34));

	Result_polyline.append(" antialias=");
	Result_polyline.append(QChar(34));
	Result_polyline.append(QET_antialias);
	Result_polyline.append(QChar(34));

	for (count_segments=0; (count_segments<segments) and (count_segments<QET_L_POLYLINE);count_segments++)
	{
        if (QET_x[count_segments]==0.0 and QET_y[count_segments]==0.0)
        {

        }
        else
        {
            Result_polyline.append(" x");
            Result_polyline.append(QString::number(count_segments+1));
            Result_polyline.append("=");
            Result_polyline.append(QChar(34));
            Result_polyline.append(QString::number(QET_x[count_segments],'f',2));
            Result_polyline.append(QChar(34));

            Result_polyline.append(" y");
            Result_polyline.append(QString::number(count_segments+1));
            Result_polyline.append("=");
            Result_polyline.append(QChar(34));
            Result_polyline.append(QString::number(-QET_y[count_segments],'f',2));
            Result_polyline.append(QChar(34));
        }
	}

	Result_polyline.append("/>");
	Result_polyline.append('\n');

	return Result_polyline;

}
