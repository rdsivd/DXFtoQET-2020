#include "elmt_tables.h"
//#include "dxftoqet3db.h"
#include "ui_dxftoqet3db.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QtSql>

extern struct DXF_Layers DXF_Layer_list[DXF_layers_set];

elmt_tables::elmt_tables(QWidget *parent) : QWidget(parent)
{

}

QString elmt_tables::Get_Tables_Layers(QString ELMT_filename)
{
    QString path = ELMT_filename;
	QSqlQuery NewQuery("SELECT * FROM dxf_tables");


	xcount=0;
	Logtext="";
	rowcount=0;



	while (NewQuery.next())
	//for (int xx=0;xx<rowcount;xx++)
	{
		QSqlRecord record=NewQuery.record();

		rowcount++;

		if(record.value("Command").toString()=="LAYER" and xcount < DXF_layers_set)
		{
			DXF_Layer_list[xcount].DXF_Layer_naam=record.value("dxf_2").toString();
			DXF_Layer_list[xcount].DXF_Layer_linetype=record.value("dxf_6").toString();
			DXF_Layer_list[xcount].DXF_Layer_color=record.value("dxf_62").toString();
			//xx=rowcount+1;
			xcount++;
		}
		else
		{


			if (xcount > DXF_layers_set)
			{

				Logtext.append("============================================================================\n");
				Logtext.append("layer table to small \n");
				Logtext.append(QString::number(rowcount));
				Logtext.append(" > ");
				Logtext.append(QString::number(DXF_layers_set));
				Logtext.append(" \n");
				Logtext.append("send email to programmer with copie of this log       \n");
				Logtext.append("============================================================================\n");
				//xcount--;
				//xx=rowcount+1;
			}

		}



	}

	if (xcount <DXF_layers_set)
	{
		Logtext.append(QString::number(rowcount));
		Logtext.append(" Tables records processed\n");
		Logtext.append("============================================================================\n");
		Logtext.append("Layers info loaded\n");
		//Logtext.append("send email to programmer with copie of this log       \n");
		Logtext.append("============================================================================\n");

		//QObject::connect(Logtext,SIGNAL(QString),,SLOT(insertPlainText()))
	}

	return Logtext;
}

void elmt_tables::Open_SQL_DB (QString ELMT_filename)
{
	dbManager mydb2;
	mydb2.dbManager1(ELMT_filename);
}

void elmt_tables::Close_SQL_DB (QString ELMT_filename)
{
	dbManager mydb2;
    mydb2.dbManager_close(ELMT_filename);
}

void elmt_tables::GetTable_info (QString ELMT_filename)
{
    QString path = ELMT_filename;
}
