#include "dxftoqet3db.h"
#include "ui_dxftoqet3db.h"

extern struct DXF_base DXF_main_base[DXF_base_set];
extern struct DXF_codes DXF_code_tables[DXF_codes_set];
extern struct DXF_codes DXF_codes_tables_empty;
extern struct DXF_var DXF_variable;
extern struct DXF_Layers DXF_Layer_list[DXF_layers_set];
extern struct DXF_Entities DXF_Entities_List;

DXFtoQET3DB::DXFtoQET3DB(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DXFtoQET3DB)
	{

	ui->setupUi(this);

    ui->dxf_log->clear();
    Signal_log1.clear();

	QCoreApplication::setOrganizationName("rds");
	QCoreApplication::setApplicationName("DXFtoQET3_DB");

	QSettings settings;

	//data ActifData;

	if (!settings.contains("dxf_path"))
	{
		settings.setValue("dxf_path","..");
	}
	if (!settings.contains("qet_element_path"))
	{
		settings.setValue("qet_element_path","..");
	}

	settings.sync();

	DXF_main_base[0].dxf_filepath = settings.value("dxf_path").toString();

	DXF_main_base[0].dxf_savepath = settings.value("qet_element_path").toString();

	ui->dxf_file_path_save->setText(DXF_main_base[0].dxf_filepath);

	ui->QET_user_symbole_path_save->setText(DXF_main_base[0].dxf_savepath);
	ui->MainTab->repaint();

	//ui->progressBar1->text()="dxf_header";
	ui->progressBar1->setMinimum(0);
	ui->progressBar1->setMaximum(100);
	ui->progressBar1->setValue(0);
	ui->progressBar1->repaint();

	connect (this ,SIGNAL (send_log(const QString &)),this,SLOT(update_log(const QString &)));
	connect (this, SIGNAL (send_elmt(const QString &)),this,SLOT(update_elmt(const QString &)));
	connect (this, SIGNAL (send_process(const QString &)),this,SLOT(update_proces(const QString &)));

	connect (this,SIGNAL(send_text(const QString &)),this,SLOT(on_progressBar_text(const QString &)));
	connect (this,SIGNAL(send_min(const int &)),this,SLOT(on_progressBar_valueMin(const int &)));
	connect (this,SIGNAL(send_max(const int &)),this,SLOT(on_progressBar_valueMax(const int &)));
	connect (this,SIGNAL(send_actual(const int &)),this,SLOT(on_progressBar_valueChanged(const int &)));

    //connect (this,SIGNAL(send_lines(const int &)),this,SLOT(QETlines(const int &)));

	ui->MainTab->setCurrentIndex(5);
	ui->MainTab->repaint();


}

DXFtoQET3DB::~DXFtoQET3DB()
{
	delete ui;
}

void DXFtoQET3DB::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		default:
			break;
	}
}

void DXFtoQET3DB::on_OpenFile_clicked()
{
	ui->MainTab->setCurrentIndex(0);
	ui->MainTab->repaint();

	ui->dxf_log->activateWindow();
	ui->dxf_file_path_save->setText(DXF_main_base[0].dxf_savepath);
	ui->QET_user_symbole_path_save->setText(DXF_main_base[0].dxf_filepath);

	main_sw1=0;
	main_sw2=0;
	main_sw3=0;

	DXF_main_base[0].DXF_file_loaded_into_table=-1;

	// open file dialog

	ui->dxf_log->clear();

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append(" -> Open file \n");
    Signal_log1.append("============================================================================");
    Signal_log1.append(" \n");

	emit send_log(Signal_log1);

	QFileDialog dialog(this);
	dialog.setNameFilter(tr("DXF files (*.dxf *.DXF *.csv *.CSV)"));
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setViewMode(QFileDialog::Detail);


	if (dialog.exec() == QDialog::Accepted)
	{
		DXF_main_base[0].dxf_filepath = dialog.selectedFiles().first();


		DXF_main_base[0].dxf_dir = dialog.directory().absolutePath();
		DXF_main_base[0].dxf_openfile=DXF_main_base[0].dxf_filepath.split("/").last();

		ui->dxf_file_path_save->setText(DXF_main_base[0].dxf_savepath);

		FileType=DXF_main_base[0].dxf_openfile.split(".").last();
		FileName=DXF_main_base[0].dxf_openfile.split(".").first().toLower();

		Filename2=FileName.remove(QRegExp("[+-/#_=<>]"));
        DXF_main_base[0].dxf_openfile.clear();
		DXF_main_base[0].dxf_openfile=Filename2.toLower();
		DXF_main_base[0].dxf_filetype=FileType;

		Signal_log1.clear();
		Signal_log1.append(DXF_main_base[0].dxf_openfile);
		Signal_log1.append(" \n");
		Signal_log1.append("============================================================================");
        Signal_log1.append(" \n");

		emit send_log(Signal_log1);

		//DXF_main_base[0].DXF_ELMT_Name_text_en=FileName;
		//DXF_main_base[0].DXF_ELMT_Name_text_fr=FileName;

		//ui->elmt_lang_en->setText(FileName);
		//ui->elmt_lang_fr->setText(FileName);

		QFile file(DXF_main_base[0].dxf_filepath);
		if (!file.open(QFile::ReadOnly | QFile::Text))
		{
			QMessageBox::warning(this, tr("Application"),
					  tr("Cannot read file %1:\n%2.").arg(DXF_main_base[0].dxf_filepath).arg("binary or other non standard dxf file"));

		}

		ui->dxf_file_path->setPlaceholderText(DXF_main_base[0].dxf_dir);
		ui->dxf_open_file->setPlaceholderText(DXF_main_base[0].dxf_openfile);

		Signal_log1.clear();
		Signal_log1.append("read file ");
		Signal_log1.append(FileName);
		Signal_log1.append(" into program ");

		emit send_log(Signal_log1);

        DXF_main_base[0].dxf_text_all.clear();

		QTextStream in(&file);
		DXF_main_base[0].dxf_text_all = in.readAll();

		file.close();

        DXF_Entities_List.DXF_Result.clear();
        DXF_Entities_List.DXF_ResultBegin.clear();
        DXF_Entities_List.DXF_ResultBlock.clear();
        DXF_Entities_List.DXF_ResultEinde.clear();
        DXF_Entities_List.DXF_ResultBlock2.clear();
        DXF_Entities_List.DXF_ResultBlock2.clear();
        DXF_Entities_List.DXF_ResultEntitie.clear();
        DXF_Entities_List.DXF_ResultEntitieLine.clear();
        DXF_Entities_List.DXF_ResultEntitieLwpolyline.clear();
        DXF_Entities_List.DXF_ResultEntitieSolid.clear();
        DXF_Entities_List.DXF_ResultEntitieSpline.clear();
        DXF_Entities_List.DXF_ResultEntitieHatch.clear();
        DXF_Entities_List.DXF_ResultEntitiePolyline.clear();

		ui->dxf_file_loaded->setPlainText(DXF_main_base[0].dxf_text_all);
		ui->dxf_file_loaded->show();

		dxf_line_count1=DXF_main_base[0].dxf_text_all.count();

		ui->dxf_line_count1->setText(QString::number(dxf_line_count1,'f',0));

		ui->dxf_line_count1_2->clear();

		ui->dxf_line_count1_2->setText(QString::number(dxf_line_count1,'f',0));

		Signal_log1.clear();
		Signal_log1.append("check file for correct type of file ");

		emit send_log(Signal_log1);

        ui->Processing_dxf_file_2->clear();
        ui->Processing_dxf_file_2->insert(FileName);


		dxf_load dxf_lf(this);

		dxf_lf.dxf_header_split();

		dxf_line_count2=DXF_main_base[0].dxf_input.count();

		main_sw1=dxf_lf.dxf_check_file();

		if (FileType=="csv" or FileType=="CSV")
		{
			main_sw2=1;
			main_sw3=0;

			Signal_log1.clear();
			Signal_log1.append("file of type CSV ");

			emit send_log(Signal_log1);

			//dxf_lf.dxf_csv_split();

			//int32_t dxf_line_count2=DXF_main_base[0].dxf_csv_line_count;
			//ui->dxf_line_count2->setText(QString::number(dxf_line_count2,'f',0));
		}
		else
		{
			main_sw2=0;
		}

		if (FileType=="dxf" or FileType=="DXF")
		{

			main_sw3=1;
			main_sw2=0;

			Signal_log1.clear();
			Signal_log1.append("file of type DXF ");

			emit send_log(Signal_log1);

		}
		else
		{
			main_sw3=0;
		}

		if (main_sw1==1 and main_sw2==0)
		{

			Signal_log1.clear();
			Signal_log1.append("file of type ASCII DXF ");

			emit send_log(Signal_log1);

		}

		if (main_sw1==0 and main_sw2==0)
		{

			Signal_log1.clear();
			Signal_log1.append("file of type BINARY DXF ");

			emit send_log(Signal_log1);

		}



	}


	Signal_log1.clear();
	Signal_log1.append("============================================================================");
    Signal_log1.append(" \n");

	emit send_log(Signal_log1);
    mydb.dbActivate(Filename_db);
	return;
}

void DXFtoQET3DB::on_savepath_2_clicked()
{

	QSettings settings;

	Config_QET_User_Symbols = QFileDialog::getExistingDirectory(this, tr("Open Directory"),DXF_main_base[0].dxf_dir ,QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

	ui->QET_user_symbole_path_save->setText(Config_QET_User_Symbols);

	if (!settings.contains("qet_element_path"))
	{
		settings.setValue("qet_element_path",Config_QET_User_Symbols);
	}
	else
	{
		settings.setValue("qet_element_path",Config_QET_User_Symbols);
	}

	settings.sync();

	DXF_main_base[0].dxf_savepath=Config_QET_User_Symbols;


}

void DXFtoQET3DB::on_Load_dxf_into_tables_clicked()
{
	ui->MainTab->setCurrentIndex(0);
	ui->MainTab->repaint();

	Filename_db=DXF_main_base[0].dxf_savepath + "/" +FileName;
	Filename_db.append(".db3");

	ui->dxf_line_count1_2->clear();
	ui->Processing_dxf_file_2->clear();
	ui->Processing_dxf_file_2->insert(FileName);

	on_Delete_DB_clicked();

	ui->dxf_log->activateWindow();

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("=> Start loading dxf");
	Signal_log1.append(FileName);
	Signal_log1.append(" file into DB tables \n");
	Signal_log1.append("Creating DB : ");
	Signal_log1.append(FileName);
	Signal_log1.append("\n");
	Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	Signal_log1.clear();
	Signal_log1.append("create : ");
	Signal_log1.append(Filename_db);

	emit send_log(Signal_log1);

	mydb.dbManager1(Filename_db);



	Signal_log1.clear();
	Signal_log1.append("creating tables \n");
	Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	mydb.dbManager_create_tables(FileName);

	dxf_split_count1=DXF_main_base[0].dxf_input.count();

	counter1=0;

	Signal_log1.clear();
	Signal_log1.append("total characters : ");
	Signal_log1.append(QString::number(dxf_line_count1));
	Signal_log1.append("\n");
	Signal_log1.append("total lines : ");
	Signal_log1.append(QString::number(dxf_line_count2));
	Signal_log1.append("\n");
	Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	index_header= DXF_main_base[0].dxf_input.indexOf("HEADER");
	index_classes= DXF_main_base[0].dxf_input.indexOf("CLASSES");
	index_tables= DXF_main_base[0].dxf_input.indexOf("TABLES");
	index_blocks= DXF_main_base[0].dxf_input.indexOf("BLOCKS");
	index_entities= DXF_main_base[0].dxf_input.indexOf("ENTITIES");
	index_objects= DXF_main_base[0].dxf_input.indexOf("OBJECTS");
	index_thumbnailimage= DXF_main_base[0].dxf_input.indexOf("THUMBNAILIMAGE");

	Signal_log1.clear();
	Signal_log1.append("index header : ");
	Signal_log1.append(QString::number(index_header));
	Signal_log1.append("\n");
	Signal_log1.append("index classes : ");
	Signal_log1.append(QString::number(index_classes));
	Signal_log1.append("\n");
	Signal_log1.append("index tables : ");
	Signal_log1.append(QString::number(index_tables));
	Signal_log1.append("\n");
	Signal_log1.append("index blocks : ");
	Signal_log1.append(QString::number(index_blocks));
	Signal_log1.append("\n");
	Signal_log1.append("index entities : ");
	Signal_log1.append(QString::number(index_entities));
	Signal_log1.append("\n");
	Signal_log1.append("index objects : ");
	Signal_log1.append(QString::number(index_objects));
	Signal_log1.append("\n");
	Signal_log1.append("index thumbnailimage : ");
	Signal_log1.append(QString::number(index_thumbnailimage));
	Signal_log1.append("\n");
	Signal_log1.append("============================================================================");
	Signal_log1.append("\n");

	emit send_log(Signal_log1);

	section_lengts();

	copy_list();

	Signal_log1.clear();
	Signal_log1.append("============================================================================");
	Signal_log1.append("\n");

	emit send_log(Signal_log1);

	if (index_header!=-1)
	{
		Signal_log1.clear();
		Signal_log1.append("Splitting HEADER list ");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);

		split_header();

	}
	else
	{

		Signal_log1.clear();
		Signal_log1.append("no HEADER list to split ");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);
	}

	if (index_classes!=-1)
	{
		Signal_log1.clear();
		Signal_log1.append("Splitting CLASSES list ");
		Signal_log1.append(": disabled");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);

		//split_classes();
	}
	else
	{

		Signal_log1.clear();
		Signal_log1.append("no CLASSES list to split ");
		Signal_log1.append(": disabled");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);
	}

	if (index_tables!=-1)
	{
		Signal_log1.clear();
		Signal_log1.append("Splitting TABLES list ");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);

		split_tables();
	}
	else
	{

		Signal_log1.clear();
		Signal_log1.append("no TABLES list to split ");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);
	}


	if (index_blocks!=-1)
	{
		Signal_log1.clear();
		Signal_log1.append("Splitting BLOCKS list ");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);

		split_blocks();
	}
	else
	{

		Signal_log1.clear();
		Signal_log1.append("no BLOCKS list to split ");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);
	}


	if (index_entities!=-1)
	{
		Signal_log1.clear();
		Signal_log1.append("Splitting ENTITIES list ");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);

		split_entities();
	}
	else
	{

		Signal_log1.clear();
		Signal_log1.append("no ENTITIES list to split ");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);
	}

	if (index_objects!=-1)
	{
		Signal_log1.clear();
		Signal_log1.append("Splitting OBJECTS list ");
		Signal_log1.append(": disabled");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);

		//split_objects();

	}
	else
	{

		Signal_log1.clear();
		Signal_log1.append("no OBJECTS list to split ");
		Signal_log1.append(": disabled");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);
	}

	if (index_thumbnailimage!=-1)
	{
		Signal_log1.clear();
		Signal_log1.append("Splitting THUMBNAILIMAGE list ");
		Signal_log1.append(": disabled");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);

		//split_thumbnailimage();

	}
	else
	{

		Signal_log1.clear();
		Signal_log1.append("no THUMBNAILIMAGE list to split ");
		Signal_log1.append(": disabled");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);
	}

	mydb.dbManager_close(FileName);

	Signal_log1.clear();
	Signal_log1.append("End loading into db ");
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);
	return;
}

void DXFtoQET3DB::on_Delete_DB_clicked()
{

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("=> Start deleting ");
	Signal_log1.append(Filename_db);
	Signal_log1.append("\n");
	Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);


	QFile::remove(Filename_db);
}

void DXFtoQET3DB::section_lengts()
{

	Signal_log1.clear();
	Signal_log1.append("calculating section lengths ");
	Signal_log1.append("\n");
	Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	// header

	lenght_header=index_classes-index_header;

	if(lenght_header<0)
	{
		lenght_header=index_tables-index_header;
	}

	if(lenght_header<0)
	{
		lenght_header=index_blocks-index_header;
	}

	if(lenght_header<0)
	{
		lenght_header=index_entities-index_header;
	}

	if(lenght_header<0)
	{
		lenght_header=index_objects-index_header;
	}

	if(lenght_header<0)
	{
		lenght_header=index_thumbnailimage-index_header;
	}

	if(lenght_header<0)
	{
		lenght_header=dxf_line_count2-index_header;
	}

	if(lenght_header<0)
	{
		Signal_log1.clear();
		Signal_log1.append("no section HEADER found  ");

		emit send_log(Signal_log1);

		lenght_header=-1;
	}

	Signal_log1.clear();
	Signal_log1.append("header lenght : ");

	Signal_log1.append(QString::number(lenght_header));

	emit send_log(Signal_log1);

	// classes

	lenght_classes=index_tables-index_classes;

	if(lenght_classes<0)
	{
		lenght_classes=index_blocks-index_classes;
	}

	if(lenght_classes<0)
	{
		lenght_classes=index_entities-index_classes;
	}

	if(lenght_classes<0)
	{
		lenght_classes=index_objects-index_classes;
	}

	if(lenght_classes<0)
	{
		lenght_header=index_thumbnailimage-index_classes;
	}

	if(lenght_classes<0)
	{
		lenght_header=dxf_line_count2-index_classes;
	}

	if(lenght_classes<0)
	{
		Signal_log1.clear();
		Signal_log1.append("no section CLASSES found  ");

		emit send_log(Signal_log1);

		lenght_classes=-1;
	}

	Signal_log1.clear();
	Signal_log1.append("classes lenght : ");

	Signal_log1.append(QString::number(lenght_classes));

	emit send_log(Signal_log1);

	// tables


	lenght_tables=index_blocks-index_tables;

	if(lenght_tables<0)
	{
		lenght_tables=index_entities-index_tables;
	}

	if(lenght_tables<0)
	{
		lenght_tables=index_objects-index_tables;
	}

	if(lenght_tables<0)
	{
		lenght_tables=index_thumbnailimage-index_tables;
	}

	if(lenght_tables<0)
	{
		lenght_tables=dxf_line_count2-index_tables;
	}

	if(lenght_tables<0)
	{
		Signal_log1.clear();
		Signal_log1.append("no section TABLES found  ");

		emit send_log(Signal_log1);

		lenght_tables=-1;

	}

	Signal_log1.clear();
	Signal_log1.append("tables lenght : ");

	Signal_log1.append(QString::number(lenght_tables));

	emit send_log(Signal_log1);

	// blocks

	lenght_blocks=index_entities-index_blocks;

	if(lenght_blocks<0)
	{
		lenght_blocks=index_objects-index_blocks;
	}

	if(lenght_blocks<0)
	{
		lenght_blocks=index_thumbnailimage-index_blocks;
	}

	if(lenght_blocks<0)
	{
		lenght_blocks=dxf_line_count2-index_blocks;
	}

	if(lenght_blocks<0)
	{
		Signal_log1.clear();
		Signal_log1.append("no section BLOCKS found  ");

		emit send_log(Signal_log1);

		lenght_blocks=-1;
	}

	Signal_log1.clear();
	Signal_log1.append("blocks lenght : ");

	Signal_log1.append(QString::number(lenght_blocks));

	emit send_log(Signal_log1);

	// entities

	lenght_entities=index_objects-index_entities;

	if(lenght_entities<0)
	{
		lenght_entities=index_thumbnailimage-index_entities;
	}

	if(lenght_entities<0)
	{
		lenght_entities=dxf_line_count2-index_entities;
	}

	if(lenght_entities<0)
	{
		Signal_log1.clear();
		Signal_log1.append("no section ENTITIES found  ");

		emit send_log(Signal_log1);

		lenght_entities=-1;
	}

	Signal_log1.clear();
	Signal_log1.append("entities lenght : ");

	Signal_log1.append(QString::number(lenght_entities));

	emit send_log(Signal_log1);

	// objects

	lenght_objects=index_thumbnailimage-index_objects;

	if(lenght_objects<0)
	{
		lenght_objects=index_thumbnailimage-index_objects;
	}

	if(lenght_objects<0)
	{
		lenght_objects=dxf_line_count2-index_objects;
	}

	if(lenght_objects<0)
	{
		Signal_log1.clear();
		Signal_log1.append("no section OBJECTS found  ");

		emit send_log(Signal_log1);

		lenght_objects=-1;
	}

	Signal_log1.clear();
	Signal_log1.append("objects lenght : ");

	Signal_log1.append(QString::number(lenght_objects));

	emit send_log(Signal_log1);

	// thumbnailimage

	lenght_thumbnailimage=dxf_line_count2-index_objects;

	if(lenght_thumbnailimage<0)
	{
		Signal_log1.clear();
		Signal_log1.append("no section THUMBNAILIMAGE found  ");

		emit send_log(Signal_log1);

		lenght_thumbnailimage=-1;
	}
	else
	{
		lenght_thumbnailimage=dxf_line_count2-index_thumbnailimage;
	}

	Signal_log1.clear();
	Signal_log1.append("thumbnailimage lenght : ");

	Signal_log1.append(QString::number(lenght_thumbnailimage));

	emit send_log(Signal_log1);

	return;

}

