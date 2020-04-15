#include "dxf_load.h"

extern struct DXF_base DXF_main_base[DXF_base_set];

dxf_load::dxf_load(QWidget *parent) : QWidget(parent)
{

}

void dxf_load::dxf_header_split()
{

	// init extern variable
	//extern DXF_base DXF_main_base[1];

	// dxf split

	DXF_main_base[0].dxf_input = DXF_main_base[0].dxf_text_all.split("\n");
	DXF_main_base[0].dxf_line_count=DXF_main_base[0].dxf_input.count();


	return;

}

void dxf_load::dxf_csv_split()
{

	DXF_main_base[0].dxf_input = DXF_main_base[0].dxf_text_all.split("\n");
	DXF_main_base[0].dxf_csv_line_count=DXF_main_base[0].dxf_input.count();


	return;
}

int dxf_load::dxf_check_file()
{

	dxf_check=DXF_main_base[0].dxf_input[0];

	if (dxf_check.contains("AC"))
	{
		return 0; // BINAIRI
	}
	else
	{
		return 1; // ASCII
	}

}
