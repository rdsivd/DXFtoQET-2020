#ifndef DXF_LTYPE_CONTROL_H
#define DXF_LTYPE_CONTROL_H

//#include <QMainWindow>
#include <QWidget>
#include <QObject>
#include <src/DXF_control/dxf_layer_control.h>

class DXF_Ltype_control : public QWidget // QMainWindow
{
	Q_OBJECT
	public:
    explicit DXF_Ltype_control(QWidget *parent = nullptr);

	QString LTfound;
	QString FindLT;
	QString Layer;

	QString Ltype_control();

	signals:

	public slots:

};

#endif // DXF_LTYPE_CONTROL_H