void DXFtoQET3DB::copy_list()
{
	dxf_header.clear();
	dxf_classes.clear();
	dxf_tables.clear();
	dxf_blocks.clear();
	dxf_entities.clear();
	dxf_objects.clear();
	dxf_thumbnailimage.clear();

	list_header=0;
	list_classes=0;
	list_tables=0;
	list_blocks=0;
	list_entities=0;
	list_objects=0;
	list_thumbnailimage=0;

	max_length=DXF_main_base[0].dxf_input.count();

	max_header=index_header+lenght_header-5;
	max_classes=index_classes+lenght_classes-5;
	max_tables=index_tables+lenght_tables-5;
	max_blocks=index_blocks+lenght_blocks-5;
	max_entities=index_entities+lenght_entities-5;
	max_objects=index_objects+lenght_objects-5;
	max_thumbnailimage=index_thumbnailimage+lenght_thumbnailimage-5;


	if (index_header != -1)
	{
		for (for1=1;for1<max_header-index_header; for1++)
		{

			dxf_header.append(DXF_main_base[0].dxf_input[index_header+for1]);

		}

		list_header=dxf_header.count();
	}

	if (index_classes != -1)
	{
		for (for2=1;for2<max_classes-index_classes;for2++)
		{

			dxf_classes.append(DXF_main_base[0].dxf_input[index_classes+for2]);

		}

		list_classes=dxf_classes.count();
	}

	if (index_tables != -1)
	{

		for (for3=1;for3<max_tables-index_tables;for3++)
		{

			dxf_tables.append(DXF_main_base[0].dxf_input[index_tables+for3]);

		}

		list_tables=dxf_tables.count();
	}

	if (index_blocks != -1)
	{
		for (for4=1;for4<max_blocks-index_blocks;for4++)
		{

			dxf_blocks.append(DXF_main_base[0].dxf_input[index_blocks+for4]);

		}

		list_blocks=dxf_blocks.count();
	}

	if (index_entities != -1)
	{
		for (for5=1;for5<max_entities-index_entities;for5++)
		{

			dxf_entities.append(DXF_main_base[0].dxf_input[index_entities+for5]);

		}

		list_entities=dxf_entities.count();
	}

	if (index_objects != -1)
	{
		for (for6=1;for6<max_objects-index_objects ;for6++)
		{

			dxf_objects.append(DXF_main_base[0].dxf_input[index_objects+for6]);

		}

		list_objects=dxf_objects.count();
	}

	if (index_thumbnailimage != -1)
	{
		for (for7=1;for7<max_thumbnailimage-index_thumbnailimage;for7++)
		{

			dxf_thumbnailimage.append(DXF_main_base[0].dxf_input[index_thumbnailimage+for7]);

		}

		list_thumbnailimage=dxf_thumbnailimage.count();
	}


	return;

}

void DXFtoQET3DB::split_header()
{
	header_max_items=dxf_header.count("  9");
	header_max_items2=dxf_header.count(" 9");
	header_max_items3=dxf_header.count("9");

	header_max_items=header_max_items+header_max_items2+header_max_items3;

	header_max_count=dxf_header.count();

	Signal_log1.clear();
	Signal_log1.append("header items : ");
	Signal_log1.append(QString::number(header_max_items));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	count_header=0;
	count_header_record_id=1;
	count_header_lines=0;
	id_header=1;

	clear_dxf_header_items();
	clear_split_tables();
	x1=-1;

	// split input into tempory table

	for (x2=0;x2<header_max_count and header_max_items<DXF_item_split;x2++)
	{

		if (QString(dxf_header[x2]).toInt()==9)
		{
			x1=x1+1;
			split_tables_list[x1].append(dxf_header[x2]); //??
			x2++;
			split_tables_list[x1].append(dxf_header[x2]);
		}
		else
		{
			split_tables_list[x1].append(dxf_header[x2]); //??
			x2++;
			split_tables_list[x1].append(dxf_header[x2]);
		}
	}


	clear_sw_header();

	Signal_log1.clear();
	Signal_log1.append("Splitting HEADER  ");

	emit send_log(Signal_log1);

	max=0;
	Record_Count_Header=1;



	clear_dxf_code_tables();

	ui->dxf_section->clear();
	ui->dxf_section->insert("Section Header");




	emit send_text("dxf_header");
	emit send_min(0);
	emit send_max(header_max_items-1);



	text1=QString::number(header_max_items);
	ui->dxf_section_count->clear();
	ui->dxf_section_count->insert(text1);


	while (count_header< header_max_items)
	{
		/*text1=QString::number(count_header);
		ui->dxf_section_count->clear();
		ui->dxf_section_count->insert(text1);
		ui->dxf_log->repaint();*/

		count_header_item=0;
		x3=split_tables_list[count_header].count();

		if (x3>DXF_codeset_copies)
		{

			Signal_log1.clear();
			Signal_log1.append("============================================================================\n");
			Signal_log1.append("Splitting header : out of range subitems acad command \n");
			Signal_log1.append(QString::number(x3));
			Signal_log1.append(" > ");
			Signal_log1.append(QString::number(DXF_codeset_copies));
			Signal_log1.append("\n");
			Signal_log1.append("============================================================================");

			emit send_log(Signal_log1);

		}

		clear_dxf_code_tables();

		emit send_actual(count_header);

		// record of temp table split to dxf table
		max=Split_list("dxf_header", x3, count_header_item, count_header, id_header );



		Record_Count_Header= mydb.dbManager_added_records(Filename_db, &max,&Record_Count_Header,"dxf_header");

		sw_header[9]=0;
		sw_header[0]=0;


		id_header++;

		count_header++;



	}



	return;

}

void DXFtoQET3DB::db_split_header()
{


	mydb.dbManager1(Filename_db);

	//QsqlString="create table dxf_file (Index_count primary key, Code, Waarde, Section, Commando )";

	QSqlQuery Header_Query;

	Header_Query.prepare("SELECT * FROM dxf_file WHERE section =(:Section)");
	Header_Query.bindValue(":Section","HEADER");


	Header_Query.exec();

	header_max_items=dxf_header.count("  9");
	header_max_items2=dxf_header.count(" 9");
	header_max_items3=dxf_header.count("9");

	header_max_items=header_max_items+header_max_items2+header_max_items3;

	header_max_count=dxf_header.count();

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("DB split header items : ");
	Signal_log1.append(QString::number(header_max_items));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	count_header=0;
	count_header_record_id=1;
	count_header_lines=0;
	id_header=1;

	//clear_dxf_header_items();
	clear_split_tables();
	x1=-1;
	x2=0;

	emit send_text("dxf_header");
	emit send_min(0);
	emit send_max(header_max_items-1);

	while (Header_Query.next())
	{
		QSqlRecord Header_record=Header_Query.record();

		//split_list_1[Header_record.value("Code").toInt()].append(Header_record.value("Waarde").toString());

		Read_Index=Header_record.value("Index_count").toString();
		Read_Code=Header_record.value("Code").toString();
		Read_Waarde=Header_record.value("Waarde").toString();
		Read_Section=Header_record.value("Section").toString();
		Read_Commando=Header_record.value("Cmmando").toString();
		Read_AcadValue=Header_record.value("AcadValue").toString();

		if ((Header_record.value("Code").toInt()==9) and (x1<DXF_item_split))
		{
			x1++;
			split_tables_list[x1].append(Header_record.value("Code").toString() );

			split_tables_list[x1].append(Header_record.value("Waarde").toString() );

		}
		else
		{
			split_tables_list[x1].append(Header_record.value("Code").toString() );

			split_tables_list[x1].append(Header_record.value("Waarde").toString() );
		}

		if (x1 > DXF_item_split)
		{
			Signal_log1.clear();
			Signal_log1.append(QTime::currentTime().toString());
			Signal_log1.append("\n");
			Signal_log1.append("split table to short : ");
			Signal_log1.append(QString::number(x1));
			Signal_log1.append(" > ");
			Signal_log1.append(QString::number(DXF_item_split));
			//Signal_log1.append("============================================================================");

			emit send_log(Signal_log1);
		}
		emit send_actual(x1);

	}

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("end split table ");
	//Signal_log1.append(QString::number(header_max_items));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	header_max_items=x1;

	Signal_log1.clear();
	Signal_log1.append("header items : ");
	Signal_log1.append(QString::number(header_max_items));
	Signal_log1.append("\n");
	Signal_log1.append("X1 : ");
	Signal_log1.append(QString::number(x1));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	// split input into tempory table

	/*for (x2=0;x2<header_max_count and header_max_items<DXF_item_split;x2++)
	{

		if (QString(dxf_header[x2]).toInt()==9)
		{
			x1=x1+1;
			split_tables_list[x1].append(dxf_header[x2]); //??
			x2++;
			split_tables_list[x1].append(dxf_header[x2]);
		}
		else
		{
			split_tables_list[x1].append(dxf_header[x2]); //??
			x2++;
			split_tables_list[x1].append(dxf_header[x2]);
		}
	}*/



	//clear_sw_header();

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("Splitting HEADER  ");

	emit send_log(Signal_log1);

	max=0;
	Record_Count_Header=1;



	//clear_dxf_code_tables();

	ui->dxf_section->clear();
	ui->dxf_section->insert("Section Header");




	emit send_text("dxf_header");
	emit send_min(0);
	emit send_max(header_max_items-1);



	text1=QString::number(header_max_items);
	ui->dxf_section_count->clear();
	ui->dxf_section_count->insert(text1);

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	//Signal_log1.append("\n");
	Signal_log1.append("filling table dxf_header ");
	emit send_log(Signal_log1);

	while (count_header< header_max_items)
	{
		/*text1=QString::number(count_header);
		ui->dxf_section_count->clear();
		ui->dxf_section_count->insert(text1);
		ui->dxf_log->repaint();*/

		/*Signal_log1.clear();
		Signal_log1.append(QTime::currentTime().toString());
		Signal_log1.append("\n");
		Signal_log1.append("start split ");
		Signal_log1.append(QString::number(count_header));
		emit send_log(Signal_log1);*/

		count_header_item=0;
		x3=split_tables_list[count_header].count();

		if (x3>DXF_codeset_copies)
		{

			Signal_log1.clear();
			Signal_log1.append("============================================================================\n");
			Signal_log1.append("Splitting header : out of range subitems acad command \n");
			Signal_log1.append(QString::number(x3));
			Signal_log1.append(" > ");
			Signal_log1.append(QString::number(DXF_codeset_copies));
			Signal_log1.append("\n");
			Signal_log1.append("============================================================================");

			emit send_log(Signal_log1);

		}

		clear_dxf_code_tables();

		emit send_actual(count_header);

		// record of temp table split to dxf table
		//max=Split_list("dxf_header", x3, count_header_item, count_header, id_header );

		max=DB_Split_list("dxf_header", x3, count_header_item, count_header, id_header );

		/*Signal_log1.clear();
		Signal_log1.append(QTime::currentTime().toString());
		Signal_log1.append("\n");
		Signal_log1.append("table dxf_header : ");
		emit send_log(Signal_log1);*/

		Record_Count_Header= mydb.DB_dbManager_added_records(Filename_db, &max,&Record_Count_Header,"dxf_header");

		/*Signal_log1.clear();
		Signal_log1.append(QTime::currentTime().toString());
		Signal_log1.append("\n");
		Signal_log1.append("end save record ");
		emit send_log(Signal_log1);*/

		sw_header[9]=0;
		sw_header[0]=0;


		id_header++;

		count_header++;



	}

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("end ");
	emit send_log(Signal_log1);

	mydb.dbManager_close(Filename_db);

	return;

}

int DXFtoQET3DB::DB_Split_list(QString TypeList, int x3max, int count_list_item, int count_tables_list, int header_id)
{

	max3=0;
	clear_sw_header();

	for (int xy=0;xy <1200;xy++)
	{
		if(DXF_main_base[0].split_list_1[xy].count()>0)
		{
			DXF_main_base[0].split_list_1[xy].clear();
		}
	}

	Signal_log1.clear();
	Signal_log1.append("============================================================================");
	Signal_log1.append("\n");
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append(" - splitter : ");
	Signal_log1.append(QString::number(x3max));
	Signal_log1.append(" - list items : ");
	Signal_log1.append(QString::number(count_list_item));
	Signal_log1.append(" - table list : ");
	Signal_log1.append(QString::number(count_tables_list));
	Signal_log1.append(" - header id : ");
	Signal_log1.append(QString::number(header_id));
	Signal_log1.append("\n");

	emit send_log(Signal_log1);


	while (count_list_item<(x3max-1) and count_list_item<DXF_codeset_copies)
	{

		line1=QString(split_tables_list[count_tables_list][count_list_item]).toInt();
		line2=split_tables_list[count_tables_list][count_list_item+1];

		Signal_log1.clear();
		Signal_log1.append(" count item ");
		Signal_log1.append(QString::number(count_list_item));
		Signal_log1.append(" - item code : ");
		Signal_log1.append(QString::number(line1));
		Signal_log1.append(" - value : ");
		Signal_log1.append(line2);
		//Signal_log1.append("\n");

		emit send_log(Signal_log1);

		DXF_main_base[0].split_list_1[line1].append(line2);


		switch (line1)
		{
			case 0:

				DXF_code_tables[0].Section=TypeList;
				DXF_code_tables[0].Command=line2;

				DXF_code_tables[0].ID_instruction=QString::number(header_id);

			break;

			case 9:

				DXF_code_tables[0].Section=TypeList;
				DXF_code_tables[0].Command=line2;

				DXF_code_tables[0].ID_instruction=QString::number(header_id);

				break;
		}



		count_list_item=count_list_item+2;
	}




	for (xx=0; xx<1200;xx++)
	{


		if(DXF_main_base[0].split_list_1[xx].count() > max3)
		{
			max3=DXF_main_base[0].split_list_1[xx].count();
		}

	}

	for (int xy=0;xy <1200;xy++)
	{
		if (DXF_main_base[0].split_list_1[xy].count()>max3)
		{
			//DXF_main_base[0].split_list_1[xy].value()=" ";
		}
		else
		{
			for (int xz=DXF_main_base[0].split_list_1[xy].count();xz<max3;xz++)
			{
				if (DXF_main_base[0].split_list_1[xy].count()>=max3)
				{

				}
				else
				{
					DXF_main_base[0].split_list_1[xy].append(" ");
				}
			}
		}

	}

	return max3;

}

void DXFtoQET3DB::split_classes()
{
	classes_max_items=dxf_classes.count("  0");
	classes_max_items2=dxf_classes.count(" 0");
	classes_max_items3=dxf_classes.count("0");

	classes_max_items=classes_max_items+classes_max_items2+classes_max_items3;

	classes_max_count=dxf_classes.count();

	Signal_log1.clear();
	Signal_log1.append("classes items : ");
	Signal_log1.append(QString::number(classes_max_items));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	count_classes=0;
	count_classes_record_id=1;
	count_classes_lines=0;
	id_header=1;


	clear_dxf_classes_items();
	clear_split_tables();

	x1=-1;

	for (x2=0;x2<classes_max_count and classes_max_items<DXF_item_split;x2++)
	{

		if (QString( dxf_classes[x2]).toInt()==0)
		{
			x1=x1+1;
			split_tables_list[x1].append(dxf_classes[x2]);
			x2++;
			split_tables_list[x1].append(dxf_header[x2]);
		}
		else
		{
			split_tables_list[x1].append(dxf_classes[x2]);
			x2++;
			split_tables_list[x1].append(dxf_header[x2]);
		}
	}

	clear_sw_header();

	Signal_log1.clear();
	Signal_log1.append("Splitting CLASSES  ");

	emit send_log(Signal_log1);

	clear_dxf_code_tables();

	max=0;
	Record_Count_Classes=1;

	//Record_Count_Tables=1;

	clear_dxf_code_tables();

	ui->dxf_section->clear();
	ui->dxf_section->insert("Section Classes");


	emit send_text("dxf_classes");
	emit send_min(0);
	emit send_max(classes_max_items-1);

	text1=QString::number(classes_max_items);
	ui->dxf_section_count->clear();
	ui->dxf_section_count->insert(text1);



	while (count_classes< classes_max_items)
	{
		count_classes_item=0;

		x3=split_tables_list[count_classes].count();

		if (x3>DXF_codeset_copies)
		{

			Signal_log1.clear();
			Signal_log1.append("============================================================================\n");
			Signal_log1.append("Splitting classes : out of range subitems acad command \n");
			Signal_log1.append(QString::number(x3));
			Signal_log1.append(" > ");
			Signal_log1.append(QString::number(DXF_codeset_copies));
			Signal_log1.append("\n");
			Signal_log1.append("============================================================================");

			emit send_log(Signal_log1);


		}

		clear_dxf_code_tables();

		emit send_actual(count_classes);

		max=Split_list("dxf_classes", x3, count_classes_item, count_classes, id_header );

		//Record_Count_Tables++;

		//Record_Count_Tables=Record_Count_Tables+count_classes;

		Record_Count_Tables= mydb.dbManager_added_records(Filename_db, &max,&Record_Count_Tables,"dxf_classes");

		sw_header[0]=0;
		sw_header[9]=0;

		id_header++;

		count_classes++;
		//Record_Count_Tables++;




	}

	mydb.dbManager_close(Filename_db);

	return;
}

