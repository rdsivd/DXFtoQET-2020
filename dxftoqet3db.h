#ifndef DXFTOQET3DB_H
#define DXFTOQET3DB_H

#include <QWidget>
#include <QObject>
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

#include "data.h"
#include "src/dxf_load.h"
#include "db/dbmanager.h"

#include "src/ELMT_steps/elmt_header_steps.h"

#include "src/ELMT_base_types/dxf_base_arc.h"
#include "src/ELMT_base_types/dxf_base_circle.h"
#include "src/ELMT_base_types/dxf_base_ellipse.h"
#include "src/ELMT_base_types/dxf_base_input.h"
#include "src/ELMT_base_types/dxf_base_line.h"
#include "src/ELMT_base_types/dxf_base_polyline.h"
#include "src/ELMT_base_types/dxf_base_rectangel.h"
#include "src/ELMT_base_types/dxf_base_terminal.h"
#include "src/ELMT_base_types/dxf_base_text.h"
#include "src/ELMT_base/baseelmt.h"
#include "src/ELMT_steps/elmt_tables.h"
#include "src/ELMT_steps/elmt_entities.h"


namespace Ui
{
	class DXFtoQET3DB;
}

class DXFtoQET3DB : public QWidget
{
	Q_OBJECT

	public:
    explicit DXFtoQET3DB(QWidget *parent = nullptr);
	~DXFtoQET3DB();

		dbManager mydb;
		//connect (&mydb ,SIGNAL (send_log(const QString &)),parent(),SLOT(update_log(const QString &)));

		QString QSQL_split;

        double hatchx;
        double hatchy;

		int main_sw1; // Binaery = 0 ASCII = 1
		int main_sw2; // CSV = 1
		int main_sw3; // DXF = 1

		int32_t CSV_line_count;
		int32_t CSV_row;
		int32_t CSV_col;

		int32_t csv_elmt_count;

		int32_t split_count1;
		int32_t counter_Split;
		int32_t split_lenght;

		int32_t dxf_split_count1;
		int32_t counter1;

		int32_t index_header;
		int32_t index_classes;
		int32_t index_tables;
		int32_t index_blocks;
		int32_t index_entities;
		int32_t index_objects;
		int32_t index_thumbnailimage;

		int32_t lenght_header;
		int32_t lenght_classes;
		int32_t lenght_tables;
		int32_t lenght_blocks;
		int32_t lenght_entities;
		int32_t lenght_objects;
		int32_t lenght_thumbnailimage;

		int32_t id_header;
		int32_t id_classes;
		int32_t id_tables;
		int32_t id_blocks;
		int32_t id_entities;
		int32_t id_objects;
		int32_t id_thumbnailimage;

        //    QVector<double> QET_x =  QVector<double>(QET_L_POLYLINE,0.0);

        int sw_header[1072];
        int sw_classes[1072];
        int sw_tables[1072];
        int sw_blocks[1072];
        int sw_entities[1072];
        int sw_objects[1072];
        int sw_thumbnailimage[1072];

		int32_t count_header;
		int32_t count_header_record_id;
		int32_t count_header_lines;
		int32_t count_header_item;

		int32_t count_classes;
		int32_t count_classes_record_id;
		int32_t count_classes_lines;
		int32_t count_classes_item;

		int32_t count_tables;
		int32_t count_tables_record_id;
		int32_t count_tables_lines;
		int32_t count_tables_item;

		int32_t count_blocks;
		int32_t count_blocks_record_id;
		int32_t count_blocks_lines;
		int32_t count_blocks_item;

		int32_t count_entities;
		int32_t count_entities_record_id;
		int32_t count_entities_lines;
		int32_t count_entities_item;

		int32_t count_objects;
		int32_t count_objects_record_id;
		int32_t count_objects_lines;
		int32_t count_object_item;

		int32_t count_thumbnailimage;
		int32_t count_thumbnailimage_record_id;
		int32_t count_thumbnailimage_lines;
		int32_t count_thumbnailimage_item;

		int32_t header_max_items;
		int32_t header_max_items2;
		int32_t header_max_items3;
		int32_t classes_max_items;
		int32_t classes_max_items2;
		int32_t classes_max_items3;
		int32_t tables_max_items;
		int32_t tables_max_items2;
		int32_t tables_max_items3;
		int32_t blocks_max_items;
		int32_t blocks_max_items2;
		int32_t blocks_max_items3;
		int32_t entities_max_items;
		int32_t entities_max_items2;
		int32_t entities_max_items3;
		int32_t objects_max_items;
		int32_t thumbnailimage_max_items;


		int32_t header_max_count;
		int32_t classes_max_count;
		int32_t tables_max_count;
		int32_t blocks_max_count;
		int32_t entities_max_count;
		int32_t objects_max_count;
		int32_t thumbnailimage_max_count;

		int32_t Record_Count_Header;
		int32_t Record_Count_Classes;
		int32_t Record_Count_Tables;
		int32_t Record_Count_Blocks;
		int32_t Record_Count_Entities;
		int32_t Record_Count_Objects;
		int32_t Record_Count_Thumbnailimage;

		int32_t for1;
		int32_t for2;
		int32_t for3;
		int32_t for4;
		int32_t for5;
		int32_t for6;
		int32_t for7;
		int32_t for8;

		int32_t line1;
		QString line2;
		int32_t line3;

		int32_t x;
		int32_t x1;
		int32_t x10;
		int32_t x2;
		int32_t x3;
		int32_t x4;
		int32_t xclear;
		int x3x;
		QString x3value;

