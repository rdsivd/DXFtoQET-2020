#ifndef DXF_TEXT_CONTROL_H
#define DXF_TEXT_CONTROL_H

//#include <QMainWindow>
#include <QWidget>
#include <QObject>


class DXF_Text_control : public QWidget // QMainWindow
{
	Q_OBJECT
	public:
    explicit DXF_Text_control(QWidget *parent = nullptr);

	QString TextToCheck;

	QString Text_control();

	signals:

	public slots:

};

#endif // DXF_TEXT_CONTROL_H