void DXFtoQET3DB::db_split_classes()
{

	mydb.dbManager1(Filename_db);

	//QsqlString="create table dxf_file (Index_count primary key, Code, Waarde, Section, Commando )";

	QSqlQuery Tables_Query;

	Tables_Query.prepare("SELECT * FROM dxf_file WHERE section =(:Section)");
	Tables_Query.bindValue(":Section","CLASSES");

	Tables_Query.exec();

	classes_max_items=dxf_classes.count("  0");
	classes_max_items=tables_max_items+dxf_classes.count(" 0");
	classes_max_items=tables_max_items+dxf_classes.count("0");


	classes_max_count=dxf_classes.count();

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("classes items : ");
	Signal_log1.append(QString::number(classes_max_items));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);



	count_tables=0;
	count_tables_record_id=1;
	count_tables_lines=0;
	id_header=1;

	clear_dxf_tables_items();
	clear_split_tables();

	x1=-1;

	while (Tables_Query.next())
	{
		QSqlRecord Header_record=Tables_Query.record();

		Read_Index=Header_record.value("Index_count").toString();
		Read_Code=Header_record.value("Code").toString();
		Read_Waarde=Header_record.value("Waarde").toString();
		Read_Section=Header_record.value("Section").toString();
		Read_Commando=Header_record.value("Cmmando").toString();
		Read_AcadValue=Header_record.value("AcadValue").toString();

		if ((Header_record.value("Code").toInt()==0) and (x1<DXF_item_split))
		{
			x1++;
			split_tables_list[x1].append(Header_record.value("Code").toString() );

			split_tables_list[x1].append(Header_record.value("Waarde").toString() );
		}
		else
		{
			split_tables_list[x1].append(Header_record.value("Code").toString() );

			split_tables_list[x1].append(Header_record.value("Waarde").toString() );
		}


		if (x1 > DXF_item_split)
		{
			Signal_log1.clear();
			Signal_log1.append(QTime::currentTime().toString());
			Signal_log1.append("\n");
			Signal_log1.append("split table to short : ");
			Signal_log1.append(QString::number(x1));
			Signal_log1.append(" > ");
			Signal_log1.append(QString::number(DXF_item_split));
			//Signal_log1.append("============================================================================");

			emit send_log(Signal_log1);
		}

	}

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("end split table ");

	//Signal_log1.append(QString::number(tables_max_items));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	/*for (x2=0;x2<tables_max_count and tables_max_items<DXF_item_split;x2++)
	{

		if (QString(dxf_tables[x2]).toInt()==0)
		{
			x1=x1+1;
			split_tables_list[x1].append(dxf_tables[x2]);
			x2++;
			split_tables_list[x1].append(dxf_tables[x2]);
		}
		else
		{
			split_tables_list[x1].append(dxf_tables[x2]);
			x2++;
			split_tables_list[x1].append(dxf_tables[x2]);
		}
	}*/

	//clear_sw_header();

	Signal_log1.clear();
	Signal_log1.append("Splitting Classes ");
	Signal_log1.append(QString::number(classes_max_items));
	Signal_log1.append("\n");
	Signal_log1.append("X1 : ");
	Signal_log1.append(QString::number(x1));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	max=0;
	Record_Count_Tables=1;

	//clear_dxf_code_tables();

	ui->dxf_section->clear();
	ui->dxf_section->insert("Section Classes");

	emit send_text("dxf_classes");
	emit send_min(0);
	emit send_max(classes_max_items-1);

	text1=QString::number(classes_max_items);
	ui->dxf_section_count->clear();
	ui->dxf_section_count->insert(text1);


	while (count_tables< classes_max_items)
	{
		/*text1=QString::number(count_tables);
		ui->dxf_section_count->clear();
		ui->dxf_section_count->insert(text1);
		ui->dxf_log->repaint();*/

		count_tables_item=0;
		x3=split_tables_list[count_tables].count();

		if (x3>DXF_codeset_copies)
		{

			Signal_log1.clear();
			Signal_log1.append("============================================================================\n");
			Signal_log1.append("Splitting tables  : out of range subitems acad command \n");
			Signal_log1.append(QString::number(x3));
			Signal_log1.append(" > ");
			Signal_log1.append(QString::number(DXF_codeset_copies));
			Signal_log1.append("\n");
			Signal_log1.append("============================================================================");

			emit send_log(Signal_log1);


		}

		clear_dxf_code_tables();

		emit send_actual(count_tables);

		max=DB_Split_list("dxf_classes", x3, count_tables_item, count_tables, id_header  );

		//Record_Count_Tables++;

		//Record_Count_Tables=Record_Count_Tables+count_tables;

		Record_Count_Tables= mydb.DB_dbManager_added_records(Filename_db, &max,&Record_Count_Tables,"dxf_classes");

		sw_header[0]=0;
		sw_header[9]=0;

		id_header++;

		count_tables++;

		//Record_Count_Tables++;


	}


	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("end ");
	emit send_log(Signal_log1);

	mydb.dbManager_close(Filename_db);

	return;
}


void DXFtoQET3DB::split_tables()
{

	tables_max_items=dxf_tables.count("  0");
	tables_max_items=tables_max_items+dxf_tables.count(" 0");
	tables_max_items=tables_max_items+dxf_tables.count("0");

	tables_max_count=dxf_tables.count();

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("tables items : ");
	Signal_log1.append(QString::number(tables_max_items));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	count_tables=0;
	count_tables_record_id=1;
	count_tables_lines=0;
	id_header=1;

	clear_dxf_tables_items();
	clear_split_tables();

	x1=-1;


	for (x2=0;x2<tables_max_count and tables_max_items<DXF_item_split;x2++)
	{

		if (QString(dxf_tables[x2]).toInt()==0)
		{
			x1=x1+1;
			split_tables_list[x1].append(dxf_tables[x2]);
			x2++;
			split_tables_list[x1].append(dxf_tables[x2]);
		}
		else
		{
			split_tables_list[x1].append(dxf_tables[x2]);
			x2++;
			split_tables_list[x1].append(dxf_tables[x2]);
		}
	}

	clear_sw_header();

	Signal_log1.clear();
	Signal_log1.append("Splitting tables ");
	Signal_log1.append(QString::number(tables_max_items));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	max=0;
	Record_Count_Tables=1;

	clear_dxf_code_tables();

	ui->dxf_section->clear();
	ui->dxf_section->insert("Section Tables");

	emit send_text("dxf_tables");
	emit send_min(0);
	emit send_max(tables_max_items-1);

	text1=QString::number(tables_max_items);
	ui->dxf_section_count->clear();
	ui->dxf_section_count->insert(text1);


	while (count_tables< tables_max_items)			
	{
		/*text1=QString::number(count_tables);
		ui->dxf_section_count->clear();
		ui->dxf_section_count->insert(text1);
		ui->dxf_log->repaint();*/

		count_tables_item=0;

		//Record_Count_Tables=1;

		x3=split_tables_list[count_tables].count();

		if (x3>DXF_codeset_copies)
		{

			Signal_log1.clear();
			Signal_log1.append("============================================================================\n");
			Signal_log1.append("Splitting tables  : out of range subitems acad command \n");
			Signal_log1.append(QString::number(x3));
			Signal_log1.append(" > ");
			Signal_log1.append(QString::number(DXF_codeset_copies));
			Signal_log1.append("\n");
			Signal_log1.append("============================================================================");

			emit send_log(Signal_log1);


		}

		clear_dxf_code_tables();

		emit send_actual(count_tables);

		max=Split_list("dxf_tables", x3, count_tables_item, count_tables, id_header  );

		//Record_Count_Tables++;

		//Record_Count_Tables=Record_Count_Tables+count_tables;

		Record_Count_Tables= mydb.dbManager_added_records(Filename_db, &max,&Record_Count_Tables,"dxf_tables");

		sw_header[0]=0;
		sw_header[9]=0;

		id_header++;

		count_tables++;

		//Record_Count_Tables++;


	}


	return;
}

void DXFtoQET3DB::db_split_tables()
{

	mydb.dbManager1(Filename_db);

	//QsqlString="create table dxf_file (Index_count primary key, Code, Waarde, Section, Commando )";

	QSqlQuery Tables_Query;

	Tables_Query.prepare("SELECT * FROM dxf_file WHERE section =(:Section)");
	Tables_Query.bindValue(":Section","TABLES");

	Tables_Query.exec();

	tables_max_items=dxf_tables.count("  0");
	tables_max_items=tables_max_items+dxf_tables.count(" 0");
	tables_max_items=tables_max_items+dxf_tables.count("0");


	tables_max_count=dxf_tables.count();

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("tables items : ");
	Signal_log1.append(QString::number(entities_max_items));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);



	count_tables=0;
	count_tables_record_id=1;
	count_tables_lines=0;
	id_header=1;

	//clear_dxf_tables_items();
	clear_split_tables();

	x1=-1;

	while (Tables_Query.next())
	{
		QSqlRecord Header_record=Tables_Query.record();

		Read_Index=Header_record.value("Index_count").toString();
		Read_Code=Header_record.value("Code").toString();
		Read_Waarde=Header_record.value("Waarde").toString();
		Read_Section=Header_record.value("Section").toString();
		Read_Commando=Header_record.value("Commando").toString();
		Read_AcadValue=Header_record.value("AcadValue").toString();

		if ((Header_record.value("Code").toInt()==0) and (x1<DXF_item_split))
		{
			x1++;
			split_tables_list[x1].append(Header_record.value("Code").toString() );

			split_tables_list[x1].append(Header_record.value("Waarde").toString() );
		}
		else
		{
			split_tables_list[x1].append(Header_record.value("Code").toString() );

			split_tables_list[x1].append(Header_record.value("Waarde").toString() );
		}


		if (x1 > DXF_item_split)
		{
			Signal_log1.clear();
			Signal_log1.append(QTime::currentTime().toString());
			Signal_log1.append("\n");
			Signal_log1.append("split table to short : ");
			Signal_log1.append(QString::number(x1));
			Signal_log1.append(" > ");
			Signal_log1.append(QString::number(DXF_item_split));
			//Signal_log1.append("============================================================================");

			emit send_log(Signal_log1);
		}

	}

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("end split table ");

	//Signal_log1.append(QString::number(tables_max_items));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	/*for (x2=0;x2<tables_max_count and tables_max_items<DXF_item_split;x2++)
	{

		if (QString(dxf_tables[x2]).toInt()==0)
		{
			x1=x1+1;
			split_tables_list[x1].append(dxf_tables[x2]);
			x2++;
			split_tables_list[x1].append(dxf_tables[x2]);
		}
		else
		{
			split_tables_list[x1].append(dxf_tables[x2]);
			x2++;
			split_tables_list[x1].append(dxf_tables[x2]);
		}
	}*/

	//clear_sw_header();

	Signal_log1.clear();
	Signal_log1.append("Splitting tables ");
	Signal_log1.append(QString::number(entities_max_items));
	Signal_log1.append("\n");
	Signal_log1.append("X1 : ");
	Signal_log1.append(QString::number(x1));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	max=0;
	Record_Count_Tables=1;

	//clear_dxf_code_tables();

	ui->dxf_section->clear();
	ui->dxf_section->insert("Section Tables");

	emit send_text("dxf_tables");
	emit send_min(0);
	emit send_max(tables_max_items-1);

	text1=QString::number(tables_max_items);
	ui->dxf_section_count->clear();
	ui->dxf_section_count->insert(text1);


	while (count_tables< tables_max_items)
	{
		/*text1=QString::number(count_tables);
		ui->dxf_section_count->clear();
		ui->dxf_section_count->insert(text1);
		ui->dxf_log->repaint();*/

		count_tables_item=0;

		//Record_Count_Tables=1;

		x3=split_tables_list[count_tables].count();

		if (x3>DXF_codeset_copies)
		{

			Signal_log1.clear();
			Signal_log1.append("============================================================================\n");
			Signal_log1.append("Splitting tables  : out of range subitems acad command \n");
			Signal_log1.append(QString::number(x3));
			Signal_log1.append(" > ");
			Signal_log1.append(QString::number(DXF_codeset_copies));
			Signal_log1.append("\n");
			Signal_log1.append("============================================================================");

			emit send_log(Signal_log1);


		}

		clear_dxf_code_tables();

		emit send_actual(count_tables);

		max=DB_Split_list("dxf_tables", x3, count_tables_item, count_tables, id_header  );

		//Record_Count_Tables++;

		//Record_Count_Tables=Record_Count_Tables+count_tables;

		Record_Count_Tables= mydb.DB_dbManager_added_records(Filename_db, &max,&Record_Count_Tables,"dxf_tables");

		sw_header[0]=0;
		sw_header[9]=0;

		id_header++;

		count_tables++;

		//Record_Count_Tables++;


	}


	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("end ");
	emit send_log(Signal_log1);

	mydb.dbManager_close(Filename_db);

	return;
}

void DXFtoQET3DB::split_blocks()
{
	blocks_max_items=dxf_blocks.count("  0");
	blocks_max_items2=dxf_blocks.count(" 0");
	blocks_max_items3=dxf_blocks.count("0");

	blocks_max_items=blocks_max_items+blocks_max_items2+blocks_max_items3;

	blocks_max_count=dxf_blocks.count();

	Signal_log1.clear();
	Signal_log1.append("blocks items : ");
	Signal_log1.append(QString::number(blocks_max_items));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	count_blocks=0;
	count_blocks_record_id=1;
	count_blocks_lines=0;
	id_header=1;

	clear_dxf_blocks_items();
	clear_split_tables();

	x1=-1;

	for (x2=0;x2<blocks_max_count and blocks_max_items<DXF_item_split;x2++)
	{

		if (QString(dxf_blocks[x2]).toInt()==0)
		{
			x1=x1+1;
			split_tables_list[x1].append(dxf_blocks[x2]);
			x2++;
			split_tables_list[x1].append(dxf_blocks[x2]);
		}
		else
		{
			split_tables_list[x1].append(dxf_blocks[x2]);
			x2++;
			split_tables_list[x1].append(dxf_blocks[x2]);
		}
	}

	clear_sw_header();

	Signal_log1.clear();
	Signal_log1.append("Splitting BLOCKS ");

	emit send_log(Signal_log1);

	max=0;
	Record_Count_Blocks=1;


	clear_dxf_code_tables();

	ui->dxf_section->clear();
	ui->dxf_section->insert("Section Blocks");

	emit send_text("dxf_blocks");
	emit send_min(0);
	emit send_max(blocks_max_items-1);

	text1=QString::number(blocks_max_items);
	ui->dxf_section_count->clear();
	ui->dxf_section_count->insert(text1);


	while (count_blocks< blocks_max_items)
	{
		/*text1=QString::number(count_blocks);
		ui->dxf_section_count->clear();
		ui->dxf_section_count->insert(text1);
		ui->dxf_log->repaint();*/

		count_blocks_item=0;
		x3=split_tables_list[count_blocks].count();

		if (x3>DXF_codeset_copies)
		{
			Signal_log1.clear();
			Signal_log1.append("============================================================================\n");
			Signal_log1.append("Splitting blocks : out of range subitems acad command \n");
			Signal_log1.append(QString::number(x3));
			Signal_log1.append(" > ");
			Signal_log1.append(QString::number(DXF_codeset_copies));
			Signal_log1.append("\n");
			Signal_log1.append("============================================================================");

			emit send_log(Signal_log1);

		}

		clear_dxf_code_tables();

		emit send_actual(count_blocks);



		max=Split_list("dxf_blocks", x3, count_blocks_item, count_blocks , id_header );

		if (split_tables_list[count_blocks].count()==0)
		{
		}
		else
		{
			if (split_tables_list[count_blocks][1]=="BLOCK")
			{

				for (x3x=0;x3x<x3-1;x3x++)
				{

					x3value=split_tables_list[count_blocks][x3x];

					if (x3value.toInt()==2)
					{

						mydb.BlockNaamID=split_tables_list[count_blocks][x3x+1];
						x3x=x3+5;
					}

				}

			}
		}

		Record_Count_Blocks= mydb.dbManager_added_records(Filename_db, &max,&Record_Count_Blocks,"dxf_blocks");

		sw_header[0]=0;
		sw_header[9]=0;

		id_header++;

		count_blocks++;


	}



	return;
}

void DXFtoQET3DB::db_split_blocks()
{

	mydb.dbManager1(Filename_db);

	//QsqlString="create table dxf_file (Index_count primary key, Code, Waarde, Section, Commando )";

	QSqlQuery Tables_Query;

	Tables_Query.prepare("SELECT * FROM dxf_file WHERE section =(:Section)");
	Tables_Query.bindValue(":Section","BLOCKS");

	Tables_Query.exec();

	blocks_max_items=dxf_tables.count("  0");
	blocks_max_items=blocks_max_items+dxf_blocks.count(" 0");
	tables_max_items=blocks_max_items+dxf_blocks.count("0");


	blocks_max_count=dxf_blocks.count();

	Signal_log1.clear();
	Signal_log1.append("============================================================================");
	Signal_log1.append("\n");
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append(" - blocks items : ");
	Signal_log1.append(QString::number(blocks_max_items));

	emit send_log(Signal_log1);



	count_tables=0;
	count_tables_record_id=1;
	count_tables_lines=0;
	id_header=1;

	//clear_dxf_tables_items();
	clear_split_tables();

	emit send_min(0);
	emit send_max(tables_max_items);

	x1=-1;

	while ((Tables_Query.next()) and (x1<DXF_item_split))
	{
		QSqlRecord Header_record=Tables_Query.record();

		//emit send_actual(x1);

		Read_Index=Header_record.value("Index_count").toString();
		Read_Code=Header_record.value("Code").toString();
		Read_Waarde=Header_record.value("Waarde").toString();
		Read_Section=Header_record.value("Section").toString();
		Read_Commando=Header_record.value("Commando").toString();
		Read_AcadValue=Header_record.value("AcadValue").toString();

		if ((Header_record.value("Code").toInt()==0) and (x1<DXF_item_split))
		{
			x1++;
			emit send_actual(x1);
			split_tables_list[x1].append(Header_record.value("Code").toString() );

			split_tables_list[x1].append(Header_record.value("Waarde").toString() );
		}
		else
		{
			split_tables_list[x1].append(Header_record.value("Code").toString() );

			split_tables_list[x1].append(Header_record.value("Waarde").toString() );
		}

	}

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append(" - end split table ");
	Signal_log1.append(QString::number(x1));
	Signal_log1.append("\n");

	emit send_log(Signal_log1);

	/*for (x2=0;x2<tables_max_count and tables_max_items<DXF_item_split;x2++)
	{

		if (QString(dxf_tables[x2]).toInt()==0)
		{
			x1=x1+1;
			split_tables_list[x1].append(dxf_tables[x2]);
			x2++;
			split_tables_list[x1].append(dxf_tables[x2]);
		}
		else
		{
			split_tables_list[x1].append(dxf_tables[x2]);
			x2++;
			split_tables_list[x1].append(dxf_tables[x2]);
		}
	}*/

	//clear_sw_header();

	Signal_log1.clear();
	Signal_log1.append("Splitting tables ");
	Signal_log1.append(QString::number(blocks_max_items));
	Signal_log1.append(" - X1 : ");
	Signal_log1.append(QString::number(x1));
	Signal_log1.append("\n");

	emit send_log(Signal_log1);

	max=0;
	Record_Count_Tables=1;

	//clear_dxf_code_tables();

	ui->dxf_section->clear();
	ui->dxf_section->insert("Section Blocks Split");

	emit send_text("dxf_blocks");
	emit send_min(0);
	emit send_max(x1-1);

	text1=QString::number(blocks_max_items);
	ui->dxf_section_count->clear();
	ui->dxf_section_count->insert(text1);

	while (count_tables<= x1)
	//while (count_tables< blocks_max_items)
	{
		/*text1=QString::number(count_tables);
		ui->dxf_section_count->clear();
		ui->dxf_section_count->insert(text1);
		ui->dxf_log->repaint();*/

		count_tables_item=0;

		//Record_Count_Tables=1;

		x3=split_tables_list[count_tables].count();

		if (x3>DXF_codeset_copies)
		{

			Signal_log1.clear();
			Signal_log1.append("============================================================================\n");
			Signal_log1.append("Splitting tables  : out of range subitems acad command \n");
			Signal_log1.append(QString::number(x3));
			Signal_log1.append(" > ");
			Signal_log1.append(QString::number(DXF_codeset_copies));
			Signal_log1.append("\n");
			Signal_log1.append("============================================================================");

			emit send_log(Signal_log1);


		}

		clear_dxf_code_tables();

		emit send_actual(count_tables);

		max=DB_Split_list("dxf_blocks", x3, count_tables_item, count_tables, id_header  );

		//Record_Count_Tables++;

		//Record_Count_Tables=Record_Count_Tables+count_tables;

		Record_Count_Tables= mydb.DB_dbManager_added_records(Filename_db, &max,&Record_Count_Tables,"dxf_blocks");

		sw_header[0]=0;
		sw_header[9]=0;

		id_header++;

		count_tables++;

		//Record_Count_Tables++;


	}


	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("end ");
	emit send_log(Signal_log1);

	mydb.dbManager_close(Filename_db);

	return;
}

