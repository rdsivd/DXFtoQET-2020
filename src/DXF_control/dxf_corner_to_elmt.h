#ifndef DXF_CORNER_TO_ELMT_H
#define DXF_CORNER_TO_ELMT_H

#include <QWidget>
#include <QObject>

#include "data.h"
#include "src/dxf_load.h"
#include "db/dbmanager.h"

class dxf_corner_to_elmt : public QWidget
{
	Q_OBJECT
	public:
    explicit dxf_corner_to_elmt(QWidget *parent = nullptr);


	double start_angle;
	double start_angle2;

	double end_angle;
	double end_angle2;

	double begin0;
	double begin1;
	double begin2;

	double einde0;
	double einde1;
	double einde2;

	double hoek2;

	double N;
	double O;
	double J;
	double K;
	double L;
	double M;
	double R;
	double S;
	double T;
	double U;
	double V;
	double W;

	double QET_start_angle();
	double QET_end_angle();
	double QET_corner_angle();

	signals:

	public slots:
};

#endif // DXF_CORNER_TO_ELMT_H
