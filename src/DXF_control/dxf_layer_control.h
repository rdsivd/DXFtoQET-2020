#ifndef DXF_LAYER_CONTROL_H
#define DXF_LAYER_CONTROL_H

//#include <QMainWindow>
#include <QWidget>
#include <QObject>

#include "data.h"
#include "src/dxf_load.h"
#include "db/dbmanager.h"

class DXF_layer_control : public QWidget // QMainWindow
{
	Q_OBJECT
	public:
    explicit DXF_layer_control(QWidget *parent = nullptr);

	QString layer_to_find;
	QString layer_ltype;

	int Layer_count;
	int Layer_end;

	QString dxf_layer_ltype();

	signals:

	public slots:

};

#endif // DXF_LAYER_CONTROL_H
