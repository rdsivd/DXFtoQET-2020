#include "elmt_blocks.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QtSql>

extern struct DXF_base DXF_main_base[DXF_base_set];
extern struct DXF_Entities DXF_Entities_List;

elmt_blocks::elmt_blocks(QWidget *parent) : QWidget(parent)
{

}

QString elmt_blocks::Insert_Block_1()
{

	//dbManager Manage_Blocks;

    DXF_main_base[0].QDXF_block_arc_color="black";
    DXF_main_base[0].QDXF_block_circle_color="black";
    DXF_main_base[0].QDXF_block_ellipse_color="black";
    DXF_main_base[0].QDXF_block_input_color="black";
    DXF_main_base[0].QDXF_block_line_color="black";
    DXF_main_base[0].QDXF_block_lwpolyline_color="black";
    DXF_main_base[0].QDXF_block_polyline_color="black";
    DXF_main_base[0].QDXF_block_rectangel_color="black";
    DXF_main_base[0].QDXF_block_terminal_color="black";
    DXF_main_base[0].QDXF_block_text_color="black";
    DXF_main_base[0].QDXF_block_solid_color="black";

	xcount=0;
	Logtext="";
	rowcount=0;
	DXF_Block_Name="";
	DXF_Block_Value="";
	Block_count=-1;



	QSqlQuery NewQueryBlock;
	NewQueryBlock.prepare("SELECT * FROM dxf_blocks WHERE dxfbase =(:dxfbase)");
	NewQueryBlock.bindValue(":dxfbase",Block_name);
	NewQueryBlock.exec();



    dxf_base_line New_DXF_Line2;
    dxf_base_circle New_DXF_Circle2;
    dxf_base_arc New_DXF_Arc2;
    dxf_base_text New_DXF_Text2;

    dxf_base_input New_DXF_Input2;
    dxf_base_terminal New_DXF_Terminal2;
    dxf_base_ellipse New_DXF_Ellipse2;
    dxf_base_polyline New_DXF_Polyline2;
    dxf_base_polyline New_DXF_LWPolyline2;
    dxf_base_polyline New_DXF_SOLID2;

    elmt_blocks New_DXF_blocks2;

	connect(&New_DXF_blocks2 ,SIGNAL (Signal1(const QString &)),parent() ,SLOT(update_proces(const QString &)));
    connect(parent() ,SIGNAL (send_log(const QString &)),this ,SLOT(update_log(const QString &)));


	Logtext.append("Converting DXF blocks\n");

	end_block=0;

	Block_recod_count=0;

    Signal_log1.clear();
    Signal_log1.append("DXF file converted blocks");
    Signal_log1.append("\n");
    Signal_log1.append("============================================================================\n");
    Signal_log1.append(QTime::currentTime().toString());
    Signal_log1.append(" \n");

    emit send_log(Signal_log1);

    Signal_log1.clear();
    Signal_log1.append("============================================================================");
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result : ");
    stringsize=DXF_Entities_List.DXF_Result.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Begin : ");
    stringsize=DXF_Entities_List.DXF_ResultBegin.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitie.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Line: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitieLine.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Polyline: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitiePolyline.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Lwpolyline: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitieLwpolyline.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Spline: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitieSpline.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Solid: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitieSolid.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Hatch: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitieHatch.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Block: ");
    stringsize=DXF_Entities_List.DXF_ResultBlock.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Block 2: ");
    stringsize=DXF_Entities_List.DXF_ResultBlock2.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Einde : ");
    stringsize=DXF_Entities_List.DXF_ResultEinde.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    emit send_log(Signal_log1);

	//while (NewQuery.next() and end_block==0)
	//while (NewQuery.next())

	//QSqlRecord Record2=NewQuery.record();

	while (NewQueryBlock.next() and end_block==0)
	{

		QSqlRecord Record2=NewQueryBlock.record();
		Recordvalue=Record2.value("Command").toString();

		Block_recod_count++;


		Signal_waarde1.clear();
		Signal_waarde1.append(QET_handle);
		Signal_waarde1.append(" : ");
		Signal_waarde1.append(Record2.value("Command").toString());
		Signal_waarde1.append(" : ");
		Signal_waarde1.append(Record2.value("dxf_5").toString());

        //emit Signal1(Signal_waarde1);

		if (Record2.value("Command_count").toInt()==0 and Record2.value("Command").toString()=="BLOCK")
		{
			Block_count++;
			ELMT_ID_instruction=Record2.value("ID_instruction").toString();
		}

		rowcount++;

		Rec_Command=Record2.value("Command").toString();
		Rec_Blocknaam=Record2.value("dxf_2").toString();

		DXF_Block_Name=Record2.value("dxf_2").toString();



		if (Record2.value("Command").toString()=="BLOCK" and Record2.value("dxf_2").toString()==Block_name)
		{
			end_block=0;
			read_error1=1;

			while (end_block==0)
			{
				read_error1= NewQueryBlock.next();
				if (read_error1==false)
				{
					end_block++;
				}
				QSqlRecord Record3=NewQueryBlock.record();

				Block_recod_count++;

				Signal_waarde1.clear();
				Signal_waarde1.append(QET_handle);
				Signal_waarde1.append(" : ");
				Signal_waarde1.append(Record3.value("Command").toString());
				Signal_waarde1.append(" : ");
				Signal_waarde1.append(Record3.value("dxf_5").toString());
				Signal_waarde1.append(" : ");
				Signal_waarde1.append(Record3.value("Command_count").toString());

                //emit Signal1(Signal_waarde1);

				if (Record3.value("Command").toString()=="LINE" and Record3.value("Command_count").toInt()==0)
				{
					/*<line length1="1.5" length2="1.5" antialias="false"
					 * end1="none" end2="none"
					 * style="line-style:normal;line-weight:normal;filling:none;color:black"
					 * y1="-20" x1="10" y2="-10" x2="10"/>*/


                    New_DXF_Line2.QET_x1=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
                    New_DXF_Line2.QET_x2=(Record3.value("dxf_11").toDouble()*Block_scale_x)+Block_X;
                    New_DXF_Line2.QET_y1=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;
                    New_DXF_Line2.QET_y2=(Record3.value("dxf_21").toDouble()*Block_scale_y)+Block_Y;

                    New_DXF_Line2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_Line2.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Line.QET_handle=QET_handle;
					//New_DXF_Line.QET_handle.append(":");
                    New_DXF_Line2.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_Line2.QET_block_name=QET_block_name;
                    New_DXF_Line2.QET_block_name_id=QET_block_name_id;
					//New_DXF_Line.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_Line2.QET_softID=Record3.value("dxf_330").toString();

                    New_DXF_Line2.QET_lenght1=1.5;
                    New_DXF_Line2.QET_lenght2=1.5;
                    New_DXF_Line2.QET_antialias="false";
                    New_DXF_Line2.QET_end1="none";
                    New_DXF_Line2.QET_end2="none";

                    New_DXF_Line2.QET_line_style="normal";
                    New_DXF_Line2.QET_line_weight="thin";
                    New_DXF_Line2.QET_filling="none";
                    New_DXF_Line2.QET_color=DXF_main_base[0].QDXF_block_line_color;

                    if (stringsize > QSTRING_max_lengt)
                    {
                        Signal_log1.clear();
                        Signal_log1.append("DXF_Result Block Line : ");
                        stringsize=DXF_Entities_List.DXF_ResultBlock.size();
                        Signal_log1.append(QString::number(stringsize));
                        Signal_log1.append(" \n");
                        emit send_log(Signal_log1);
                    }
                    else
                    {
                        DXF_Entities_List.DXF_ResultBlock.append(New_DXF_Line2.CreateElmt());
                    }
					//DXF_Block_Value.append(New_DXF_Line.CreateElmt());

				}

				if (Record3.value("Command").toString()=="CIRCLE" and Record3.value("Command_count").toInt()==0)
				{
					/* <circle x="-28" y="-8" antialias="true"
					 * style="line-style:normal;line-weight:thin;filling:none;color:black"
					 * diameter="22"/> */

                    New_DXF_Circle2.QET_x=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
                    New_DXF_Circle2.QET_y=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;
                    New_DXF_Circle2.QET_diameter=Record3.value(("dxf_40")).toDouble()*Block_scale_x;

                    New_DXF_Circle2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_Circle2.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Circle.QET_handle=QET_handle;
					//New_DXF_Circle.QET_handle.append(":");
                    New_DXF_Circle2.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_Circle2.QET_block_name=QET_block_name;
                    New_DXF_Circle2.QET_block_name_id=QET_block_name_id;
					//New_DXF_Circle.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_Circle2.QET_softID=Record3.value("dxf_330").toString();

                    New_DXF_Circle2.QET_antialias="false";
                    New_DXF_Circle2.QET_line_style="normal";
                    New_DXF_Circle2.QET_line_weight="thin";
                    New_DXF_Circle2.QET_filling="none";
                    New_DXF_Circle2.QET_color=DXF_main_base[0].QDXF_block_circle_color;

                    if (stringsize > QSTRING_max_lengt)
                    {
                        Signal_log1.clear();
                        Signal_log1.append("DXF_Result Block Circle : ");
                        stringsize=DXF_Entities_List.DXF_ResultBlock.size();
                        Signal_log1.append(QString::number(stringsize));
                        Signal_log1.append(" \n");
                        emit send_log(Signal_log1);
                    }
                    else
                    {
                        DXF_Entities_List.DXF_ResultBlock.append(New_DXF_Circle2.Create_circle());
                    }
					//DXF_Block_Value.append(New_DXF_Circle.Create_circle());
				}

				if (Record3.value("Command").toString()=="ARC" and Record3.value("Command_count").toInt()==0)
				{
					/*  <arc width="20" x="-15" y="-8" antialias="true"
						height="38" style="line-style:normal;
						line-weight:normal;filling:none;color:black"
						start="-30" angle="-299"/> */

                    New_DXF_Arc2.QET_x=((Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X)-(Record3.value("dxf_40").toDouble()*Block_scale_x);
					//New_DXF_Arc.QET_x=((Record3.value("dxf_10").toDouble())+Block_X)-(Record3.value("dxf_40").toDouble()*Block_scale_x);
                    New_DXF_Arc2.QET_y=((Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y)+(Record3.value("dxf_40").toDouble()*Block_scale_y);
					//New_DXF_Arc.QET_y=((Record3.value("dxf_20").toDouble())+Block_Y)+(Record3.value("dxf_40").toDouble()*Block_scale_y);
                    New_DXF_Arc2.QET_width=Record3.value("dxf_40").toDouble()*2*Block_scale_x;
                    New_DXF_Arc2.QET_height=Record3.value("dxf_40").toDouble()*2*Block_scale_y;
                    New_DXF_Arc2.QET_start=Record3.value("dxf_50").toDouble();
                    New_DXF_Arc2.QET_end=Record3.value("dxf_51").toDouble();

                    New_DXF_Arc2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_Arc2.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Arc.QET_handle=QET_handle;
					//New_DXF_Arc.QET_handle.append(":");
                    New_DXF_Arc2.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_Arc2.QET_block_name=QET_block_name;
                    New_DXF_Arc2.QET_block_name_id=QET_block_name_id;
					//New_DXF_Arc.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_Arc2.QET_softID=Record3.value("dxf_330").toString();


                    New_DXF_Arc2.QET_antialias="false";
                    New_DXF_Arc2.QET_line_style="normal";
                    New_DXF_Arc2.QET_line_weight="thin";
                    New_DXF_Arc2.QET_filling="none";
                    New_DXF_Arc2.QET_color=DXF_main_base[0].QDXF_block_arc_color;

                    if (stringsize > QSTRING_max_lengt)
                    {
                        Signal_log1.clear();
                        Signal_log1.append("DXF_Result Block Arc : ");
                        stringsize=DXF_Entities_List.DXF_ResultBlock.size();
                        Signal_log1.append(QString::number(stringsize));
                        Signal_log1.append(" \n");
                        emit send_log(Signal_log1);
                    }
                    else
                    {
                        DXF_Entities_List.DXF_ResultBlock.append(New_DXF_Arc2.Create_arc());
                    }
					//DXF_Block_Value.append(New_DXF_Arc.Create_arc());
				}

				if (Record3.value("Command").toString()=="TEXT" and Record3.value("Command_count").toInt()==0)
				{
					/*  <text x="-11" y="3" size="6" rotation="90" text="Vcc"/>
						<text x="-7" y="-8" size="3" text="HC-SR04"/>
						<text x="-50" y="-45" text="Test" color="white" size="9"/>*/

                    New_DXF_Text2.QET_x=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
					//New_DXF_Text.QET_x=(Record3.value("dxf_10").toDouble())+Block_X;
                    New_DXF_Text2.QET_y=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;
					//New_DXF_Text.QET_y=(Record3.value("dxf_20").toDouble())+Block_Y;

                    New_DXF_Text2.QET_rotation=Record3.value("dxf_50").toDouble();
                    New_DXF_Text2.QET_text=Record3.value("dxf_1").toString();
                    New_DXF_Text2.QET_size=Record3.value("dxf_40").toDouble();
                    New_DXF_Text2.QET_text_style=Record3.value("dxf_7").toString();

                    New_DXF_Text2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_Text2.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Text.QET_handle=QET_handle;
					//New_DXF_Text.QET_handle.append(":");
                    New_DXF_Text2.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_Text2.QET_block_name=QET_block_name;
                    New_DXF_Text2.QET_block_name_id=QET_block_name_id;
					//New_DXF_Text.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_Text2.QET_softID=Record3.value("dxf_330").toString();


					//New_DXF_Text.QET_antialias="false";
					//New_DXF_Text.QET_line_style="normal";
					//New_DXF_Text.QET_line_weight="thin";
					//New_DXF_Text.QET_filling="none";
                    New_DXF_Text2.QET_color=DXF_main_base[0].QDXF_block_text_color;

                    if (stringsize > QSTRING_max_lengt)
                    {
                        Signal_log1.clear();
                        Signal_log1.append("DXF_Result Block Text : ");
                        stringsize=DXF_Entities_List.DXF_ResultBlock.size();
                        Signal_log1.append(QString::number(stringsize));
                        Signal_log1.append(" \n");
                        emit send_log(Signal_log1);
                    }
                    else
                    {
                        DXF_Entities_List.DXF_ResultBlock.append(New_DXF_Text2.Create_text());
                    }
					//DXF_Block_Value.append(New_DXF_Text.Create_text());
				}

				if (Record3.value("Command").toString()=="INPUT" and Record3.value("Command_count").toInt()==0)
				{
					/*  <text x="-11" y="3" size="6" rotation="90" text="Vcc"/>
						<text x="-7" y="-8" size="3" text="HC-SR04"/>
						<text x="-50" y="-45" text="Test" color="white" size="9"/>*/

                    New_DXF_Input2.QET_x=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
                    New_DXF_Input2.QET_y=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;

                    New_DXF_Input2.QET_rotation=Record3.value("dxf_50").toDouble();
                    New_DXF_Input2.QET_text=Record3.value("dxf_1").toString();
                    New_DXF_Input2.QET_size=Record3.value("dxf_40").toDouble()*Block_scale_y;
                    New_DXF_Input2.QET_text_style=Record3.value("dxf_7").toString();
                    New_DXF_Input2.QET_dxf_tag=Record3.value("dxf_2").toString();

                    New_DXF_Input2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_Input2.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Input.QET_handle=QET_handle;
					//New_DXF_Input.QET_handle.append(":");
					//New_DXF_Input.QET_handle.append(Record3.value("dxf_5").toString());
                    New_DXF_Input2.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_Input2.QET_block_name=QET_block_name;
                    New_DXF_Input2.QET_block_name_id=QET_block_name_id;
                    New_DXF_Input2.QET_softID=Record3.value("dxf_330").toString();

					//New_DXF_Text.QET_antialias="false";
					//New_DXF_Text.QET_line_style="normal";
					//New_DXF_Text.QET_line_weight="thin";
					//New_DXF_Text.QET_filling="none";
                    New_DXF_Input2.QET_rotate="true";
                    New_DXF_Input2.QET_tag="none";

                    New_DXF_Input2.QET_color=DXF_main_base[0].QDXF_block_input_color;

                    if (stringsize > QSTRING_max_lengt)
                    {
                        Signal_log1.clear();
                        Signal_log1.append("DXF_Result Block Input : ");
                        stringsize=DXF_Entities_List.DXF_ResultBlock.size();
                        Signal_log1.append(QString::number(stringsize));
                        Signal_log1.append(" \n");
                        emit send_log(Signal_log1);
                    }
                    else
                    {
                        DXF_Entities_List.DXF_ResultBlock.append(New_DXF_Input2.Create_input());
                    }
					//DXF_Block_Value.append(New_DXF_Input.Create_input());
				}

				if (Record3.value("Command").toString()=="ATTRIB" and Record3.value("Command_count").toInt()==0)
				{
					/*  <text x="-11" y="3" size="6" rotation="90" text="Vcc"/>
						<text x="-7" y="-8" size="3" text="HC-SR04"/>
						<text x="-50" y="-45" text="Test" color="white" size="9"/>*/

                    New_DXF_Input2.QET_x=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
                    New_DXF_Input2.QET_y=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;

                    New_DXF_Input2.QET_rotation=Record3.value("dxf_50").toDouble();
                    New_DXF_Input2.QET_text=Record3.value("dxf_1").toString();
                    New_DXF_Input2.QET_size=Record3.value("dxf_40").toDouble()*Block_scale_y;
                    New_DXF_Input2.QET_text_style=Record3.value("dxf_7").toString();

                    New_DXF_Input2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_Input2.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Input.QET_handle=QET_handle;
					//New_DXF_Input.QET_handle.append(":");
					//New_DXF_Input.QET_handle.append(Record3.value("dxf_5").toString());
                    New_DXF_Input2.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_Input2.QET_block_name=QET_block_name;
                    New_DXF_Input2.QET_block_name_id=QET_block_name_id;
                    New_DXF_Input2.QET_softID=Record3.value("dxf_330").toString();


					//New_DXF_Text.QET_antialias="false";
					//New_DXF_Text.QET_line_style="normal";
					//New_DXF_Text.QET_line_weight="thin";
					//New_DXF_Text.QET_filling="none";
                    New_DXF_Input2.QET_rotate="true";
                    New_DXF_Input2.QET_tag="none";

                    New_DXF_Input2.QET_color=DXF_main_base[0].QDXF_block_input_color;

                    if (stringsize > QSTRING_max_lengt)
                    {
                        Signal_log1.clear();
                        Signal_log1.append("DXF_Result Block Attrib : ");
                        stringsize=DXF_Entities_List.DXF_ResultBlock.size();
                        Signal_log1.append(QString::number(stringsize));
                        Signal_log1.append(" \n");
                        emit send_log(Signal_log1);
                    }
                    else
                    {
                        DXF_Entities_List.DXF_ResultBlock.append(New_DXF_Input2.Create_input());
                    }
					//DXF_Block_Value.append(New_DXF_Input.Create_input());
				}

				if (Record3.value("Command").toString()=="POINT" and Record3.value("Command_count").toInt()==0)
				{
					/*  <text x="-11" y="3" size="6" rotation="90" text="Vcc"/>
						<text x="-7" y="-8" size="3" text="HC-SR04"/>
						<text x="-50" y="-45" text="Test" color="white" size="9"/>*/

                    New_DXF_Terminal2.QET_x=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
                    New_DXF_Terminal2.QET_y=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;

                    New_DXF_Terminal2.QET_orientation="north";//Record2.value("dxf_50").toDouble();
					//New_DXF_Input.QET_text=Record2.value("dxf_1").toString();
					//New_DXF_Input.QET_size=Record2.value("dxf_40").toDouble();
					//New_DXF_Input.QET_text_style=Record2.value("dxf_7").toString();

                    New_DXF_Terminal2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_Terminal2.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Terminal.QET_handle=QET_handle;
					//New_DXF_Terminal.QET_handle.append(":");
					//New_DXF_Terminal.QET_handle.append(Record3.value("dxf_5").toString());
                    New_DXF_Terminal2.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_Terminal2.QET_block_name=QET_block_name;
                    New_DXF_Terminal2.QET_block_name_id=QET_block_name_id;
                    New_DXF_Terminal2.QET_softID=Record3.value("dxf_330").toString();


					//New_DXF_Text.QET_antialias="false";
					//New_DXF_Text.QET_line_style="normal";
					//New_DXF_Text.QET_line_weight="thin";
					//New_DXF_Text.QET_filling="none";
					//New_DXF_Input.QET_rotate="true";
					//New_DXF_Input.QET_tag="label";

					//New_DXF_Input.QET_color=DXF_main_base[0].QDXF_circle_color;

                    if (stringsize > QSTRING_max_lengt)
                    {
                        Signal_log1.clear();
                        Signal_log1.append("DXF_Result Block Point : ");
                        stringsize=DXF_Entities_List.DXF_ResultBlock.size();
                        Signal_log1.append(QString::number(stringsize));
                        Signal_log1.append(" \n");
                        emit send_log(Signal_log1);
                    }
                    else
                    {
                        DXF_Entities_List.DXF_ResultBlock.append(New_DXF_Terminal2.Create_terminal());
                    }
					//DXF_Block_Value.append(New_DXF_Terminal.Create_terminal());
				}

				if (Record3.value("Command").toString()=="ELLIPSE" and Record3.value("Command_count").toInt()==0)
				{
					/*  <text x="-11" y="3" size="6" rotation="90" text="Vcc"/>
						<text x="-7" y="-8" size="3" text="HC-SR04"/>
						<text x="-50" y="-45" text="Test" color="white" size="9"/>*/

                    New_DXF_Ellipse2.QET_center_x=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
                    New_DXF_Ellipse2.QET_center_y=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;
                    New_DXF_Ellipse2.QET_major_radius_x=Record3.value("dxf_11").toDouble()*Block_scale_x;
                    New_DXF_Ellipse2.QET_major_radius_y=Record3.value("dxf_21").toDouble()*Block_scale_y;

                    New_DXF_Ellipse2.QET_end_parameter=Record3.value("dxf_42").toDouble();
                    New_DXF_Ellipse2.QET_Start_parameter=Record3.value("dxf_41").toDouble();
                    New_DXF_Ellipse2.QET_ratio_minor_axis=Record3.value("dxf_40").toDouble();

                    New_DXF_Ellipse2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_Ellipse2.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Ellipse.QET_handle=QET_handle;
					//New_DXF_Ellipse.QET_handle.append(":");
					//New_DXF_Ellipse.QET_handle.append(Record3.value("dxf_5").toString());
                    New_DXF_Ellipse2.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_Ellipse2.QET_block_name=QET_block_name;
                    New_DXF_Ellipse2.QET_block_name_id=QET_block_name_id;
                    New_DXF_Ellipse2.QET_softID=Record3.value("dxf_330").toString();

					//New_DXF_Terminal.QET_orientation="sud";//Record2.value("dxf_50").toDouble();
					//New_DXF_Input.QET_text=Record2.value("dxf_1").toString();
					//New_DXF_Input.QET_size=Record2.value("dxf_40").toDouble();
					//New_DXF_Input.QET_text_style=Record2.value("dxf_7").toString();


                    New_DXF_Ellipse2.QET_antialias="false";
                    New_DXF_Ellipse2.QET_line_style="normal";
                    New_DXF_Ellipse2.QET_line_weight="thin";
                    New_DXF_Ellipse2.QET_filling="none";
					//New_DXF_Ellipse.QET_rotate="true";
					//New_DXF_Input.QET_tag="label";

                    New_DXF_Ellipse2.QET_color=DXF_main_base[0].QDXF_block_ellipse_color;

                    if (stringsize > QSTRING_max_lengt)
                    {
                        Signal_log1.clear();
                        Signal_log1.append("DXF_Result Block Ellipse : ");
                        stringsize=DXF_Entities_List.DXF_ResultBlock.size();
                        Signal_log1.append(QString::number(stringsize));
                        Signal_log1.append(" \n");
                        emit send_log(Signal_log1);
                    }
                    else
                    {
                        DXF_Entities_List.DXF_ResultBlock.append(New_DXF_Ellipse2.Create_ellipse());
                    }
					//DXF_Block_Value.append(New_DXF_Ellipse.Create_ellipse());
				}

				if (Record3.value("Command").toString()=="POLYLINE" and Record3.value("Command_count").toInt()==0)
				{
                    for( int xx = 0;xx < QET_L_POLYLINE;xx++ )
                    {
                        New_DXF_Polyline2.QET_x[xx]=0.0;
                        New_DXF_Polyline2.QET_y[xx]=0.0;
                    }

                    New_DXF_Polyline2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_Polyline2.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Polyline.QET_handle=QET_handle;
					//New_DXF_Polyline.QET_handle.append(":");
					//New_DXF_Polyline.QET_handle.append(Record3.value("dxf_5").toString());
                    New_DXF_Polyline2.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_Polyline2.QET_block_name=QET_block_name;
                    New_DXF_Polyline2.QET_block_name_id=QET_block_name_id;
                    New_DXF_Polyline2.QET_softID=Record3.value("dxf_330").toString();

                    New_DXF_Polyline2.QET_antialias="false";
                    New_DXF_Polyline2.QET_line_style="normal";
                    New_DXF_Polyline2.QET_line_weight="thin";
                    New_DXF_Polyline2.QET_filling="none";

                    New_DXF_Polyline2.QET_color=DXF_main_base[0].QDXF_block_polyline_color;

					if (Record3.value("dxf_70").toInt()==1)
					{
                        New_DXF_Polyline2.QET_closed="true";
					}
					else
					{
                        New_DXF_Polyline2.QET_closed="false";
					}

					end_seqend=0;
					count_vertex=0;
					readrecord=1;


					while (end_seqend==0 and count_vertex<QET_L_POLYLINE)
					{
						readrecord=NewQueryBlock.next();
						QSqlRecord Record4=NewQueryBlock.record();
                        //Recordvalue2=Record4.value("Command").toString();
						if (readrecord==true)
						{

							if (Record4.value("Command").toString()=="VERTEX" and Record4.value("Command_count").toInt()==0)
							{
                                New_DXF_Polyline2.QET_x[count_vertex]=(Record4.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
                                New_DXF_Polyline2.QET_y[count_vertex]=(Record4.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;
								count_vertex++;

							}
							else
							{
								if (Record4.value("Command").toString()=="SEQEND" and Record4.value("Command_count").toInt()==0)
								{
									end_seqend=1;
								}

								//count_vertex++;
							}
						}
						else
						{
							end_seqend=1;

						}
						if (Record4.value("Command").toString()=="SEQEND" and Record4.value("Command_count").toInt()==0)
						{
							end_seqend=1;
						}

					}

                    New_DXF_Polyline2.segments=count_vertex;

                    if (stringsize > QSTRING_max_lengt)
                    {
                        Signal_log1.clear();
                        Signal_log1.append("DXF_Result Block Polyline : ");
                        stringsize=DXF_Entities_List.DXF_ResultBlock.size();
                        Signal_log1.append(QString::number(stringsize));
                        Signal_log1.append(" \n");
                        emit send_log(Signal_log1);
                    }
                    else
                    {
                        DXF_Entities_List.DXF_ResultBlock.append(New_DXF_Polyline2.Create_polyline());
                    }
					//DXF_Block_Value.append(New_DXF_Polyline.Create_polyline());


				}

				if (Record3.value("Command").toString()=="INSERT" and Record3.value("Command_count").toInt()==0)
				{
					New_DXF_blocks2.Block_name=Record3.value("dxf_2").toString();
					New_DXF_blocks2.Block_X=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
					New_DXF_blocks2.Block_Y=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;

					New_DXF_blocks2.QET_layer=Record3.value("dxf_8").toString();
					New_DXF_blocks2.QET_ltype=Record3.value("dxf_6").toString();
                    New_DXF_blocks2.QET_handle=QET_handle;
                    New_DXF_blocks2.QET_handle.append(":");
					New_DXF_blocks2.QET_block_name=Record3.value("dxf_2").toString();
                    New_DXF_blocks2.QET_handle.append(":");
					New_DXF_blocks2.QET_handle=Record3.value("dxf_5").toString();
					New_DXF_blocks2.QET_softID=Record3.value("dxf_330").toString();

					New_DXF_blocks2.Block_scale_x=Record3.value("dxf_41").toDouble();
                    if (New_DXF_blocks2.Block_scale_x==0.0)
					{
						New_DXF_blocks2.Block_scale_x=1;
					}
					New_DXF_blocks2.Block_scale_y=Record3.value("dxf_42").toDouble();
                    if (New_DXF_blocks2.Block_scale_y==0.0)
					{
						New_DXF_blocks2.Block_scale_y=1;
					}
					New_DXF_blocks2.Block_rotation=Record3.value("dxf_43").toDouble();

					New_DXF_blocks2.QET_block_name_id=QET_block_name_id;

					Signal_waarde1.clear();
					Signal_waarde1.append("block : ");
					Signal_waarde1.append(Record3.value("dxf_2").toString());
					Signal_waarde1.append(" inside block :");
					Signal_waarde1.append(FromBlock);
					Signal_waarde1.append(" will be converted as a part of the elmt");

                    //emit Signal1(Signal_waarde1);

					New_DXF_blocks2.FromBlock=Record3.value("dxf_2").toString();

                    New_DXF_blocks2.Insert_Block_1();

					//Logtext.append(New_DXF_blocks2.Insert_Block());
					//DXF_Entities_List.DXF_Result.append(New_DXF_blocks2.Insert_Block());

				}

				if (Record3.value("Command").toString()=="LWPOLYLINE" and Record3.value("Command_count").toInt()==0)
				{
                    for( int xx = 0;xx < QET_L_POLYLINE;xx++ )
                    {
                        New_DXF_LWPolyline2.QET_x[xx]=0.0;
                        New_DXF_LWPolyline2.QET_y[xx]=0.0;
                    }

                    New_DXF_LWPolyline2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_LWPolyline2.QET_ltype=Record3.value("dxf_6").toString();
                    New_DXF_LWPolyline2.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_LWPolyline2.QET_softID=Record3.value("dxf_330").toString();

                    New_DXF_LWPolyline2.QET_antialias="false";
                    New_DXF_LWPolyline2.QET_line_style="normal";
                    New_DXF_LWPolyline2.QET_line_weight="thin";
                    New_DXF_LWPolyline2.QET_filling="none";

                    New_DXF_LWPolyline2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_LWPolyline2.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_LWPolyline.QET_handle=QET_handle;
					//New_DXF_LWPolyline.QET_handle.append(":");
					//New_DXF_LWPolyline.QET_handle.append(Record3.value("dxf_5").toString());
                    New_DXF_LWPolyline2.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_LWPolyline2.QET_block_name=QET_block_name;
                    New_DXF_LWPolyline2.QET_block_name_id=QET_block_name_id;
                    New_DXF_LWPolyline2.QET_softID=Record3.value("dxf_330").toString();


                    New_DXF_LWPolyline2.QET_color=DXF_main_base[0].QDXF_block_polyline_color;

					if (Record3.value("dxf_70").toInt()==1)
					{
                        New_DXF_LWPolyline2.QET_closed="true";
					}
					else
					{
                        New_DXF_LWPolyline2.QET_closed="false";
					}

					end_lwpoly=0;
					max_vertex=0;
					count_vertex=0;
					readrecord=1;

					max_vertex=Record3.value("dxf_90").toInt();

					if (max_vertex >=QET_L_POLYLINE)
					{
						Logtext.append("max_vertex :  ");
						Logtext.append(QString::number(max_vertex));
						Logtext.append(" > ");
						Logtext.append(QString::number(QET_L_POLYLINE));
						Logtext.append(" \n");
					}

					NewQueryBlock.previous();
					while (end_lwpoly==0 and count_vertex<max_vertex)
					{
						readrecord=NewQueryBlock.next();
						QSqlRecord Record4=NewQueryBlock.record();
						//Recordvalue2=Record4.value("Command").toString();
						if(readrecord==true)
						{

							if (Record3.value("Command").toString()=="LWPOLYLINE" and max_vertex<QET_L_POLYLINE)
							{
                                New_DXF_LWPolyline2.QET_x[count_vertex]=(Record4.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
                                New_DXF_LWPolyline2.QET_y[count_vertex]=(Record4.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;
								count_vertex++;

							}
							else
							{
								if (count_vertex>max_vertex)
								{
									end_lwpoly=1;
								}

								//count_vertex++;
							}
						}
						else
						{
							end_lwpoly=1;
						}

						if (count_vertex>max_vertex)
						{
							end_lwpoly=1;
						}

					}

                    New_DXF_LWPolyline2.segments=count_vertex;

                    if (stringsize > QSTRING_max_lengt)
                    {
                        Signal_log1.clear();
                        Signal_log1.append("DXF_Result Block Lwpolyline : ");
                        stringsize=DXF_Entities_List.DXF_ResultBlock.size();
                        Signal_log1.append(QString::number(stringsize));
                        Signal_log1.append(" \n");
                        emit send_log(Signal_log1);
                    }
                    else
                    {
                        DXF_Entities_List.DXF_ResultBlock.append(New_DXF_LWPolyline2.Create_polyline());
                    }
					//DXF_Block_Value.append(New_DXF_LWPolyline.Create_polyline());


				}


				if (Record3.value("Command").toString()=="SOLID" and Record3.value("Command_count").toInt()==0)
				{
                    for( int xx = 0;xx < QET_L_POLYLINE;xx++ )
                    {
                        New_DXF_SOLID2.QET_x[xx]=0.0;
                        New_DXF_SOLID2.QET_y[xx]=0.0;
                    }
                    New_DXF_SOLID2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_SOLID2.QET_ltype=Record3.value("dxf_6").toString();
                    New_DXF_SOLID2.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_SOLID2.QET_block_name=QET_block_name;
                    New_DXF_SOLID2.QET_block_name_id=QET_block_name_id;
                    New_DXF_SOLID2.QET_softID=Record3.value("dxf_330").toString();

                    New_DXF_SOLID2.QET_antialias="false";
                    New_DXF_SOLID2.QET_line_style="normal";
                    New_DXF_SOLID2.QET_line_weight="thin";
                    New_DXF_SOLID2.QET_filling="red";

                    New_DXF_SOLID2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_SOLID2.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_SOLID.QET_handle=QET_handle;
					//New_DXF_SOLID.QET_handle.append(":");
					//New_DXF_SOLID.QET_handle.append(Record3.value("dxf_5").toString());
                    New_DXF_SOLID2.QET_softID=Record3.value("dxf_330").toString();

                    New_DXF_SOLID2.QET_color=DXF_main_base[0].QDXF_block_solid_color;

					if (Record2.value("dxf_70").toInt()==1)
					{
                        New_DXF_SOLID2.QET_closed="true";
					}
					else
					{
                        New_DXF_SOLID2.QET_closed="false";
					}

					end_lwpoly=0;
					max_vertex=0;
					count_vertex=0;

					//max_vertex=Record2.value("dxf_90").toInt();
					max_vertex=4;

					if (max_vertex >=QET_L_POLYLINE)
					{
						Logtext.append("max_vertex :  ");
						Logtext.append(QString::number(max_vertex));
						Logtext.append(" > ");
						Logtext.append(QString::number(QET_L_POLYLINE));
						Logtext.append(" \n");
					}

                    while (end_lwpoly==0 and count_vertex<max_vertex+1)
					{
                        NewQueryBlock.next();
                        QSqlRecord Record3=NewQueryBlock.record();
                        Recordvalue2=Record3.value("Command").toString();
                        if (Record3.value("Command").toString()=="SOLID" and max_vertex<QET_L_POLYLINE)
                        {
                            New_DXF_SOLID2.QET_x[0]=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
                            New_DXF_SOLID2.QET_y[0]=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;

                            New_DXF_SOLID2.QET_x[1]=(Record3.value("dxf_11").toDouble()*Block_scale_x)+Block_X;
                            New_DXF_SOLID2.QET_y[1]=(Record3.value("dxf_21").toDouble()*Block_scale_y)+Block_Y;

                            New_DXF_SOLID2.QET_x[3]=(Record3.value("dxf_12").toDouble()*Block_scale_x)+Block_X;
                            New_DXF_SOLID2.QET_y[3]=(Record3.value("dxf_22").toDouble()*Block_scale_y)+Block_Y;

                            New_DXF_SOLID2.QET_x[2]=(Record3.value("dxf_13").toDouble()*Block_scale_x)+Block_X;
                            New_DXF_SOLID2.QET_y[2]=(Record3.value("dxf_23").toDouble()*Block_scale_y)+Block_Y;
							count_vertex=4;
                        }


						if (count_vertex>max_vertex)
						{
							end_lwpoly=1;
						}

                    }

                    New_DXF_SOLID2.segments=count_vertex;

                    if (stringsize > QSTRING_max_lengt)
                    {
                        Signal_log1.clear();
                        Signal_log1.append("DXF_Result Block Solid : ");
                        stringsize=DXF_Entities_List.DXF_ResultBlock.size();
                        Signal_log1.append(QString::number(stringsize));
                        Signal_log1.append(" \n");
                        emit send_log(Signal_log1);
                    }
                    else
                    {
                        DXF_Entities_List.DXF_ResultBlock.append(New_DXF_SOLID2.Create_polyline());
                    }
					//DXF_Block_Value.append(New_DXF_SOLID.Create_polyline());


				}

				if (Record3.value("Command").toString()=="SPLINE" and Record3.value("Command_count").toInt()==0)
				{
                    for( int xx = 0;xx < QET_L_POLYLINE;xx++ )
                    {
                        New_DXF_LWPolyline2.QET_x[xx]=0.0;
                        New_DXF_LWPolyline2.QET_y[xx]=0.0;
                    }

                    New_DXF_LWPolyline2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_LWPolyline2.QET_ltype=Record3.value("dxf_6").toString();
                    New_DXF_LWPolyline2.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_LWPolyline2.QET_block_name=QET_block_name;
                    New_DXF_LWPolyline2.QET_block_name_id=QET_block_name_id;
                    New_DXF_LWPolyline2.QET_softID=Record3.value("dxf_330").toString();

                    New_DXF_LWPolyline2.QET_antialias="false";
                    New_DXF_LWPolyline2.QET_line_style="normal";
                    New_DXF_LWPolyline2.QET_line_weight="thin";
                    New_DXF_LWPolyline2.QET_filling="none";

                    New_DXF_LWPolyline2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_LWPolyline2.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_LWPolyline.QET_handle=QET_handle;
					//New_DXF_LWPolyline.QET_handle.append(":");
					//New_DXF_LWPolyline.QET_handle.append(Record3.value("dxf_5").toString());
					//New_DXF_LWPolyline.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_LWPolyline2.QET_softID=Record3.value("dxf_330").toString();


                    New_DXF_LWPolyline2.QET_color=DXF_main_base[0].QDXF_block_polyline_color;

					if (Record3.value("dxf_70").toInt()==1)
					{
                        New_DXF_LWPolyline2.QET_closed="true";
					}
					else
					{
                        New_DXF_LWPolyline2.QET_closed="false";
					}

					end_lwpoly=0;
					max_vertex=0;
					count_vertex=0;
					readrecord=1;

					max_vertex=Record3.value("dxf_73").toInt();

                    New_DXF_LWPolyline2.QET_x[count_vertex]=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
                    New_DXF_LWPolyline2.QET_y[count_vertex]=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;
					count_vertex++;

					if (max_vertex >=QET_L_POLYLINE)
					{
                        Signal_log1.clear();
                        Signal_log1.append("max_vertex :  ");
                        Signal_log1.append(QString::number(max_vertex));
                        Signal_log1.append(" > ");
                        Signal_log1.append(QString::number(QET_L_POLYLINE));
                        Signal_log1.append(" \n");
                        emit send_log(Signal_log1);
					}

					//NewQueryBlock.previous();

					while (end_lwpoly==0 and count_vertex<max_vertex)
					{
						readrecord=NewQueryBlock.next();
						QSqlRecord Record4=NewQueryBlock.record();
						//Recordvalue2=Record4.value("Command").toString();
						if (readrecord==true)
						{

							if (Record3.value("Command").toString()=="SPLINE" and max_vertex<QET_L_POLYLINE)
							{
                                New_DXF_LWPolyline2.QET_x[count_vertex]=(Record4.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
                                New_DXF_LWPolyline2.QET_y[count_vertex]=(Record4.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;
								count_vertex++;

							}
							else
							{
								if (count_vertex>max_vertex)
								{
									end_lwpoly=1;
								}

								//count_vertex++;
							}
						}
						else
						{
							end_lwpoly=1;
						}

						if (count_vertex>max_vertex)
						{
							end_lwpoly=1;
						}

					}

                    New_DXF_LWPolyline2.segments=count_vertex;

                    if (stringsize > QSTRING_max_lengt)
                    {
                        Signal_log1.clear();
                        Signal_log1.append("DXF_Result Block Spline : ");
                        stringsize=DXF_Entities_List.DXF_ResultBlock.size();
                        Signal_log1.append(QString::number(stringsize));
                        Signal_log1.append(" \n");
                        emit send_log(Signal_log1);
                    }
                    else
                    {
                        DXF_Entities_List.DXF_ResultBlock.append(New_DXF_LWPolyline2.Create_polyline());
                    }
					//DXF_Block_Value.append(New_DXF_LWPolyline.Create_polyline());


				}

				if (Record3.value("Command").toString()=="MTEXT" and Record3.value("Command_count").toInt()==0)
				{
					/*  <text x="-11" y="3" size="6" rotation="90" text="Vcc"/>
						<text x="-7" y="-8" size="3" text="HC-SR04"/>
						<text x="-50" y="-45" text="Test" color="white" size="9"/>*/

                    New_DXF_Text2.QET_x=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
					//New_DXF_Text.QET_x=(Record3.value("dxf_10").toDouble())+Block_X;
                    New_DXF_Text2.QET_y=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;
					//New_DXF_Text.QET_y=(Record3.value("dxf_20").toDouble())+Block_Y;

                    New_DXF_Text2.QET_rotation=Record3.value("dxf_50").toDouble();
                    New_DXF_Text2.QET_text=Record3.value("dxf_1").toString();
                    New_DXF_Text2.QET_size=Record3.value("dxf_40").toDouble();
                    New_DXF_Text2.QET_text_style=Record3.value("dxf_7").toString();

                    New_DXF_Text2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_Text2.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Text.QET_handle=QET_handle;
					//New_DXF_Text.QET_handle.append(":");
					//New_DXF_Text.QET_handle.append(Record3.value("dxf_5").toString());
                    New_DXF_Text2.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_Text2.QET_block_name=QET_block_name;
                    New_DXF_Text2.QET_block_name_id=QET_block_name_id;
                    New_DXF_Text2.QET_softID=Record3.value("dxf_330").toString();


					//New_DXF_Text.QET_antialias="false";
					//New_DXF_Text.QET_line_style="normal";
					//New_DXF_Text.QET_line_weight="thin";
					//New_DXF_Text.QET_filling="none";
                    New_DXF_Text2.QET_color=DXF_main_base[0].QDXF_block_text_color;

                    if (stringsize > QSTRING_max_lengt)
                    {
                        Signal_log1.clear();
                        Signal_log1.append("DXF_Result Block Hatch : ");
                        stringsize=DXF_Entities_List.DXF_ResultBlock.size();
                        Signal_log1.append(QString::number(stringsize));
                        Signal_log1.append(" \n");
                        emit send_log(Signal_log1);
                    }
                    else
                    {
                        DXF_Entities_List.DXF_ResultBlock.append(New_DXF_Text2.Create_text());
                    }
					//DXF_Block_Value.append(New_DXF_Text.Create_text());
				}

				if (Record3.value("Command").toString()=="HATCH" and Record3.value("Command_count").toInt()==0)
				{
                    for( int xx = 0;xx < QET_L_POLYLINE;xx++ )
                    {
                        New_DXF_LWPolyline2.QET_x[xx]=0.0;
                        New_DXF_LWPolyline2.QET_y[xx]=0.0;
                    }



                    New_DXF_LWPolyline2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_LWPolyline2.QET_ltype=Record3.value("dxf_6").toString();
                    New_DXF_LWPolyline2.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_LWPolyline2.QET_block_name=QET_block_name;
                    New_DXF_LWPolyline2.QET_block_name_id=QET_block_name_id;
                    New_DXF_LWPolyline2.QET_softID=Record3.value("dxf_330").toString();

                    New_DXF_LWPolyline2.QET_antialias="false";
                    New_DXF_LWPolyline2.QET_line_style="normal";
                    New_DXF_LWPolyline2.QET_line_weight="thin";
                    New_DXF_LWPolyline2.QET_filling="yellow";

                    New_DXF_LWPolyline2.QET_layer=Record3.value("dxf_8").toString();
                    New_DXF_LWPolyline2.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_LWPolyline.QET_handle=QET_handle;
					//New_DXF_LWPolyline.QET_handle.append(":");
					//New_DXF_LWPolyline.QET_handle.append(Record3.value("dxf_5").toString());
					//New_DXF_LWPolyline.QET_handle=Record3.value("dxf_5").toString();
                    New_DXF_LWPolyline2.QET_softID=Record3.value("dxf_330").toString();


                    New_DXF_LWPolyline2.QET_color="yellow";//DXF_main_base[0].QDXF_block_polyline_color;

					if (Record3.value("dxf_70").toInt()==1)
					{
                        New_DXF_LWPolyline2.QET_closed="true";
					}
					else
					{
                        New_DXF_LWPolyline2.QET_closed="false";
					}

					end_lwpoly=0;
					max_vertex=0;
					count_vertex=0;
					readrecord=1;

					max_vertex=Record3.value("dxf_96").toInt()*Record3.value("dxf_91").toInt();

					//New_DXF_LWPolyline.QET_x[count_vertex]=(Record4.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
					//New_DXF_LWPolyline.QET_y[count_vertex]=(Record4.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;
					//count_vertex++;

					if (max_vertex >=QET_L_POLYLINE)
					{
						Logtext.append("max_vertex :  ");
						Logtext.append(QString::number(max_vertex));
						Logtext.append(" > ");
						Logtext.append(QString::number(QET_L_POLYLINE));
						Logtext.append(" \n");
					}

					//NewQueryBlock.previous();

					while (end_lwpoly==0 and count_vertex<max_vertex)
					{
						readrecord=NewQueryBlock.next();
						QSqlRecord Record4=NewQueryBlock.record();
						//Recordvalue2=Record4.value("Command").toString();

						if (readrecord==true)
						{

							if (Record3.value("Command").toString()=="HATCH" and max_vertex<QET_L_POLYLINE)
							{
                                hatchx=Record4.value("dxf_10").toDouble();
                                hatchy=Record4.value("dxf_20").toDouble();

                                if (hatchx==0.0 and hatchy==0.0 )
                                {
                                    //count_vertex++;
                                }

                                else
                                {
                                    New_DXF_LWPolyline2.QET_x[count_vertex]=(Record4.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
                                    New_DXF_LWPolyline2.QET_y[count_vertex]=(Record4.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;
                                    count_vertex++;
                                }

                                hatchx=Record4.value("dxf_11").toDouble();
                                hatchy=Record4.value("dxf_21").toDouble();

                                if (hatchx==0.0 and hatchy==0.0 )
                                {

                                }
                                else
                                {
                                    New_DXF_LWPolyline2.QET_x[count_vertex]=Record4.value("dxf_11").toDouble();
                                    New_DXF_LWPolyline2.QET_y[count_vertex]=Record4.value("dxf_21").toDouble();
                                    count_vertex++;
                                }

							}
							else
							{
								if (count_vertex>max_vertex)
								{
									end_lwpoly=1;
								}

								//count_vertex++;
							}
						}
						else
						{
							end_lwpoly=1;

						}

						if (count_vertex>max_vertex)
						{
							end_lwpoly=1;
						}

					}

                    New_DXF_LWPolyline2.segments=count_vertex;

                    if (stringsize > QSTRING_max_lengt)
                    {
                        Signal_log1.clear();
                        Signal_log1.append("DXF_Result Block Hatch : ");
                        stringsize=DXF_Entities_List.DXF_ResultBlock.size();
                        Signal_log1.append(QString::number(stringsize));
                        Signal_log1.append(" \n");
                        emit send_log(Signal_log1);
                    }
                    else
                    {
                        //DXF_Entities_List.DXF_ResultBlock.append(New_DXF_LWPolyline2.Create_polyline());
                    }
					//DXF_Block_Value.append(New_DXF_LWPolyline.Create_polyline());


				}

				if (Record3.value("Command").toString()=="ENDBLK" and Record3.value("Command_count").toInt()==0)
				{
					end_block=1;
				}
			}


			//Manage_Blocks.dbManager_create_elmt_block(&filename1,Block_count,DXF_Block_Name,DXF_Block_Value);

			DXF_Block_Name="";
			DXF_Block_Value="";

		}
		else
		{
			//NewQueryBlock.next();
		}
	}

	//Logtext.append("Records BLOCK passed : ");
	//Logtext.append(QString::number(rowcount));
    //Logtext.append(" \n");
	return Logtext;

}
