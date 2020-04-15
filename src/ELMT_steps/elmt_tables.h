#ifndef ELMT_TABLES_H
#define ELMT_TABLES_H

#include <QWidget>
#include <QObject>

#include "data.h"
#include "src/dxf_load.h"
#include "db/dbmanager.h"

class elmt_tables : public QWidget
{
	Q_OBJECT
	public:
    explicit elmt_tables(QWidget *parent = nullptr);

	int xcount;
	int rowcount;

	QString Logtext;
	int db_error;

	void Open_SQL_DB (QString ELMT_filename);
	void Close_SQL_DB (QString ELMT_filename);

	void GetTable_info (QString ELMT_filename);

	QString Get_Tables_Layers(QString ELMT_filename);

	signals:

	void Log();

	public slots:
};

#endif // ELMT_TABLES_H
