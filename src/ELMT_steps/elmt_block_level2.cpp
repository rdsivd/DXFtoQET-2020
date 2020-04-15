#include "elmt_block_level2.h"


#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QtSql>

extern struct DXF_base DXF_main_base[DXF_base_set];
extern struct DXF_Entities DXF_Entities_List;

elmt_block_level2::elmt_block_level2(QWidget *parent) : QWidget(parent)
{

}

QString elmt_block_level2::Insert_Block()
{

	dbManager Manage_Blocks;

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

	//QSqlQuery NewQuery4("SELECT * FROM dxf_blocks");

	QSqlQuery NewQuery4;
	NewQuery4.prepare("SELECT * FROM dxf_blocks WHERE dxfbase =(:dxfbase)");
	NewQuery4.bindValue(":dxfbase",Block_name);
	NewQuery4.exec();


	dxf_base_line New_DXF_Line;
	dxf_base_circle New_DXF_Circle;
	dxf_base_arc New_DXF_Arc;
	dxf_base_text New_DXF_Text;
	dxf_base_input New_DXF_Input;
	dxf_base_terminal New_DXF_Terminal;
	dxf_base_ellipse New_DXF_Ellipse;
	dxf_base_polyline New_DXF_Polyline;
	dxf_base_polyline New_DXF_LWPolyline;
	dxf_base_polyline New_DXF_SOLID;
	elmt_blocks New_DXF_blocks2;


	Logtext.append("Converting DXF blocks\n");

	end_block=0;

	//while (NewQuery.next() and end_block==0)
	//while (NewQuery.next())

	//QSqlRecord Record2=NewQuery.record();

	while (NewQuery4.next() and end_block==0)
	{

		QSqlRecord Record2=NewQuery4.record();
		Recordvalue=Record2.value("Command").toString();

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

		read_error2=1;

		if (Record2.value("Command").toString()=="BLOCK" and Record2.value("dxf_2").toString()==Block_name)
		{
			end_block=0;

			while (end_block==0)
			{
				read_error2 = NewQuery4.next();
				if (read_error2==false)
				{
					end_block++;
				}
				QSqlRecord Record3=NewQuery4.record();

				if (Record3.value("Command").toString()=="LINE" and Record3.value("Command_count").toInt()==0)
				{
					/*<line length1="1.5" length2="1.5" antialias="false"
					 * end1="none" end2="none"
					 * style="line-style:normal;line-weight:normal;filling:none;color:black"
					 * y1="-20" x1="10" y2="-10" x2="10"/>*/


					New_DXF_Line.QET_x1=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
					New_DXF_Line.QET_x2=(Record3.value("dxf_11").toDouble()*Block_scale_x)+Block_X;
					New_DXF_Line.QET_y1=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;
					New_DXF_Line.QET_y2=(Record3.value("dxf_21").toDouble()*Block_scale_y)+Block_Y;

					New_DXF_Line.QET_layer=Record3.value("dxf_8").toString();
					New_DXF_Line.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Line.QET_handle=QET_handle;
					//New_DXF_Line.QET_handle.append(":");
					//New_DXF_Line.QET_handle.append(Record3.value("dxf_5").toString());
					New_DXF_Line.QET_handle=Record3.value("dxf_5").toString();
					New_DXF_Line.QET_block_name=QET_block_name;
					New_DXF_Line.QET_softID=Record3.value("dxf_330").toString();

					New_DXF_Line.QET_lenght1=1.5;
					New_DXF_Line.QET_lenght2=1.5;
					New_DXF_Line.QET_antialias="false";
					New_DXF_Line.QET_end1="none";
					New_DXF_Line.QET_end2="none";

					New_DXF_Line.QET_line_style="normal";
					New_DXF_Line.QET_line_weight="thin";
					New_DXF_Line.QET_filling="none";
					New_DXF_Line.QET_color=DXF_main_base[0].QDXF_block_line_color;

                    DXF_Entities_List.DXF_ResultBlock2.append(New_DXF_Line.CreateElmt());
					//DXF_Block_Value.append(New_DXF_Line.CreateElmt());

				}

				if (Record3.value("Command").toString()=="CIRCLE" and Record3.value("Command_count").toInt()==0)
				{
					/* <circle x="-28" y="-8" antialias="true"
					 * style="line-style:normal;line-weight:thin;filling:none;color:black"
					 * diameter="22"/> */

					New_DXF_Circle.QET_x=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
					New_DXF_Circle.QET_y=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;
					New_DXF_Circle.QET_diameter=Record3.value(("dxf_40")).toDouble()*Block_scale_x;

					New_DXF_Circle.QET_layer=Record3.value("dxf_8").toString();
					New_DXF_Circle.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Circle.QET_handle=QET_handle;
					//New_DXF_Circle.QET_handle.append(":");
					//New_DXF_Circle.QET_handle.append(Record3.value("dxf_5").toString());
					New_DXF_Circle.QET_handle=Record3.value("dxf_5").toString();
					New_DXF_Circle.QET_block_name=QET_block_name;
					New_DXF_Circle.QET_softID=Record3.value("dxf_330").toString();

					New_DXF_Circle.QET_antialias="false";
					New_DXF_Circle.QET_line_style="normal";
					New_DXF_Circle.QET_line_weight="thin";
					New_DXF_Circle.QET_filling="none";
					New_DXF_Circle.QET_color=DXF_main_base[0].QDXF_block_circle_color;

                    DXF_Entities_List.DXF_ResultBlock2.append(New_DXF_Circle.Create_circle());
					//DXF_Block_Value.append(New_DXF_Circle.Create_circle());
				}

				if (Record3.value("Command").toString()=="ARC" and Record3.value("Command_count").toInt()==0)
				{
					/*  <arc width="20" x="-15" y="-8" antialias="true"
						height="38" style="line-style:normal;
						line-weight:normal;filling:none;color:black"
						start="-30" angle="-299"/> */

					New_DXF_Arc.QET_x=((Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X)-(Record3.value("dxf_40").toDouble()*Block_scale_x);
					New_DXF_Arc.QET_y=((Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y)+(Record3.value("dxf_40").toDouble()*Block_scale_y);
					New_DXF_Arc.QET_width=Record3.value("dxf_40").toDouble()*2*Block_scale_x;
					New_DXF_Arc.QET_height=Record3.value("dxf_40").toDouble()*2*Block_scale_y;
					New_DXF_Arc.QET_start=Record3.value("dxf_50").toDouble();
					New_DXF_Arc.QET_end=Record3.value("dxf_51").toDouble();

					New_DXF_Arc.QET_layer=Record3.value("dxf_8").toString();
					New_DXF_Arc.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Arc.QET_handle=QET_handle;
					//New_DXF_Arc.QET_handle.append(":");
					//New_DXF_Arc.QET_handle.append(Record3.value("dxf_5").toString());
					New_DXF_Arc.QET_handle=Record3.value("dxf_5").toString();
					New_DXF_Arc.QET_block_name=QET_block_name;
					New_DXF_Arc.QET_softID=Record3.value("dxf_330").toString();


					New_DXF_Arc.QET_antialias="false";
					New_DXF_Arc.QET_line_style="normal";
					New_DXF_Arc.QET_line_weight="thin";
					New_DXF_Arc.QET_filling="none";
					New_DXF_Arc.QET_color=DXF_main_base[0].QDXF_block_arc_color;

                    DXF_Entities_List.DXF_ResultBlock2.append(New_DXF_Arc.Create_arc());
					//DXF_Block_Value.append(New_DXF_Arc.Create_arc());
				}

				if (Record3.value("Command").toString()=="TEXT" and Record3.value("Command_count").toInt()==0)
				{
					/*  <text x="-11" y="3" size="6" rotation="90" text="Vcc"/>
						<text x="-7" y="-8" size="3" text="HC-SR04"/>
						<text x="-50" y="-45" text="Test" color="white" size="9"/>*/

					New_DXF_Text.QET_x=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
					New_DXF_Text.QET_y=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;

					New_DXF_Text.QET_rotation=Record3.value("dxf_50").toDouble();
					New_DXF_Text.QET_text=Record3.value("dxf_1").toString();
					New_DXF_Text.QET_size=Record3.value("dxf_40").toDouble();
					New_DXF_Text.QET_text_style=Record3.value("dxf_7").toString();

					New_DXF_Text.QET_layer=Record3.value("dxf_8").toString();
					New_DXF_Text.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Text.QET_handle=QET_handle;
					//New_DXF_Text.QET_handle.append(":");
					//New_DXF_Text.QET_handle.append(Record3.value("dxf_5").toString());
					New_DXF_Text.QET_handle=Record3.value("dxf_5").toString();
					New_DXF_Text.QET_block_name=QET_block_name;
					New_DXF_Text.QET_softID=Record3.value("dxf_330").toString();

					//New_DXF_Text.QET_antialias="false";
					//New_DXF_Text.QET_line_style="normal";
					//New_DXF_Text.QET_line_weight="thin";
					//New_DXF_Text.QET_filling="none";
					New_DXF_Text.QET_color=DXF_main_base[0].QDXF_block_text_color;

                    DXF_Entities_List.DXF_ResultBlock2.append(New_DXF_Text.Create_text());
					//DXF_Block_Value.append(New_DXF_Text.Create_text());
				}

				if (Record3.value("Command").toString()=="INPUT" and Record3.value("Command_count").toInt()==0)
				{
					/*  <text x="-11" y="3" size="6" rotation="90" text="Vcc"/>
						<text x="-7" y="-8" size="3" text="HC-SR04"/>
						<text x="-50" y="-45" text="Test" color="white" size="9"/>*/

					New_DXF_Input.QET_x=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
					New_DXF_Input.QET_y=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;

					New_DXF_Input.QET_rotation=Record3.value("dxf_50").toDouble();
					New_DXF_Input.QET_text=Record3.value("dxf_1").toString();
					New_DXF_Input.QET_size=Record3.value("dxf_40").toDouble()*Block_scale_y;
					New_DXF_Input.QET_text_style=Record3.value("dxf_7").toString();

					New_DXF_Input.QET_layer=Record3.value("dxf_8").toString();
					New_DXF_Input.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Input.QET_handle=QET_handle;
					//New_DXF_Input.QET_handle.append(":");
					//New_DXF_Input.QET_handle.append(Record3.value("dxf_5").toString());
					New_DXF_Input.QET_handle=Record3.value("dxf_5").toString();
					New_DXF_Input.QET_block_name=QET_block_name;
					New_DXF_Input.QET_softID=Record3.value("dxf_330").toString();

					//New_DXF_Text.QET_antialias="false";
					//New_DXF_Text.QET_line_style="normal";
					//New_DXF_Text.QET_line_weight="thin";
					//New_DXF_Text.QET_filling="none";
					New_DXF_Input.QET_rotate="true";
					New_DXF_Input.QET_tag="none";

					New_DXF_Input.QET_color=DXF_main_base[0].QDXF_block_input_color;

                    DXF_Entities_List.DXF_ResultBlock2.append(New_DXF_Input.Create_input());
					//DXF_Block_Value.append(New_DXF_Input.Create_input());
				}

				if (Record3.value("Command").toString()=="ATTRIB" and Record3.value("Command_count").toInt()==0)
				{
					/*  <text x="-11" y="3" size="6" rotation="90" text="Vcc"/>
						<text x="-7" y="-8" size="3" text="HC-SR04"/>
						<text x="-50" y="-45" text="Test" color="white" size="9"/>*/

					New_DXF_Input.QET_x=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
					New_DXF_Input.QET_y=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;

					New_DXF_Input.QET_rotation=Record3.value("dxf_50").toDouble();
					New_DXF_Input.QET_text=Record3.value("dxf_1").toString();
					New_DXF_Input.QET_size=Record3.value("dxf_40").toDouble()*Block_scale_y;
					New_DXF_Input.QET_text_style=Record3.value("dxf_7").toString();

					New_DXF_Input.QET_layer=Record3.value("dxf_8").toString();
					New_DXF_Input.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Input.QET_handle=QET_handle;
					//New_DXF_Input.QET_handle.append(":");
					//New_DXF_Input.QET_handle.append(Record3.value("dxf_5").toString());
					New_DXF_Input.QET_handle=Record3.value("dxf_5").toString();
					New_DXF_Input.QET_block_name=QET_block_name;
					New_DXF_Input.QET_softID=Record3.value("dxf_330").toString();

					//New_DXF_Text.QET_antialias="false";
					//New_DXF_Text.QET_line_style="normal";
					//New_DXF_Text.QET_line_weight="thin";
					//New_DXF_Text.QET_filling="none";
					New_DXF_Input.QET_rotate="true";
					New_DXF_Input.QET_tag="none";

					New_DXF_Input.QET_color=DXF_main_base[0].QDXF_block_input_color;

                    DXF_Entities_List.DXF_ResultBlock2.append(New_DXF_Input.Create_input());
					//DXF_Block_Value.append(New_DXF_Input.Create_input());
				}

				if (Record3.value("Command").toString()=="POINT" and Record3.value("Command_count").toInt()==0)
				{
					/*  <text x="-11" y="3" size="6" rotation="90" text="Vcc"/>
						<text x="-7" y="-8" size="3" text="HC-SR04"/>
						<text x="-50" y="-45" text="Test" color="white" size="9"/>*/

					New_DXF_Terminal.QET_x=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
					New_DXF_Terminal.QET_y=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;

					New_DXF_Terminal.QET_orientation="north";//Record2.value("dxf_50").toDouble();
					//New_DXF_Input.QET_text=Record2.value("dxf_1").toString();
					//New_DXF_Input.QET_size=Record2.value("dxf_40").toDouble();
					//New_DXF_Input.QET_text_style=Record2.value("dxf_7").toString();

					New_DXF_Terminal.QET_layer=Record3.value("dxf_8").toString();
					New_DXF_Terminal.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Terminal.QET_handle=QET_handle;
					//New_DXF_Terminal.QET_handle.append(":");
					//New_DXF_Terminal.QET_handle.append(Record3.value("dxf_5").toString());
					New_DXF_Terminal.QET_handle=Record3.value("dxf_5").toString();
					New_DXF_Terminal.QET_block_name=QET_block_name;
					New_DXF_Terminal.QET_softID=Record3.value("dxf_330").toString();

					//New_DXF_Text.QET_antialias="false";
					//New_DXF_Text.QET_line_style="normal";
					//New_DXF_Text.QET_line_weight="thin";
					//New_DXF_Text.QET_filling="none";
					//New_DXF_Input.QET_rotate="true";
					//New_DXF_Input.QET_tag="label";

					//New_DXF_Input.QET_color=DXF_main_base[0].QDXF_circle_color;

                    DXF_Entities_List.DXF_ResultBlock2.append(New_DXF_Terminal.Create_terminal());
					//DXF_Block_Value.append(New_DXF_Terminal.Create_terminal());
				}

				if (Record3.value("Command").toString()=="ELLIPSE" and Record3.value("Command_count").toInt()==0)
				{
					/*  <text x="-11" y="3" size="6" rotation="90" text="Vcc"/>
						<text x="-7" y="-8" size="3" text="HC-SR04"/>
						<text x="-50" y="-45" text="Test" color="white" size="9"/>*/

					New_DXF_Ellipse.QET_center_x=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
					New_DXF_Ellipse.QET_center_y=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;
					New_DXF_Ellipse.QET_major_radius_x=Record3.value("dxf_11").toDouble()*Block_scale_x;
					New_DXF_Ellipse.QET_major_radius_y=Record3.value("dxf_21").toDouble()*Block_scale_y;

					New_DXF_Ellipse.QET_end_parameter=Record3.value("dxf_42").toDouble();
					New_DXF_Ellipse.QET_Start_parameter=Record3.value("dxf_41").toDouble();
					New_DXF_Ellipse.QET_ratio_minor_axis=Record3.value("dxf_40").toDouble();

					New_DXF_Ellipse.QET_layer=Record3.value("dxf_8").toString();
					New_DXF_Ellipse.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Ellipse.QET_handle=QET_handle;
					//New_DXF_Ellipse.QET_handle.append(":");
					//New_DXF_Ellipse.QET_handle.append(Record3.value("dxf_5").toString());
					New_DXF_Ellipse.QET_handle=Record3.value("dxf_5").toString();
					New_DXF_Ellipse.QET_block_name=QET_block_name;
					New_DXF_Ellipse.QET_block_name_id=QET_block_name_id;
					New_DXF_Ellipse.QET_softID=Record3.value("dxf_330").toString();

					//New_DXF_Terminal.QET_orientation="sud";//Record2.value("dxf_50").toDouble();
					//New_DXF_Input.QET_text=Record2.value("dxf_1").toString();
					//New_DXF_Input.QET_size=Record2.value("dxf_40").toDouble();
					//New_DXF_Input.QET_text_style=Record2.value("dxf_7").toString();


					New_DXF_Ellipse.QET_antialias="false";
					New_DXF_Ellipse.QET_line_style="normal";
					New_DXF_Ellipse.QET_line_weight="thin";
					New_DXF_Ellipse.QET_filling="none";
					//New_DXF_Ellipse.QET_rotate="true";
					//New_DXF_Input.QET_tag="label";

					New_DXF_Ellipse.QET_color=DXF_main_base[0].QDXF_block_ellipse_color;

                    DXF_Entities_List.DXF_ResultBlock2.append(New_DXF_Ellipse.Create_ellipse());
					//DXF_Block_Value.append(New_DXF_Ellipse.Create_ellipse());
				}

				if (Record3.value("Command").toString()=="POLYLINE" and Record3.value("Command_count").toInt()==0)
				{
					New_DXF_Polyline.QET_layer=Record3.value("dxf_8").toString();
					New_DXF_Polyline.QET_ltype=Record3.value("dxf_6").toString();
					New_DXF_Polyline.QET_handle=Record3.value("dxf_5").toString();
					New_DXF_Polyline.QET_softID=Record3.value("dxf_330").toString();

					New_DXF_Polyline.QET_antialias="false";
					New_DXF_Polyline.QET_line_style="normal";
					New_DXF_Polyline.QET_line_weight="thin";
					New_DXF_Polyline.QET_filling="none";

					New_DXF_Polyline.QET_layer=Record3.value("dxf_8").toString();
					New_DXF_Polyline.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_Polyline.QET_handle=QET_handle;
					//New_DXF_Polyline.QET_handle.append(":");
					//New_DXF_Polyline.QET_handle.append(Record3.value("dxf_5").toString());
					New_DXF_Polyline.QET_handle=Record3.value("dxf_5").toString();
					New_DXF_Polyline.QET_block_name=QET_block_name;
					New_DXF_Polyline.QET_block_name_id=QET_block_name_id;
					New_DXF_Polyline.QET_softID=Record3.value("dxf_330").toString();


					New_DXF_Polyline.QET_color=DXF_main_base[0].QDXF_block_polyline_color;

					if (Record3.value("dxf_70").toInt()==1)
					{
						New_DXF_Polyline.QET_closed="true";
					}
					else
					{
						New_DXF_Polyline.QET_closed="false";
					}

					end_seqend=0;
					count_vertex=0;
					readrecord=1;

					while (end_seqend==0 and count_vertex<QET_L_POLYLINE)
					{
						readrecord=NewQuery4.next();
						QSqlRecord Record4=NewQuery4.record();
						//Recordvalue2=Record4.value("Command").toString();

						if(readrecord==true)
						{

							if (Record4.value("Command").toString()=="VERTEX" and Record4.value("Command_count").toInt()==0)
							{
								New_DXF_Polyline.QET_x[count_vertex]=(Record4.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
								New_DXF_Polyline.QET_y[count_vertex]=(Record4.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;
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

					New_DXF_Polyline.segments=count_vertex;

					DXF_Entities_List.DXF_Result.append(New_DXF_Polyline.Create_polyline());
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
                    New_DXF_blocks2.QET_handle.append(Record3.value("dxf_2").toString());
                    New_DXF_blocks2.QET_handle.append(":");
					New_DXF_blocks2.QET_handle=Record3.value("dxf_5").toString();
					New_DXF_blocks2.QET_block_name=Record3.value("dxf_2").toString();
					New_DXF_blocks2.QET_block_name_id=Record3.value("dxf_5").toString();
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

					Logtext.append("block : ");
					Logtext.append(Record3.value("dxf_2").toString());
					Logtext.append(" inside block :");
					Logtext.append(FromBlock);
					Logtext.append(" will not converted to elmt drawing parts");
					Logtext.append(" \n");

					New_DXF_blocks2.FromBlock=Record3.value("dxf_2").toString();

                    DXF_Entities_List.DXF_ResultBlock2.append(New_DXF_blocks2.Insert_Block());
                    //DXF_Entities_List.DXF_Result.append(New_DXF_blocks2.Insert_Block());

				}

				if (Record3.value("Command").toString()=="LWPOLYLINE" and Record3.value("Command_count").toInt()==0)
				{

					New_DXF_LWPolyline.QET_layer=Record3.value("dxf_8").toString();
					New_DXF_LWPolyline.QET_ltype=Record3.value("dxf_6").toString();
					New_DXF_LWPolyline.QET_handle=Record3.value("dxf_5").toString();
					New_DXF_LWPolyline.QET_softID=Record3.value("dxf_330").toString();

					New_DXF_LWPolyline.QET_antialias="false";
					New_DXF_LWPolyline.QET_line_style="normal";
					New_DXF_LWPolyline.QET_line_weight="thin";
					New_DXF_LWPolyline.QET_filling="none";

					New_DXF_LWPolyline.QET_layer=Record3.value("dxf_8").toString();
					New_DXF_LWPolyline.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_LWPolyline.QET_handle=QET_handle;
					//New_DXF_LWPolyline.QET_handle.append(":");
					//New_DXF_LWPolyline.QET_handle.append(Record3.value("dxf_5").toString());
					New_DXF_LWPolyline.QET_handle=Record3.value("dxf_5").toString();
					New_DXF_LWPolyline.QET_block_name=QET_block_name;
					New_DXF_LWPolyline.QET_block_name_id=QET_block_name_id;
					New_DXF_LWPolyline.QET_softID=Record3.value("dxf_330").toString();


					New_DXF_LWPolyline.QET_color=DXF_main_base[0].QDXF_block_polyline_color;

					if (Record3.value("dxf_70").toInt()==1)
					{
						New_DXF_LWPolyline.QET_closed="true";
					}
					else
					{
						New_DXF_LWPolyline.QET_closed="false";
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

					while (end_lwpoly==0 and count_vertex<max_vertex-1)
					{
						readrecord=NewQuery4.next();
						QSqlRecord Record4=NewQuery4.record();
						//Recordvalue2=Record4.value("Command").toString();

						if(readrecord==true)
						{

							if (Record3.value("Command").toString()=="LWPOLYLINE" and max_vertex<QET_L_POLYLINE)
							{
								New_DXF_LWPolyline.QET_x[count_vertex]=(Record4.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
								New_DXF_LWPolyline.QET_y[count_vertex]=(Record4.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;
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

					New_DXF_LWPolyline.segments=count_vertex;

                    DXF_Entities_List.DXF_ResultBlock2.append(New_DXF_LWPolyline.Create_polyline());
					//DXF_Block_Value.append(New_DXF_LWPolyline.Create_polyline());


				}


				if (Record3.value("Command").toString()=="SOLID" and Record3.value("Command_count").toInt()==0)
				{

					New_DXF_SOLID.QET_layer=Record3.value("dxf_8").toString();
					New_DXF_SOLID.QET_ltype=Record3.value("dxf_6").toString();
					New_DXF_SOLID.QET_handle=Record3.value("dxf_5").toString();
					New_DXF_SOLID.QET_softID=Record3.value("dxf_330").toString();

					New_DXF_SOLID.QET_antialias="false";
					New_DXF_SOLID.QET_line_style="normal";
					New_DXF_SOLID.QET_line_weight="thin";
					New_DXF_SOLID.QET_filling="red";

					New_DXF_SOLID.QET_layer=Record3.value("dxf_8").toString();
					New_DXF_SOLID.QET_ltype=Record3.value("dxf_6").toString();
					//New_DXF_SOLID.QET_handle=QET_handle;
					//New_DXF_SOLID.QET_handle.append(":");
					//New_DXF_SOLID.QET_handle.append(Record3.value("dxf_5").toString());
					New_DXF_SOLID.QET_handle=Record3.value("dxf_5").toString();
					New_DXF_SOLID.QET_block_name=QET_block_name;
					New_DXF_SOLID.QET_block_name_id=QET_block_name_id;
					New_DXF_SOLID.QET_softID=Record3.value("dxf_330").toString();

					New_DXF_SOLID.QET_color=DXF_main_base[0].QDXF_block_solid_color;

					if (Record2.value("dxf_70").toInt()==1)
					{
						New_DXF_SOLID.QET_closed="true";
					}
					else
					{
						New_DXF_SOLID.QET_closed="false";
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

					/*while (end_lwpoly==0 and count_vertex<max_vertex+1)
					{
						NewQuery.next();
						QSqlRecord Record3=NewQuery.record();
						Recordvalue2=Record3.value("Command").toString();
						if (Record3.value("Command").toString()=="SOLID" and max_vertex<QET_L_POLYLINE)


					{*/
							New_DXF_SOLID.QET_x[0]=(Record3.value("dxf_10").toDouble()*Block_scale_x)+Block_X;
							New_DXF_SOLID.QET_y[0]=(Record3.value("dxf_20").toDouble()*Block_scale_y)+Block_Y;

							New_DXF_SOLID.QET_x[1]=(Record3.value("dxf_11").toDouble()*Block_scale_x)+Block_X;
							New_DXF_SOLID.QET_y[1]=(Record3.value("dxf_21").toDouble()*Block_scale_y)+Block_Y;

							New_DXF_SOLID.QET_x[3]=(Record3.value("dxf_12").toDouble()*Block_scale_x)+Block_X;
							New_DXF_SOLID.QET_y[3]=(Record3.value("dxf_22").toDouble()*Block_scale_y)+Block_Y;

							New_DXF_SOLID.QET_x[2]=(Record3.value("dxf_13").toDouble()*Block_scale_x)+Block_X;
							New_DXF_SOLID.QET_y[2]=(Record3.value("dxf_23").toDouble()*Block_scale_y)+Block_Y;
							count_vertex=4;

						/*}
						if (count_vertex>max_vertex)
						{
							end_lwpoly=1;
						}

					}*/

					New_DXF_SOLID.segments=count_vertex;

                    DXF_Entities_List.DXF_ResultBlock2.append(New_DXF_SOLID.Create_polyline());
					//DXF_Block_Value.append(New_DXF_SOLID.Create_polyline());


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
			//NewQuery.next();
		}
	}

	//Logtext.append("Records BLOCK passed : ");
	//Logtext.append(QString::number(rowcount));
	Logtext.append(" \n");
	return Logtext;

}
