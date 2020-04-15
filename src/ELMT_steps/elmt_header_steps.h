#ifndef ELMT_HEADER_STEPS_H
#define ELMT_HEADER_STEPS_H

#include <QWidget>
#include <QObject>

#include "data.h"
#include "src/dxf_load.h"
#include "db/dbmanager.h"

class ELMT_header_steps : public QWidget
{
	Q_OBJECT
	public:
    explicit ELMT_header_steps(QWidget *parent = nullptr);

	QString QsqlString;
	QString ResultCommand;
	QString Logtext;

	double DXF_LIMMIN_X;
	double DXF_LIMMAX_X;

	double DXF_LIMMIN_Y;
	double DXF_LIMMAX_Y;

	double DXF_width;
	double DXF_height;


	int rowcount;

	void Open_SQL_DB (QString ELMT_filename);
	void Close_SQL_DB (QString ELMT_filename);

	QString GetHeader_info(QString ELMT_filename);

	QString Calc_Width();
	QString Calc_Height();



	signals:

	public slots:
};

#endif // ELMT_HEADER_STEPS_H
