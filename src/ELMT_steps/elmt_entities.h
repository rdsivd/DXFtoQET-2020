#ifndef ELMT_ENTITIES_H
#define ELMT_ENTITIES_H

#include <QWidget>
#include <QObject>

#include "data.h"
#include "src/dxf_load.h"
#include "db/dbmanager.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include "src/DXF_control/dxf_layer_control.h"
#include "src/DXF_control/dxf_ltype_control.h"
#include "src/DXF_control/dxf_text_control.h"
#include "src/ELMT_base_types/dxf_base_line.h"
#include "src/ELMT_base_types/dxf_base_circle.h"
#include "src/ELMT_base_types/dxf_base_arc.h"
#include "src/ELMT_base_types/dxf_base_text.h"
#include "src/ELMT_base_types/dxf_base_input.h"
#include "src/ELMT_base_types/dxf_base_terminal.h"
#include "src/ELMT_base_types/dxf_base_ellipse.h"
#include "src/ELMT_base_types/dxf_base_rectangel.h"
#include "src/ELMT_base_types/dxf_base_polyline.h"
#include "src/ELMT_steps/elmt_blocks.h"


class elmt_entities : public QWidget
{
	Q_OBJECT

	public:
    explicit elmt_entities(QWidget *parent = nullptr);

	int32_t xcount;
	int32_t rowcount;

    double hatchx;
    double hatchy;

	int end_seqend;
	int end_lwpoly;
	int readrecord;
    int32_t stringsize;

	int32_t count_vertex;
	int32_t comand_count2;
	int32_t max_vertex;

	QString Logtext;
	QString Recordvalue;
	QString Recordvalue2;
	QString RecordID;

	QString Signal_waarde1;
	QString Signal_log1;
	QString Signal_elmt1;


	QString ELMT_ID_instruction;


	void Open_SQL_DB (QString ELMT_filename);
	void Close_SQL_DB (QString ELMT_filename);

	QString Get_Entities (QString ELMT_filename);

	signals:

	void Signal1 (const QString &Waarde1);
	void send_log(const QString &Waarde2);
	void send_elmt(const QString &Waarde3);
	void send_process(const QString &Waarde4);

	public slots:
};

#endif // ELMT_ENTITIES_H
