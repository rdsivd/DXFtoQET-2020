#include "dxf_layer_control.h"

extern struct DXF_Layers DXF_Layer_list[DXF_layers_set];

DXF_layer_control::DXF_layer_control(QWidget *parent) : QWidget(parent)
{
}

QString DXF_layer_control::dxf_layer_ltype()
{
	Layer_count=0;
	Layer_end=0;

	Layer_end=DXF_layers_set;

	if (layer_to_find=="")
	{
		layer_ltype="Continuous";
	}

	else
	{

		while (Layer_count<Layer_end)
		{

			if (DXF_Layer_list[Layer_count].DXF_Layer_naam==layer_to_find)
			{
				layer_ltype=DXF_Layer_list[Layer_count].DXF_Layer_linetype;
				Layer_count=Layer_end;
			}
			else
			{
				Layer_count=Layer_count+1;
			}


		}
	}



	return layer_ltype;
}