void DXFtoQET3DB::split_entities()
{
	entities_max_items=dxf_entities.count("  0");
	entities_max_items2=dxf_entities.count("  0");
	entities_max_items3=dxf_entities.count("  0");

	entities_max_items=entities_max_items+entities_max_items2+entities_max_items3;

	entities_max_count=dxf_entities.count();

	Signal_log1.clear();
	Signal_log1.append("entities items : ");
	Signal_log1.append(QString::number(entities_max_items));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);


	count_entities=0;
	count_entities_record_id=1;
	count_entities_lines=0;
	id_header=1;

	clear_dxf_entities_items();
	clear_split_tables();

	x1=-1;

	for (x2=0;x2<entities_max_count and entities_max_items<DXF_item_split;x2++)
	{

		if (QString( dxf_entities[x2]).toInt()==0)
		{
			x1=x1+1;
			split_tables_list[x1].append(dxf_entities[x2]);
			x2++;
			split_tables_list[x1].append(dxf_entities[x2]);
		}
		else
		{
			split_tables_list[x1].append(dxf_entities[x2]);
			x2++;
			split_tables_list[x1].append(dxf_entities[x2]);
		}
	}

	clear_sw_header();

	Signal_log1.clear();
	Signal_log1.append("Splitting ENTITIES ");

	emit send_log(Signal_log1);


	max=0;
	Record_Count_Entities=1;

	clear_dxf_code_tables();

	Signal_log1.clear();
	Signal_log1.append("Splitting ENTITIES ");

	emit send_log(Signal_log1);

	count_entities=0;

	ui->dxf_section->clear();
	ui->dxf_section->insert("Section Entities");


	emit send_text("dxf_entities");
	emit send_min(0);
	emit send_max(entities_max_items-1);


	text1=QString::number(entities_max_items);
	ui->dxf_section_count->clear();
	ui->dxf_section_count->insert(text1);


	while (count_entities< entities_max_items)
	{
		/*text1=QString::number(count_entities);
		ui->dxf_section_count->clear();
		ui->dxf_section_count->insert(text1);
		ui->dxf_log->repaint();*/

		count_entities_item=0;

		//Record_Count_Tables=1;

		x3=split_tables_list[count_entities].count();

		if (x3>DXF_codeset_copies)
		{
			Signal_log1.clear();
			Signal_log1.append("============================================================================\n");
			Signal_log1.append("Splitting entities  : out of range subitems acad command \n");
			Signal_log1.append(QString::number(x3));
			Signal_log1.append(" > ");
			Signal_log1.append(QString::number(DXF_codeset_copies));
			Signal_log1.append("\n");
			Signal_log1.append("============================================================================");

			emit send_log(Signal_log1);

		}

		clear_dxf_code_tables();

		emit send_actual(count_entities);

		max=Split_list("dxf_entities", x3, count_entities_item, count_entities, id_header  );


		Record_Count_Entities= mydb.dbManager_added_records(Filename_db, &max,&Record_Count_Entities,"dxf_entities");

		sw_header[0]=0;
		sw_header[9]=0;

		id_header++;

		count_entities++;



	}



	return;
}

void DXFtoQET3DB::db_split_entities()
{

	mydb.dbManager1(Filename_db);

	//QsqlString="create table dxf_file (Index_count primary key, Code, Waarde, Section, Commando )";

	QSqlQuery Tables_Query;

	Tables_Query.prepare("SELECT * FROM dxf_file WHERE section =(:Section)");
	Tables_Query.bindValue(":Section","ENTITIES");

	Tables_Query.exec();

	entities_max_items=dxf_entities.count("  0");
	entities_max_items=entities_max_items+dxf_entities.count(" 0");
	entities_max_items=entities_max_items+dxf_entities.count("0");


	tables_max_count=dxf_entities.count();

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("entities items : ");
	Signal_log1.append(QString::number(entities_max_items));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);



	count_tables=0;
	count_tables_record_id=1;
	count_tables_lines=0;
	id_header=1;

	//clear_dxf_tables_items();
	clear_split_tables();

	x1=-1;

	while (Tables_Query.next())
	{
		QSqlRecord Header_record=Tables_Query.record();

		Read_Index=Header_record.value("Index_count").toString();
		Read_Code=Header_record.value("Code").toString();
		Read_Waarde=Header_record.value("Waarde").toString();
		Read_Section=Header_record.value("Section").toString();
		Read_Commando=Header_record.value("Cmmando").toString();
		Read_AcadValue=Header_record.value("AcadValue").toString();


		if ((Header_record.value("Code").toInt()==0) and (x1<DXF_item_split))
		{
			x1++;
			split_tables_list[x1].append(Header_record.value("Code").toString() );

			split_tables_list[x1].append(Header_record.value("Waarde").toString() );
		}
		else
		{
			split_tables_list[x1].append(Header_record.value("Code").toString() );

			split_tables_list[x1].append(Header_record.value("Waarde").toString() );
		}

	}

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("end split table ");

	//Signal_log1.append(QString::number(tables_max_items));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	/*for (x2=0;x2<tables_max_count and tables_max_items<DXF_item_split;x2++)
	{

		if (QString(dxf_tables[x2]).toInt()==0)
		{
			x1=x1+1;
			split_tables_list[x1].append(dxf_tables[x2]);
			x2++;
			split_tables_list[x1].append(dxf_tables[x2]);
		}
		else
		{
			split_tables_list[x1].append(dxf_tables[x2]);
			x2++;
			split_tables_list[x1].append(dxf_tables[x2]);
		}
	}*/

	//clear_sw_header();

	Signal_log1.clear();
	Signal_log1.append("Splitting entities ");
	Signal_log1.append(QString::number(entities_max_items));
	Signal_log1.append("\n");
	Signal_log1.append("X1 : ");
	Signal_log1.append(QString::number(x1));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	max=0;
	Record_Count_Tables=1;

	//clear_dxf_code_tables();

	ui->dxf_section->clear();
	ui->dxf_section->insert("Section entities");

	emit send_text("dxf_entities");
	emit send_min(0);
	emit send_max(entities_max_items-1);

	text1=QString::number(entities_max_items);
	ui->dxf_section_count->clear();
	ui->dxf_section_count->insert(text1);


	while (count_tables< entities_max_items)
	{
		/*text1=QString::number(count_tables);
		ui->dxf_section_count->clear();
		ui->dxf_section_count->insert(text1);
		ui->dxf_log->repaint();*/

		count_tables_item=0;

		//Record_Count_Tables=1;

		x3=split_tables_list[count_tables].count();

		if (x3>DXF_codeset_copies)
		{

			Signal_log1.clear();
			Signal_log1.append("============================================================================\n");
			Signal_log1.append("Splitting tables  : out of range subitems acad command \n");
			Signal_log1.append(QString::number(x3));
			Signal_log1.append(" > ");
			Signal_log1.append(QString::number(DXF_codeset_copies));
			Signal_log1.append("\n");
			Signal_log1.append("============================================================================");

			emit send_log(Signal_log1);


		}

		clear_dxf_code_tables();

		emit send_actual(count_tables);

		max=DB_Split_list("dxf_entities", x3, count_tables_item, count_tables, id_header  );

		//Record_Count_Tables++;

		//Record_Count_Tables=Record_Count_Tables+count_tables;

		Record_Count_Tables= mydb.DB_dbManager_added_records(Filename_db, &max,&Record_Count_Tables,"dxf_entities");

		sw_header[0]=0;
		sw_header[9]=0;

		id_header++;

		count_tables++;

		//Record_Count_Tables++;


	}


	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("end ");
	emit send_log(Signal_log1);

	mydb.dbManager_close(Filename_db);

	return;
}


void DXFtoQET3DB::split_objects()
{
	objects_max_items=dxf_objects.count("  0");
	if (objects_max_items==0)
	{
		objects_max_items=dxf_objects.count(" 0");
	}
	if (objects_max_items==0)
	{
		objects_max_items=dxf_objects.count("0");
	}

	objects_max_count=dxf_objects.count();

	Signal_log1.clear();
	Signal_log1.append("objects items : ");
	Signal_log1.append(QString::number(entities_max_items));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	count_objects=0;
	count_objects_record_id=1;
	count_objects_lines=0;


	count_objects=0;
	count_objects_record_id=1;
	count_objects_lines=0;
	id_header=1;

	clear_dxf_tables_items();
	clear_split_tables();

	x1=-1;

	for (x2=0;x2<objects_max_count and objects_max_items<DXF_item_split;x2++)
	{

		if ( (QString( dxf_objects[x2]).toInt()==0) and (x1<DXF_item_split))
		{
			x1=x1+1;
			split_tables_list[x1].append(dxf_objects[x2]);
			x2++;
			split_tables_list[x1].append(dxf_objects[x2]);
		}
		else
		{
			split_tables_list[x1].append(dxf_objects[x2]);
			x2++;
			split_tables_list[x1].append(dxf_objects[x2]);
		}
	}

	clear_sw_header();

	Signal_log1.clear();
	Signal_log1.append("Splitting OBJECTS ");

	emit send_log(Signal_log1);



	max=0;
	Record_Count_Objects=1;


	clear_dxf_code_tables();

	ui->dxf_section->clear();
	ui->dxf_section->insert("Section Objects");

	emit send_text("dxf_entities");
	emit send_min(0);
	emit send_max(objects_max_items-1);


	text1=QString::number(objects_max_items);
	ui->dxf_section_count->clear();
	ui->dxf_section_count->insert(text1);


	while (count_objects< objects_max_items)
	{
		/*text1=QString::number(count_objects);
		ui->dxf_section_count->clear();
		ui->dxf_section_count->insert(text1);
		ui->dxf_log->repaint();*/

		count_object_item=0;

		//Record_Count_Tables=1;

		x3=split_tables_list[count_objects].count();

		if (x3>DXF_codeset_copies)
		{
			Signal_log1.clear();
			Signal_log1.append("============================================================================\n");
			Signal_log1.append("Splitting objects : out of range subitems acad command \n");
			Signal_log1.append(QString::number(x3));
			Signal_log1.append(" > ");
			Signal_log1.append(QString::number(DXF_codeset_copies));
			Signal_log1.append("\n");
			Signal_log1.append("============================================================================");

			emit send_log(Signal_log1);



		}

		clear_dxf_code_tables();

		emit send_actual(count_objects);


		max=Split_list("dxf_objects", x3, count_object_item, count_objects, id_header  );

		//Record_Count_Tables=Record_Count_Tables+count_objects;

		Record_Count_Objects= mydb.dbManager_added_records(Filename_db, &max,&Record_Count_Objects,"dxf_objects");

		sw_header[0]=0;
		sw_header[9]=0;

		id_header++;

		count_objects++;

		//Record_Count_Tables++;

	}



	return;
}

void DXFtoQET3DB::split_thumbnailimage()
{
	thumbnailimage_max_items=dxf_thumbnailimage.count("  0");
	count_thumbnailimage=0;
	count_thumbnailimage_record_id=1;
	count_thumbnailimage_lines=0;


	Signal_log1.clear();
	Signal_log1.append("thumbnailimage items : ");
	Signal_log1.append(QString::number(entities_max_items));
	//Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);


	while (count_thumbnailimage< dxf_thumbnailimage.count())
	{



		line1=QString(dxf_thumbnailimage[count_thumbnailimage]).toInt();
		line2=(dxf_thumbnailimage[count_thumbnailimage+1]);
		switch (line1)
		{
			case 0:

			break;

			case 9:


			break;

			default:

				ui->dxf_log->insertPlainText("Found code : ");
				ui->dxf_log->insertPlainText(dxf_thumbnailimage[count_thumbnailimage]);
				ui->dxf_log->insertPlainText(" | ");
				ui->dxf_log->insertPlainText(dxf_thumbnailimage[count_thumbnailimage+1]);
				ui->dxf_log->insertPlainText("\n");

				ui->dxf_log->moveCursor(QTextCursor::End);
				ui->dxf_log->repaint();
		}

		count_thumbnailimage=count_thumbnailimage+2;



		//count_thumbnailimage=count_thumbnailimage+count_thumbnailimage_lines;

	}


	ui->dxf_log->insertPlainText("============================================================================\n");
	ui->dxf_log->moveCursor(QTextCursor::End);
	ui->dxf_log->repaint();

	return;

}

void DXFtoQET3DB::clear_sw_header()
{

	for (x4=0; x4<=1072;x4++)
	{
		sw_header[x4]=0;
	}

}

void DXFtoQET3DB::clear_dxf_header_items()
{

	for (xclear=0;xclear<DXF_item_split;xclear++)
	{
		dxf_header_items[xclear].clear();
	}
}

void DXFtoQET3DB::clear_dxf_classes_items()
{

	for (xclear=0;xclear<DXF_item_split;xclear++)
	{
		dxf_classes_items[xclear].clear();
	}
}

void DXFtoQET3DB::clear_dxf_tables_items()
{

	for (xclear=0;xclear<DXF_item_split;xclear++)
	{
		dxf_tables_items[xclear].clear();
	}
}

void DXFtoQET3DB::clear_dxf_blocks_items()
{

	for (xclear=0;xclear<DXF_item_split;xclear++)
	{
		dxf_blocks_items[xclear].clear();
	}
}

void DXFtoQET3DB::clear_dxf_entities_items()
{

	for (xclear=0;xclear<DXF_item_split;xclear++)
	{
		dxf_entities_items[xclear].clear();
	}
}

void DXFtoQET3DB::clear_dxf_objects_items()
{

	for (xclear=0;xclear<DXF_item_split;xclear++)
	{
		dxf_objects_items[xclear].clear();
	}
}

void DXFtoQET3DB::clear_dxf_thumbnailimage_items()
{

	for (xclear=0;xclear<DXF_item_split;xclear++)
	{
		dxf_thumbnailimage_items[xclear].clear();
	}
}

void DXFtoQET3DB::clear_dxf_code_tables()
{

	for (clear_code_set=0;clear_code_set<DXF_codes_set;clear_code_set++)
	{
		//for (int clear2=0;clear2<DXF_codeset_copies;clear2++)
		//{
			DXF_code_tables[clear_code_set]=DXF_codes_tables_empty;
		//}
	}

	//memset(&myStruct, 0, sizeof(myStruct));

	//memset (&DXF_code_tables,0,sizeof(DXF_code_tables));
	//DXF_code_tables=DXF_codes_tables_empty;

}

