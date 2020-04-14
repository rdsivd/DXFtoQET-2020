#include "dxftoqet3db.h"
#include <QApplication>

#include "data.h"

struct DXF_base DXF_main_base[DXF_base_set];
struct DXF_codes DXF_code_tables[DXF_codes_set];
struct DXF_codes DXF_codes_tables_empty;
struct DXF_var DXF_variable;
struct DXF_Layers DXF_Layer_list[DXF_layers_set];
struct DXF_Entities DXF_Entities_List;

int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
	DXFtoQET3DB w;
	w.show();

	//ui->Info_2->activateWindow();

	return a.exec();
}
