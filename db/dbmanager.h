#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QWidget>
#include <QObject>

#include <QtSql>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

#include <QtWidgets>
#include <QTableView>
#include <QTextStream>
#include <QFileDialog>
#include <QFile>
#include <QModelIndex>
#include <QSettings>
#include <QDateTime>
#include <QPlainTextEdit>
#include <QSqlTableModel>
#include <QSqlRecord>

#include "data.h"



class dbManager : public QWidget
{
	Q_OBJECT
	public:
    explicit dbManager(QWidget *parent = nullptr );

	int x1;
	int x2;
	int x10;

	int Command_Count;
	int Max_count_lines;
	int Record_count_lines;

	int32_t dxf_line_count;
	int32_t dxf_line_count_max;
	int32_t count_input;

	int32_t transfer_count;
	QString Transfer_Code;
	QString Transfer_waarde;
	QString Transfer_Section;
	QString Transfer_Commando;
	int32_t Transfer_AcadValue;

	int List_1;
	QString List_2;
	int List_3;
	QString List_4;

	QString QsqlString;
	QString QsqlString2;
	QString Qsqlstring3;
	QString dxf_section;

	QString QSql_dxf_list;
	QString QSql_transfer;

	QString Qsql_Block;
	QString Qsql_entitie;
	QString Qsql_List;

	QString Waarde1;
	QString Waarde2;

	QString BlockNaamID;


	QString Signal_log1;
	QString Signal_elmt1;

	QString RecordNr;

	QVariantList dxf_list1;
	QVariantList dxf_list2;
	QVariantList dxf_list3;
	QVariantList dxf_list4;

    void dbActivate (const QString &pathname);
	void dbManager1(const QString &pathname);

	void dbManager_close(const QString &pathname);

	void dbManager_create_tables(const QString &pathname);

	int dbManager_added_records(const QString &pathname, int32_t *Max_lines, int32_t *Record_count, QString dxf_type);

	int DB_dbManager_added_records(const QString &pathname, int32_t *Max_lines, int32_t *Record_count, QString dxf_type);


	void dbManager_load_dxf(const QString &pathname);

	void dbManager_load_dxf_list(const QString &pathname);

	void dbManager_transfer_dxf(const QString &pathname);

	void dbManager_create_elmt_entitie(const QString &pathname, int32_t Index_count_1,QString Block_naam_1, QString Block_value_1);

	void dbManager_create_elmt_block(const QString &pathname, int32_t Index_count_2, QString Block_naam_2, QString Block_value_2);

	QString db_split_header(const QString &pathname);

    int32_t dbManager_create_elmt (const QStringList &elmt_txt, int32_t Index_count);


	signals:


	void send_text (const QString &text2);
	void send_min(const int &valuemin);
	void send_max(const int &valuemax);
	void send_actual(const int &valueactual);

	void send_log(const QString &Waarde2);
	void send_elmt(const QString &Waarde3);
	void send_process(const QString &Waarde4);

	public slots:

	private:
		QSqlDatabase m_db;
};

#endif // DBMANAGER_H
