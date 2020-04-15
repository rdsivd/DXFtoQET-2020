#include "elmt_header_steps.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
//#include <QtSql>

extern struct DXF_var DXF_variable;

ELMT_header_steps::ELMT_header_steps(QWidget *parent) : QWidget(parent)
{

}

void ELMT_header_steps::Open_SQL_DB (QString ELMT_filename)
{

	dbManager mydb2;
	mydb2.dbManager1(ELMT_filename);


}

void ELMT_header_steps::Close_SQL_DB (QString ELMT_filename)
{

	dbManager mydb2;
	mydb2.dbManager_close (ELMT_filename);


}

QString ELMT_header_steps::GetHeader_info (QString ELMT_filename)
{
    QString path = ELMT_filename;
	QSqlQueryModel model;
	model.setQuery("SELECT * FROM dxf_header");

	rowcount=model.rowCount();

	for (int xx=0;xx<rowcount;xx++)
	{
		QSqlRecord record=model.record(xx);

		if(record.value("Command").toString()=="$ACADVER")
		{
			DXF_variable.DXF_ACADVER=record.value("dxf_1").toString();
		}

		if(record.value("Command").toString()=="$ACADMAINTVER")
		{
			DXF_variable.DXF_ACADMAINTVER=record.value("dxf_70").toString();
		}

		if(record.value("Command").toString()=="$INSBASE")
		{
			DXF_variable.DXF_INSBASE_X=record.value("dxf_10").toString();
			DXF_variable.DXF_INSBASE_Y=record.value("dxf_20").toString();

			if (DXF_variable.DXF_INSBASE_X=="")
			{
				DXF_variable.DXF_INSBASE_X=5;
			}

			if (DXF_variable.DXF_INSBASE_Y=="")
			{
				DXF_variable.DXF_INSBASE_Y=5;
			}
		}

		if(record.value("Command").toString()=="$EXTMIN")
		{
			DXF_variable.DXF_EXTMIN_X=record.value("dxf_10").toString();
			DXF_variable.DXF_EXTMIN_Y=record.value("dxf_20").toString();
		}

		if(record.value("Command").toString()=="$EXTMAX")
		{
			DXF_variable.DXF_EXTMAX_X=record.value("dxf_10").toString();
			DXF_variable.DXF_EXTMAX_Y=record.value("dxf_20").toString();
		}

		if(record.value("Command").toString()=="$TEXTSIZE")
		{
			DXF_variable.DXF_TEXTSIZE=record.value("dxf_40").toString();
		}

		if(record.value("Command").toString()=="$TEXTSTYLE")
		{
			DXF_variable.DXF_TEXTSTYLE=record.value("dxf_7").toString();
		}

		if(record.value("Command").toString()=="$LIMMIN")
		{
			DXF_variable.DXF_LIMMIN_X=record.value("dxf_10").toString();
			DXF_variable.DXF_LIMMIN_Y=record.value("dxf_20").toString();
		}

		if(record.value("Command").toString()=="$LIMMAX")
		{
			DXF_variable.DXF_LIMMAX_X=record.value("dxf_10").toString();
			DXF_variable.DXF_LIMMAX_Y=record.value("dxf_20").toString();
		}

	}



	return Logtext;

}

QString ELMT_header_steps::Calc_Width()
{
	DXF_LIMMAX_X=DXF_variable.DXF_LIMMAX_X.toDouble();
	DXF_LIMMIN_X=DXF_variable.DXF_LIMMIN_X.toDouble();

	//DXF_variable.DXF_INSBASE_X;
	//DXF_variable.DXF_INSBASE_y;

	if (DXF_LIMMIN_X <0)
	{
		DXF_LIMMIN_X=-DXF_LIMMIN_X;
	}
	if (DXF_LIMMAX_X <0)
	{
		DXF_LIMMAX_X=-DXF_LIMMAX_X;
	}

	//return (QString::number(DXF_LIMMIN_X+DXF_LIMMAX_X));
	return (QString::number((DXF_variable.DXF_INSBASE_X.toDouble()*2)+5));
}

QString ELMT_header_steps::Calc_Height()
{
	DXF_LIMMAX_Y=DXF_variable.DXF_LIMMAX_Y.toDouble();
	DXF_LIMMIN_Y=DXF_variable.DXF_LIMMIN_Y.toDouble();

	if (DXF_LIMMIN_Y <0)
	{
		DXF_LIMMIN_Y=-DXF_LIMMIN_Y;
	}
	if (DXF_LIMMAX_Y <0)
	{
		DXF_LIMMAX_Y=-DXF_LIMMAX_Y;
	}

	//return (QString::number(DXF_LIMMIN_Y+DXF_LIMMAX_Y));
	return (QString::number((DXF_variable.DXF_INSBASE_Y.toDouble()*2)+5));
}