int DXFtoQET3DB::Split_list(QString TypeList, int x3max, int count_list_item, int count_tables_list, int header_id)
{

	max3=0;
	clear_sw_header();




	while (count_list_item<x3max and count_list_item<DXF_codeset_copies)
	{

		line1=QString(split_tables_list[count_tables_list][count_list_item]).toInt();
		line2=split_tables_list[count_tables_list][count_list_item+1];


			switch (line1)
			{
				case 0:
					if (sw_header[0]==0)
					{

						DXF_code_tables[sw_header[0]].dxf_0=line2;

						DXF_code_tables[sw_header[0]].Section=TypeList;
						DXF_code_tables[sw_header[0]].Command=line2;

						DXF_code_tables[sw_header[0]].ID_instruction=QString::number(header_id);

						sw_header[0]++;

						if (sw_header[0]>max3)
						{
							max3=sw_header[0];
						}
					}

				break;

				case 1:
					if (sw_header[1]>=0)
					{

						DXF_code_tables[sw_header[1]].dxf_1=line2;
						sw_header[1]++;

						if (sw_header[1]>max3)
						{
							max3=sw_header[1];
						}
					}

				break;

				case 2:
					if (sw_header[2]>=0)
					{

						DXF_code_tables[sw_header[2]].dxf_2=line2;
						sw_header[2]++;

						if (sw_header[2]>max3)
						{
							max3=sw_header[2];
						}
					}

				break;

				case 3:
					if (sw_header[3]>=0)
					{

						DXF_code_tables[sw_header[3]].dxf_3=line2;
						sw_header[3]++;

						if (sw_header[3]>max3)
						{
							max3=sw_header[3];
						}
					}

				break;

				case 4:
					if (sw_header[4]>=0)
					{

						DXF_code_tables[sw_header[4]].dxf_4=line2;
						sw_header[4]++;

						if (sw_header[4]>max3)
						{
							max3=sw_header[4];
						}
					}

				break;

				case 5:
					if (sw_header[5]>=0)
					{

						DXF_code_tables[sw_header[5]].dxf_5=line2;
						sw_header[5]++;

						if (sw_header[5]>max3)
						{
							max3=sw_header[5];
						}
					}

				break;

				case 6:
					if (sw_header[6]>=0)
					{

						DXF_code_tables[sw_header[6]].dxf_6=line2;
						sw_header[6]++;

						if (sw_header[6]>max3)
						{
							max3=sw_header[6];
						}
					}

				break;

				case 7:
					if (sw_header[7]>=0)
					{

						DXF_code_tables[sw_header[7]].dxf_7=line2;
						sw_header[7]++;

						if (sw_header[7]>max3)
						{
							max3=sw_header[7];
						}
					}

				break;

				case 8:
					if (sw_header[8]>=0)
					{

						DXF_code_tables[sw_header[8]].dxf_8=line2;
						sw_header[8]++;

						if (sw_header[8]>max3)
						{
							max3=sw_header[8];
						}
					}

				break;

				case 9:
					if (sw_header[9]==0)
					{

						DXF_code_tables[sw_header[9]].dxf_9=line2;

						DXF_code_tables[sw_header[9]].Section=TypeList;
						DXF_code_tables[sw_header[9]].Command=line2;
						DXF_code_tables[sw_header[9]].ID_instruction=QString::number(header_id);
						//DXF_code_tables[sw_header[9]].ID_instruction=DXF_code_tables[sw_header[0]].dxf_5;

						sw_header[9]++;

						//Record_Count_Header++;

						if (sw_header[9]>max)
						{
							max=sw_header[9];
						}
					}

				break;

				case 10:
					if (sw_header[10]>=0)
					{

						DXF_code_tables[sw_header[10]].dxf_10=line2;
						sw_header[10]++;

						if (sw_header[10]>max3)
						{
							max3=sw_header[10];
						}
					}

				break;

				case 11:
					if (sw_header[11]>=0)
					{

						DXF_code_tables[sw_header[11]].dxf_11=line2;
						sw_header[11]++;

						if (sw_header[11]>max3)
						{
							max3=sw_header[11];
						}
					}

				break;

				case 12:
					if (sw_header[12]>=0)
					{

						DXF_code_tables[sw_header[12]].dxf_12=line2;
						sw_header[12]++;

						if (sw_header[12]>max3)
						{
							max3=sw_header[12];
						}
					}

				break;


				case 13:
					if (sw_header[13]>=0)
					{

						DXF_code_tables[sw_header[13]].dxf_13=line2;
						sw_header[13]++;

						if (sw_header[13]>max3)
						{
							max3=sw_header[13];
						}
					}

				break;


				case 14:
					if (sw_header[14]>=0)
					{

						DXF_code_tables[sw_header[14]].dxf_14=line2;
						sw_header[14]++;

						if (sw_header[14]>max3)
						{
							max3=sw_header[14];
						}
					}

				break;

				case 15:
					if (sw_header[15]>=0)
					{

						DXF_code_tables[sw_header[15]].dxf_15=line2;
						sw_header[15]++;

						if (sw_header[15]>max)
						{
							max=sw_header[15];
						}
					}

				break;

				case 16:
					if (sw_header[16]>=0)
					{

						DXF_code_tables[sw_header[16]].dxf_16=line2;
						sw_header[16]++;

						if (sw_header[16]>max3)
						{
							max3=sw_header[16];
						}
					}

				break;

				case 17:
					if (sw_header[17]>=0)
					{

						DXF_code_tables[sw_header[17]].dxf_17=line2;
						sw_header[17]++;

						if (sw_header[17]>max3)
						{
							max3=sw_header[17];
						}
					}

				break;

				case 20:
					if (sw_header[20]>=0)
					{

						DXF_code_tables[sw_header[20]].dxf_20=line2;
						sw_header[20]++;

						if (sw_header[20]>max3)
						{
							max3=sw_header[20];
						}
					}

				break;

				case 21:
					if (sw_header[21]>=0)
					{

						DXF_code_tables[sw_header[21]].dxf_21=line2;
						sw_header[21]++;

						if (sw_header[21]>max3)
						{
							max3=sw_header[21];
						}
					}

				break;

				case 22:
					if (sw_header[22]>=0)
					{

						DXF_code_tables[sw_header[22]].dxf_22=line2;
						sw_header[22]++;

						if (sw_header[22]>max3)
						{
							max3=sw_header[22];
						}
					}

				break;

				case 23:
					if (sw_header[23]>=0)
					{

						DXF_code_tables[sw_header[23]].dxf_23=line2;
						sw_header[23]++;

						if (sw_header[23]>max3)
						{
							max3=sw_header[23];
						}
					}

				break;

				case 24:
					if (sw_header[24]>=0)
					{

						DXF_code_tables[sw_header[24]].dxf_24=line2;
						sw_header[24]++;

						if (sw_header[24]>max3)
						{
							max3=sw_header[24];
						}
					}

				break;

				case 25:
					if (sw_header[25]>=0)
					{

						DXF_code_tables[sw_header[25]].dxf_25=line2;
						sw_header[25]++;

						if (sw_header[25]>max3)
						{
							max3=sw_header[25];
						}
					}

				break;


				case 26:
					if (sw_header[26]>=0)
					{

						DXF_code_tables[sw_header[26]].dxf_26=line2;
						sw_header[26]++;

						if (sw_header[26]>max3)
						{
							max3=sw_header[26];
						}
					}

				break;

				case 27:
					if (sw_header[27]>=0)
					{

						DXF_code_tables[sw_header[27]].dxf_27=line2;
						sw_header[27]++;

						if (sw_header[27]>max3)
						{
							max3=sw_header[27];
						}
					}

				break;

				case 28:
					if (sw_header[28]>=0)
					{

						DXF_code_tables[sw_header[28]].dxf_28=line2;
						sw_header[28]++;

						if (sw_header[28]>max3)
						{
							max3=sw_header[28];
						}
					}

				break;

				case 29:
					if (sw_header[29]>=0)
					{

						DXF_code_tables[sw_header[29]].dxf_29=line2;
						sw_header[29]++;

						if (sw_header[29]>max3)
						{
							max3=sw_header[29];
						}
					}

				break;



				case 30:
					if (sw_header[30]>=0)
					{

						DXF_code_tables[sw_header[30]].dxf_30=line2;
						sw_header[30]++;

						if (sw_header[30]>max3)
						{
							max3=sw_header[30];
						}
					}

				break;

				case 31:
					if (sw_header[31]>=0)
					{

						DXF_code_tables[sw_header[31]].dxf_31=line2;
						sw_header[31]++;

						if (sw_header[31]>max3)
						{
							max3=sw_header[31];
						}
					}

				break;

				case 32:
					if (sw_header[32]>=0)
					{

						DXF_code_tables[sw_header[32]].dxf_32=line2;
						sw_header[32]++;

						if (sw_header[32]>max3)
						{
							max3=sw_header[32];
						}
					}

				break;

				case 33:
					if (sw_header[33]>=0)
					{

						DXF_code_tables[sw_header[33]].dxf_33=line2;
						sw_header[33]++;

						if (sw_header[33]>max3)
						{
							max3=sw_header[33];
						}
					}

				break;

				case 34:
					if (sw_header[34]>=0)
					{

						DXF_code_tables[sw_header[34]].dxf_34=line2;
						sw_header[34]++;

						if (sw_header[34]>max3)
						{
							max3=sw_header[34];
						}
					}

				break;

				case 35:
					if (sw_header[35]>=0)
					{

						DXF_code_tables[sw_header[35]].dxf_35=line2;
						sw_header[35]++;

						if (sw_header[35]>max3)
						{
							max3=sw_header[35];
						}
					}

				break;

				case 36:
					if (sw_header[36]>=0)
					{

						DXF_code_tables[sw_header[36]].dxf_36=line2;
						sw_header[36]++;

						if (sw_header[36]>max3)
						{
							max3=sw_header[36];
						}
					}

				break;

				case 37:
					if (sw_header[37]>=0)
					{

						DXF_code_tables[sw_header[37]].dxf_37=line2;
						sw_header[37]++;

						if (sw_header[37]>max3)
						{
							max3=sw_header[37];
						}
					}

				break;

				case 38:
					if (sw_header[38]>=0)
					{

						DXF_code_tables[sw_header[38]].dxf_38=line2;
						sw_header[38]++;

						if (sw_header[38]>max3)
						{
							max3=sw_header[38];
						}
					}

				break;

				case 39:
					if (sw_header[39]>=0)
					{

						DXF_code_tables[sw_header[39]].dxf_39=line2;
						sw_header[39]++;

						if (sw_header[39]>max3)
						{
							max3=sw_header[39];
						}
					}

				break;


				case 40:
					if (sw_header[40]>=0)
					{

						DXF_code_tables[sw_header[40]].dxf_40=line2;
						sw_header[40]++;

						if (sw_header[40]>max3)
						{
							max3=sw_header[40];
						}
					}

				break;


				case 41:
					if (sw_header[41]>=0)
					{

						DXF_code_tables[sw_header[41]].dxf_41=line2;
						sw_header[41]++;

						if (sw_header[41]>max3)
						{
							max3=sw_header[41];
						}
					}

				break;


				case 42:
					if (sw_header[42]>=0)
					{

						DXF_code_tables[sw_header[42]].dxf_42=line2;
						sw_header[42]++;

						if (sw_header[42]>max3)
						{
							max3=sw_header[42];
						}
					}

				break;

				case 43:
					if (sw_header[43]>=0)
					{

						DXF_code_tables[sw_header[43]].dxf_43=line2;
						sw_header[43]++;

						if (sw_header[43]>max3)
						{
							max3=sw_header[43];
						}
					}

				break;

				case 44:
					if (sw_header[44]>=0)
					{

						DXF_code_tables[sw_header[44]].dxf_44=line2;
						sw_header[44]++;

						if (sw_header[44]>max3)
						{
							max3=sw_header[44];
						}
					}

				break;

				case 45:
					if (sw_header[45]>=0)
					{

						DXF_code_tables[sw_header[45]].dxf_45=line2;
						sw_header[45]++;

						if (sw_header[45]>max3)
						{
							max3=sw_header[45];
						}
					}

				break;

				case 46:
					if (sw_header[46]>=0)
					{

						DXF_code_tables[sw_header[46]].dxf_46=line2;
						sw_header[46]++;

						if (sw_header[46]>max3)
						{
							max3=sw_header[46];
						}
					}

				break;

				case 47:
					if (sw_header[47]>=0)
					{

						DXF_code_tables[sw_header[47]].dxf_47=line2;
						sw_header[47]++;

						if (sw_header[47]>max3)
						{
							max3=sw_header[47];
						}
					}

				break;

				case 48:
					if (sw_header[48]>=0)
					{

						DXF_code_tables[sw_header[48]].dxf_48=line2;
						sw_header[48]++;

						if (sw_header[48]>max3)
						{
							max3=sw_header[48];
						}
					}

				break;

				case 49:
					if (sw_header[49]>=0)
					{

						DXF_code_tables[sw_header[49]].dxf_49=line2;
						sw_header[49]++;

						if (sw_header[49]>max3)
						{
							max3=sw_header[49];
						}
					}

				break;

				case 50:
					if (sw_header[50]>=0)
					{

						DXF_code_tables[sw_header[50]].dxf_50=line2;
						sw_header[50]++;

						if (sw_header[50]>max3)
						{
							max3=sw_header[50];
						}
					}

				break;


				case 51:
					if (sw_header[51]>=0)
					{

						DXF_code_tables[sw_header[51]].dxf_51=line2;
						sw_header[51]++;

						if (sw_header[51]>max3)
						{
							max3=sw_header[51];
						}
					}

				break;

				case 52:
					if (sw_header[52]>=0)
					{

						DXF_code_tables[sw_header[52]].dxf_52=line2;
						sw_header[52]++;

						if (sw_header[52]>max3)
						{
							max3=sw_header[52];
						}
					}

				break;

				case 53:
					if (sw_header[53]>=0)
					{

						DXF_code_tables[sw_header[53]].dxf_53=line2;
						sw_header[53]++;

						if (sw_header[53]>max3)
						{
							max3=sw_header[53];
						}
					}

				break;

				case 60:
					if (sw_header[60]>=0)
					{

						DXF_code_tables[sw_header[60]].dxf_60=line2;
						sw_header[60]++;

						if (sw_header[60]>max3)
						{
							max3=sw_header[60];
						}
					}

				break;

				case 61:
					if (sw_header[61]>=0)
					{

						DXF_code_tables[sw_header[61]].dxf_61=line2;
						sw_header[61]++;

						if (sw_header[61]>max3)
						{
							max3=sw_header[61];
						}
					}

				break;

				case 62:
					if (sw_header[62]>=0)
					{

						DXF_code_tables[sw_header[62]].dxf_62=line2;
						sw_header[62]++;

						if (sw_header[62]>max3)
						{
							max3=sw_header[62];
						}
					}

				break;

				case 63:
					if (sw_header[63]>=0)
					{

						DXF_code_tables[sw_header[63]].dxf_63=line2;
						sw_header[63]++;

						if (sw_header[63]>max3)
						{
							max3=sw_header[63];
						}
					}

				break;

				case 64:
					if (sw_header[64]>=0)
					{

						DXF_code_tables[sw_header[64]].dxf_64=line2;
						sw_header[64]++;

						if (sw_header[64]>max3)
						{
							max3=sw_header[64];
						}
					}

				break;


				case 65:
					if (sw_header[65]>=0)
					{

						DXF_code_tables[sw_header[65]].dxf_65=line2;
						sw_header[65]++;

						if (sw_header[65]>max3)
						{
							max3=sw_header[65];
						}
					}

				break;

				case 66:
					if (sw_header[66]>=0)
					{

						DXF_code_tables[sw_header[66]].dxf_66=line2;
						sw_header[66]++;

						if (sw_header[66]>max3)
						{
							max3=sw_header[66];
						}
					}

				break;

				case 67:
					if (sw_header[67]>=0)
					{

						DXF_code_tables[sw_header[67]].dxf_67=line2;
						sw_header[67]++;

						if (sw_header[67]>max3)
						{
							max3=sw_header[67];
						}
					}

				break;

				case 68:
					if (sw_header[68]>=0)
					{

						DXF_code_tables[sw_header[68]].dxf_68=line2;
						sw_header[68]++;

						if (sw_header[68]>max3)
						{
							max3=sw_header[68];
						}
					}

				break;

				case 69:
					if (sw_header[69]>=0)
					{

						DXF_code_tables[sw_header[69]].dxf_69=line2;
						sw_header[69]++;

						if (sw_header[69]>max3)
						{
							max3=sw_header[69];
						}
					}

				break;

				case 70:
					if (sw_header[70]>=0)
					{

						DXF_code_tables[sw_header[70]].dxf_70=line2;
						sw_header[70]++;

						if (sw_header[70]>max3)
						{
							max3=sw_header[70];
						}
					}

				break;

				case 71:
					if (sw_header[71]>=0)
					{

						DXF_code_tables[sw_header[71]].dxf_71=line2;
						sw_header[71]++;

						if (sw_header[71]>max3)
						{
							max3=sw_header[71];
						}
					}

				break;

				case 72:
					if (sw_header[72]>=0)
					{

						DXF_code_tables[sw_header[72]].dxf_72=line2;
						sw_header[72]++;

						if (sw_header[72]>max3)
						{
							max3=sw_header[72];
						}
					}

				break;

				case 73:
					if (sw_header[73]>=0)
					{

						DXF_code_tables[sw_header[73]].dxf_73=line2;
						sw_header[73]++;

						if (sw_header[73]>max3)
						{
							max3=sw_header[73];
						}
					}

				break;

				case 74:
					if (sw_header[74]>=0)
					{

						DXF_code_tables[sw_header[74]].dxf_74=line2;
						sw_header[74]++;

						if (sw_header[74]>max3)
						{
							max3=sw_header[74];
						}
					}

				break;

				case 75:
					if (sw_header[75]>=0)
					{

						DXF_code_tables[sw_header[75]].dxf_75=line2;
						sw_header[75]++;

						if (sw_header[75]>max3)
						{
							max3=sw_header[75];
						}
					}

				break;

				case 76:
					if (sw_header[76]>=0)
					{

						DXF_code_tables[sw_header[76]].dxf_76=line2;
						sw_header[76]++;

						if (sw_header[76]>max3)
						{
							max3=sw_header[76];
						}
					}

				break;

				case 77:
					if (sw_header[77]>=0)
					{

						DXF_code_tables[sw_header[77]].dxf_77=line2;
						sw_header[77]++;

						if (sw_header[77]>max3)
						{
							max3=sw_header[77];
						}
					}

				break;

				case 78:
					if (sw_header[78]>=0)
					{

						DXF_code_tables[sw_header[78]].dxf_78=line2;
						sw_header[78]++;

						if (sw_header[78]>max3)
						{
							max3=sw_header[78];
						}
					}

				break;

				case 79:
					if (sw_header[79]>=0)
					{

						DXF_code_tables[sw_header[79]].dxf_79=line2;
						sw_header[79]++;

						if (sw_header[79]>max3)
						{
							max3=sw_header[79];
						}
					}

				break;

				case 90:
					if (sw_header[90]>=0)
					{

						DXF_code_tables[sw_header[90]].dxf_90=line2;
						sw_header[90]++;

						if (sw_header[90]>max3)
						{
							max3=sw_header[90];
						}
					}

				break;


				case 91:
					if (sw_header[91]>=0)
					{

						DXF_code_tables[sw_header[91]].dxf_91=line2;
						sw_header[91]++;

						if (sw_header[91]>max3)
						{
							max3=sw_header[91];
						}
					}

				break;


				case 92:
					if (sw_header[92]>=0)
					{

						DXF_code_tables[sw_header[92]].dxf_92=line2;
						sw_header[92]++;

						if (sw_header[92]>max3)
						{
							max3=sw_header[92];
						}
					}

				break;

				case 93:
					if (sw_header[93]>=0)
					{

						DXF_code_tables[sw_header[93]].dxf_93=line2;
						sw_header[93]++;

						if (sw_header[93]>max3)
						{
							max3=sw_header[93];
						}
					}

				break;

				case 94:
					if (sw_header[94]>=0)
					{

						DXF_code_tables[sw_header[94]].dxf_94=line2;
						sw_header[94]++;

						if (sw_header[94]>max3)
						{
							max3=sw_header[94];
						}
					}

				break;

				case 95:
					if (sw_header[95]>=0)
					{

						DXF_code_tables[sw_header[95]].dxf_95=line2;
						sw_header[95]++;

						if (sw_header[95]>max3)
						{
							max3=sw_header[95];
						}
					}

				break;

				case 96:
					if (sw_header[96]>=0)
					{

						DXF_code_tables[sw_header[96]].dxf_96=line2;
						sw_header[96]++;

						if (sw_header[96]>max3)
						{
							max3=sw_header[96];
						}
					}

				break;

				case 97:
					if (sw_header[97]>=0)
					{

						DXF_code_tables[sw_header[97]].dxf_97=line2;
						sw_header[97]++;

						if (sw_header[97]>max3)
						{
							max3=sw_header[97];
						}
					}

				break;

				case 98:
					if (sw_header[98]>=0)
					{

						DXF_code_tables[sw_header[98]].dxf_98=line2;
						sw_header[98]++;

						if (sw_header[98]>max3)
						{
							max3=sw_header[98];
						}
					}

				break;

				case 99:
					if (sw_header[99]>=0)
					{

						DXF_code_tables[sw_header[99]].dxf_99=line2;
						sw_header[99]++;

						if (sw_header[99]>max3)
						{
							max3=sw_header[99];
						}
					}

				break;

				case 100:
					if (sw_header[100]>=0)
					{

						DXF_code_tables[sw_header[100]].dxf_100=line2;
						sw_header[100]++;

						if (sw_header[100]>max3)
						{
							max3=sw_header[100];
						}
					}

				break;

				//code 101 dont exist

				case 102:
					if (sw_header[102]>=0)
					{

						DXF_code_tables[sw_header[102]].dxf_102=line2;
						sw_header[102]++;

						if (sw_header[102]>max3)
						{
							max3=sw_header[102];
						}
					}

				break;

				case 105:
					if (sw_header[105]>=0)
					{

						DXF_code_tables[sw_header[105]].dxf_105=line2;
						sw_header[105]++;

						if (sw_header[105]>max3)
						{
							max3=sw_header[105];
						}
					}

				break;

				case 110:
					if (sw_header[110]>=0)
					{

						DXF_code_tables[sw_header[110]].dxf_110=line2;
						sw_header[110]++;

						if (sw_header[110]>max3)
						{
							max3=sw_header[110];
						}
					}

				break;

				case 111:
					if (sw_header[111]>=0)
					{

						DXF_code_tables[sw_header[111]].dxf_111=line2;
						sw_header[111]++;

						if (sw_header[111]>max3)
						{
							max3=sw_header[111];
						}
					}

				break;

				case 112:
					if (sw_header[112]>=0)
					{

						DXF_code_tables[sw_header[112]].dxf_112=line2;
						sw_header[112]++;

						if (sw_header[112]>max3)
						{
							max3=sw_header[112];
						}
					}

				break;

				case 120:
					if (sw_header[120]>=0)
					{

						DXF_code_tables[sw_header[120]].dxf_120=line2;
						sw_header[120]++;

						if (sw_header[120]>max3)
						{
							max3=sw_header[120];
						}
					}

				break;

				case 121:
					if (sw_header[121]>=0)
					{

						DXF_code_tables[sw_header[121]].dxf_121=line2;
						sw_header[121]++;

						if (sw_header[121]>max3)
						{
							max3=sw_header[121];
						}
					}

				break;

				case 122:
					if (sw_header[122]>=0)
					{

						DXF_code_tables[sw_header[122]].dxf_122=line2;
						sw_header[122]++;

						if (sw_header[122]>max3)
						{
							max3=sw_header[122];
						}
					}

				break;

				case 130:
					if (sw_header[130]>=0)
					{

						DXF_code_tables[sw_header[130]].dxf_130=line2;
						sw_header[130]++;

						if (sw_header[130]>max3)
						{
							max3=sw_header[130];
						}
					}

				break;

				case 131:
					if (sw_header[131]>=0)
					{

						DXF_code_tables[sw_header[131]].dxf_131=line2;
						sw_header[131]++;

						if (sw_header[131]>max3)
						{
							max3=sw_header[131];
						}
					}

				break;

				case 132:
					if (sw_header[132]>=0)
					{

						DXF_code_tables[sw_header[132]].dxf_132=line2;
						sw_header[132]++;

						if (sw_header[132]>max3)
						{
							max3=sw_header[132];
						}
					}

				break;

				case 140:
					if (sw_header[140]>=0)
					{

						DXF_code_tables[sw_header[140]].dxf_140=line2;
						sw_header[140]++;

						if (sw_header[140]>max3)
						{
							max3=sw_header[140];
						}
					}

				break;

				case 141:
					if (sw_header[141]>=0)
					{

						DXF_code_tables[sw_header[141]].dxf_141=line2;
						sw_header[141]++;

						if (sw_header[141]>max3)
						{
							max3=sw_header[141];
						}
					}

				break;

				case 142:
					if (sw_header[142]>=0)
					{

						DXF_code_tables[sw_header[142]].dxf_142=line2;
						sw_header[142]++;

						if (sw_header[142]>max3)
						{
							max3=sw_header[142];
						}
					}

				break;

				case 143:
					if (sw_header[143]>=0)
					{

						DXF_code_tables[sw_header[143]].dxf_143=line2;
						sw_header[143]++;

						if (sw_header[143]>max3)
						{
							max3=sw_header[143];
						}
					}

				break;

				case 144:
					if (sw_header[144]>=0)
					{

						DXF_code_tables[sw_header[144]].dxf_144=line2;
						sw_header[144]++;

						if (sw_header[144]>max3)
						{
							max3=sw_header[144];
						}
					}

				break;

				case 145:
					if (sw_header[145]>=0)
					{

						DXF_code_tables[sw_header[145]].dxf_145=line2;
						sw_header[145]++;

						if (sw_header[145]>max3)
						{
							max3=sw_header[145];
						}
					}

				break;

				case 146:
					if (sw_header[146]>=0)
					{

						DXF_code_tables[sw_header[146]].dxf_146=line2;
						sw_header[146]++;

						if (sw_header[146]>max3)
						{
							max3=sw_header[146];
						}
					}

				break;

				case 147:
					if (sw_header[147]>=0)
					{

						DXF_code_tables[sw_header[147]].dxf_147=line2;
						sw_header[147]++;

						if (sw_header[147]>max3)
						{
							max3=sw_header[147];
						}
					}

				break;

				case 148:
					if (sw_header[148]>=0)
					{

						DXF_code_tables[sw_header[148]].dxf_148=line2;
						sw_header[148]++;

						if (sw_header[148]>max3)
						{
							max3=sw_header[148];
						}
					}

				break;

				case 149:
					if (sw_header[149]>=0)
					{

						DXF_code_tables[sw_header[149]].dxf_149=line2;
						sw_header[149]++;

						if (sw_header[149]>max3)
						{
							max3=sw_header[149];
						}
					}

				break;

				case 160:
					if (sw_header[160]>=0)
					{

						DXF_code_tables[sw_header[160]].dxf_160=line2;
						sw_header[160]++;

						if (sw_header[160]>max3)
						{
							max3=sw_header[160];
						}
					}

				break;

				case 170:
					if (sw_header[170]>=0)
					{

						DXF_code_tables[sw_header[170]].dxf_170=line2;
						sw_header[170]++;

						if (sw_header[170]>max3)
						{
							max3=sw_header[170];
						}
					}

				break;

				case 171:
					if (sw_header[171]>=0)
					{

						DXF_code_tables[sw_header[171]].dxf_171=line2;
						sw_header[171]++;

						if (sw_header[171]>max3)
						{
							max3=sw_header[171];
						}
					}

				break;

				case 172:
					if (sw_header[172]>=0)
					{

						DXF_code_tables[sw_header[172]].dxf_172=line2;
						sw_header[172]++;

						if (sw_header[172]>max3)
						{
							max3=sw_header[172];
						}
					}

				break;

				case 173:
					if (sw_header[173]>=0)
					{

						DXF_code_tables[sw_header[173]].dxf_173=line2;
						sw_header[173]++;

						if (sw_header[173]>max3)
						{
							max3=sw_header[173];
						}
					}

				break;

				case 174:
					if (sw_header[174]>=0)
					{

						DXF_code_tables[sw_header[174]].dxf_174=line2;
						sw_header[174]++;

						if (sw_header[174]>max3)
						{
							max3=sw_header[174];
						}
					}

				break;

				case 175:
					if (sw_header[175]>=0)
					{

						DXF_code_tables[sw_header[175]].dxf_175=line2;
						sw_header[175]++;

						if (sw_header[175]>max3)
						{
							max3=sw_header[175];
						}
					}

				break;

				case 176:
					if (sw_header[176]>=0)
					{

						DXF_code_tables[sw_header[176]].dxf_176=line2;
						sw_header[176]++;

						if (sw_header[176]>max3)
						{
							max3=sw_header[176];
						}
					}

				break;

				case 177:
					if (sw_header[177]>=0)
					{

						DXF_code_tables[sw_header[177]].dxf_177=line2;
						sw_header[177]++;

						if (sw_header[177]>max3)
						{
							max3=sw_header[177];
						}
					}

				break;

				case 178:
					if (sw_header[178]>=0)
					{

						DXF_code_tables[sw_header[178]].dxf_178=line2;
						sw_header[178]++;

						if (sw_header[178]>max3)
						{
							max3=sw_header[178];
						}
					}

				break;


				case 179:
					if (sw_header[179]>=0)
					{

						DXF_code_tables[sw_header[179]].dxf_179=line2;
						sw_header[179]++;

						if (sw_header[179]>max3)
						{
							max3=sw_header[179];
						}
					}

				break;

				case 210:
					if (sw_header[210]>=0)
					{

						DXF_code_tables[sw_header[210]].dxf_210=line2;
						sw_header[210]++;

						if (sw_header[210]>max3)
						{
							max3=sw_header[210];
						}
					}

				break;

				case 213:
					if (sw_header[213]>=0)
					{

						DXF_code_tables[sw_header[213]].dxf_213=line2;
						sw_header[213]++;

						if (sw_header[213]>max3)
						{
							max3=sw_header[213];
						}
					}

				break;

				case 220:
					if (sw_header[220]>=0)
					{

						DXF_code_tables[sw_header[220]].dxf_220=line2;
						sw_header[220]++;

						if (sw_header[220]>max3)
						{
							max3=sw_header[220];
						}
					}

				break;

				case 223:
					if (sw_header[223]>=0)
					{

						DXF_code_tables[sw_header[223]].dxf_223=line2;
						sw_header[223]++;

						if (sw_header[223]>max3)
						{
							max3=sw_header[223];
						}
					}

				break;

				case 230:
					if (sw_header[230]>=0)
					{

						DXF_code_tables[sw_header[230]].dxf_230=line2;
						sw_header[230]++;

						if (sw_header[230]>max3)
						{
							max3=sw_header[230];
						}
					}

				break;

				case 233:
					if (sw_header[233]>=0)
					{

						DXF_code_tables[sw_header[233]].dxf_233=line2;
						sw_header[233]++;

						if (sw_header[233]>max3)
						{
							max3=sw_header[233];
						}
					}

				break;

				case 270:
					if (sw_header[270]>=0)
					{

						DXF_code_tables[sw_header[270]].dxf_270=line2;
						sw_header[270]++;

						if (sw_header[270]>max3)
						{
							max3=sw_header[270];
						}
					}

				break;

				case 271:
					if (sw_header[271]>=0)
					{

						DXF_code_tables[sw_header[271]].dxf_271=line2;
						sw_header[271]++;

						if (sw_header[271]>max3)
						{
							max3=sw_header[271];
						}
					}

				break;

				case 272:
					if (sw_header[272]>=0)
					{

						DXF_code_tables[sw_header[272]].dxf_272=line2;
						sw_header[272]++;

						if (sw_header[272]>max3)
						{
							max3=sw_header[272];
						}
					}

				break;

				case 273:
					if (sw_header[273]>=0)
					{

						DXF_code_tables[sw_header[273]].dxf_273=line2;
						sw_header[273]++;

						if (sw_header[273]>max3)
						{
							max3=sw_header[273];
						}
					}

				break;

				case 274:
					if (sw_header[274]>=0)
					{

						DXF_code_tables[sw_header[274]].dxf_274=line2;
						sw_header[274]++;

						if (sw_header[274]>max3)
						{
							max3=sw_header[274];
						}
					}

				break;

				case 275:
					if (sw_header[275]>=0)
					{

						DXF_code_tables[sw_header[275]].dxf_275=line2;
						sw_header[275]++;

						if (sw_header[275]>max3)
						{
							max3=sw_header[275];
						}
					}

				break;

				case 276:
					if (sw_header[276]>=0)
					{

						DXF_code_tables[sw_header[276]].dxf_276=line2;
						sw_header[276]++;

						if (sw_header[276]>max3)
						{
							max3=sw_header[276];
						}
					}

				break;


				case 277:
					if (sw_header[277]>=0)
					{

						DXF_code_tables[sw_header[277]].dxf_277=line2;
						sw_header[277]++;

						if (sw_header[277]>max3)
						{
							max3=sw_header[277];
						}
					}

				break;

				case 278:
					if (sw_header[278]>=0)
					{

						DXF_code_tables[sw_header[278]].dxf_278=line2;
						sw_header[278]++;

						if (sw_header[278]>max3)
						{
							max3=sw_header[278];
						}
					}

				break;

				case 279:
					if (sw_header[279]>=0)
					{

						DXF_code_tables[sw_header[279]].dxf_279=line2;
						sw_header[279]++;

						if (sw_header[279]>max3)
						{
							max3=sw_header[279];
						}
					}

				break;

				case 280:
					if (sw_header[280]>=0)
					{

						DXF_code_tables[sw_header[280]].dxf_280=line2;
						sw_header[280]++;

						if (sw_header[280]>max3)
						{
							max3=sw_header[280];
						}
					}

				break;

				case 281:
					if (sw_header[281]>=0)
					{

						DXF_code_tables[sw_header[281]].dxf_281=line2;
						sw_header[281]++;

						if (sw_header[281]>max3)
						{
							max3=sw_header[281];
						}
					}

				break;

				case 282:
					if (sw_header[282]>=0)
					{

						DXF_code_tables[sw_header[282]].dxf_282=line2;
						sw_header[282]++;

						if (sw_header[282]>max3)
						{
							max3=sw_header[282];
						}
					}

				break;

				case 283:
					if (sw_header[283]>=0)
					{

						DXF_code_tables[sw_header[283]].dxf_283=line2;
						sw_header[283]++;

						if (sw_header[283]>max3)
						{
							max3=sw_header[283];
						}
					}

				break;

				case 284:
					if (sw_header[284]>=0)
					{

						DXF_code_tables[sw_header[284]].dxf_284=line2;
						sw_header[284]++;

						if (sw_header[284]>max3)
						{
							max3=sw_header[284];
						}
					}

				break;

				case 285:
					if (sw_header[285]>=0)
					{

						DXF_code_tables[sw_header[285]].dxf_285=line2;
						sw_header[285]++;

						if (sw_header[285]>max3)
						{
							max3=sw_header[285];
						}
					}

				break;

				case 286:
					if (sw_header[286]>=0)
					{

						DXF_code_tables[sw_header[286]].dxf_286=line2;
						sw_header[286]++;

						if (sw_header[286]>max3)
						{
							max3=sw_header[286];
						}
					}

				break;

				case 287:
					if (sw_header[287]>=0)
					{

						DXF_code_tables[sw_header[287]].dxf_287=line2;
						sw_header[287]++;

						if (sw_header[287]>max3)
						{
							max3=sw_header[287];
						}
					}

				break;

				case 288:
					if (sw_header[288]>=0)
					{

						DXF_code_tables[sw_header[288]].dxf_288=line2;
						sw_header[288]++;

						if (sw_header[288]>max3)
						{
							max3=sw_header[288];
						}
					}

				break;

				case 289:
					if (sw_header[289]>=0)
					{

						DXF_code_tables[sw_header[289]].dxf_289=line2;
						sw_header[289]++;

						if (sw_header[289]>max3)
						{
							max3=sw_header[289];
						}
					}

				break;

				case 290:
					if (sw_header[290]>=0)
					{

						DXF_code_tables[sw_header[290]].dxf_290=line2;
						sw_header[290]++;

						if (sw_header[290]>max3)
						{
							max3=sw_header[290];
						}
					}

				break;

				case 291:
					if (sw_header[291]>=0)
					{

						DXF_code_tables[sw_header[291]].dxf_291=line2;
						sw_header[291]++;

						if (sw_header[291]>max3)
						{
							max3=sw_header[291];
						}
					}

				break;

				case 292:
					if (sw_header[292]>=0)
					{

						DXF_code_tables[sw_header[292]].dxf_292=line2;
						sw_header[292]++;

						if (sw_header[292]>max3)
						{
							max3=sw_header[292];
						}
					}

				break;

				case 293:
					if (sw_header[293]>=0)
					{

						DXF_code_tables[sw_header[293]].dxf_293=line2;
						sw_header[293]++;

						if (sw_header[293]>max3)
						{
							max3=sw_header[293];
						}
					}

				break;

				case 294:
					if (sw_header[294]>=0)
					{

						DXF_code_tables[sw_header[294]].dxf_294=line2;
						sw_header[294]++;

						if (sw_header[294]>max3)
						{
							max3=sw_header[294];
						}
					}

				break;

				case 295:
					if (sw_header[295]>=0)
					{

						DXF_code_tables[sw_header[295]].dxf_295=line2;
						sw_header[295]++;

						if (sw_header[295]>max3)
						{
							max3=sw_header[295];
						}
					}

				break;

				case 296:
					if (sw_header[296]>=0)
					{

						DXF_code_tables[sw_header[296]].dxf_296=line2;
						sw_header[296]++;

						if (sw_header[296]>max3)
						{
							max3=sw_header[296];
						}
					}

				break;

				case 297:
					if (sw_header[297]>=0)
					{

						DXF_code_tables[sw_header[297]].dxf_297=line2;
						sw_header[297]++;

						if (sw_header[297]>max3)
						{
							max3=sw_header[297];
						}
					}

				break;

				case 298:
					if (sw_header[298]>=0)
					{

						DXF_code_tables[sw_header[298]].dxf_298=line2;
						sw_header[298]++;

						if (sw_header[298]>max3)
						{
							max3=sw_header[298];
						}
					}

				break;

				case 299:
					if (sw_header[299]>=0)
					{

						DXF_code_tables[sw_header[299]].dxf_299=line2;
						sw_header[299]++;

						if (sw_header[299]>max3)
						{
							max3=sw_header[299];
						}
					}

				break;

				case 300:
					if (sw_header[300]>=0)
					{

						DXF_code_tables[sw_header[300]].dxf_300=line2;
						sw_header[300]++;

						if (sw_header[300]>max3)
						{
							max3=sw_header[300];
						}
					}

				break;

				case 301:
					if (sw_header[301]>=0)
					{

						DXF_code_tables[sw_header[301]].dxf_301=line2;
						sw_header[301]++;

						if (sw_header[301]>max3)
						{
							max3=sw_header[301];
						}
					}

				break;

				case 302:
					if (sw_header[302]>=0)
					{

						DXF_code_tables[sw_header[302]].dxf_302=line2;
						sw_header[302]++;

						if (sw_header[302]>max3)
						{
							max3=sw_header[302];
						}
					}

				break;

				case 303:
					if (sw_header[303]>=0)
					{

						DXF_code_tables[sw_header[303]].dxf_303=line2;
						sw_header[303]++;

						if (sw_header[303]>max3)
						{
							max3=sw_header[303];
						}
					}

				break;

				case 304:
					if (sw_header[304]>=0)
					{

						DXF_code_tables[sw_header[304]].dxf_304=line2;
						sw_header[304]++;

						if (sw_header[304]>max3)
						{
							max3=sw_header[304];
						}
					}

				break;

				case 305:
					if (sw_header[305]>=0)
					{

						DXF_code_tables[sw_header[305]].dxf_305=line2;
						sw_header[305]++;

						if (sw_header[305]>max3)
						{
							max3=sw_header[305];
						}
					}

				break;

				case 306:
					if (sw_header[306]>=0)
					{

						DXF_code_tables[sw_header[306]].dxf_306=line2;
						sw_header[306]++;

						if (sw_header[306]>max3)
						{
							max3=sw_header[306];
						}
					}

				break;

				case 307:
					if (sw_header[307]>=0)
					{

						DXF_code_tables[sw_header[307]].dxf_307=line2;
						sw_header[307]++;

						if (sw_header[307]>max3)
						{
							max3=sw_header[307];
						}
					}

				break;

				case 308:
					if (sw_header[308]>=0)
					{

						DXF_code_tables[sw_header[308]].dxf_308=line2;
						sw_header[308]++;

						if (sw_header[308]>max3)
						{
							max3=sw_header[308];
						}
					}

				break;

				case 309:
					if (sw_header[309]>=0)
					{

						DXF_code_tables[sw_header[309]].dxf_309=line2;
						sw_header[309]++;

						if (sw_header[309]>max3)
						{
							max3=sw_header[309];
						}
					}

				break;

				case 310:
					if (sw_header[310]>=0)
					{

						DXF_code_tables[sw_header[310]].dxf_310=line2;
						sw_header[310]++;

						if (sw_header[310]>max3)
						{
							max3=sw_header[310];
						}
					}

				break;

				case 330:
					if (sw_header[330]>=0)
					{

						DXF_code_tables[sw_header[330]].dxf_330=line2;
						sw_header[330]++;

						if (sw_header[330]>max3)
						{
							max3=sw_header[330];
						}
					}

				break;



				case 331:
					if (sw_header[331]>=0)
					{

						DXF_code_tables[sw_header[331]].dxf_331=line2;
						sw_header[331]++;

						if (sw_header[331]>max3)
						{
							max3=sw_header[331];
						}
					}

				break;

				case 332:
					if (sw_header[332]>=0)
					{

						DXF_code_tables[sw_header[332]].dxf_332=line2;
						sw_header[332]++;

						if (sw_header[332]>max3)
						{
							max3=sw_header[332];
						}
					}

				break;

				case 338:
					if (sw_header[338]>=0)
					{

						DXF_code_tables[sw_header[338]].dxf_342=line2;
						sw_header[338]++;

						if (sw_header[338]>max3)
						{
							max3=sw_header[338];
						}
					}

				break;

				case 340:
					if (sw_header[340]>=0)
					{

						DXF_code_tables[sw_header[340]].dxf_340=line2;
						sw_header[340]++;

						if (sw_header[340]>max3)
						{
							max3=sw_header[340];
						}
					}

				break;

				case 341:
					if (sw_header[341]>=0)
					{

						DXF_code_tables[sw_header[341]].dxf_341=line2;
						sw_header[341]++;

						if (sw_header[341]>max3)
						{
							max3=sw_header[341];
						}
					}

				break;

				case 342:
					if (sw_header[342]>=0)
					{

						DXF_code_tables[sw_header[342]].dxf_342=line2;
						sw_header[342]++;

						if (sw_header[342]>max3)
						{
							max3=sw_header[342];
						}
					}

				break;

				case 343:
					if (sw_header[343]>=0)
					{

						DXF_code_tables[sw_header[343]].dxf_343=line2;
						sw_header[343]++;

						if (sw_header[343]>max3)
						{
							max3=sw_header[343];
						}
					}

				break;

				case 344:
					if (sw_header[344]>=0)
					{

						DXF_code_tables[sw_header[344]].dxf_344=line2;
						sw_header[344]++;

						if (sw_header[344]>max3)
						{
							max3=sw_header[344];
						}
					}

				break;

				case 345:
					if (sw_header[345]>=0)
					{

						DXF_code_tables[sw_header[345]].dxf_345=line2;
						sw_header[345]++;

						if (sw_header[345]>max3)
						{
							max3=sw_header[345];
						}
					}

				break;

				case 346:
					if (sw_header[346]>=0)
					{

						DXF_code_tables[sw_header[346]].dxf_346=line2;
						sw_header[346]++;

						if (sw_header[346]>max3)
						{
							max3=sw_header[346];
						}
					}

				break;

				case 347:
					if (sw_header[347]>=0)
					{

						DXF_code_tables[sw_header[347]].dxf_347=line2;
						sw_header[347]++;

						if (sw_header[347]>max3)
						{
							max3=sw_header[347];
						}
					}

				break;

				case 348:
					if (sw_header[348]>=0)
					{

						DXF_code_tables[sw_header[348]].dxf_348=line2;
						sw_header[348]++;

						if (sw_header[348]>max3)
						{
							max3=sw_header[348];
						}
					}

				break;

				case 350:
					if (sw_header[350]>=0)
					{

						DXF_code_tables[sw_header[350]].dxf_350=line2;
						sw_header[350]++;

						if (sw_header[350]>max3)
						{
							max3=sw_header[350];
						}
					}

				break;

				case 360:
					if (sw_header[360]>=0)
					{

						DXF_code_tables[sw_header[360]].dxf_360=line2;
						sw_header[360]++;

						if (sw_header[360]>max3)
						{
							max3=sw_header[360];
						}
					}

				break;

				case 361:
					if (sw_header[361]>=0)
					{

						DXF_code_tables[sw_header[361]].dxf_361=line2;
						sw_header[361]++;

						if (sw_header[361]>max3)
						{
							max3=sw_header[361];
						}
					}

				break;

				case 370:
					if (sw_header[370]>=0)
					{

						DXF_code_tables[sw_header[370]].dxf_370=line2;
						sw_header[370]++;

						if (sw_header[370]>max3)
						{
							max3=sw_header[370];
						}
					}

				break;

				case 371:
					if (sw_header[371]>=0)
					{

						DXF_code_tables[sw_header[371]].dxf_371=line2;
						sw_header[371]++;

						if (sw_header[371]>max3)
						{
							max3=sw_header[371];
						}
					}

				break;

				case 372:
					if (sw_header[372]>=0)
					{

						DXF_code_tables[sw_header[372]].dxf_372=line2;
						sw_header[372]++;

						if (sw_header[372]>max3)
						{
							max3=sw_header[372];
						}
					}

				break;

				case 373:
					if (sw_header[373]>=0)
					{

						DXF_code_tables[sw_header[373]].dxf_373=line2;
						sw_header[373]++;

						if (sw_header[373]>max3)
						{
							max3=sw_header[373];
						}
					}

				break;

				case 380:
					if (sw_header[380]>=0)
					{

						DXF_code_tables[sw_header[380]].dxf_380=line2;
						sw_header[380]++;

						if (sw_header[380]>max3)
						{
							max3=sw_header[380];
						}
					}

				break;

				case 390:
					if (sw_header[390]>=0)
					{

						DXF_code_tables[sw_header[390]].dxf_390=line2;
						sw_header[390]++;

						if (sw_header[390]>max3)
						{
							max3=sw_header[390];
						}
					}

				break;

				case 420:
					if (sw_header[420]>=0)
					{

						DXF_code_tables[sw_header[420]].dxf_420=line2;
						sw_header[420]++;

						if (sw_header[420]>max3)
						{
							max3=sw_header[420];
						}
					}

				break;


				case 421:
					if (sw_header[421]>=0)
					{

						DXF_code_tables[sw_header[421]].dxf_421=line2;
						sw_header[421]++;

						if (sw_header[421]>max3)
						{
							max3=sw_header[421];
						}
					}

				break;

				case 424:
					if (sw_header[424]>=0)
					{

						DXF_code_tables[sw_header[424]].dxf_424=line2;
						sw_header[424]++;

						if (sw_header[424]>max3)
						{
							max3=sw_header[424];
						}
					}

                break;

				case 425:
					if (sw_header[425]>=0)
					{

						DXF_code_tables[sw_header[425]].dxf_425=line2;
						sw_header[425]++;

						if (sw_header[425]>max3)
						{
							max3=sw_header[425];
						}
					}

				break;

                case 450:
                    if (sw_header[450]>=0)
                    {

                        DXF_code_tables[sw_header[450]].dxf_450=line2;
                        sw_header[450]++;

                        if (sw_header[450]>max3)
                        {
                            max3=sw_header[450];
                        }
                    }

                break;

            case 451:
                if (sw_header[451]>=0)
                {

                    DXF_code_tables[sw_header[451]].dxf_451=line2;
                    sw_header[451]++;

                    if (sw_header[451]>max3)
                    {
                        max3=sw_header[451];
                    }
                }

            break;

            case 452:
                if (sw_header[452]>=0)
                {

                    DXF_code_tables[sw_header[452]].dxf_452=line2;
                    sw_header[452]++;

                    if (sw_header[452]>max3)
                    {
                        max3=sw_header[452];
                    }
                }

            break;

            case 453:
                if (sw_header[453]>=0)
                {

                    DXF_code_tables[sw_header[453]].dxf_453=line2;
                    sw_header[453]++;

                    if (sw_header[453]>max3)
                    {
                        max3=sw_header[453];
                    }
                }

            break;

            case 460:
                if (sw_header[460]>=0)
                {

                    DXF_code_tables[sw_header[460]].dxf_460=line2;
                    sw_header[460]++;

                    if (sw_header[460]>max3)
                    {
                        max3=sw_header[460];
                    }
                }

            break;

            case 461:
                if (sw_header[461]>=0)
                {

                    DXF_code_tables[sw_header[461]].dxf_461=line2;
                    sw_header[461]++;

                    if (sw_header[461]>max3)
                    {
                        max3=sw_header[461];
                    }
                }

            break;

            case 462:
                if (sw_header[462]>=0)
                {

                    DXF_code_tables[sw_header[462]].dxf_462=line2;
                    sw_header[462]++;

                    if (sw_header[462]>max3)
                    {
                        max3=sw_header[462];
                    }
                }

            break;

            case 470:
                if (sw_header[470]>=0)
                {

                    DXF_code_tables[sw_header[470]].dxf_470=line2;
                    sw_header[470]++;

                    if (sw_header[470]>max3)
                    {
                        max3=sw_header[470];
                    }
                }

            break;

				case 1000:
					if (sw_header[1000]>=0)
					{

						DXF_code_tables[sw_header[1000]].dxf_1000=line2;
						sw_header[1000]++;

						if (sw_header[1000]>max3)
						{
							max3=sw_header[1000];
						}
					}

				break;

				case 1001:
					if (sw_header[1001]>=0)
					{

						DXF_code_tables[sw_header[1001]].dxf_1001=line2;
						sw_header[1001]++;

						if (sw_header[1001]>max3)
						{
							max3=sw_header[1001];
						}
					}

				break;

				case 1002:
					if (sw_header[1002]>=0)
					{

						DXF_code_tables[sw_header[1002]].dxf_1002=line2;
						sw_header[1002]++;

						if (sw_header[1002]>max3)
						{
							max3=sw_header[1002];
						}
					}

				break;

				case 1005:
					if (sw_header[1005]>=0)
					{

						DXF_code_tables[sw_header[1005]].dxf_1005=line2;
						sw_header[1005]++;

						if (sw_header[1005]>max3)
						{
							max3=sw_header[1005];
						}
					}

				break;

				case 1010:
					if (sw_header[1010]>=0)
					{

						DXF_code_tables[sw_header[1010]].dxf_1010=line2;
						sw_header[1010]++;

						if (sw_header[1010]>max3)
						{
							max3=sw_header[1010];
						}
					}

				break;

				case 1011:
					if (sw_header[1011]>=0)
					{

						DXF_code_tables[sw_header[1011]].dxf_1011=line2;
						sw_header[1011]++;

						if (sw_header[1011]>max3)
						{
							max3=sw_header[1011];
						}
					}

				break;

				case 1012:
					if (sw_header[1012]>=0)
					{

						DXF_code_tables[sw_header[1012]].dxf_1012=line2;
						sw_header[1012]++;

						if (sw_header[1012]>max3)
						{
							max3=sw_header[1012];
						}
					}

				break;

				case 1013:
					if (sw_header[1013]>=0)
					{

						DXF_code_tables[sw_header[1013]].dxf_1013=line2;
						sw_header[1013]++;

						if (sw_header[1013]>max3)
						{
							max3=sw_header[1013];
						}
					}

				break;


				case 1020:
					if (sw_header[1020]>=0)
					{

						DXF_code_tables[sw_header[1020]].dxf_1020=line2;
						sw_header[1020]++;

						if (sw_header[1020]>max3)
						{
							max3=sw_header[1020];
						}
					}

				break;

				case 1021:
					if (sw_header[1021]>=0)
					{

						DXF_code_tables[sw_header[1021]].dxf_1021=line2;
						sw_header[1021]++;

						if (sw_header[1021]>max3)
						{
							max3=sw_header[1021];
						}
					}

				break;

				case 1022:
					if (sw_header[1022]>=0)
					{

						DXF_code_tables[sw_header[1022]].dxf_1022=line2;
						sw_header[1022]++;

						if (sw_header[1022]>max3)
						{
							max3=sw_header[1022];
						}
					}

				break;

				case 1023:
					if (sw_header[1023]>=0)
					{

						DXF_code_tables[sw_header[1023]].dxf_1023=line2;
						sw_header[1023]++;

						if (sw_header[1023]>max3)
						{
							max3=sw_header[1023];
						}
					}

				break;

				case 1030:
					if (sw_header[1030]>=0)
					{

						DXF_code_tables[sw_header[1030]].dxf_1030=line2;
						sw_header[1030]++;

						if (sw_header[1030]>max3)
						{
							max3=sw_header[1030];
						}
					}

				break;

				case 1031:
					if (sw_header[1031]>=0)
					{

						DXF_code_tables[sw_header[1031]].dxf_1031=line2;
						sw_header[1031]++;

						if (sw_header[1031]>max3)
						{
							max3=sw_header[1031];
						}
					}

				break;

				case 1032:
					if (sw_header[1032]>=0)
					{

						DXF_code_tables[sw_header[1032]].dxf_1032=line2;
						sw_header[1032]++;

						if (sw_header[1032]>max3)
						{
							max3=sw_header[1032];
						}
					}

				break;

				case 1033:
					if (sw_header[1033]>=0)
					{

						DXF_code_tables[sw_header[1033]].dxf_1033=line2;
						sw_header[1033]++;

						if (sw_header[1033]>max3)
						{
							max3=sw_header[1033];
						}
					}

				break;

				case 1040:
					if (sw_header[1040]>=0)
					{

						DXF_code_tables[sw_header[1040]].dxf_1040=line2;
						sw_header[1040]++;

						if (sw_header[1040]>max3)
						{
							max3=sw_header[1040];
						}
					}

				break;

				case 1070:
					if (sw_header[1070]>=0)
					{

						DXF_code_tables[sw_header[1070]].dxf_1070=line2;
						sw_header[1070]++;

						if (sw_header[1070]>max3)
						{
							max3=sw_header[1070];
						}
					}

				break;


				case 1071:
					if (sw_header[1071]>=0)
					{

						DXF_code_tables[sw_header[1071]].dxf_1071=line2;
						sw_header[1071]++;

						if (sw_header[1071]>max3)
						{
							max3=sw_header[1071];
						}
					}

				break;

				default:

					ui->dxf_log->insertPlainText("Found code : ");
					ui->dxf_log->insertPlainText(split_tables_list[count_tables_list][count_list_item]);
					ui->dxf_log->insertPlainText(" | ");
					ui->dxf_log->insertPlainText(split_tables_list[count_tables_list][count_list_item+1]);
					ui->dxf_log->insertPlainText("\n");

					ui->dxf_log->moveCursor(QTextCursor::End);
					ui->dxf_log->repaint();

			}


		count_list_item=count_list_item+2;
	}







	return max3;
}

