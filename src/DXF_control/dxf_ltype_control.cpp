#include "dxf_ltype_control.h"

DXF_Ltype_control::DXF_Ltype_control(QWidget *parent) : QWidget(parent)
{


}

QString DXF_Ltype_control::Ltype_control()
{

	LTfound="normal";

	if (FindLT == "" )
	{
		DXF_layer_control db_layer_control;

		db_layer_control.layer_to_find=Layer;

		DXF_Ltype_control db_ltype;

		db_ltype.FindLT=db_layer_control.dxf_layer_ltype();


	   LTfound=db_ltype.Ltype_control();

	}

	if (FindLT == "ByLayer" )
	{
		DXF_layer_control db_layer_control;

		db_layer_control.layer_to_find=Layer;

		DXF_Ltype_control db_ltype;

		db_ltype.FindLT=db_layer_control.dxf_layer_ltype();


	   LTfound=db_ltype.Ltype_control();

	}

	if (FindLT == "ByBlock" )
	{
	   LTfound="normal";
	}

	if (FindLT == "Continuous" )
	{
	   LTfound="normal";
	}

	if (FindLT == "CONTINUOUS" )
	{
	   LTfound="normal";
	}

	if (FindLT == "Center" )
	{
	   LTfound="dashdotted";
	}

	if (FindLT == "CENTER" )
	{
	   LTfound="dashdotted";
	}

	if (FindLT == "CENTER2" )
	{
	   LTfound="dashdotted";
	}

	if (FindLT == "CENTERX2" )
	{
	   LTfound="dashdotted";
	}


	if (FindLT == "Dashed" )
	{
	   LTfound="dashed";
	}

	if (FindLT == "DASHED" )
	{
	   LTfound="dashed";
	}

	if (FindLT == "DASHED2" )
	{
	   LTfound="dashed";
	}

	if (FindLT == "DASHEDX2" )
	{
	   LTfound="dashed";
	}


	if (FindLT == "HIDDEN" )
	{
	   LTfound="dashed";
	}

	if (FindLT == "HIDDEN2" )
	{
	   LTfound="dashed";
	}

	if (FindLT == "HIDDENX2" )
	{
	   LTfound="dashed";
	}

	if (FindLT == "EPL_DASH" )
	{
	   LTfound="dashed";
	}

	if (FindLT == "EPL_DASH2" )
	{
	   LTfound="dashed";
	}

	if (FindLT == "EPL_DASHDOT" )
	{
	   LTfound="dashdotted";
	}

	if (FindLT == "EPL_DASHDOTDOT" )
	{
	   LTfound="dashdotted";
	}

	if (FindLT == "DASHDOT" )
	{
	   LTfound="dashdotted";
	}

	if (FindLT == "DASHDOT2" )
	{
	   LTfound="dashdotted";
	}

	if (FindLT == "DASHDOTX2" )
	{
	   LTfound="dashdotted";
	}
	if (FindLT == "normal" )
	{
	   LTfound="normal";
	}


	return LTfound;
}
