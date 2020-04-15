#ifndef DXF_LOAD_H
#define DXF_LOAD_H

#include "data.h"
#include <QObject>

class dxf_load : public QWidget
{
	Q_OBJECT
	public:
    explicit dxf_load(QWidget *parent = nullptr);


	QString dxf_check;



	void dxf_header_split();
	void dxf_csv_split();
	int dxf_check_file();

	signals:

	public slots:
};

#endif // DXF_LOAD_H