void DXFtoQET3DB::clear_split_tables()
{
	for (xclear = 0;xclear < DXF_item_split;xclear++)
	{
		split_tables_list[xclear].clear();
	}

}

void DXFtoQET3DB::on_Create_QET_ELMT_clicked()
{



    Signal_log1.clear();
    Signal_log1.append("============================================================================");
    Signal_log1.append(" \n");
    Signal_log1.append(QTime::currentTime().toString());
    Signal_log1.append(" - Create file : ");
    Signal_log1.append(DXF_main_base[0].dxf_savepath + "/" + DXF_main_base[0].dxf_openfile + ".elmt");
    Signal_log1.append(" \n");
    Signal_log1.append("============================================================================");
    Signal_log1.append(" \n");
    emit send_log(Signal_log1);

	ui->ELMT_Result->clear();
	DXF_Entities_List.DXF_Result.clear();
    DXF_Entities_List.DXF_ResultBegin.clear();
    DXF_Entities_List.DXF_ResultEinde.clear();
    DXF_Entities_List.DXF_ResultEntitie.clear();
    DXF_Entities_List.DXF_ResultEntitieLine.clear();
    DXF_Entities_List.DXF_ResultBlock.clear();
    DXF_Entities_List.DXF_ResultBlock2.clear();
    DXF_Entities_List.DXF_ResultEntitiePolyline.clear();
    DXF_Entities_List.DXF_ResultEntitieLwpolyline.clear();
    DXF_Entities_List.DXF_ResultEntitieSpline.clear();
    DXF_Entities_List.DXF_ResultEntitieSolid.clear();
    DXF_Entities_List.DXF_ResultEntitieHatch.clear();

    Signal_log1.clear();
    Signal_log1.append("============================================================================");
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result : ");
    stringsize=DXF_Entities_List.DXF_Result.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Begin : ");
    stringsize=DXF_Entities_List.DXF_ResultBegin.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitie.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Line: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitieLine.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Polyline: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitiePolyline.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Lwpolyline: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitieLwpolyline.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Spline: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitieSpline.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Solid: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitieSolid.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Hatch: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitieHatch.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Block: ");
    stringsize=DXF_Entities_List.DXF_ResultBlock.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Block 2: ");
    stringsize=DXF_Entities_List.DXF_ResultBlock2.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Einde : ");
    stringsize=DXF_Entities_List.DXF_ResultEinde.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    emit send_log(Signal_log1);

	ui->Procesing_dxf->clear();

    ui->MainTab->setCurrentIndex(0);
	ui->MainTab->repaint();


	DXF_main_base[0].QDXF_arc_color="black";
	DXF_main_base[0].QDXF_circle_color="black";
	DXF_main_base[0].QDXF_ellipse_color="black";
	DXF_main_base[0].QDXF_input_color="black";
	DXF_main_base[0].QDXF_line_color="black";
	DXF_main_base[0].QDXF_lwpolyline_color="black";
	DXF_main_base[0].QDXF_polyline_color="black";
	DXF_main_base[0].QDXF_rectangel_color="black";
	DXF_main_base[0].QDXF_terminal_color="black";
	DXF_main_base[0].QDXF_text_color="black";
	DXF_main_base[0].QDXF_solid_color="black";

	Signal_log1.clear();
    Signal_log1.append("============================================================================");
    Signal_log1.append("\n");
	Signal_log1.append(QTime::currentTime().toString());
    Signal_log1.append("\n");
	Signal_log1.append(" - Start creating elmt : ");
	Signal_log1.append(QString::number(entities_max_items));
    Signal_log1.append("\n");
	Signal_log1.append("============================================================================");
    Signal_log1.append("\n");
	emit send_log(Signal_log1);

	Filename_db=DXF_main_base[0].dxf_savepath + "/" +DXF_main_base[0].dxf_openfile;
	Filename_db.append(".db3");

	Signal_log1.clear();
	Signal_log1.append("Open : ");
	Signal_log1.append(Filename_db);
	Signal_log1.append("\n");
	Signal_log1.append("Get dxf Header information");


	ui->Processing_dxf_file_2->clear();
	ui->Processing_dxf_file_2->insert(Filename_db);

	emit send_log(Signal_log1);

    stringsize=DXF_Entities_List.DXF_ResultBegin.size();
    emit send_lines(stringsize);

	ELMT_header_steps NewHeader;

    NewHeader.Open_SQL_DB(Filename_db);

	NewHeader.GetHeader_info(Filename_db);

    //NewHeader.Close_SQL_DB(Filename_db);

	elmt_tables NewLayerTable;

	Signal_log1.clear();
	Signal_log1.append("Get dxf Layer information");

	emit send_log(Signal_log1);

    //NewLayerTable.Open_SQL_DB(Filename_db);

    ui->dxf_log->insertPlainText(NewLayerTable.Get_Tables_Layers(Filename_db));

    //NewLayerTable.Close_SQL_DB(Filename_db);

	ui->dxf_log->insertPlainText(NewLayerTable.Get_Tables_Layers(Filename_db));
	ui->dxf_log->moveCursor(QTextCursor::End);
	ui->dxf_log->repaint();

	ResultELMT="";
	BaseELMT NewBase;

	Signal_log1.clear();
	Signal_log1.append("Creating header of ELMT file");

	emit send_log(Signal_log1);

	NewBase.ELMT_definition_width=NewHeader.Calc_Width();
	NewBase.ELMT_definition_height=NewHeader.Calc_Height();
	NewBase.ELMT_definition_version="0.51";
	NewBase.ELMT_definition_hotspot_x=DXF_variable.DXF_INSBASE_X;
	NewBase.ELMT_definition_hotspot_y=DXF_variable.DXF_INSBASE_Y;
	NewBase.ELMT_definition_link_type="simple";
	NewBase.ELMT_definition_orientation="dyyy";
	NewBase.ELMT_definition_type="element";

	NewBase.ELMT_Name_en="en";
	NewBase.ELMT_Name_fr="fr";

	NewBase.ELMT_Name_text_en=DXF_main_base[0].dxf_openfile;
	NewBase.ELMT_Name_text_fr=DXF_main_base[0].dxf_openfile;

	//NewBase.ELMT_kind_name="";
	//NewBase.ELMT_kind_show="";
	//NewBase.ELMT_kind_type="";

	NewBase.ELMT_informations_Author="DXF converter";
	NewBase.ELMT_informations_License="see http://qelectrotech.org/wiki/doc/elements_license";
	NewBase.ELMT_converter_version="V3.0 DB";
	NewBase.ELMT_converter_by="Ronny Desmedt";

	ui->dxf_log->insertPlainText("Add UUID names, kindinformation, information ... ELMT file \n");
	ui->dxf_log->moveCursor(QTextCursor::End);
	ui->dxf_log->repaint();

	//ResultELMT.append(NewBase.DefinitionStart());
    DXF_Entities_List.DXF_ResultBegin.append(NewBase.DefinitionStart());


    stringsize=DXF_Entities_List.DXF_ResultBegin.count();
    emit send_lines(stringsize);

    Signal_elmt1.clear();
    Signal_elmt1.append(DXF_Entities_List.DXF_ResultBegin);

    emit send_elmt(Signal_elmt1);

    //ResultELMT.append(NewBase.Uuid());
    DXF_Entities_List.DXF_ResultBegin.append(NewBase.Uuid());


    stringsize=DXF_Entities_List.DXF_ResultBegin.size();
    emit send_lines(stringsize);

	Signal_elmt1.clear();
    Signal_elmt1.append(DXF_Entities_List.DXF_ResultBegin);

    emit send_elmt(Signal_elmt1);

	//ResultELMT.append(NewBase.Names());
    DXF_Entities_List.DXF_ResultBegin.append(NewBase.Names());


    stringsize=DXF_Entities_List.DXF_ResultBegin.size();
    emit send_lines(stringsize);

	Signal_elmt1.clear();
    Signal_elmt1.append(DXF_Entities_List.DXF_ResultBegin);

    emit send_elmt(Signal_elmt1);

	//ResultELMT.append(NewBase.KindInformation());
    DXF_Entities_List.DXF_ResultBegin.append(NewBase.KindInformation());


    stringsize=DXF_Entities_List.DXF_ResultBegin.size();
    emit send_lines(stringsize);

	Signal_elmt1.clear();
	Signal_elmt1.append(DXF_Entities_List.DXF_Result);

    emit send_elmt(Signal_elmt1);

	//ResultELMT.append(NewBase.Informations());
    DXF_Entities_List.DXF_ResultBegin.append(NewBase.Informations());


    stringsize=DXF_Entities_List.DXF_ResultBegin.size();
    emit send_lines(stringsize);

	Signal_elmt1.clear();
    Signal_elmt1.append(DXF_Entities_List.DXF_ResultBegin);

    emit send_elmt(Signal_elmt1);

	//ResultELMT.append(NewBase.DescriptionStart());
    DXF_Entities_List.DXF_ResultBegin.append(NewBase.DescriptionStart());


    stringsize=DXF_Entities_List.DXF_ResultBegin.size();
    emit send_lines(stringsize);

	Signal_elmt1.clear();
    Signal_elmt1.append(DXF_Entities_List.DXF_ResultBegin);

    emit send_elmt(Signal_elmt1);

	elmt_entities NewEntity(this);

	connect(&NewEntity ,SIGNAL (Signal1(const QString &)),this ,SLOT(update_proces(const QString &)));

	connect(&NewEntity ,SIGNAL (send_log(const QString &)),this ,SLOT(update_log(const QString &)));
	connect(&NewEntity ,SIGNAL (send_elmt(const QString &)),this ,SLOT(update_elmt(const QString &)));



    Signal_log1.clear();
    Signal_log1.append("============================================================================");
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result : ");
    stringsize=DXF_Entities_List.DXF_Result.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Begin : ");
    stringsize=DXF_Entities_List.DXF_ResultBegin.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitie.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Line: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitieLine.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Polyline: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitiePolyline.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Lwpolyline: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitieLwpolyline.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Spline: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitieSpline.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Solid: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitieSolid.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Entitie Hatch: ");
    stringsize=DXF_Entities_List.DXF_ResultEntitieHatch.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Block: ");
    stringsize=DXF_Entities_List.DXF_ResultBlock.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Block 2: ");
    stringsize=DXF_Entities_List.DXF_ResultBlock2.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    Signal_log1.append("DXF_Result Einde : ");
    stringsize=DXF_Entities_List.DXF_ResultEinde.size();
    Signal_log1.append(QString::number(stringsize));
    Signal_log1.append(" \n");
    emit send_log(Signal_log1);

	Signal_log1.clear();
	Signal_log1.append("Add DXF entities to ELMT file");

	emit send_log(Signal_log1);

    //NewEntity.Open_SQL_DB(Filename_db);

	ui->ELMT_Result->clear();

	//create entities
	ui->dxf_log->insertPlainText(NewEntity.Get_Entities(Filename_db));
	ui->dxf_log->moveCursor(QTextCursor::End);
	ui->dxf_log->repaint();

    NewEntity.Close_SQL_DB(Filename_db);

	Signal_elmt1.clear();
    Signal_elmt1.append("append entitis");

    emit send_elmt(Signal_elmt1);



	//ResultELMT.append(NewBase.DescriptionEnd());
    DXF_Entities_List.DXF_ResultEinde.append(NewBase.DescriptionEnd());


    stringsize=DXF_Entities_List.DXF_ResultEinde.size();
    emit send_lines(stringsize);

	Signal_elmt1.clear();
    Signal_elmt1.append(DXF_Entities_List.DXF_ResultEinde);

    emit send_elmt(Signal_elmt1);

	//ResultELMT.append(NewBase.DefinitionEnd());
    DXF_Entities_List.DXF_ResultEinde.append(NewBase.DefinitionEnd());


    stringsize=DXF_Entities_List.DXF_ResultEinde.size();
    emit send_lines(stringsize);

	Signal_elmt1.clear();
    Signal_elmt1.append(DXF_Entities_List.DXF_ResultEinde);

    emit send_elmt(Signal_elmt1);

	Signal_log1.clear();
	Signal_log1.append("DXF file converted to ELMT file");
	Signal_log1.append("\n");
	Signal_log1.append("============================================================================\n");
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append(" => End of converting DXF to ELMT \n");
	Signal_log1.append("============================================================================");
    Signal_log1.append("\n");

	emit send_log(Signal_log1);



    Signal_log1.clear();
    Signal_log1.append("============================================================================");
    Signal_log1.append(QTime::currentTime().toString());
    Signal_log1.append(" - Closed file : ");
    Signal_log1.append(DXF_main_base[0].dxf_savepath + "/" + DXF_main_base[0].dxf_openfile + ".elmt");
    Signal_log1.append("============================================================================");
    emit send_log(Signal_log1);
}

