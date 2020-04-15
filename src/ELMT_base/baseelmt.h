#ifndef BASEELMT_H
#define BASEELMT_H

//#include <QMainWindow>
#include <QWidget>
#include <QtCore>
#include <QObject>



class BaseELMT : public QWidget // QMainWindow
{
	Q_OBJECT
	public:
    explicit BaseELMT(QWidget *parent = nullptr);

	QString ELMT_definition_width;
	QString ELMT_definition_version;
	QString ELMT_definition_hotspot_x;
	QString ELMT_definition_hotspot_y;
	QString ELMT_definition_height;
	QString ELMT_definition_link_type;
	QString ELMT_definition_type;
	QString ELMT_definition_orientation;

	QString ELMT_uuid;

	QString ELMT_Name_en;
	QString ELMT_Name_fr;
	QString ELMT_Name_de;
	QString ELMT_Name_ar;
	QString ELMT_Name_it;
	QString ELMT_Name_pl;
	QString ELMT_Name_nl;
	QString ELMT_Name_be_nl;
	QString ELMT_Name_es;
	QString ELMT_Name_cs;

	QString ELMT_Name_text_en;
	QString ELMT_Name_text_fr;
	QString ELMT_Name_text_de;
	QString ELMT_Name_text_ar;
	QString ELMT_Name_text_it;
	QString ELMT_Name_text_pl;
	QString ELMT_Name_text_nl;
	QString ELMT_Name_text_be_nl;
	QString ELMT_Name_text_es;
	QString ELMT_Name_text_cs;

	QString ELMT_kind_name;
	QString ELMT_kind_show;
	QString ELMT_kind_type;

	QString ELMT_informations_Author;
	QString ELMT_informations_License;
	QString ELMT_converter_version;
	QString ELMT_converter_by;

	QString Result;

	QString DefinitionStart();
	QString DefinitionEnd();
	QString Uuid();
	QString Names();
	QString KindInformation();
	QString Informations();
	QString DescriptionStart();
	QString DescriptionEnd();

	QUuid Uuidstring;

	signals:

	public slots:

};

#endif // BASEELMT_H