		int32_t clear_code_set;

		int32_t max;
		int max3;

		int32_t index1;
		int32_t	index2;

		QStringList dxf_header;
		QStringList dxf_classes;
		QStringList dxf_tables;
		QStringList dxf_blocks;
		QStringList dxf_entities;
		QStringList dxf_objects;
		QStringList dxf_thumbnailimage;

        //    QVector<double> QET_x =  QVector<double>(QET_L_POLYLINE,0.0);

		QStringList dxf_header_items[DXF_item_split];
		QStringList dxf_classes_items[DXF_item_split];
		QStringList dxf_tables_items[DXF_item_split];
		QStringList dxf_blocks_items[DXF_item_split];
		QStringList dxf_entities_items[DXF_item_split];
		QStringList dxf_objects_items[DXF_item_split];
		QStringList dxf_thumbnailimage_items[DXF_item_split];
		QStringList split_tables_list[DXF_item_split];

		//QStringList split_list_1[1200];

		int count_tables_list;

		QString Copy_list_item;

		QString ResultELMT;
        QString Scaler;

		QString Inline0;
		QStringList Inline1;

		int InSW1;
		int InSW2;
		int xx;
        int stringsize;

		QString BlockNameItem;

		int32_t list_header;
		int32_t list_classes;
		int32_t list_tables;
		int32_t list_blocks;
		int32_t list_entities;
		int32_t list_objects;
		int32_t list_thumbnailimage;

		int32_t max_header;
		int32_t max_classes;
		int32_t max_tables;
		int32_t max_blocks;
		int32_t max_entities;
		int32_t max_objects;
		int32_t max_thumbnailimage;

		int32_t max_length;

		int32_t dxf_line_count1;
		int32_t dxf_line_count2;

		QString log_file;
		QString log_trans;
		QString log_split;
		QString status1;

		QString FileType;
		QString FileName;
		QString Filename2;
		QString Filename_db;
		QString Filename_db_temp;

		QString text1;

		QString Config_QET_User_Symbols;
		QString Config_DXF_Block_color;
		QString Config_DXF_Entities_color;
		QString Config_save_to_file;
		QString Config_in_read_all;

		QStringList Config_list;
		QStringList Config_List_Split;

		QString Result;
		QString Result4;

		QStandardItemModel *model;
		QStandardItemModel *model2;
		QStandardItemModel *model3;
		QAbstractItemModel *model4;
		QAbstractItemModel *model5;

		QStringList List2;
		QStringList List3;

		QStringList header_split;
		QStringList classes_split;
		QStringList tables_split;
		QStringList blocks_split;
		QStringList entities_split;
		QStringList objects_split;
		QStringList thumbnailimage_split;
		//QStringList split_tables_list;

		QString Signal_log1;
		QString Signal_elmt1;

		//db var

		int32_t Max_Lines;
		int32_t Count_x1;
        int32_t index_count_elmt;

		QString Read_Index;
		QString Read_Code;
		QString Read_Waarde;
		QString Read_Section;
		QString Read_Commando;
		QString Read_AcadValue;

        QStringList dbelmt;

	public:

		void split_header();

		void db_split_header();

		void split_classes();

		void db_split_classes();

		void split_tables();

		void db_split_tables();

		void split_blocks();

		void db_split_blocks();

		void split_entities();

		void db_split_entities();

		void split_objects();

		void db_split_objects();

		void split_thumbnailimage();

		void db_split_thumbnailimage();

		void section_lengts();

		void copy_list();

		void clear_dxf_header_items();

		void clear_dxf_classes_items();

		void clear_dxf_tables_items();

		void clear_dxf_blocks_items();

		void clear_dxf_entities_items();

		void clear_dxf_objects_items();

		void clear_dxf_thumbnailimage_items();

		void clear_split_tables();

		void clear_sw_header();

		void clear_dxf_code_tables();

		int Split_list(QString TypeList, int x3max, int count_list_item, int count_tables_list, int header_id);

		int DB_Split_list(QString TypeList, int x3max, int count_list_item, int count_tables_list, int header_id);

		//QString Calc_Width();
		//QString Calc_Height();

	signals:

		void send_text (const QString &text2);
		void send_min(const int &valuemin);
		void send_max(const int &valuemax);
		void send_actual(const int &valueactual);

		void send_log(const QString &Waarde2);
		void send_elmt(const QString &Waarde3);
		void send_process(const QString &Waarde4);
        void send_lines(const int &valuelines);

	public slots:

		void on_OpenFile_clicked();

		void on_savepath_2_clicked();

		void on_Load_dxf_into_tables_clicked();

		void on_Delete_DB_clicked();

		void on_Create_QET_ELMT_clicked();
		void on_Choose_DB_clicked();
		void on_SavetoELMT_clicked();
		void on_Convert_dxf_blocks_clicked();
		void on_Convert_dxf_entities_clicked();


		void on_progressBar_valueChanged(const int value1);
		void on_progressBar_valueMin(const int value2);
		void on_progressBar_valueMax(const int value3);
		void on_progressBar_text(const QString text4);

		void update_proces(const QString &Waarde_receve1);
		void update_elmt(const QString &Waarde_receve2);
		void update_log(const QString &Waarde_receve3);

	protected:
		void changeEvent(QEvent *e);

		private slots:
		void on_Button_Open_DXF_clicked();

        void on_CreateDBelmt_clicked();

private:
		Ui::DXFtoQET3DB *ui;
};

#endif // DXFTOQET3DB_H