void DXFtoQET3DB::on_Choose_DB_clicked()
{
	ui->dxf_log->clear();

	ui->MainTab->setCurrentIndex(0);
	ui->MainTab->repaint();

	QFileDialog dialog(this);
	dialog.setNameFilter(tr("DB files (*.*)"));
	dialog.setFileMode(QFileDialog::ExistingFile);
	dialog.setViewMode(QFileDialog::Detail);

	if (dialog.exec() == QDialog::Accepted)
	{
		DXF_main_base[0].dxf_filepath = dialog.selectedFiles().first();
		DXF_main_base[0].dxf_dir = dialog.directory().absolutePath();
		DXF_main_base[0].dxf_openfile=DXF_main_base[0].dxf_filepath.split("/").last();
		ui->dxf_file_path_save->setText(DXF_main_base[0].dxf_savepath);

		Filename_db_temp=dialog.selectedFiles().first();
		Filename_db=Filename_db_temp.split("/").last();
		DXF_main_base[0].dxf_openfile=Filename_db.split(".").first();
		Filename_db=DXF_main_base[0].dxf_openfile;
		ui->dxf_open_file->setPlaceholderText(DXF_main_base[0].dxf_openfile);
	}

	ui->dxf_log->insertPlainText("============================================================================\n");

	ui->dxf_log->insertPlainText(QTime::currentTime().toString());
	ui->dxf_log->insertPlainText("=> Opening DB3 file (dxf converted table file) \n");
	ui->dxf_log->insertPlainText(Filename_db);
	ui->dxf_log->insertPlainText("\n");
	ui->dxf_log->insertPlainText("============================================================================\n");

	return;
}

void DXFtoQET3DB::on_SavetoELMT_clicked()
{
	QFile file(DXF_main_base[0].dxf_savepath + "/" + DXF_main_base[0].dxf_openfile + ".elmt");

	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Application"),
							 tr("Cannot write file %1:\n%2.")
							 .arg(DXF_main_base[0].dxf_dir)
							 .arg(file.errorString()));
		return;
	}

	QTextStream out(&file);
	//out << ui->ELMT_Result->toPlainText();
    out << DXF_Entities_List.DXF_ResultBegin;
    out << DXF_Entities_List.DXF_ResultEntitie;
    out << DXF_Entities_List.DXF_ResultEntitieLine;
    out << DXF_Entities_List.DXF_ResultEntitiePolyline;
    out << DXF_Entities_List.DXF_ResultEntitieLwpolyline;
    out << DXF_Entities_List.DXF_ResultEntitieSpline;
    out << DXF_Entities_List.DXF_ResultEntitieSolid;
    out << DXF_Entities_List.DXF_ResultEntitieHatch;
    out << DXF_Entities_List.DXF_Result;
    out << DXF_Entities_List.DXF_ResultBlock;
    out << DXF_Entities_List.DXF_ResultBlock2;
    out << DXF_Entities_List.DXF_ResultEinde;

	file.close();
	QMessageBox::information(this, tr("Export as elmt file"), tr("L'element %1 a bien ete enregistre").arg(ui->dxf_open_file->text()));
}

void DXFtoQET3DB::on_Convert_dxf_blocks_clicked()
{



}

void DXFtoQET3DB::on_Convert_dxf_entities_clicked()
{

}

void DXFtoQET3DB::on_progressBar_valueChanged(int value1)
{
	ui->progressBar1->setValue(value1);
	ui->progressBar1->repaint();
}
void DXFtoQET3DB::on_progressBar_valueMin(const int value2)
{
	ui->progressBar1->setMinimum(value2);
	ui->progressBar1->repaint();
}
void DXFtoQET3DB::on_progressBar_valueMax(const int value1)
{
	ui->progressBar1->setMaximum(value1);
	ui->progressBar1->repaint();
}
void DXFtoQET3DB::on_progressBar_text(const QString text1)
{
	ui->progressBar1->text()=text1;
	ui->progressBar1->repaint();
}

void DXFtoQET3DB::update_proces(const QString &Waarde_receve1)
{
    ui->Procesing_dxf->setPlainText(Waarde_receve1);
	ui->Procesing_dxf->moveCursor(QTextCursor::End);
	ui->Procesing_dxf->repaint();
}

void DXFtoQET3DB::update_elmt(const QString &Waarde_receve2)
{
	ui->ELMT_Result->clear();
    //ui->ELMT_Result->setPlainText();
    ui->ELMT_Result->setPlainText(Waarde_receve2);
	ui->ELMT_Result->moveCursor(QTextCursor::End);
	ui->ELMT_Result->repaint();
}

void DXFtoQET3DB::update_log(const QString &Waarde_receve3)
{
	ui->dxf_log->appendPlainText(Waarde_receve3);
	ui->dxf_log->moveCursor(QTextCursor::End);
	ui->dxf_log->repaint();
}

void DXFtoQET3DB::on_Button_Open_DXF_clicked()
{

	ui->MainTab->setCurrentIndex(0);
	ui->MainTab->repaint();

	Filename_db=DXF_main_base[0].dxf_savepath + "/" +FileName;
	Filename_db.append(".db3");

	ui->dxf_line_count1_2->clear();
	ui->Processing_dxf_file_2->clear();
	ui->Processing_dxf_file_2->insert(FileName);

	on_Delete_DB_clicked();

	ui->dxf_log->activateWindow();

	Signal_log1.clear();
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("=> Start loading dxf");
	Signal_log1.append(FileName);
	Signal_log1.append(" file into SQLite DB tables \n");
	Signal_log1.append("Creating SQLite DB : ");
	Signal_log1.append(FileName);
	Signal_log1.append("\n");
	Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	Signal_log1.clear();
	Signal_log1.append("create : ");
	Signal_log1.append(Filename_db);

	emit send_log(Signal_log1);

	mydb.dbManager1(Filename_db);

	Signal_log1.clear();
	Signal_log1.append("creating tables \n");
	Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	connect (&mydb ,SIGNAL (send_log(const QString &)),this,SLOT(update_log(const QString &)));

	mydb.dbManager_create_tables(FileName);

	dxf_split_count1=DXF_main_base[0].dxf_input.count();

	counter1=0;

	Signal_log1.clear();
	Signal_log1.append("total characters : ");
	Signal_log1.append(QString::number(dxf_line_count1));
	Signal_log1.append("\n");
	Signal_log1.append("total lines : ");
	Signal_log1.append(QString::number(dxf_line_count2));
	Signal_log1.append("\n");
	Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);


	//DXF_main_base[0].dxf_input = DXF_main_base[0].dxf_text_all.split("\n");
	//DXF_main_base[0].dxf_line_count=DXF_main_base[0].dxf_input.count();

	emit send_text("dxf into SQLite DB");
	emit send_min(0);
	emit send_max(dxf_line_count2-1);


	mydb.dbManager_load_dxf_list(FileName);

	mydb.dbManager_transfer_dxf(FileName);


	mydb.dbManager_close(FileName);

	Signal_log1.clear();
	Signal_log1.append("End loading into db ");
	Signal_log1.append(QTime::currentTime().toString());
	Signal_log1.append("\n");
	Signal_log1.append("============================================================================");

	emit send_log(Signal_log1);

	dxf_split_count1=DXF_main_base[0].dxf_input.count();

	index_header= DXF_main_base[0].dxf_input.indexOf("HEADER");
	index_classes= DXF_main_base[0].dxf_input.indexOf("CLASSES");
	index_tables= DXF_main_base[0].dxf_input.indexOf("TABLES");
	index_blocks= DXF_main_base[0].dxf_input.indexOf("BLOCKS");
	index_entities= DXF_main_base[0].dxf_input.indexOf("ENTITIES");
	index_objects= DXF_main_base[0].dxf_input.indexOf("OBJECTS");
	index_thumbnailimage= DXF_main_base[0].dxf_input.indexOf("THUMBNAILIMAGE");

	Signal_log1.clear();
	Signal_log1.append("index header : ");
	Signal_log1.append(QString::number(index_header));
	Signal_log1.append("\n");
	Signal_log1.append("index classes : ");
	Signal_log1.append(QString::number(index_classes));
	Signal_log1.append("\n");
	Signal_log1.append("index tables : ");
	Signal_log1.append(QString::number(index_tables));
	Signal_log1.append("\n");
	Signal_log1.append("index blocks : ");
	Signal_log1.append(QString::number(index_blocks));
	Signal_log1.append("\n");
	Signal_log1.append("index entities : ");
	Signal_log1.append(QString::number(index_entities));
	Signal_log1.append("\n");
	Signal_log1.append("index objects : ");
	Signal_log1.append(QString::number(index_objects));
	Signal_log1.append("\n");
	Signal_log1.append("index thumbnailimage : ");
	Signal_log1.append(QString::number(index_thumbnailimage));
	Signal_log1.append("\n");
	Signal_log1.append("============================================================================");
	Signal_log1.append("\n");

	emit send_log(Signal_log1);

	section_lengts();

	copy_list();





	if (index_header!=-1)
	{
		Signal_log1.clear();
		Signal_log1.append("Splitting HEADER list ");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);



		db_split_header();

	}
	else
	{

		Signal_log1.clear();
		Signal_log1.append("no HEADER list to split ");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);
	}

	if (index_classes!=-1)
	{
		Signal_log1.clear();
		Signal_log1.append("Splitting CLASSES list ");
		Signal_log1.append(": disabled");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);

		//db_split_classes();
	}
	else
	{

		Signal_log1.clear();
		Signal_log1.append("no CLASSES list to split ");
		Signal_log1.append(": disabled");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);
	}

	if (index_tables!=-1)
	{
		Signal_log1.clear();
		Signal_log1.append("Splitting TABLES list ");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);

		db_split_tables();
	}
	else
	{

		Signal_log1.clear();
		Signal_log1.append("no TABLES list to split ");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);
	}


	if (index_blocks!=-1)
	{
		Signal_log1.clear();
		Signal_log1.append("Splitting BLOCKS list ");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);

		db_split_blocks();
	}
	else
	{

		Signal_log1.clear();
		Signal_log1.append("no BLOCKS list to split ");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);
	}


	if (index_entities!=-1)
	{
		Signal_log1.clear();
		Signal_log1.append("Splitting ENTITIES list ");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);

		db_split_entities();
	}
	else
	{

		Signal_log1.clear();
		Signal_log1.append("no ENTITIES list to split ");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);
	}

	if (index_objects!=-1)
	{
		Signal_log1.clear();
		Signal_log1.append("Splitting OBJECTS list ");
		Signal_log1.append(": disabled");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);

		//db_split_objects();

	}
	else
	{

		Signal_log1.clear();
		Signal_log1.append("no OBJECTS list to split ");
		Signal_log1.append(": disabled");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);
	}

	if (index_thumbnailimage!=-1)
	{
		Signal_log1.clear();
		Signal_log1.append("Splitting THUMBNAILIMAGE list ");
		Signal_log1.append(": disabled");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);

		//db_split_thumbnailimage();

	}
	else
	{

		Signal_log1.clear();
		Signal_log1.append("no THUMBNAILIMAGE list to split ");
		Signal_log1.append(": disabled");
		//Signal_log1.append("============================================================================");

		emit send_log(Signal_log1);
	}




	return;

}
