#include "dbmanager.h"
//#include "ui_dxftoqet3db.h"

extern struct DXF_codes DXF_code_tables[DXF_codes_set];
extern struct DXF_base DXF_main_base[DXF_base_set];

dbManager::dbManager(QWidget *parent) : QWidget(parent)
{
    /*connect (this ,SIGNAL (send_log(const QString &)),this,SLOT(update_log(const QString &)));
    connect (this, SIGNAL (send_elmt(const QString &)),this,SLOT(update_elmt(const QString &)));
    connect (this, SIGNAL (send_process(const QString &)),this,SLOT(update_proces(const QString &)));

    connect (this,SIGNAL(send_text(const QString &)),this,SLOT(on_progressBar_text(const QString &)));
    connect (this,SIGNAL(send_min(const int &)),this,SLOT(on_progressBar_valueMin(const int &)));
    connect (this,SIGNAL(send_max(const int &)),this,SLOT(on_progressBar_valueMax(const int &)));
    connect (this,SIGNAL(send_actual(const int &)),this,SLOT(on_progressBar_valueChanged(const int &)));*/
}

void dbManager::dbActivate(const QString &pathname)
{
    QString path = pathname;
    m_db=QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(pathname);

    if (!m_db.open())
    {
        /*QMessageBox::warning(this, tr("Application"),
                  tr("Error : connection with database fails"));*/
    }
    else
    {
        /*QMessageBox::warning(this, tr("Application"),
                  tr("Connection with database ok"));*/

        m_db.exec("PRAGMA temp_store = FILE");
        //m_db.exec("PRAGMA temp_store_directory = 'c:/temp/'");
        m_db.exec("PRAGMA journal_mode = MEMORY");
        m_db.exec("PRAGMA page_size = 4096");
        m_db.exec("PRAGMA cache_size = 16384");
        m_db.exec("PRAGMA locking_mode = EXCLUSIVE");
        m_db.exec("PRAGMA synchronous = OFF");
        //m_db.exec("PRAGMA journal_mode = OFF");
    }

}

void dbManager::dbManager1(const QString &pathname)
{
    m_db=QSqlDatabase::addDatabase("QSQLITE");
    //m_db.setDatabaseName(pathname);
    QString path = pathname;
    m_db.setDatabaseName(pathname);


    if (!m_db.open())
	{
		/*QMessageBox::warning(this, tr("Application"),
				  tr("Error : connection with database fails"));*/
    }
	else
	{
        /*QMessageBox::warning(this, tr("Application"),
                  tr("Connection with database ok"));*/
		
        m_db.exec("PRAGMA temp_store = FILE");
        //m_db.exec("PRAGMA temp_store_directory = 'c:/temp/'");
		m_db.exec("PRAGMA journal_mode = MEMORY");
		m_db.exec("PRAGMA page_size = 4096");
		m_db.exec("PRAGMA cache_size = 16384");
		m_db.exec("PRAGMA locking_mode = EXCLUSIVE");
		m_db.exec("PRAGMA synchronous = OFF");
        //m_db.exec("PRAGMA journal_mode = OFF");
    }

}

void dbManager::dbManager_close(const QString &pathname)
{
    QString path = pathname;
	if (m_db.isOpen())
	{
		m_db.close();

        //m_db.removeDatabase("QSQLITE");
	}

}

void dbManager::dbManager_create_tables(const QString &pathname)
{
    QString path = pathname;
	QsqlString="create table dxf_list (Index_count primary key, Code)";

	m_db.exec(QsqlString);

	QsqlString="create table dxf_file (Index_count primary key, Code, Waarde, Section, Commando, AcadValue )";

	m_db.exec(QsqlString);

	QsqlString="create table elmt_blocks (Index_count primary key,Block_Naam, Block_value)";

	m_db.exec(QsqlString);

	QsqlString="create table elmt_entities (Index_count primary key,Block_Naam, Block_value)";

	m_db.exec(QsqlString);

	QsqlString="create table dxf_header (Index_count primary key,Section";
	QsqlString.append(", dxfbase, Command, ID_instruction, Command_count");
	QsqlString.append(", dxf_m1, dxf_m2, dxf_m3, dxf_m4, dxf_m5");
	QsqlString.append(", dxf_0, dxf_1, dxf_2, dxf_3, dxf_4, dxf_5, dxf_6, dxf_7, dxf_8, dxf_9");
	QsqlString.append(", dxf_10, dxf_11, dxf_12, dxf_13, dxf_14, dxf_15, dxf_16, dxf_17, dxf_18, dxf_19");
	QsqlString.append(", dxf_20, dxf_21, dxf_22, dxf_23, dxf_24, dxf_25, dxf_26, dxf_27, dxf_28, dxf_29");
	QsqlString.append(", dxf_30, dxf_31, dxf_32, dxf_33, dxf_34, dxf_35, dxf_36, dxf_37, dxf_38, dxf_39");
	QsqlString.append(", dxf_40, dxf_41, dxf_42, dxf_43, dxf_44, dxf_45, dxf_46, dxf_47, dxf_48, dxf_49");
	QsqlString.append(", dxf_50, dxf_51, dxf_52, dxf_53, dxf_54, dxf_55, dxf_56, dxf_57, dxf_58, dxf_59");
	QsqlString.append(", dxf_60, dxf_61, dxf_62, dxf_63, dxf_64, dxf_65, dxf_66, dxf_67, dxf_68, dxf_69");
	QsqlString.append(", dxf_70, dxf_71, dxf_72, dxf_73, dxf_74, dxf_75, dxf_76, dxf_77, dxf_78, dxf_79");
	QsqlString.append(", dxf_90, dxf_91, dxf_92, dxf_93, dxf_94, dxf_95, dxf_96, dxf_97, dxf_98, dxf_99");
	QsqlString.append(", dxf_100, dxf_102, dxf_105");
	QsqlString.append(", dxf_110, dxf_111, dxf_112, dxf_113, dxf_114, dxf_115, dxf_116, dxf_117, dxf_118, dxf_119");
	QsqlString.append(", dxf_120, dxf_121, dxf_122, dxf_123, dxf_124, dxf_125, dxf_126, dxf_127, dxf_128, dxf_129");
	QsqlString.append(", dxf_130, dxf_131, dxf_132, dxf_133, dxf_134, dxf_135, dxf_136, dxf_137, dxf_138, dxf_139");
	QsqlString.append(", dxf_140, dxf_141, dxf_142, dxf_143, dxf_144, dxf_145, dxf_146, dxf_147, dxf_148, dxf_149");

	QsqlString.append(", dxf_160, dxf_161, dxf_162, dxf_163, dxf_164, dxf_165, dxf_166, dxf_167, dxf_168, dxf_169");
	QsqlString.append(", dxf_170, dxf_171, dxf_172, dxf_173, dxf_174, dxf_175, dxf_176, dxf_177, dxf_178, dxf_179");

	QsqlString.append(", dxf_210, dxf_211, dxf_212, dxf_213, dxf_214, dxf_215, dxf_216, dxf_217, dxf_218, dxf_219");
	QsqlString.append(", dxf_220, dxf_221, dxf_222, dxf_223, dxf_224, dxf_225, dxf_226, dxf_227, dxf_228, dxf_229");
	QsqlString.append(", dxf_230, dxf_231, dxf_232, dxf_233, dxf_234, dxf_235, dxf_236, dxf_237, dxf_238, dxf_239");

	QsqlString.append(", dxf_270, dxf_271, dxf_272, dxf_273, dxf_274, dxf_275, dxf_276, dxf_277, dxf_278, dxf_279");
	QsqlString.append(", dxf_280, dxf_281, dxf_282, dxf_283, dxf_284, dxf_285, dxf_286, dxf_287, dxf_288, dxf_289");
	QsqlString.append(", dxf_290, dxf_291, dxf_292, dxf_293, dxf_294, dxf_295, dxf_296, dxf_297, dxf_298, dxf_299");
	QsqlString.append(", dxf_300, dxf_301, dxf_302, dxf_303, dxf_304, dxf_305, dxf_306, dxf_307, dxf_308, dxf_309");
	QsqlString.append(", dxf_310, dxf_311, dxf_312, dxf_313, dxf_314, dxf_315, dxf_316, dxf_317, dxf_318, dxf_319");
	QsqlString.append(", dxf_320, dxf_321, dxf_322, dxf_323, dxf_324, dxf_325, dxf_326, dxf_327, dxf_328, dxf_329");
	QsqlString.append(", dxf_330, dxf_331, dxf_332, dxf_333, dxf_334, dxf_335, dxf_336, dxf_337, dxf_338, dxf_339");
	QsqlString.append(", dxf_340, dxf_341, dxf_342, dxf_343, dxf_344, dxf_345, dxf_346, dxf_347, dxf_348, dxf_349");
	QsqlString.append(", dxf_350, dxf_351, dxf_352, dxf_353, dxf_354, dxf_355, dxf_356, dxf_357, dxf_358, dxf_359");
	QsqlString.append(", dxf_360, dxf_361, dxf_362, dxf_363, dxf_364, dxf_365, dxf_366, dxf_367, dxf_368, dxf_369");
	QsqlString.append(", dxf_370, dxf_371, dxf_372, dxf_373, dxf_374, dxf_375, dxf_376, dxf_377, dxf_378, dxf_379");
	QsqlString.append(", dxf_380, dxf_381, dxf_382, dxf_383, dxf_384, dxf_385, dxf_386, dxf_387, dxf_388, dxf_389");
	QsqlString.append(", dxf_390, dxf_391, dxf_392, dxf_393, dxf_394, dxf_395, dxf_396, dxf_397, dxf_398, dxf_399");
	QsqlString.append(", dxf_400, dxf_401, dxf_402, dxf_403, dxf_404, dxf_405, dxf_406, dxf_407, dxf_408, dxf_409");
	QsqlString.append(", dxf_410, dxf_411, dxf_412, dxf_413, dxf_414, dxf_415, dxf_416, dxf_417, dxf_418, dxf_419");
	QsqlString.append(", dxf_420, dxf_421, dxf_422, dxf_423, dxf_424, dxf_425, dxf_426, dxf_427, dxf_428, dxf_429");
	QsqlString.append(", dxf_430, dxf_431, dxf_432, dxf_433, dxf_434, dxf_435, dxf_436, dxf_437, dxf_438, dxf_439");
	QsqlString.append(", dxf_440, dxf_441, dxf_442, dxf_443, dxf_444, dxf_445, dxf_446, dxf_447, dxf_448, dxf_449");
	QsqlString.append(", dxf_450, dxf_451, dxf_452, dxf_453, dxf_454, dxf_455, dxf_456, dxf_457, dxf_458, dxf_459");
	QsqlString.append(", dxf_460, dxf_461, dxf_462, dxf_463, dxf_464, dxf_465, dxf_466, dxf_467, dxf_468, dxf_469");
	QsqlString.append(", dxf_470, dxf_471, dxf_472, dxf_473, dxf_474, dxf_475, dxf_476, dxf_477, dxf_478, dxf_479");
	QsqlString.append(", dxf_480, dxf_481, dxf_482, dxf_483, dxf_484, dxf_485, dxf_486, dxf_487, dxf_488, dxf_489");
	QsqlString.append(", dxf_999");
	QsqlString.append(", dxf_1000, dxf_1001, dxf_1002, dxf_1003, dxf_1004, dxf_1005, dxf_1006, dxf_1007, dxf_1008, dxf_1009");
	QsqlString.append(", dxf_1010, dxf_1011, dxf_1012, dxf_1013, dxf_1014, dxf_1015, dxf_1016, dxf_1017, dxf_1018, dxf_1019");
	QsqlString.append(", dxf_1020, dxf_1021, dxf_1022, dxf_1023, dxf_1024, dxf_1025, dxf_1026, dxf_1027, dxf_1028, dxf_1029");
	QsqlString.append(", dxf_1030, dxf_1031, dxf_1032, dxf_1033, dxf_1034, dxf_1035, dxf_1036, dxf_1037, dxf_1038, dxf_1039");
	QsqlString.append(", dxf_1040, dxf_1041, dxf_1042, dxf_1043, dxf_1044, dxf_1045, dxf_1046, dxf_1047, dxf_1048, dxf_1049");
	QsqlString.append(", dxf_1050, dxf_1051, dxf_1052, dxf_1053, dxf_1054, dxf_1055, dxf_1056, dxf_1057, dxf_1058, dxf_1059");
	QsqlString.append(", dxf_1060, dxf_1061, dxf_1062, dxf_1063, dxf_1064, dxf_1065, dxf_1066, dxf_1067, dxf_1068, dxf_1069");
	QsqlString.append(", dxf_1070, dxf_1071");


	QsqlString.append(")");

	m_db.exec(QsqlString);


	QsqlString="create table dxf_classes (Index_count primary key,Section";
	QsqlString.append(", dxfbase, Command, ID_instruction, Command_count");
	QsqlString.append(", dxf_m1, dxf_m2, dxf_m3, dxf_m4, dxf_m5");
	QsqlString.append(", dxf_0, dxf_1, dxf_2, dxf_3, dxf_4, dxf_5, dxf_6, dxf_7, dxf_8, dxf_9");
	QsqlString.append(", dxf_10, dxf_11, dxf_12, dxf_13, dxf_14, dxf_15, dxf_16, dxf_17, dxf_18, dxf_19");
	QsqlString.append(", dxf_20, dxf_21, dxf_22, dxf_23, dxf_24, dxf_25, dxf_26, dxf_27, dxf_28, dxf_29");
	QsqlString.append(", dxf_30, dxf_31, dxf_32, dxf_33, dxf_34, dxf_35, dxf_36, dxf_37, dxf_38, dxf_39");
	QsqlString.append(", dxf_40, dxf_41, dxf_42, dxf_43, dxf_44, dxf_45, dxf_46, dxf_47, dxf_48, dxf_49");
	QsqlString.append(", dxf_50, dxf_51, dxf_52, dxf_53, dxf_54, dxf_55, dxf_56, dxf_57, dxf_58, dxf_59");
	QsqlString.append(", dxf_60, dxf_61, dxf_62, dxf_63, dxf_64, dxf_65, dxf_66, dxf_67, dxf_68, dxf_69");
	QsqlString.append(", dxf_70, dxf_71, dxf_72, dxf_73, dxf_74, dxf_75, dxf_76, dxf_77, dxf_78, dxf_79");
	QsqlString.append(", dxf_90, dxf_91, dxf_92, dxf_93, dxf_94, dxf_95, dxf_96, dxf_97, dxf_98, dxf_99");
	QsqlString.append(", dxf_100, dxf_102, dxf_105");
	QsqlString.append(", dxf_110, dxf_111, dxf_112, dxf_113, dxf_114, dxf_115, dxf_116, dxf_117, dxf_118, dxf_119");
	QsqlString.append(", dxf_120, dxf_121, dxf_122, dxf_123, dxf_124, dxf_125, dxf_126, dxf_127, dxf_128, dxf_129");
	QsqlString.append(", dxf_130, dxf_131, dxf_132, dxf_133, dxf_134, dxf_135, dxf_136, dxf_137, dxf_138, dxf_139");
	QsqlString.append(", dxf_140, dxf_141, dxf_142, dxf_143, dxf_144, dxf_145, dxf_146, dxf_147, dxf_148, dxf_149");

	QsqlString.append(", dxf_160, dxf_161, dxf_162, dxf_163, dxf_164, dxf_165, dxf_166, dxf_167, dxf_168, dxf_169");
	QsqlString.append(", dxf_170, dxf_171, dxf_172, dxf_173, dxf_174, dxf_175, dxf_176, dxf_177, dxf_178, dxf_179");

	QsqlString.append(", dxf_210, dxf_211, dxf_212, dxf_213, dxf_214, dxf_215, dxf_216, dxf_217, dxf_218, dxf_219");
	QsqlString.append(", dxf_220, dxf_221, dxf_222, dxf_223, dxf_224, dxf_225, dxf_226, dxf_227, dxf_228, dxf_229");
	QsqlString.append(", dxf_230, dxf_231, dxf_232, dxf_233, dxf_234, dxf_235, dxf_236, dxf_237, dxf_238, dxf_239");

	QsqlString.append(", dxf_270, dxf_271, dxf_272, dxf_273, dxf_274, dxf_275, dxf_276, dxf_277, dxf_278, dxf_279");
	QsqlString.append(", dxf_280, dxf_281, dxf_282, dxf_283, dxf_284, dxf_285, dxf_286, dxf_287, dxf_288, dxf_289");
	QsqlString.append(", dxf_290, dxf_291, dxf_292, dxf_293, dxf_294, dxf_295, dxf_296, dxf_297, dxf_298, dxf_299");
	QsqlString.append(", dxf_300, dxf_301, dxf_302, dxf_303, dxf_304, dxf_305, dxf_306, dxf_307, dxf_308, dxf_309");
	QsqlString.append(", dxf_310, dxf_311, dxf_312, dxf_313, dxf_314, dxf_315, dxf_316, dxf_317, dxf_318, dxf_319");
	QsqlString.append(", dxf_320, dxf_321, dxf_322, dxf_323, dxf_324, dxf_325, dxf_326, dxf_327, dxf_328, dxf_329");
	QsqlString.append(", dxf_330, dxf_331, dxf_332, dxf_333, dxf_334, dxf_335, dxf_336, dxf_337, dxf_338, dxf_339");
	QsqlString.append(", dxf_340, dxf_341, dxf_342, dxf_343, dxf_344, dxf_345, dxf_346, dxf_347, dxf_348, dxf_349");
	QsqlString.append(", dxf_350, dxf_351, dxf_352, dxf_353, dxf_354, dxf_355, dxf_356, dxf_357, dxf_358, dxf_359");
	QsqlString.append(", dxf_360, dxf_361, dxf_362, dxf_363, dxf_364, dxf_365, dxf_366, dxf_367, dxf_368, dxf_369");
	QsqlString.append(", dxf_370, dxf_371, dxf_372, dxf_373, dxf_374, dxf_375, dxf_376, dxf_377, dxf_378, dxf_379");
	QsqlString.append(", dxf_380, dxf_381, dxf_382, dxf_383, dxf_384, dxf_385, dxf_386, dxf_387, dxf_388, dxf_389");
	QsqlString.append(", dxf_390, dxf_391, dxf_392, dxf_393, dxf_394, dxf_395, dxf_396, dxf_397, dxf_398, dxf_399");
	QsqlString.append(", dxf_400, dxf_401, dxf_402, dxf_403, dxf_404, dxf_405, dxf_406, dxf_407, dxf_408, dxf_409");
	QsqlString.append(", dxf_410, dxf_411, dxf_412, dxf_413, dxf_414, dxf_415, dxf_416, dxf_417, dxf_418, dxf_419");
	QsqlString.append(", dxf_420, dxf_421, dxf_422, dxf_423, dxf_424, dxf_425, dxf_426, dxf_427, dxf_428, dxf_429");
	QsqlString.append(", dxf_430, dxf_431, dxf_432, dxf_433, dxf_434, dxf_435, dxf_436, dxf_437, dxf_438, dxf_439");
	QsqlString.append(", dxf_440, dxf_441, dxf_442, dxf_443, dxf_444, dxf_445, dxf_446, dxf_447, dxf_448, dxf_449");
	QsqlString.append(", dxf_450, dxf_451, dxf_452, dxf_453, dxf_454, dxf_455, dxf_456, dxf_457, dxf_458, dxf_459");
	QsqlString.append(", dxf_460, dxf_461, dxf_462, dxf_463, dxf_464, dxf_465, dxf_466, dxf_467, dxf_468, dxf_469");
	QsqlString.append(", dxf_470, dxf_471, dxf_472, dxf_473, dxf_474, dxf_475, dxf_476, dxf_477, dxf_478, dxf_479");
	QsqlString.append(", dxf_480, dxf_481, dxf_482, dxf_483, dxf_484, dxf_485, dxf_486, dxf_487, dxf_488, dxf_489");
	QsqlString.append(", dxf_999");
	QsqlString.append(", dxf_1000, dxf_1001, dxf_1002, dxf_1003, dxf_1004, dxf_1005, dxf_1006, dxf_1007, dxf_1008, dxf_1009");
	QsqlString.append(", dxf_1010, dxf_1011, dxf_1012, dxf_1013, dxf_1014, dxf_1015, dxf_1016, dxf_1017, dxf_1018, dxf_1019");
	QsqlString.append(", dxf_1020, dxf_1021, dxf_1022, dxf_1023, dxf_1024, dxf_1025, dxf_1026, dxf_1027, dxf_1028, dxf_1029");
	QsqlString.append(", dxf_1030, dxf_1031, dxf_1032, dxf_1033, dxf_1034, dxf_1035, dxf_1036, dxf_1037, dxf_1038, dxf_1039");
	QsqlString.append(", dxf_1040, dxf_1041, dxf_1042, dxf_1043, dxf_1044, dxf_1045, dxf_1046, dxf_1047, dxf_1048, dxf_1049");
	QsqlString.append(", dxf_1050, dxf_1051, dxf_1052, dxf_1053, dxf_1054, dxf_1055, dxf_1056, dxf_1057, dxf_1058, dxf_1059");
	QsqlString.append(", dxf_1060, dxf_1061, dxf_1062, dxf_1063, dxf_1064, dxf_1065, dxf_1066, dxf_1067, dxf_1068, dxf_1069");
	QsqlString.append(", dxf_1070, dxf_1071");


	QsqlString.append(")");

	m_db.exec(QsqlString);

	QsqlString="create table dxf_tables (Index_count primary key,Section";
	QsqlString.append(", dxfbase, Command, ID_instruction, Command_count");
	QsqlString.append(", dxf_m1, dxf_m2, dxf_m3, dxf_m4, dxf_m5");
	QsqlString.append(", dxf_0, dxf_1, dxf_2, dxf_3, dxf_4, dxf_5, dxf_6, dxf_7, dxf_8, dxf_9");
	QsqlString.append(", dxf_10, dxf_11, dxf_12, dxf_13, dxf_14, dxf_15, dxf_16, dxf_17, dxf_18, dxf_19");
	QsqlString.append(", dxf_20, dxf_21, dxf_22, dxf_23, dxf_24, dxf_25, dxf_26, dxf_27, dxf_28, dxf_29");
	QsqlString.append(", dxf_30, dxf_31, dxf_32, dxf_33, dxf_34, dxf_35, dxf_36, dxf_37, dxf_38, dxf_39");
	QsqlString.append(", dxf_40, dxf_41, dxf_42, dxf_43, dxf_44, dxf_45, dxf_46, dxf_47, dxf_48, dxf_49");
	QsqlString.append(", dxf_50, dxf_51, dxf_52, dxf_53, dxf_54, dxf_55, dxf_56, dxf_57, dxf_58, dxf_59");
	QsqlString.append(", dxf_60, dxf_61, dxf_62, dxf_63, dxf_64, dxf_65, dxf_66, dxf_67, dxf_68, dxf_69");
	QsqlString.append(", dxf_70, dxf_71, dxf_72, dxf_73, dxf_74, dxf_75, dxf_76, dxf_77, dxf_78, dxf_79");
	QsqlString.append(", dxf_90, dxf_91, dxf_92, dxf_93, dxf_94, dxf_95, dxf_96, dxf_97, dxf_98, dxf_99");
	QsqlString.append(", dxf_100, dxf_102, dxf_105");
	QsqlString.append(", dxf_110, dxf_111, dxf_112, dxf_113, dxf_114, dxf_115, dxf_116, dxf_117, dxf_118, dxf_119");
	QsqlString.append(", dxf_120, dxf_121, dxf_122, dxf_123, dxf_124, dxf_125, dxf_126, dxf_127, dxf_128, dxf_129");
	QsqlString.append(", dxf_130, dxf_131, dxf_132, dxf_133, dxf_134, dxf_135, dxf_136, dxf_137, dxf_138, dxf_139");
	QsqlString.append(", dxf_140, dxf_141, dxf_142, dxf_143, dxf_144, dxf_145, dxf_146, dxf_147, dxf_148, dxf_149");

	QsqlString.append(", dxf_160, dxf_161, dxf_162, dxf_163, dxf_164, dxf_165, dxf_166, dxf_167, dxf_168, dxf_169");
	QsqlString.append(", dxf_170, dxf_171, dxf_172, dxf_173, dxf_174, dxf_175, dxf_176, dxf_177, dxf_178, dxf_179");

	QsqlString.append(", dxf_210, dxf_211, dxf_212, dxf_213, dxf_214, dxf_215, dxf_216, dxf_217, dxf_218, dxf_219");
	QsqlString.append(", dxf_220, dxf_221, dxf_222, dxf_223, dxf_224, dxf_225, dxf_226, dxf_227, dxf_228, dxf_229");
	QsqlString.append(", dxf_230, dxf_231, dxf_232, dxf_233, dxf_234, dxf_235, dxf_236, dxf_237, dxf_238, dxf_239");

	QsqlString.append(", dxf_270, dxf_271, dxf_272, dxf_273, dxf_274, dxf_275, dxf_276, dxf_277, dxf_278, dxf_279");
	QsqlString.append(", dxf_280, dxf_281, dxf_282, dxf_283, dxf_284, dxf_285, dxf_286, dxf_287, dxf_288, dxf_289");
	QsqlString.append(", dxf_290, dxf_291, dxf_292, dxf_293, dxf_294, dxf_295, dxf_296, dxf_297, dxf_298, dxf_299");
	QsqlString.append(", dxf_300, dxf_301, dxf_302, dxf_303, dxf_304, dxf_305, dxf_306, dxf_307, dxf_308, dxf_309");
	QsqlString.append(", dxf_310, dxf_311, dxf_312, dxf_313, dxf_314, dxf_315, dxf_316, dxf_317, dxf_318, dxf_319");
	QsqlString.append(", dxf_320, dxf_321, dxf_322, dxf_323, dxf_324, dxf_325, dxf_326, dxf_327, dxf_328, dxf_329");
	QsqlString.append(", dxf_330, dxf_331, dxf_332, dxf_333, dxf_334, dxf_335, dxf_336, dxf_337, dxf_338, dxf_339");
	QsqlString.append(", dxf_340, dxf_341, dxf_342, dxf_343, dxf_344, dxf_345, dxf_346, dxf_347, dxf_348, dxf_349");
	QsqlString.append(", dxf_350, dxf_351, dxf_352, dxf_353, dxf_354, dxf_355, dxf_356, dxf_357, dxf_358, dxf_359");
	QsqlString.append(", dxf_360, dxf_361, dxf_362, dxf_363, dxf_364, dxf_365, dxf_366, dxf_367, dxf_368, dxf_369");
	QsqlString.append(", dxf_370, dxf_371, dxf_372, dxf_373, dxf_374, dxf_375, dxf_376, dxf_377, dxf_378, dxf_379");
	QsqlString.append(", dxf_380, dxf_381, dxf_382, dxf_383, dxf_384, dxf_385, dxf_386, dxf_387, dxf_388, dxf_389");
	QsqlString.append(", dxf_390, dxf_391, dxf_392, dxf_393, dxf_394, dxf_395, dxf_396, dxf_397, dxf_398, dxf_399");
	QsqlString.append(", dxf_400, dxf_401, dxf_402, dxf_403, dxf_404, dxf_405, dxf_406, dxf_407, dxf_408, dxf_409");
	QsqlString.append(", dxf_410, dxf_411, dxf_412, dxf_413, dxf_414, dxf_415, dxf_416, dxf_417, dxf_418, dxf_419");
	QsqlString.append(", dxf_420, dxf_421, dxf_422, dxf_423, dxf_424, dxf_425, dxf_426, dxf_427, dxf_428, dxf_429");
	QsqlString.append(", dxf_430, dxf_431, dxf_432, dxf_433, dxf_434, dxf_435, dxf_436, dxf_437, dxf_438, dxf_439");
	QsqlString.append(", dxf_440, dxf_441, dxf_442, dxf_443, dxf_444, dxf_445, dxf_446, dxf_447, dxf_448, dxf_449");
	QsqlString.append(", dxf_450, dxf_451, dxf_452, dxf_453, dxf_454, dxf_455, dxf_456, dxf_457, dxf_458, dxf_459");
	QsqlString.append(", dxf_460, dxf_461, dxf_462, dxf_463, dxf_464, dxf_465, dxf_466, dxf_467, dxf_468, dxf_469");
	QsqlString.append(", dxf_470, dxf_471, dxf_472, dxf_473, dxf_474, dxf_475, dxf_476, dxf_477, dxf_478, dxf_479");
	QsqlString.append(", dxf_480, dxf_481, dxf_482, dxf_483, dxf_484, dxf_485, dxf_486, dxf_487, dxf_488, dxf_489");
	QsqlString.append(", dxf_999");
	QsqlString.append(", dxf_1000, dxf_1001, dxf_1002, dxf_1003, dxf_1004, dxf_1005, dxf_1006, dxf_1007, dxf_1008, dxf_1009");
	QsqlString.append(", dxf_1010, dxf_1011, dxf_1012, dxf_1013, dxf_1014, dxf_1015, dxf_1016, dxf_1017, dxf_1018, dxf_1019");
	QsqlString.append(", dxf_1020, dxf_1021, dxf_1022, dxf_1023, dxf_1024, dxf_1025, dxf_1026, dxf_1027, dxf_1028, dxf_1029");
	QsqlString.append(", dxf_1030, dxf_1031, dxf_1032, dxf_1033, dxf_1034, dxf_1035, dxf_1036, dxf_1037, dxf_1038, dxf_1039");
	QsqlString.append(", dxf_1040, dxf_1041, dxf_1042, dxf_1043, dxf_1044, dxf_1045, dxf_1046, dxf_1047, dxf_1048, dxf_1049");
	QsqlString.append(", dxf_1050, dxf_1051, dxf_1052, dxf_1053, dxf_1054, dxf_1055, dxf_1056, dxf_1057, dxf_1058, dxf_1059");
	QsqlString.append(", dxf_1060, dxf_1061, dxf_1062, dxf_1063, dxf_1064, dxf_1065, dxf_1066, dxf_1067, dxf_1068, dxf_1069");
	QsqlString.append(", dxf_1070, dxf_1071");


	QsqlString.append(")");

	m_db.exec(QsqlString);

	QsqlString="create table dxf_blocks (Index_count primary key,Section";
	QsqlString.append(", dxfbase, Command, ID_instruction, Command_count");
	QsqlString.append(", dxf_m1, dxf_m2, dxf_m3, dxf_m4, dxf_m5");
	QsqlString.append(", dxf_0, dxf_1, dxf_2, dxf_3, dxf_4, dxf_5, dxf_6, dxf_7, dxf_8, dxf_9");
	QsqlString.append(", dxf_10, dxf_11, dxf_12, dxf_13, dxf_14, dxf_15, dxf_16, dxf_17, dxf_18, dxf_19");
	QsqlString.append(", dxf_20, dxf_21, dxf_22, dxf_23, dxf_24, dxf_25, dxf_26, dxf_27, dxf_28, dxf_29");
	QsqlString.append(", dxf_30, dxf_31, dxf_32, dxf_33, dxf_34, dxf_35, dxf_36, dxf_37, dxf_38, dxf_39");
	QsqlString.append(", dxf_40, dxf_41, dxf_42, dxf_43, dxf_44, dxf_45, dxf_46, dxf_47, dxf_48, dxf_49");
	QsqlString.append(", dxf_50, dxf_51, dxf_52, dxf_53, dxf_54, dxf_55, dxf_56, dxf_57, dxf_58, dxf_59");
	QsqlString.append(", dxf_60, dxf_61, dxf_62, dxf_63, dxf_64, dxf_65, dxf_66, dxf_67, dxf_68, dxf_69");
	QsqlString.append(", dxf_70, dxf_71, dxf_72, dxf_73, dxf_74, dxf_75, dxf_76, dxf_77, dxf_78, dxf_79");
	QsqlString.append(", dxf_90, dxf_91, dxf_92, dxf_93, dxf_94, dxf_95, dxf_96, dxf_97, dxf_98, dxf_99");
	QsqlString.append(", dxf_100, dxf_102, dxf_105");
	QsqlString.append(", dxf_110, dxf_111, dxf_112, dxf_113, dxf_114, dxf_115, dxf_116, dxf_117, dxf_118, dxf_119");
	QsqlString.append(", dxf_120, dxf_121, dxf_122, dxf_123, dxf_124, dxf_125, dxf_126, dxf_127, dxf_128, dxf_129");
	QsqlString.append(", dxf_130, dxf_131, dxf_132, dxf_133, dxf_134, dxf_135, dxf_136, dxf_137, dxf_138, dxf_139");
	QsqlString.append(", dxf_140, dxf_141, dxf_142, dxf_143, dxf_144, dxf_145, dxf_146, dxf_147, dxf_148, dxf_149");

	QsqlString.append(", dxf_160, dxf_161, dxf_162, dxf_163, dxf_164, dxf_165, dxf_166, dxf_167, dxf_168, dxf_169");
	QsqlString.append(", dxf_170, dxf_171, dxf_172, dxf_173, dxf_174, dxf_175, dxf_176, dxf_177, dxf_178, dxf_179");

	QsqlString.append(", dxf_210, dxf_211, dxf_212, dxf_213, dxf_214, dxf_215, dxf_216, dxf_217, dxf_218, dxf_219");
	QsqlString.append(", dxf_220, dxf_221, dxf_222, dxf_223, dxf_224, dxf_225, dxf_226, dxf_227, dxf_228, dxf_229");
	QsqlString.append(", dxf_230, dxf_231, dxf_232, dxf_233, dxf_234, dxf_235, dxf_236, dxf_237, dxf_238, dxf_239");

	QsqlString.append(", dxf_270, dxf_271, dxf_272, dxf_273, dxf_274, dxf_275, dxf_276, dxf_277, dxf_278, dxf_279");
	QsqlString.append(", dxf_280, dxf_281, dxf_282, dxf_283, dxf_284, dxf_285, dxf_286, dxf_287, dxf_288, dxf_289");
	QsqlString.append(", dxf_290, dxf_291, dxf_292, dxf_293, dxf_294, dxf_295, dxf_296, dxf_297, dxf_298, dxf_299");
	QsqlString.append(", dxf_300, dxf_301, dxf_302, dxf_303, dxf_304, dxf_305, dxf_306, dxf_307, dxf_308, dxf_309");
	QsqlString.append(", dxf_310, dxf_311, dxf_312, dxf_313, dxf_314, dxf_315, dxf_316, dxf_317, dxf_318, dxf_319");
	QsqlString.append(", dxf_320, dxf_321, dxf_322, dxf_323, dxf_324, dxf_325, dxf_326, dxf_327, dxf_328, dxf_329");
	QsqlString.append(", dxf_330, dxf_331, dxf_332, dxf_333, dxf_334, dxf_335, dxf_336, dxf_337, dxf_338, dxf_339");
	QsqlString.append(", dxf_340, dxf_341, dxf_342, dxf_343, dxf_344, dxf_345, dxf_346, dxf_347, dxf_348, dxf_349");
	QsqlString.append(", dxf_350, dxf_351, dxf_352, dxf_353, dxf_354, dxf_355, dxf_356, dxf_357, dxf_358, dxf_359");
	QsqlString.append(", dxf_360, dxf_361, dxf_362, dxf_363, dxf_364, dxf_365, dxf_366, dxf_367, dxf_368, dxf_369");
	QsqlString.append(", dxf_370, dxf_371, dxf_372, dxf_373, dxf_374, dxf_375, dxf_376, dxf_377, dxf_378, dxf_379");
	QsqlString.append(", dxf_380, dxf_381, dxf_382, dxf_383, dxf_384, dxf_385, dxf_386, dxf_387, dxf_388, dxf_389");
	QsqlString.append(", dxf_390, dxf_391, dxf_392, dxf_393, dxf_394, dxf_395, dxf_396, dxf_397, dxf_398, dxf_399");
	QsqlString.append(", dxf_400, dxf_401, dxf_402, dxf_403, dxf_404, dxf_405, dxf_406, dxf_407, dxf_408, dxf_409");
	QsqlString.append(", dxf_410, dxf_411, dxf_412, dxf_413, dxf_414, dxf_415, dxf_416, dxf_417, dxf_418, dxf_419");
	QsqlString.append(", dxf_420, dxf_421, dxf_422, dxf_423, dxf_424, dxf_425, dxf_426, dxf_427, dxf_428, dxf_429");
	QsqlString.append(", dxf_430, dxf_431, dxf_432, dxf_433, dxf_434, dxf_435, dxf_436, dxf_437, dxf_438, dxf_439");
	QsqlString.append(", dxf_440, dxf_441, dxf_442, dxf_443, dxf_444, dxf_445, dxf_446, dxf_447, dxf_448, dxf_449");
	QsqlString.append(", dxf_450, dxf_451, dxf_452, dxf_453, dxf_454, dxf_455, dxf_456, dxf_457, dxf_458, dxf_459");
	QsqlString.append(", dxf_460, dxf_461, dxf_462, dxf_463, dxf_464, dxf_465, dxf_466, dxf_467, dxf_468, dxf_469");
	QsqlString.append(", dxf_470, dxf_471, dxf_472, dxf_473, dxf_474, dxf_475, dxf_476, dxf_477, dxf_478, dxf_479");
	QsqlString.append(", dxf_480, dxf_481, dxf_482, dxf_483, dxf_484, dxf_485, dxf_486, dxf_487, dxf_488, dxf_489");
	QsqlString.append(", dxf_999");
	QsqlString.append(", dxf_1000, dxf_1001, dxf_1002, dxf_1003, dxf_1004, dxf_1005, dxf_1006, dxf_1007, dxf_1008, dxf_1009");
	QsqlString.append(", dxf_1010, dxf_1011, dxf_1012, dxf_1013, dxf_1014, dxf_1015, dxf_1016, dxf_1017, dxf_1018, dxf_1019");
	QsqlString.append(", dxf_1020, dxf_1021, dxf_1022, dxf_1023, dxf_1024, dxf_1025, dxf_1026, dxf_1027, dxf_1028, dxf_1029");
	QsqlString.append(", dxf_1030, dxf_1031, dxf_1032, dxf_1033, dxf_1034, dxf_1035, dxf_1036, dxf_1037, dxf_1038, dxf_1039");
	QsqlString.append(", dxf_1040, dxf_1041, dxf_1042, dxf_1043, dxf_1044, dxf_1045, dxf_1046, dxf_1047, dxf_1048, dxf_1049");
	QsqlString.append(", dxf_1050, dxf_1051, dxf_1052, dxf_1053, dxf_1054, dxf_1055, dxf_1056, dxf_1057, dxf_1058, dxf_1059");
	QsqlString.append(", dxf_1060, dxf_1061, dxf_1062, dxf_1063, dxf_1064, dxf_1065, dxf_1066, dxf_1067, dxf_1068, dxf_1069");
	QsqlString.append(", dxf_1070, dxf_1071");


	QsqlString.append(")");

	m_db.exec(QsqlString);

	QsqlString="create table dxf_entities (Index_count primary key,Section";
	QsqlString.append(", dxfbase, Command, ID_instruction, Command_count");
	QsqlString.append(", dxf_m1, dxf_m2, dxf_m3, dxf_m4, dxf_m5");
	QsqlString.append(", dxf_0, dxf_1, dxf_2, dxf_3, dxf_4, dxf_5, dxf_6, dxf_7, dxf_8, dxf_9");
	QsqlString.append(", dxf_10, dxf_11, dxf_12, dxf_13, dxf_14, dxf_15, dxf_16, dxf_17, dxf_18, dxf_19");
	QsqlString.append(", dxf_20, dxf_21, dxf_22, dxf_23, dxf_24, dxf_25, dxf_26, dxf_27, dxf_28, dxf_29");
	QsqlString.append(", dxf_30, dxf_31, dxf_32, dxf_33, dxf_34, dxf_35, dxf_36, dxf_37, dxf_38, dxf_39");
	QsqlString.append(", dxf_40, dxf_41, dxf_42, dxf_43, dxf_44, dxf_45, dxf_46, dxf_47, dxf_48, dxf_49");
	QsqlString.append(", dxf_50, dxf_51, dxf_52, dxf_53, dxf_54, dxf_55, dxf_56, dxf_57, dxf_58, dxf_59");
	QsqlString.append(", dxf_60, dxf_61, dxf_62, dxf_63, dxf_64, dxf_65, dxf_66, dxf_67, dxf_68, dxf_69");
	QsqlString.append(", dxf_70, dxf_71, dxf_72, dxf_73, dxf_74, dxf_75, dxf_76, dxf_77, dxf_78, dxf_79");
	QsqlString.append(", dxf_90, dxf_91, dxf_92, dxf_93, dxf_94, dxf_95, dxf_96, dxf_97, dxf_98, dxf_99");
	QsqlString.append(", dxf_100, dxf_102, dxf_105");
	QsqlString.append(", dxf_110, dxf_111, dxf_112, dxf_113, dxf_114, dxf_115, dxf_116, dxf_117, dxf_118, dxf_119");
	QsqlString.append(", dxf_120, dxf_121, dxf_122, dxf_123, dxf_124, dxf_125, dxf_126, dxf_127, dxf_128, dxf_129");
	QsqlString.append(", dxf_130, dxf_131, dxf_132, dxf_133, dxf_134, dxf_135, dxf_136, dxf_137, dxf_138, dxf_139");
	QsqlString.append(", dxf_140, dxf_141, dxf_142, dxf_143, dxf_144, dxf_145, dxf_146, dxf_147, dxf_148, dxf_149");

	QsqlString.append(", dxf_160, dxf_161, dxf_162, dxf_163, dxf_164, dxf_165, dxf_166, dxf_167, dxf_168, dxf_169");
	QsqlString.append(", dxf_170, dxf_171, dxf_172, dxf_173, dxf_174, dxf_175, dxf_176, dxf_177, dxf_178, dxf_179");

	QsqlString.append(", dxf_210, dxf_211, dxf_212, dxf_213, dxf_214, dxf_215, dxf_216, dxf_217, dxf_218, dxf_219");
	QsqlString.append(", dxf_220, dxf_221, dxf_222, dxf_223, dxf_224, dxf_225, dxf_226, dxf_227, dxf_228, dxf_229");
	QsqlString.append(", dxf_230, dxf_231, dxf_232, dxf_233, dxf_234, dxf_235, dxf_236, dxf_237, dxf_238, dxf_239");

	QsqlString.append(", dxf_270, dxf_271, dxf_272, dxf_273, dxf_274, dxf_275, dxf_276, dxf_277, dxf_278, dxf_279");
	QsqlString.append(", dxf_280, dxf_281, dxf_282, dxf_283, dxf_284, dxf_285, dxf_286, dxf_287, dxf_288, dxf_289");
	QsqlString.append(", dxf_290, dxf_291, dxf_292, dxf_293, dxf_294, dxf_295, dxf_296, dxf_297, dxf_298, dxf_299");
	QsqlString.append(", dxf_300, dxf_301, dxf_302, dxf_303, dxf_304, dxf_305, dxf_306, dxf_307, dxf_308, dxf_309");
	QsqlString.append(", dxf_310, dxf_311, dxf_312, dxf_313, dxf_314, dxf_315, dxf_316, dxf_317, dxf_318, dxf_319");
	QsqlString.append(", dxf_320, dxf_321, dxf_322, dxf_323, dxf_324, dxf_325, dxf_326, dxf_327, dxf_328, dxf_329");
	QsqlString.append(", dxf_330, dxf_331, dxf_332, dxf_333, dxf_334, dxf_335, dxf_336, dxf_337, dxf_338, dxf_339");
	QsqlString.append(", dxf_340, dxf_341, dxf_342, dxf_343, dxf_344, dxf_345, dxf_346, dxf_347, dxf_348, dxf_349");
	QsqlString.append(", dxf_350, dxf_351, dxf_352, dxf_353, dxf_354, dxf_355, dxf_356, dxf_357, dxf_358, dxf_359");
	QsqlString.append(", dxf_360, dxf_361, dxf_362, dxf_363, dxf_364, dxf_365, dxf_366, dxf_367, dxf_368, dxf_369");
	QsqlString.append(", dxf_370, dxf_371, dxf_372, dxf_373, dxf_374, dxf_375, dxf_376, dxf_377, dxf_378, dxf_379");
	QsqlString.append(", dxf_380, dxf_381, dxf_382, dxf_383, dxf_384, dxf_385, dxf_386, dxf_387, dxf_388, dxf_389");
	QsqlString.append(", dxf_390, dxf_391, dxf_392, dxf_393, dxf_394, dxf_395, dxf_396, dxf_397, dxf_398, dxf_399");
	QsqlString.append(", dxf_400, dxf_401, dxf_402, dxf_403, dxf_404, dxf_405, dxf_406, dxf_407, dxf_408, dxf_409");
	QsqlString.append(", dxf_410, dxf_411, dxf_412, dxf_413, dxf_414, dxf_415, dxf_416, dxf_417, dxf_418, dxf_419");
	QsqlString.append(", dxf_420, dxf_421, dxf_422, dxf_423, dxf_424, dxf_425, dxf_426, dxf_427, dxf_428, dxf_429");
	QsqlString.append(", dxf_430, dxf_431, dxf_432, dxf_433, dxf_434, dxf_435, dxf_436, dxf_437, dxf_438, dxf_439");
	QsqlString.append(", dxf_440, dxf_441, dxf_442, dxf_443, dxf_444, dxf_445, dxf_446, dxf_447, dxf_448, dxf_449");
	QsqlString.append(", dxf_450, dxf_451, dxf_452, dxf_453, dxf_454, dxf_455, dxf_456, dxf_457, dxf_458, dxf_459");
	QsqlString.append(", dxf_460, dxf_461, dxf_462, dxf_463, dxf_464, dxf_465, dxf_466, dxf_467, dxf_468, dxf_469");
	QsqlString.append(", dxf_470, dxf_471, dxf_472, dxf_473, dxf_474, dxf_475, dxf_476, dxf_477, dxf_478, dxf_479");
	QsqlString.append(", dxf_480, dxf_481, dxf_482, dxf_483, dxf_484, dxf_485, dxf_486, dxf_487, dxf_488, dxf_489");
	QsqlString.append(", dxf_999");
	QsqlString.append(", dxf_1000, dxf_1001, dxf_1002, dxf_1003, dxf_1004, dxf_1005, dxf_1006, dxf_1007, dxf_1008, dxf_1009");
	QsqlString.append(", dxf_1010, dxf_1011, dxf_1012, dxf_1013, dxf_1014, dxf_1015, dxf_1016, dxf_1017, dxf_1018, dxf_1019");
	QsqlString.append(", dxf_1020, dxf_1021, dxf_1022, dxf_1023, dxf_1024, dxf_1025, dxf_1026, dxf_1027, dxf_1028, dxf_1029");
	QsqlString.append(", dxf_1030, dxf_1031, dxf_1032, dxf_1033, dxf_1034, dxf_1035, dxf_1036, dxf_1037, dxf_1038, dxf_1039");
	QsqlString.append(", dxf_1040, dxf_1041, dxf_1042, dxf_1043, dxf_1044, dxf_1045, dxf_1046, dxf_1047, dxf_1048, dxf_1049");
	QsqlString.append(", dxf_1050, dxf_1051, dxf_1052, dxf_1053, dxf_1054, dxf_1055, dxf_1056, dxf_1057, dxf_1058, dxf_1059");
	QsqlString.append(", dxf_1060, dxf_1061, dxf_1062, dxf_1063, dxf_1064, dxf_1065, dxf_1066, dxf_1067, dxf_1068, dxf_1069");
	QsqlString.append(", dxf_1070, dxf_1071");


	QsqlString.append(")");

	m_db.exec(QsqlString);


	QsqlString="create table dxf_objects (Index_count primary key,Section";
	QsqlString.append(", dxfbase, Command, ID_instruction, Command_count");
	QsqlString.append(", dxf_m1, dxf_m2, dxf_m3, dxf_m4, dxf_m5");
	QsqlString.append(", dxf_0, dxf_1, dxf_2, dxf_3, dxf_4, dxf_5, dxf_6, dxf_7, dxf_8, dxf_9");
	QsqlString.append(", dxf_10, dxf_11, dxf_12, dxf_13, dxf_14, dxf_15, dxf_16, dxf_17, dxf_18, dxf_19");
	QsqlString.append(", dxf_20, dxf_21, dxf_22, dxf_23, dxf_24, dxf_25, dxf_26, dxf_27, dxf_28, dxf_29");
	QsqlString.append(", dxf_30, dxf_31, dxf_32, dxf_33, dxf_34, dxf_35, dxf_36, dxf_37, dxf_38, dxf_39");
	QsqlString.append(", dxf_40, dxf_41, dxf_42, dxf_43, dxf_44, dxf_45, dxf_46, dxf_47, dxf_48, dxf_49");
	QsqlString.append(", dxf_50, dxf_51, dxf_52, dxf_53, dxf_54, dxf_55, dxf_56, dxf_57, dxf_58, dxf_59");
	QsqlString.append(", dxf_60, dxf_61, dxf_62, dxf_63, dxf_64, dxf_65, dxf_66, dxf_67, dxf_68, dxf_69");
	QsqlString.append(", dxf_70, dxf_71, dxf_72, dxf_73, dxf_74, dxf_75, dxf_76, dxf_77, dxf_78, dxf_79");
	QsqlString.append(", dxf_90, dxf_91, dxf_92, dxf_93, dxf_94, dxf_95, dxf_96, dxf_97, dxf_98, dxf_99");
	QsqlString.append(", dxf_100, dxf_102, dxf_105");
	QsqlString.append(", dxf_110, dxf_111, dxf_112, dxf_113, dxf_114, dxf_115, dxf_116, dxf_117, dxf_118, dxf_119");
	QsqlString.append(", dxf_120, dxf_121, dxf_122, dxf_123, dxf_124, dxf_125, dxf_126, dxf_127, dxf_128, dxf_129");
	QsqlString.append(", dxf_130, dxf_131, dxf_132, dxf_133, dxf_134, dxf_135, dxf_136, dxf_137, dxf_138, dxf_139");
	QsqlString.append(", dxf_140, dxf_141, dxf_142, dxf_143, dxf_144, dxf_145, dxf_146, dxf_147, dxf_148, dxf_149");

	QsqlString.append(", dxf_160, dxf_161, dxf_162, dxf_163, dxf_164, dxf_165, dxf_166, dxf_167, dxf_168, dxf_169");
	QsqlString.append(", dxf_170, dxf_171, dxf_172, dxf_173, dxf_174, dxf_175, dxf_176, dxf_177, dxf_178, dxf_179");

	QsqlString.append(", dxf_210, dxf_211, dxf_212, dxf_213, dxf_214, dxf_215, dxf_216, dxf_217, dxf_218, dxf_219");
	QsqlString.append(", dxf_220, dxf_221, dxf_222, dxf_223, dxf_224, dxf_225, dxf_226, dxf_227, dxf_228, dxf_229");
	QsqlString.append(", dxf_230, dxf_231, dxf_232, dxf_233, dxf_234, dxf_235, dxf_236, dxf_237, dxf_238, dxf_239");

	QsqlString.append(", dxf_270, dxf_271, dxf_272, dxf_273, dxf_274, dxf_275, dxf_276, dxf_277, dxf_278, dxf_279");
	QsqlString.append(", dxf_280, dxf_281, dxf_282, dxf_283, dxf_284, dxf_285, dxf_286, dxf_287, dxf_288, dxf_289");
	QsqlString.append(", dxf_290, dxf_291, dxf_292, dxf_293, dxf_294, dxf_295, dxf_296, dxf_297, dxf_298, dxf_299");
	QsqlString.append(", dxf_300, dxf_301, dxf_302, dxf_303, dxf_304, dxf_305, dxf_306, dxf_307, dxf_308, dxf_309");
	QsqlString.append(", dxf_310, dxf_311, dxf_312, dxf_313, dxf_314, dxf_315, dxf_316, dxf_317, dxf_318, dxf_319");
	QsqlString.append(", dxf_320, dxf_321, dxf_322, dxf_323, dxf_324, dxf_325, dxf_326, dxf_327, dxf_328, dxf_329");
	QsqlString.append(", dxf_330, dxf_331, dxf_332, dxf_333, dxf_334, dxf_335, dxf_336, dxf_337, dxf_338, dxf_339");
	QsqlString.append(", dxf_340, dxf_341, dxf_342, dxf_343, dxf_344, dxf_345, dxf_346, dxf_347, dxf_348, dxf_349");
	QsqlString.append(", dxf_350, dxf_351, dxf_352, dxf_353, dxf_354, dxf_355, dxf_356, dxf_357, dxf_358, dxf_359");
	QsqlString.append(", dxf_360, dxf_361, dxf_362, dxf_363, dxf_364, dxf_365, dxf_366, dxf_367, dxf_368, dxf_369");
	QsqlString.append(", dxf_370, dxf_371, dxf_372, dxf_373, dxf_374, dxf_375, dxf_376, dxf_377, dxf_378, dxf_379");
	QsqlString.append(", dxf_380, dxf_381, dxf_382, dxf_383, dxf_384, dxf_385, dxf_386, dxf_387, dxf_388, dxf_389");
	QsqlString.append(", dxf_390, dxf_391, dxf_392, dxf_393, dxf_394, dxf_395, dxf_396, dxf_397, dxf_398, dxf_399");
	QsqlString.append(", dxf_400, dxf_401, dxf_402, dxf_403, dxf_404, dxf_405, dxf_406, dxf_407, dxf_408, dxf_409");
	QsqlString.append(", dxf_410, dxf_411, dxf_412, dxf_413, dxf_414, dxf_415, dxf_416, dxf_417, dxf_418, dxf_419");
	QsqlString.append(", dxf_420, dxf_421, dxf_422, dxf_423, dxf_424, dxf_425, dxf_426, dxf_427, dxf_428, dxf_429");
	QsqlString.append(", dxf_430, dxf_431, dxf_432, dxf_433, dxf_434, dxf_435, dxf_436, dxf_437, dxf_438, dxf_439");
	QsqlString.append(", dxf_440, dxf_441, dxf_442, dxf_443, dxf_444, dxf_445, dxf_446, dxf_447, dxf_448, dxf_449");
	QsqlString.append(", dxf_450, dxf_451, dxf_452, dxf_453, dxf_454, dxf_455, dxf_456, dxf_457, dxf_458, dxf_459");
	QsqlString.append(", dxf_460, dxf_461, dxf_462, dxf_463, dxf_464, dxf_465, dxf_466, dxf_467, dxf_468, dxf_469");
	QsqlString.append(", dxf_470, dxf_471, dxf_472, dxf_473, dxf_474, dxf_475, dxf_476, dxf_477, dxf_478, dxf_479");
	QsqlString.append(", dxf_480, dxf_481, dxf_482, dxf_483, dxf_484, dxf_485, dxf_486, dxf_487, dxf_488, dxf_489");
	QsqlString.append(", dxf_999");
	QsqlString.append(", dxf_1000, dxf_1001, dxf_1002, dxf_1003, dxf_1004, dxf_1005, dxf_1006, dxf_1007, dxf_1008, dxf_1009");
	QsqlString.append(", dxf_1010, dxf_1011, dxf_1012, dxf_1013, dxf_1014, dxf_1015, dxf_1016, dxf_1017, dxf_1018, dxf_1019");
	QsqlString.append(", dxf_1020, dxf_1021, dxf_1022, dxf_1023, dxf_1024, dxf_1025, dxf_1026, dxf_1027, dxf_1028, dxf_1029");
	QsqlString.append(", dxf_1030, dxf_1031, dxf_1032, dxf_1033, dxf_1034, dxf_1035, dxf_1036, dxf_1037, dxf_1038, dxf_1039");
	QsqlString.append(", dxf_1040, dxf_1041, dxf_1042, dxf_1043, dxf_1044, dxf_1045, dxf_1046, dxf_1047, dxf_1048, dxf_1049");
	QsqlString.append(", dxf_1050, dxf_1051, dxf_1052, dxf_1053, dxf_1054, dxf_1055, dxf_1056, dxf_1057, dxf_1058, dxf_1059");
	QsqlString.append(", dxf_1060, dxf_1061, dxf_1062, dxf_1063, dxf_1064, dxf_1065, dxf_1066, dxf_1067, dxf_1068, dxf_1069");
	QsqlString.append(", dxf_1070, dxf_1071");


	QsqlString.append(")");

	m_db.exec(QsqlString);

	QsqlString="create table dxf_thumbnailimage (Index_count primary key,Section";
	QsqlString.append(", dxfbase, Command, ID_instruction, Command_count");
	QsqlString.append(", dxf_m1, dxf_m2, dxf_m3, dxf_m4, dxf_m5");
	QsqlString.append(", dxf_0, dxf_1, dxf_2, dxf_3, dxf_4, dxf_5, dxf_6, dxf_7, dxf_8, dxf_9");
	QsqlString.append(", dxf_10, dxf_11, dxf_12, dxf_13, dxf_14, dxf_15, dxf_16, dxf_17, dxf_18, dxf_19");
	QsqlString.append(", dxf_20, dxf_21, dxf_22, dxf_23, dxf_24, dxf_25, dxf_26, dxf_27, dxf_28, dxf_29");
	QsqlString.append(", dxf_30, dxf_31, dxf_32, dxf_33, dxf_34, dxf_35, dxf_36, dxf_37, dxf_38, dxf_39");
	QsqlString.append(", dxf_40, dxf_41, dxf_42, dxf_43, dxf_44, dxf_45, dxf_46, dxf_47, dxf_48, dxf_49");
	QsqlString.append(", dxf_50, dxf_51, dxf_52, dxf_53, dxf_54, dxf_55, dxf_56, dxf_57, dxf_58, dxf_59");
	QsqlString.append(", dxf_60, dxf_61, dxf_62, dxf_63, dxf_64, dxf_65, dxf_66, dxf_67, dxf_68, dxf_69");
	QsqlString.append(", dxf_70, dxf_71, dxf_72, dxf_73, dxf_74, dxf_75, dxf_76, dxf_77, dxf_78, dxf_79");
	QsqlString.append(", dxf_90, dxf_91, dxf_92, dxf_93, dxf_94, dxf_95, dxf_96, dxf_97, dxf_98, dxf_99");
	QsqlString.append(", dxf_100, dxf_102, dxf_105");
	QsqlString.append(", dxf_110, dxf_111, dxf_112, dxf_113, dxf_114, dxf_115, dxf_116, dxf_117, dxf_118, dxf_119");
	QsqlString.append(", dxf_120, dxf_121, dxf_122, dxf_123, dxf_124, dxf_125, dxf_126, dxf_127, dxf_128, dxf_129");
	QsqlString.append(", dxf_130, dxf_131, dxf_132, dxf_133, dxf_134, dxf_135, dxf_136, dxf_137, dxf_138, dxf_139");
	QsqlString.append(", dxf_140, dxf_141, dxf_142, dxf_143, dxf_144, dxf_145, dxf_146, dxf_147, dxf_148, dxf_149");

	QsqlString.append(", dxf_160, dxf_161, dxf_162, dxf_163, dxf_164, dxf_165, dxf_166, dxf_167, dxf_168, dxf_169");
	QsqlString.append(", dxf_170, dxf_171, dxf_172, dxf_173, dxf_174, dxf_175, dxf_176, dxf_177, dxf_178, dxf_179");

	QsqlString.append(", dxf_210, dxf_211, dxf_212, dxf_213, dxf_214, dxf_215, dxf_216, dxf_217, dxf_218, dxf_219");
	QsqlString.append(", dxf_220, dxf_221, dxf_222, dxf_223, dxf_224, dxf_225, dxf_226, dxf_227, dxf_228, dxf_229");
	QsqlString.append(", dxf_230, dxf_231, dxf_232, dxf_233, dxf_234, dxf_235, dxf_236, dxf_237, dxf_238, dxf_239");

	QsqlString.append(", dxf_270, dxf_271, dxf_272, dxf_273, dxf_274, dxf_275, dxf_276, dxf_277, dxf_278, dxf_279");
	QsqlString.append(", dxf_280, dxf_281, dxf_282, dxf_283, dxf_284, dxf_285, dxf_286, dxf_287, dxf_288, dxf_289");
	QsqlString.append(", dxf_290, dxf_291, dxf_292, dxf_293, dxf_294, dxf_295, dxf_296, dxf_297, dxf_298, dxf_299");
	QsqlString.append(", dxf_300, dxf_301, dxf_302, dxf_303, dxf_304, dxf_305, dxf_306, dxf_307, dxf_308, dxf_309");
	QsqlString.append(", dxf_310, dxf_311, dxf_312, dxf_313, dxf_314, dxf_315, dxf_316, dxf_317, dxf_318, dxf_319");
	QsqlString.append(", dxf_320, dxf_321, dxf_322, dxf_323, dxf_324, dxf_325, dxf_326, dxf_327, dxf_328, dxf_329");
	QsqlString.append(", dxf_330, dxf_331, dxf_332, dxf_333, dxf_334, dxf_335, dxf_336, dxf_337, dxf_338, dxf_339");
	QsqlString.append(", dxf_340, dxf_341, dxf_342, dxf_343, dxf_344, dxf_345, dxf_346, dxf_347, dxf_348, dxf_349");
	QsqlString.append(", dxf_350, dxf_351, dxf_352, dxf_353, dxf_354, dxf_355, dxf_356, dxf_357, dxf_358, dxf_359");
	QsqlString.append(", dxf_360, dxf_361, dxf_362, dxf_363, dxf_364, dxf_365, dxf_366, dxf_367, dxf_368, dxf_369");
	QsqlString.append(", dxf_370, dxf_371, dxf_372, dxf_373, dxf_374, dxf_375, dxf_376, dxf_377, dxf_378, dxf_379");
	QsqlString.append(", dxf_380, dxf_381, dxf_382, dxf_383, dxf_384, dxf_385, dxf_386, dxf_387, dxf_388, dxf_389");
	QsqlString.append(", dxf_390, dxf_391, dxf_392, dxf_393, dxf_394, dxf_395, dxf_396, dxf_397, dxf_398, dxf_399");
	QsqlString.append(", dxf_400, dxf_401, dxf_402, dxf_403, dxf_404, dxf_405, dxf_406, dxf_407, dxf_408, dxf_409");
	QsqlString.append(", dxf_410, dxf_411, dxf_412, dxf_413, dxf_414, dxf_415, dxf_416, dxf_417, dxf_418, dxf_419");
	QsqlString.append(", dxf_420, dxf_421, dxf_422, dxf_423, dxf_424, dxf_425, dxf_426, dxf_427, dxf_428, dxf_429");
	QsqlString.append(", dxf_430, dxf_431, dxf_432, dxf_433, dxf_434, dxf_435, dxf_436, dxf_437, dxf_438, dxf_439");
	QsqlString.append(", dxf_440, dxf_441, dxf_442, dxf_443, dxf_444, dxf_445, dxf_446, dxf_447, dxf_448, dxf_449");
	QsqlString.append(", dxf_450, dxf_451, dxf_452, dxf_453, dxf_454, dxf_455, dxf_456, dxf_457, dxf_458, dxf_459");
	QsqlString.append(", dxf_460, dxf_461, dxf_462, dxf_463, dxf_464, dxf_465, dxf_466, dxf_467, dxf_468, dxf_469");
	QsqlString.append(", dxf_470, dxf_471, dxf_472, dxf_473, dxf_474, dxf_475, dxf_476, dxf_477, dxf_478, dxf_479");
	QsqlString.append(", dxf_480, dxf_481, dxf_482, dxf_483, dxf_484, dxf_485, dxf_486, dxf_487, dxf_488, dxf_489");
	QsqlString.append(", dxf_999");
	QsqlString.append(", dxf_1000, dxf_1001, dxf_1002, dxf_1003, dxf_1004, dxf_1005, dxf_1006, dxf_1007, dxf_1008, dxf_1009");
	QsqlString.append(", dxf_1010, dxf_1011, dxf_1012, dxf_1013, dxf_1014, dxf_1015, dxf_1016, dxf_1017, dxf_1018, dxf_1019");
	QsqlString.append(", dxf_1020, dxf_1021, dxf_1022, dxf_1023, dxf_1024, dxf_1025, dxf_1026, dxf_1027, dxf_1028, dxf_1029");
	QsqlString.append(", dxf_1030, dxf_1031, dxf_1032, dxf_1033, dxf_1034, dxf_1035, dxf_1036, dxf_1037, dxf_1038, dxf_1039");
	QsqlString.append(", dxf_1040, dxf_1041, dxf_1042, dxf_1043, dxf_1044, dxf_1045, dxf_1046, dxf_1047, dxf_1048, dxf_1049");
	QsqlString.append(", dxf_1050, dxf_1051, dxf_1052, dxf_1053, dxf_1054, dxf_1055, dxf_1056, dxf_1057, dxf_1058, dxf_1059");
	QsqlString.append(", dxf_1060, dxf_1061, dxf_1062, dxf_1063, dxf_1064, dxf_1065, dxf_1066, dxf_1067, dxf_1068, dxf_1069");
	QsqlString.append(", dxf_1070, dxf_1071");


	QsqlString.append(")");

	m_db.exec(QsqlString);

	return;
}

int dbManager::dbManager_added_records(const QString &pathname, int32_t *Max_lines, int32_t *Record_count, QString dxf_type)
{
    QString path = pathname;
	m_db.transaction();
	QSqlQuery Query1;

	x1=0;
	//x10=0;

	QsqlString="INSERT INTO ";
	QsqlString.append(dxf_type);
	QsqlString.append(" (Index_count, Section");
	QsqlString.append(", dxfbase, Command, ID_instruction, Command_count");
	QsqlString.append(", dxf_m1, dxf_m2, dxf_m3, dxf_m4, dxf_m5");
	QsqlString.append(", dxf_0, dxf_1, dxf_2, dxf_3, dxf_4, dxf_5, dxf_6, dxf_7, dxf_8, dxf_9");
	QsqlString.append(", dxf_10, dxf_11, dxf_12, dxf_13, dxf_14, dxf_15, dxf_16, dxf_17, dxf_18, dxf_19");
	QsqlString.append(", dxf_20, dxf_21, dxf_22, dxf_23, dxf_24, dxf_25, dxf_26, dxf_27, dxf_28, dxf_29");
	QsqlString.append(", dxf_30, dxf_31, dxf_32, dxf_33, dxf_34, dxf_35, dxf_36, dxf_37, dxf_38, dxf_39");
	QsqlString.append(", dxf_40, dxf_41, dxf_42, dxf_43, dxf_44, dxf_45, dxf_46, dxf_47, dxf_48, dxf_49");
	QsqlString.append(", dxf_50, dxf_51, dxf_52, dxf_53, dxf_54, dxf_55, dxf_56, dxf_57, dxf_58, dxf_59");
	QsqlString.append(", dxf_60, dxf_61, dxf_62, dxf_63, dxf_64, dxf_65, dxf_66, dxf_67, dxf_68, dxf_69");
	QsqlString.append(", dxf_70, dxf_71, dxf_72, dxf_73, dxf_74, dxf_75, dxf_76, dxf_77, dxf_78, dxf_79");
	QsqlString.append(", dxf_90, dxf_91, dxf_92, dxf_93, dxf_94, dxf_95, dxf_96, dxf_97, dxf_98, dxf_99");
	QsqlString.append(", dxf_100, dxf_102, dxf_105");
	QsqlString.append(", dxf_110, dxf_111, dxf_112, dxf_113, dxf_114, dxf_115, dxf_116, dxf_117, dxf_118, dxf_119");
	QsqlString.append(", dxf_120, dxf_121, dxf_122, dxf_123, dxf_124, dxf_125, dxf_126, dxf_127, dxf_128, dxf_129");
	QsqlString.append(", dxf_130, dxf_131, dxf_132, dxf_133, dxf_134, dxf_135, dxf_136, dxf_137, dxf_138, dxf_139");
	QsqlString.append(", dxf_140, dxf_141, dxf_142, dxf_143, dxf_144, dxf_145, dxf_146, dxf_147, dxf_148, dxf_149");

	QsqlString.append(", dxf_160, dxf_161, dxf_162, dxf_163, dxf_164, dxf_165, dxf_166, dxf_167, dxf_168, dxf_169");
	QsqlString.append(", dxf_170, dxf_171, dxf_172, dxf_173, dxf_174, dxf_175, dxf_176, dxf_177, dxf_178, dxf_179");

	QsqlString.append(", dxf_210, dxf_211, dxf_212, dxf_213, dxf_214, dxf_215, dxf_216, dxf_217, dxf_218, dxf_219");
	QsqlString.append(", dxf_220, dxf_221, dxf_222, dxf_223, dxf_224, dxf_225, dxf_226, dxf_227, dxf_228, dxf_229");
	QsqlString.append(", dxf_230, dxf_231, dxf_232, dxf_233, dxf_234, dxf_235, dxf_236, dxf_237, dxf_238, dxf_239");

	QsqlString.append(", dxf_270, dxf_271, dxf_272, dxf_273, dxf_274, dxf_275, dxf_276, dxf_277, dxf_278, dxf_279");
	QsqlString.append(", dxf_280, dxf_281, dxf_282, dxf_283, dxf_284, dxf_285, dxf_286, dxf_287, dxf_288, dxf_289");
	QsqlString.append(", dxf_290, dxf_291, dxf_292, dxf_293, dxf_294, dxf_295, dxf_296, dxf_297, dxf_298, dxf_299");
	QsqlString.append(", dxf_300, dxf_301, dxf_302, dxf_303, dxf_304, dxf_305, dxf_306, dxf_307, dxf_308, dxf_309");
	QsqlString.append(", dxf_310, dxf_311, dxf_312, dxf_313, dxf_314, dxf_315, dxf_316, dxf_317, dxf_318, dxf_319");
	QsqlString.append(", dxf_320, dxf_321, dxf_322, dxf_323, dxf_324, dxf_325, dxf_326, dxf_327, dxf_328, dxf_329");
	QsqlString.append(", dxf_330, dxf_331, dxf_332, dxf_333, dxf_334, dxf_335, dxf_336, dxf_337, dxf_338, dxf_339");
	QsqlString.append(", dxf_340, dxf_341, dxf_342, dxf_343, dxf_344, dxf_345, dxf_346, dxf_347, dxf_348, dxf_349");
	QsqlString.append(", dxf_350, dxf_351, dxf_352, dxf_353, dxf_354, dxf_355, dxf_356, dxf_357, dxf_358, dxf_359");
	QsqlString.append(", dxf_360, dxf_361, dxf_362, dxf_363, dxf_364, dxf_365, dxf_366, dxf_367, dxf_368, dxf_369");
	QsqlString.append(", dxf_370, dxf_371, dxf_372, dxf_373, dxf_374, dxf_375, dxf_376, dxf_377, dxf_378, dxf_379");
	QsqlString.append(", dxf_380, dxf_381, dxf_382, dxf_383, dxf_384, dxf_385, dxf_386, dxf_387, dxf_388, dxf_389");
	QsqlString.append(", dxf_390, dxf_391, dxf_392, dxf_393, dxf_394, dxf_395, dxf_396, dxf_397, dxf_398, dxf_399");
	QsqlString.append(", dxf_400, dxf_401, dxf_402, dxf_403, dxf_404, dxf_405, dxf_406, dxf_407, dxf_408, dxf_409");
	QsqlString.append(", dxf_410, dxf_411, dxf_412, dxf_413, dxf_414, dxf_415, dxf_416, dxf_417, dxf_418, dxf_419");
	QsqlString.append(", dxf_420, dxf_421, dxf_422, dxf_423, dxf_424, dxf_425, dxf_426, dxf_427, dxf_428, dxf_429");
	QsqlString.append(", dxf_430, dxf_431, dxf_432, dxf_433, dxf_434, dxf_435, dxf_436, dxf_437, dxf_438, dxf_439");
	QsqlString.append(", dxf_440, dxf_441, dxf_442, dxf_443, dxf_444, dxf_445, dxf_446, dxf_447, dxf_448, dxf_449");
	QsqlString.append(", dxf_450, dxf_451, dxf_452, dxf_453, dxf_454, dxf_455, dxf_456, dxf_457, dxf_458, dxf_459");
	QsqlString.append(", dxf_460, dxf_461, dxf_462, dxf_463, dxf_464, dxf_465, dxf_466, dxf_467, dxf_468, dxf_469");
	QsqlString.append(", dxf_470, dxf_471, dxf_472, dxf_473, dxf_474, dxf_475, dxf_476, dxf_477, dxf_478, dxf_479");
	QsqlString.append(", dxf_480, dxf_481, dxf_482, dxf_483, dxf_484, dxf_485, dxf_486, dxf_487, dxf_488, dxf_489");
	QsqlString.append(", dxf_999");
	QsqlString.append(", dxf_1000, dxf_1001, dxf_1002, dxf_1003, dxf_1004, dxf_1005, dxf_1006, dxf_1007, dxf_1008, dxf_1009");
	QsqlString.append(", dxf_1010, dxf_1011, dxf_1012, dxf_1013, dxf_1014, dxf_1015, dxf_1016, dxf_1017, dxf_1018, dxf_1019");
	QsqlString.append(", dxf_1020, dxf_1021, dxf_1022, dxf_1023, dxf_1024, dxf_1025, dxf_1026, dxf_1027, dxf_1028, dxf_1029");
	QsqlString.append(", dxf_1030, dxf_1031, dxf_1032, dxf_1033, dxf_1034, dxf_1035, dxf_1036, dxf_1037, dxf_1038, dxf_1039");
	QsqlString.append(", dxf_1040, dxf_1041, dxf_1042, dxf_1043, dxf_1044, dxf_1045, dxf_1046, dxf_1047, dxf_1048, dxf_1049");
	QsqlString.append(", dxf_1050, dxf_1051, dxf_1052, dxf_1053, dxf_1054, dxf_1055, dxf_1056, dxf_1057, dxf_1058, dxf_1059");
	QsqlString.append(", dxf_1060, dxf_1061, dxf_1062, dxf_1063, dxf_1064, dxf_1065, dxf_1066, dxf_1067, dxf_1068, dxf_1069");
	QsqlString.append(", dxf_1070, dxf_1071");
	QsqlString.append(")");
	QsqlString.append(" VALUES (:Index_count, :Section");
	QsqlString.append(", :dxfbase, :Command, :ID_instruction, :Command_count");
	QsqlString.append(", :dxf_m1, :dxf_m2, :dxf_m3, :dxf_m4, :dxf_m5");
	QsqlString.append(", :dxf_0, :dxf_1, :dxf_2, :dxf_3, :dxf_4, :dxf_5, :dxf_6, :dxf_7, :dxf_8, :dxf_9");//dxf_0
	QsqlString.append(", :dxf_10, :dxf_11, :dxf_12, :dxf_13, :dxf_14, :dxf_15, :dxf_16, :dxf_17, :dxf_18, :dxf_19");
	QsqlString.append(", :dxf_20, :dxf_21, :dxf_22, :dxf_23, :dxf_24, :dxf_25, :dxf_26, :dxf_27, :dxf_28, :dxf_29");
	QsqlString.append(", :dxf_30, :dxf_31, :dxf_32, :dxf_33, :dxf_34, :dxf_35, :dxf_36, :dxf_37, :dxf_38, :dxf_39");
	QsqlString.append(", :dxf_40, :dxf_41, :dxf_42, :dxf_43, :dxf_44, :dxf_45, :dxf_46, :dxf_47, :dxf_48, :dxf_49");
	QsqlString.append(", :dxf_50, :dxf_51, :dxf_52, :dxf_53, :dxf_54, :dxf_55, :dxf_56, :dxf_57, :dxf_58, :dxf_59");
	QsqlString.append(", :dxf_60, :dxf_61, :dxf_62, :dxf_63, :dxf_64, :dxf_65, :dxf_66, :dxf_67, :dxf_68, :dxf_69");
	QsqlString.append(", :dxf_70, :dxf_71, :dxf_72, :dxf_73, :dxf_74, :dxf_75, :dxf_76, :dxf_77, :dxf_78, :dxf_79");
	QsqlString.append(", :dxf_90, :dxf_91, :dxf_92, :dxf_93, :dxf_94, :dxf_95, :dxf_96, :dxf_97, :dxf_98, :dxf_99");
	QsqlString.append(", :dxf_100, :dxf_102, :dxf_105");
	QsqlString.append(", :dxf_110, :dxf_111, :dxf_112, :dxf_113, :dxf_114, :dxf_115, :dxf_116, :dxf_117, :dxf_118, :dxf_119");
	QsqlString.append(", :dxf_120, :dxf_121, :dxf_122, :dxf_123, :dxf_124, :dxf_125, :dxf_126, :dxf_127, :dxf_128, :dxf_129");
	QsqlString.append(", :dxf_130, :dxf_131, :dxf_132, :dxf_133, :dxf_134, :dxf_135, :dxf_136, :dxf_137, :dxf_138, :dxf_139");
	QsqlString.append(", :dxf_140, :dxf_141, :dxf_142, :dxf_143, :dxf_144, :dxf_145, :dxf_146, :dxf_147, :dxf_148, :dxf_149");

	QsqlString.append(", :dxf_160, :dxf_161, :dxf_162, :dxf_163, :dxf_164, :dxf_165, :dxf_166, :dxf_167, :dxf_168, :dxf_169");
	QsqlString.append(", :dxf_170, :dxf_171, :dxf_172, :dxf_173, :dxf_174, :dxf_175, :dxf_176, :dxf_177, :dxf_178, :dxf_179");


	QsqlString.append(", :dxf_210, :dxf_211, :dxf_212, :dxf_213, :dxf_214, :dxf_215, :dxf_216, :dxf_217, :dxf_218, :dxf_219");
	QsqlString.append(", :dxf_220, :dxf_221, :dxf_222, :dxf_223, :dxf_224, :dxf_225, :dxf_226, :dxf_227, :dxf_228, :dxf_229");
	QsqlString.append(", :dxf_230, :dxf_231, :dxf_232, :dxf_233, :dxf_234, :dxf_235, :dxf_236, :dxf_237, :dxf_238, :dxf_239");

	QsqlString.append(", :dxf_270, :dxf_271, :dxf_272, :dxf_273, :dxf_274, :dxf_275, :dxf_276, :dxf_277, :dxf_278, :dxf_279");
	QsqlString.append(", :dxf_280, :dxf_281, :dxf_282, :dxf_283, :dxf_284, :dxf_285, :dxf_286, :dxf_287, :dxf_288, :dxf_289");
	QsqlString.append(", :dxf_290, :dxf_291, :dxf_292, :dxf_293, :dxf_294, :dxf_295, :dxf_296, :dxf_297, :dxf_298, :dxf_299");
	QsqlString.append(", :dxf_300, :dxf_301, :dxf_302, :dxf_303, :dxf_304, :dxf_305, :dxf_306, :dxf_307, :dxf_308, :dxf_309");
	QsqlString.append(", :dxf_310, :dxf_311, :dxf_312, :dxf_313, :dxf_314, :dxf_315, :dxf_316, :dxf_317, :dxf_318, :dxf_319");
	QsqlString.append(", :dxf_320, :dxf_321, :dxf_322, :dxf_323, :dxf_324, :dxf_325, :dxf_326, :dxf_327, :dxf_328, :dxf_329");
	QsqlString.append(", :dxf_330, :dxf_331, :dxf_332, :dxf_333, :dxf_334, :dxf_335, :dxf_336, :dxf_337, :dxf_338, :dxf_339");
	QsqlString.append(", :dxf_340, :dxf_341, :dxf_342, :dxf_343, :dxf_344, :dxf_345, :dxf_346, :dxf_347, :dxf_348, :dxf_349");
	QsqlString.append(", :dxf_350, :dxf_351, :dxf_352, :dxf_353, :dxf_354, :dxf_355, :dxf_356, :dxf_357, :dxf_358, :dxf_359");
	QsqlString.append(", :dxf_360, :dxf_361, :dxf_362, :dxf_363, :dxf_364, :dxf_365, :dxf_366, :dxf_367, :dxf_368, :dxf_369");
	QsqlString.append(", :dxf_370, :dxf_371, :dxf_372, :dxf_373, :dxf_374, :dxf_375, :dxf_376, :dxf_377, :dxf_378, :dxf_379");
	QsqlString.append(", :dxf_380, :dxf_381, :dxf_382, :dxf_383, :dxf_384, :dxf_385, :dxf_386, :dxf_387, :dxf_388, :dxf_389");
	QsqlString.append(", :dxf_390, :dxf_391, :dxf_392, :dxf_393, :dxf_394, :dxf_395, :dxf_396, :dxf_397, :dxf_398, :dxf_399");
	QsqlString.append(", :dxf_400, :dxf_401, :dxf_402, :dxf_403, :dxf_404, :dxf_405, :dxf_406, :dxf_407, :dxf_408, :dxf_409");
	QsqlString.append(", :dxf_410, :dxf_411, :dxf_412, :dxf_413, :dxf_414, :dxf_415, :dxf_416, :dxf_417, :dxf_418, :dxf_419");
	QsqlString.append(", :dxf_420, :dxf_421, :dxf_422, :dxf_423, :dxf_424, :dxf_425, :dxf_426, :dxf_427, :dxf_428, :dxf_429");
	QsqlString.append(", :dxf_430, :dxf_431, :dxf_432, :dxf_433, :dxf_434, :dxf_435, :dxf_436, :dxf_437, :dxf_438, :dxf_439");
	QsqlString.append(", :dxf_440, :dxf_441, :dxf_442, :dxf_443, :dxf_444, :dxf_445, :dxf_446, :dxf_447, :dxf_448, :dxf_449");
	QsqlString.append(", :dxf_450, :dxf_451, :dxf_452, :dxf_453, :dxf_454, :dxf_455, :dxf_456, :dxf_457, :dxf_458, :dxf_459");
	QsqlString.append(", :dxf_460, :dxf_461, :dxf_462, :dxf_463, :dxf_464, :dxf_465, :dxf_466, :dxf_467, :dxf_468, :dxf_469");
	QsqlString.append(", :dxf_470, :dxf_471, :dxf_472, :dxf_473, :dxf_474, :dxf_475, :dxf_476, :dxf_477, :dxf_478, :dxf_479");
	QsqlString.append(", :dxf_480, :dxf_481, :dxf_482, :dxf_483, :dxf_484, :dxf_485, :dxf_486, :dxf_487, :dxf_488, :dxf_489");
	QsqlString.append(", :dxf_999");
	QsqlString.append(", :dxf_1000, :dxf_1001, :dxf_1002, :dxf_1003, :dxf_1004, :dxf_1005, :dxf_1006, :dxf_1007, :dxf_1008, :dxf_1009");
	QsqlString.append(", :dxf_1010, :dxf_1011, :dxf_1012, :dxf_1013, :dxf_1014, :dxf_1015, :dxf_1016, :dxf_1017, :dxf_1018, :dxf_1019");
	QsqlString.append(", :dxf_1020, :dxf_1021, :dxf_1022, :dxf_1023, :dxf_1024, :dxf_1025, :dxf_1026, :dxf_1027, :dxf_1028, :dxf_1029");
	QsqlString.append(", :dxf_1030, :dxf_1031, :dxf_1032, :dxf_1033, :dxf_1034, :dxf_1035, :dxf_1036, :dxf_1037, :dxf_1038, :dxf_1039");
	QsqlString.append(", :dxf_1040, :dxf_1041, :dxf_1042, :dxf_1043, :dxf_1044, :dxf_1045, :dxf_1046, :dxf_1047, :dxf_1048, :dxf_1049");
	QsqlString.append(", :dxf_1050, :dxf_1051, :dxf_1052, :dxf_1053, :dxf_1054, :dxf_1055, :dxf_1056, :dxf_1057, :dxf_1058, :dxf_1059");
	QsqlString.append(", :dxf_1060, :dxf_1061, :dxf_1062, :dxf_1063, :dxf_1064, :dxf_1065, :dxf_1066, :dxf_1067, :dxf_1068, :dxf_1069");
	QsqlString.append(", :dxf_1070, :dxf_1071");

	QsqlString.append(")");


	Query1.prepare(QsqlString);

	Command_Count=-1;
	Max_count_lines=*Max_lines;
	Record_count_lines=*Record_count;
	x1=0;

	while ((x1<Max_count_lines) and (x1<DXF_codes_set))
	{
		//DXF_code_tables[x1].ID_instruction=1;
		//Record_count_lines++;
		//x10++;
		if(Command_Count>=Max_count_lines)
		{
			Command_Count=-1;
		}

		Command_Count++;
		//Record_count_lines++;
		x2=0;

		//while (x10<Max_count_lines)
		//{

		//Record_count_lines++;

			//RecordNr=(QString::number(Record_count_lines));
			//Query1.bindValue(":Index_count",RecordNr);
			Query1.bindValue(":Index_count",Record_count_lines);
			Query1.bindValue(":Section",DXF_code_tables[0].Section);
			Query1.bindValue(":Command",DXF_code_tables[0].Command);


			Record_count_lines++;

			/*if (DXF_code_tables[0].dxf_5!="")
			{
				Query1.bindValue(":ID_instruction",DXF_code_tables[0].dxf_5);

			}
			else
			{
				Query1.bindValue(":ID_instruction",DXF_code_tables[0].ID_instruction);
			}*/

			Query1.bindValue(":ID_instruction",DXF_code_tables[0].ID_instruction);
			Query1.bindValue(":dxfbase",BlockNaamID);
			Query1.bindValue(":Command_count",QString::number(Command_Count));
			Query1.bindValue(":dxf_m1",DXF_code_tables[x1].dxf_m1);
			Query1.bindValue(":dxf_m2",DXF_code_tables[x1].dxf_m2);
			Query1.bindValue(":dxf_m3",DXF_code_tables[x1].dxf_m3);
			Query1.bindValue(":dxf_m4",DXF_code_tables[x1].dxf_m4);
			Query1.bindValue(":dxf_m1",DXF_code_tables[x1].dxf_m5);

			Query1.bindValue(":dxf_0",DXF_code_tables[x1].dxf_0);
			Query1.bindValue(":dxf_1",DXF_code_tables[x1].dxf_1);
			Query1.bindValue(":dxf_2",DXF_code_tables[x1].dxf_2);
			Query1.bindValue(":dxf_3",DXF_code_tables[x1].dxf_3);
			Query1.bindValue(":dxf_4",DXF_code_tables[x1].dxf_4);
			Query1.bindValue(":dxf_5",DXF_code_tables[0].dxf_5);
			Query1.bindValue(":dxf_6",DXF_code_tables[x1].dxf_6);
			Query1.bindValue(":dxf_7",DXF_code_tables[x1].dxf_7);
			Query1.bindValue(":dxf_8",DXF_code_tables[x1].dxf_8);
			Query1.bindValue(":dxf_9",DXF_code_tables[x1].dxf_9);
			Query1.bindValue(":dxf_10",DXF_code_tables[x1].dxf_10);
			Query1.bindValue(":dxf_10",DXF_code_tables[x1].dxf_10);
			Query1.bindValue(":dxf_11",DXF_code_tables[x1].dxf_11);
			Query1.bindValue(":dxf_12",DXF_code_tables[x1].dxf_12);
			Query1.bindValue(":dxf_13",DXF_code_tables[x1].dxf_13);
			Query1.bindValue(":dxf_14",DXF_code_tables[x1].dxf_14);
			Query1.bindValue(":dxf_15",DXF_code_tables[x1].dxf_15);
			Query1.bindValue(":dxf_16",DXF_code_tables[x1].dxf_16);
			Query1.bindValue(":dxf_17",DXF_code_tables[x1].dxf_17);
			Query1.bindValue(":dxf_18",DXF_code_tables[x1].dxf_18);
			Query1.bindValue(":dxf_19",DXF_code_tables[x1].dxf_19);
			Query1.bindValue(":dxf_20",DXF_code_tables[x1].dxf_20);
			Query1.bindValue(":dxf_21",DXF_code_tables[x1].dxf_21);
			Query1.bindValue(":dxf_22",DXF_code_tables[x1].dxf_22);
			Query1.bindValue(":dxf_23",DXF_code_tables[x1].dxf_23);
			Query1.bindValue(":dxf_24",DXF_code_tables[x1].dxf_24);
			Query1.bindValue(":dxf_25",DXF_code_tables[x1].dxf_25);
			Query1.bindValue(":dxf_26",DXF_code_tables[x1].dxf_26);
			Query1.bindValue(":dxf_27",DXF_code_tables[x1].dxf_27);
			Query1.bindValue(":dxf_28",DXF_code_tables[x1].dxf_28);
			Query1.bindValue(":dxf_29",DXF_code_tables[x1].dxf_29);
			Query1.bindValue(":dxf_30",DXF_code_tables[x1].dxf_30);
			Query1.bindValue(":dxf_31",DXF_code_tables[x1].dxf_31);
			Query1.bindValue(":dxf_32",DXF_code_tables[x1].dxf_32);
			Query1.bindValue(":dxf_33",DXF_code_tables[x1].dxf_33);
			Query1.bindValue(":dxf_34",DXF_code_tables[x1].dxf_34);
			Query1.bindValue(":dxf_35",DXF_code_tables[x1].dxf_35);
			Query1.bindValue(":dxf_36",DXF_code_tables[x1].dxf_36);
			Query1.bindValue(":dxf_37",DXF_code_tables[x1].dxf_37);
			Query1.bindValue(":dxf_38",DXF_code_tables[x1].dxf_38);
			Query1.bindValue(":dxf_39",DXF_code_tables[x1].dxf_39);
			Query1.bindValue(":dxf_40",DXF_code_tables[x1].dxf_40);
			Query1.bindValue(":dxf_41",DXF_code_tables[x1].dxf_41);
			Query1.bindValue(":dxf_42",DXF_code_tables[x1].dxf_42);
			Query1.bindValue(":dxf_43",DXF_code_tables[x1].dxf_43);
			Query1.bindValue(":dxf_44",DXF_code_tables[x1].dxf_44);
			Query1.bindValue(":dxf_45",DXF_code_tables[x1].dxf_45);
			Query1.bindValue(":dxf_46",DXF_code_tables[x1].dxf_46);
			Query1.bindValue(":dxf_47",DXF_code_tables[x1].dxf_47);
			Query1.bindValue(":dxf_48",DXF_code_tables[x1].dxf_48);
			Query1.bindValue(":dxf_49",DXF_code_tables[x1].dxf_49);
			Query1.bindValue(":dxf_50",DXF_code_tables[x1].dxf_50);
			Query1.bindValue(":dxf_51",DXF_code_tables[x1].dxf_51);
			Query1.bindValue(":dxf_52",DXF_code_tables[x1].dxf_52);
			Query1.bindValue(":dxf_53",DXF_code_tables[x1].dxf_53);
			Query1.bindValue(":dxf_54",DXF_code_tables[x1].dxf_54);
			Query1.bindValue(":dxf_55",DXF_code_tables[x1].dxf_55);
			Query1.bindValue(":dxf_56",DXF_code_tables[x1].dxf_56);
			Query1.bindValue(":dxf_57",DXF_code_tables[x1].dxf_57);
			Query1.bindValue(":dxf_58",DXF_code_tables[x1].dxf_58);
			Query1.bindValue(":dxf_59",DXF_code_tables[x1].dxf_59);
			Query1.bindValue(":dxf_60",DXF_code_tables[x1].dxf_60);
			Query1.bindValue(":dxf_61",DXF_code_tables[x1].dxf_61);
			Query1.bindValue(":dxf_62",DXF_code_tables[x1].dxf_62);
			Query1.bindValue(":dxf_63",DXF_code_tables[x1].dxf_63);
			Query1.bindValue(":dxf_64",DXF_code_tables[x1].dxf_64);
			Query1.bindValue(":dxf_65",DXF_code_tables[x1].dxf_65);
			Query1.bindValue(":dxf_66",DXF_code_tables[x1].dxf_66);
			Query1.bindValue(":dxf_67",DXF_code_tables[x1].dxf_67);
			Query1.bindValue(":dxf_68",DXF_code_tables[x1].dxf_68);
			Query1.bindValue(":dxf_69",DXF_code_tables[x1].dxf_69);
			Query1.bindValue(":dxf_70",DXF_code_tables[x1].dxf_70);
			Query1.bindValue(":dxf_71",DXF_code_tables[x1].dxf_71);
			Query1.bindValue(":dxf_72",DXF_code_tables[x1].dxf_72);
			Query1.bindValue(":dxf_73",DXF_code_tables[x1].dxf_73);
			Query1.bindValue(":dxf_74",DXF_code_tables[x1].dxf_74);
			Query1.bindValue(":dxf_75",DXF_code_tables[x1].dxf_75);
			Query1.bindValue(":dxf_76",DXF_code_tables[x1].dxf_76);
			Query1.bindValue(":dxf_77",DXF_code_tables[x1].dxf_77);
			Query1.bindValue(":dxf_78",DXF_code_tables[x1].dxf_78);
			Query1.bindValue(":dxf_79",DXF_code_tables[x1].dxf_79);


			Query1.bindValue(":dxf_90",DXF_code_tables[x1].dxf_90);
			Query1.bindValue(":dxf_91",DXF_code_tables[x1].dxf_91);
			Query1.bindValue(":dxf_92",DXF_code_tables[x1].dxf_92);
			Query1.bindValue(":dxf_93",DXF_code_tables[x1].dxf_93);
			Query1.bindValue(":dxf_94",DXF_code_tables[x1].dxf_94);
			Query1.bindValue(":dxf_95",DXF_code_tables[x1].dxf_95);
			Query1.bindValue(":dxf_96",DXF_code_tables[x1].dxf_96);
			Query1.bindValue(":dxf_97",DXF_code_tables[x1].dxf_97);
			Query1.bindValue(":dxf_98",DXF_code_tables[x1].dxf_98);
			Query1.bindValue(":dxf_99",DXF_code_tables[x1].dxf_99);
			Query1.bindValue(":dxf_100",DXF_code_tables[x1].dxf_100);

			Query1.bindValue(":dxf_102",DXF_code_tables[x1].dxf_102);


			Query1.bindValue(":dxf_105",DXF_code_tables[x1].dxf_105);


			Query1.bindValue(":dxf_110",DXF_code_tables[x1].dxf_110);
			Query1.bindValue(":dxf_111",DXF_code_tables[x1].dxf_111);
			Query1.bindValue(":dxf_112",DXF_code_tables[x1].dxf_112);
			Query1.bindValue(":dxf_113",DXF_code_tables[x1].dxf_113);
			Query1.bindValue(":dxf_114",DXF_code_tables[x1].dxf_114);
			Query1.bindValue(":dxf_115",DXF_code_tables[x1].dxf_115);
			Query1.bindValue(":dxf_116",DXF_code_tables[x1].dxf_116);
			Query1.bindValue(":dxf_117",DXF_code_tables[x1].dxf_117);
			Query1.bindValue(":dxf_118",DXF_code_tables[x1].dxf_118);
			Query1.bindValue(":dxf_119",DXF_code_tables[x1].dxf_119);
			Query1.bindValue(":dxf_120",DXF_code_tables[x1].dxf_120);
			Query1.bindValue(":dxf_121",DXF_code_tables[x1].dxf_121);
			Query1.bindValue(":dxf_122",DXF_code_tables[x1].dxf_122);
			Query1.bindValue(":dxf_123",DXF_code_tables[x1].dxf_123);
			Query1.bindValue(":dxf_124",DXF_code_tables[x1].dxf_124);
			Query1.bindValue(":dxf_125",DXF_code_tables[x1].dxf_125);
			Query1.bindValue(":dxf_126",DXF_code_tables[x1].dxf_126);
			Query1.bindValue(":dxf_127",DXF_code_tables[x1].dxf_127);
			Query1.bindValue(":dxf_128",DXF_code_tables[x1].dxf_128);
			Query1.bindValue(":dxf_129",DXF_code_tables[x1].dxf_129);
			Query1.bindValue(":dxf_130",DXF_code_tables[x1].dxf_130);
			Query1.bindValue(":dxf_131",DXF_code_tables[x1].dxf_131);
			Query1.bindValue(":dxf_132",DXF_code_tables[x1].dxf_132);
			Query1.bindValue(":dxf_133",DXF_code_tables[x1].dxf_133);
			Query1.bindValue(":dxf_134",DXF_code_tables[x1].dxf_134);
			Query1.bindValue(":dxf_135",DXF_code_tables[x1].dxf_135);
			Query1.bindValue(":dxf_136",DXF_code_tables[x1].dxf_136);
			Query1.bindValue(":dxf_137",DXF_code_tables[x1].dxf_137);
			Query1.bindValue(":dxf_138",DXF_code_tables[x1].dxf_138);
			Query1.bindValue(":dxf_139",DXF_code_tables[x1].dxf_139);
			Query1.bindValue(":dxf_140",DXF_code_tables[x1].dxf_140);
			Query1.bindValue(":dxf_141",DXF_code_tables[x1].dxf_141);
			Query1.bindValue(":dxf_142",DXF_code_tables[x1].dxf_142);
			Query1.bindValue(":dxf_143",DXF_code_tables[x1].dxf_143);
			Query1.bindValue(":dxf_144",DXF_code_tables[x1].dxf_144);
			Query1.bindValue(":dxf_145",DXF_code_tables[x1].dxf_145);
			Query1.bindValue(":dxf_146",DXF_code_tables[x1].dxf_146);
			Query1.bindValue(":dxf_147",DXF_code_tables[x1].dxf_147);
			Query1.bindValue(":dxf_148",DXF_code_tables[x1].dxf_148);
			Query1.bindValue(":dxf_149",DXF_code_tables[x1].dxf_149);


			Query1.bindValue(":dxf_160",DXF_code_tables[x1].dxf_160);
			Query1.bindValue(":dxf_161",DXF_code_tables[x1].dxf_161);
			Query1.bindValue(":dxf_162",DXF_code_tables[x1].dxf_162);
			Query1.bindValue(":dxf_163",DXF_code_tables[x1].dxf_163);
			Query1.bindValue(":dxf_164",DXF_code_tables[x1].dxf_164);
			Query1.bindValue(":dxf_165",DXF_code_tables[x1].dxf_165);
			Query1.bindValue(":dxf_166",DXF_code_tables[x1].dxf_166);
			Query1.bindValue(":dxf_167",DXF_code_tables[x1].dxf_167);
			Query1.bindValue(":dxf_168",DXF_code_tables[x1].dxf_168);
			Query1.bindValue(":dxf_169",DXF_code_tables[x1].dxf_169);
			Query1.bindValue(":dxf_170",DXF_code_tables[x1].dxf_170);
			Query1.bindValue(":dxf_171",DXF_code_tables[x1].dxf_171);
			Query1.bindValue(":dxf_172",DXF_code_tables[x1].dxf_172);
			Query1.bindValue(":dxf_173",DXF_code_tables[x1].dxf_173);
			Query1.bindValue(":dxf_174",DXF_code_tables[x1].dxf_174);
			Query1.bindValue(":dxf_175",DXF_code_tables[x1].dxf_175);
			Query1.bindValue(":dxf_176",DXF_code_tables[x1].dxf_176);
			Query1.bindValue(":dxf_177",DXF_code_tables[x1].dxf_177);
			Query1.bindValue(":dxf_178",DXF_code_tables[x1].dxf_178);
			Query1.bindValue(":dxf_179",DXF_code_tables[x1].dxf_179);


			Query1.bindValue(":dxf_210",DXF_code_tables[x1].dxf_210);
			Query1.bindValue(":dxf_211",DXF_code_tables[x1].dxf_211);
			Query1.bindValue(":dxf_212",DXF_code_tables[x1].dxf_212);
			Query1.bindValue(":dxf_213",DXF_code_tables[x1].dxf_213);
			Query1.bindValue(":dxf_214",DXF_code_tables[x1].dxf_214);
			Query1.bindValue(":dxf_215",DXF_code_tables[x1].dxf_215);
			Query1.bindValue(":dxf_216",DXF_code_tables[x1].dxf_216);
			Query1.bindValue(":dxf_217",DXF_code_tables[x1].dxf_217);
			Query1.bindValue(":dxf_218",DXF_code_tables[x1].dxf_218);
			Query1.bindValue(":dxf_219",DXF_code_tables[x1].dxf_219);
			Query1.bindValue(":dxf_220",DXF_code_tables[x1].dxf_220);
			Query1.bindValue(":dxf_221",DXF_code_tables[x1].dxf_221);
			Query1.bindValue(":dxf_222",DXF_code_tables[x1].dxf_222);
			Query1.bindValue(":dxf_223",DXF_code_tables[x1].dxf_223);
			Query1.bindValue(":dxf_224",DXF_code_tables[x1].dxf_224);
			Query1.bindValue(":dxf_225",DXF_code_tables[x1].dxf_225);
			Query1.bindValue(":dxf_226",DXF_code_tables[x1].dxf_226);
			Query1.bindValue(":dxf_227",DXF_code_tables[x1].dxf_227);
			Query1.bindValue(":dxf_228",DXF_code_tables[x1].dxf_228);
			Query1.bindValue(":dxf_229",DXF_code_tables[x1].dxf_229);
			Query1.bindValue(":dxf_230",DXF_code_tables[x1].dxf_230);
			Query1.bindValue(":dxf_231",DXF_code_tables[x1].dxf_231);
			Query1.bindValue(":dxf_232",DXF_code_tables[x1].dxf_232);
			Query1.bindValue(":dxf_233",DXF_code_tables[x1].dxf_233);
			Query1.bindValue(":dxf_234",DXF_code_tables[x1].dxf_234);
			Query1.bindValue(":dxf_235",DXF_code_tables[x1].dxf_235);
			Query1.bindValue(":dxf_236",DXF_code_tables[x1].dxf_236);
			Query1.bindValue(":dxf_237",DXF_code_tables[x1].dxf_237);
			Query1.bindValue(":dxf_238",DXF_code_tables[x1].dxf_238);
			Query1.bindValue(":dxf_239",DXF_code_tables[x1].dxf_239);


			Query1.bindValue(":dxf_270",DXF_code_tables[x1].dxf_270);
			Query1.bindValue(":dxf_271",DXF_code_tables[x1].dxf_271);
			Query1.bindValue(":dxf_272",DXF_code_tables[x1].dxf_272);
			Query1.bindValue(":dxf_273",DXF_code_tables[x1].dxf_273);
			Query1.bindValue(":dxf_274",DXF_code_tables[x1].dxf_274);
			Query1.bindValue(":dxf_275",DXF_code_tables[x1].dxf_275);
			Query1.bindValue(":dxf_276",DXF_code_tables[x1].dxf_276);
			Query1.bindValue(":dxf_277",DXF_code_tables[x1].dxf_277);
			Query1.bindValue(":dxf_278",DXF_code_tables[x1].dxf_278);
			Query1.bindValue(":dxf_279",DXF_code_tables[x1].dxf_279);
			Query1.bindValue(":dxf_280",DXF_code_tables[x1].dxf_280);
			Query1.bindValue(":dxf_281",DXF_code_tables[x1].dxf_281);
			Query1.bindValue(":dxf_282",DXF_code_tables[x1].dxf_282);
			Query1.bindValue(":dxf_283",DXF_code_tables[x1].dxf_283);
			Query1.bindValue(":dxf_284",DXF_code_tables[x1].dxf_284);
			Query1.bindValue(":dxf_285",DXF_code_tables[x1].dxf_285);
			Query1.bindValue(":dxf_286",DXF_code_tables[x1].dxf_286);
			Query1.bindValue(":dxf_287",DXF_code_tables[x1].dxf_287);
			Query1.bindValue(":dxf_288",DXF_code_tables[x1].dxf_288);
			Query1.bindValue(":dxf_289",DXF_code_tables[x1].dxf_289);
			Query1.bindValue(":dxf_290",DXF_code_tables[x1].dxf_290);
			Query1.bindValue(":dxf_291",DXF_code_tables[x1].dxf_291);
			Query1.bindValue(":dxf_292",DXF_code_tables[x1].dxf_292);
			Query1.bindValue(":dxf_293",DXF_code_tables[x1].dxf_293);
			Query1.bindValue(":dxf_294",DXF_code_tables[x1].dxf_294);
			Query1.bindValue(":dxf_295",DXF_code_tables[x1].dxf_295);
			Query1.bindValue(":dxf_296",DXF_code_tables[x1].dxf_296);
			Query1.bindValue(":dxf_297",DXF_code_tables[x1].dxf_297);
			Query1.bindValue(":dxf_298",DXF_code_tables[x1].dxf_298);
			Query1.bindValue(":dxf_299",DXF_code_tables[x1].dxf_299);
			Query1.bindValue(":dxf_300",DXF_code_tables[x1].dxf_300);
			Query1.bindValue(":dxf_301",DXF_code_tables[x1].dxf_301);
			Query1.bindValue(":dxf_302",DXF_code_tables[x1].dxf_302);
			Query1.bindValue(":dxf_303",DXF_code_tables[x1].dxf_303);
			Query1.bindValue(":dxf_304",DXF_code_tables[x1].dxf_304);
			Query1.bindValue(":dxf_305",DXF_code_tables[x1].dxf_305);
			Query1.bindValue(":dxf_306",DXF_code_tables[x1].dxf_306);
			Query1.bindValue(":dxf_307",DXF_code_tables[x1].dxf_307);
			Query1.bindValue(":dxf_308",DXF_code_tables[x1].dxf_308);
			Query1.bindValue(":dxf_309",DXF_code_tables[x1].dxf_309);
			Query1.bindValue(":dxf_310",DXF_code_tables[x1].dxf_310);
			Query1.bindValue(":dxf_311",DXF_code_tables[x1].dxf_311);
			Query1.bindValue(":dxf_312",DXF_code_tables[x1].dxf_312);
			Query1.bindValue(":dxf_313",DXF_code_tables[x1].dxf_313);
			Query1.bindValue(":dxf_314",DXF_code_tables[x1].dxf_314);
			Query1.bindValue(":dxf_315",DXF_code_tables[x1].dxf_315);
			Query1.bindValue(":dxf_316",DXF_code_tables[x1].dxf_316);
			Query1.bindValue(":dxf_317",DXF_code_tables[x1].dxf_317);
			Query1.bindValue(":dxf_318",DXF_code_tables[x1].dxf_318);
			Query1.bindValue(":dxf_319",DXF_code_tables[x1].dxf_319);
			Query1.bindValue(":dxf_320",DXF_code_tables[x1].dxf_320);
			Query1.bindValue(":dxf_321",DXF_code_tables[x1].dxf_321);
			Query1.bindValue(":dxf_322",DXF_code_tables[x1].dxf_322);
			Query1.bindValue(":dxf_323",DXF_code_tables[x1].dxf_323);
			Query1.bindValue(":dxf_324",DXF_code_tables[x1].dxf_324);
			Query1.bindValue(":dxf_325",DXF_code_tables[x1].dxf_325);
			Query1.bindValue(":dxf_326",DXF_code_tables[x1].dxf_326);
			Query1.bindValue(":dxf_327",DXF_code_tables[x1].dxf_327);
			Query1.bindValue(":dxf_328",DXF_code_tables[x1].dxf_328);
			Query1.bindValue(":dxf_329",DXF_code_tables[x1].dxf_329);
			Query1.bindValue(":dxf_330",DXF_code_tables[x1].dxf_330);
			Query1.bindValue(":dxf_331",DXF_code_tables[x1].dxf_331);
			Query1.bindValue(":dxf_332",DXF_code_tables[x1].dxf_332);
			Query1.bindValue(":dxf_333",DXF_code_tables[x1].dxf_333);
			Query1.bindValue(":dxf_334",DXF_code_tables[x1].dxf_334);
			Query1.bindValue(":dxf_335",DXF_code_tables[x1].dxf_335);
			Query1.bindValue(":dxf_336",DXF_code_tables[x1].dxf_336);
			Query1.bindValue(":dxf_337",DXF_code_tables[x1].dxf_337);
			Query1.bindValue(":dxf_338",DXF_code_tables[x1].dxf_338);
			Query1.bindValue(":dxf_339",DXF_code_tables[x1].dxf_339);
			Query1.bindValue(":dxf_340",DXF_code_tables[x1].dxf_340);
			Query1.bindValue(":dxf_341",DXF_code_tables[x1].dxf_341);
			Query1.bindValue(":dxf_342",DXF_code_tables[x1].dxf_342);
			Query1.bindValue(":dxf_343",DXF_code_tables[x1].dxf_343);
			Query1.bindValue(":dxf_344",DXF_code_tables[x1].dxf_344);
			Query1.bindValue(":dxf_345",DXF_code_tables[x1].dxf_345);
			Query1.bindValue(":dxf_346",DXF_code_tables[x1].dxf_346);
			Query1.bindValue(":dxf_347",DXF_code_tables[x1].dxf_347);
			Query1.bindValue(":dxf_348",DXF_code_tables[x1].dxf_348);
			Query1.bindValue(":dxf_349",DXF_code_tables[x1].dxf_349);
			Query1.bindValue(":dxf_350",DXF_code_tables[x1].dxf_350);
			Query1.bindValue(":dxf_351",DXF_code_tables[x1].dxf_351);
			Query1.bindValue(":dxf_352",DXF_code_tables[x1].dxf_352);
			Query1.bindValue(":dxf_353",DXF_code_tables[x1].dxf_353);
			Query1.bindValue(":dxf_354",DXF_code_tables[x1].dxf_354);
			Query1.bindValue(":dxf_355",DXF_code_tables[x1].dxf_355);
			Query1.bindValue(":dxf_356",DXF_code_tables[x1].dxf_356);
			Query1.bindValue(":dxf_357",DXF_code_tables[x1].dxf_357);
			Query1.bindValue(":dxf_358",DXF_code_tables[x1].dxf_358);
			Query1.bindValue(":dxf_359",DXF_code_tables[x1].dxf_359);
			Query1.bindValue(":dxf_360",DXF_code_tables[x1].dxf_360);
			Query1.bindValue(":dxf_361",DXF_code_tables[x1].dxf_361);
			Query1.bindValue(":dxf_362",DXF_code_tables[x1].dxf_362);
			Query1.bindValue(":dxf_363",DXF_code_tables[x1].dxf_363);
			Query1.bindValue(":dxf_364",DXF_code_tables[x1].dxf_364);
			Query1.bindValue(":dxf_365",DXF_code_tables[x1].dxf_365);
			Query1.bindValue(":dxf_366",DXF_code_tables[x1].dxf_366);
			Query1.bindValue(":dxf_367",DXF_code_tables[x1].dxf_367);
			Query1.bindValue(":dxf_368",DXF_code_tables[x1].dxf_368);
			Query1.bindValue(":dxf_369",DXF_code_tables[x1].dxf_369);
			Query1.bindValue(":dxf_370",DXF_code_tables[x1].dxf_370);
			Query1.bindValue(":dxf_371",DXF_code_tables[x1].dxf_371);
			Query1.bindValue(":dxf_372",DXF_code_tables[x1].dxf_372);
			Query1.bindValue(":dxf_373",DXF_code_tables[x1].dxf_373);
			Query1.bindValue(":dxf_374",DXF_code_tables[x1].dxf_374);
			Query1.bindValue(":dxf_375",DXF_code_tables[x1].dxf_375);
			Query1.bindValue(":dxf_376",DXF_code_tables[x1].dxf_376);
			Query1.bindValue(":dxf_377",DXF_code_tables[x1].dxf_377);
			Query1.bindValue(":dxf_378",DXF_code_tables[x1].dxf_378);
			Query1.bindValue(":dxf_379",DXF_code_tables[x1].dxf_379);
			Query1.bindValue(":dxf_380",DXF_code_tables[x1].dxf_380);
			Query1.bindValue(":dxf_381",DXF_code_tables[x1].dxf_381);
			Query1.bindValue(":dxf_382",DXF_code_tables[x1].dxf_382);
			Query1.bindValue(":dxf_383",DXF_code_tables[x1].dxf_383);
			Query1.bindValue(":dxf_384",DXF_code_tables[x1].dxf_384);
			Query1.bindValue(":dxf_385",DXF_code_tables[x1].dxf_385);
			Query1.bindValue(":dxf_386",DXF_code_tables[x1].dxf_386);
			Query1.bindValue(":dxf_387",DXF_code_tables[x1].dxf_387);
			Query1.bindValue(":dxf_388",DXF_code_tables[x1].dxf_388);
			Query1.bindValue(":dxf_389",DXF_code_tables[x1].dxf_389);
			Query1.bindValue(":dxf_390",DXF_code_tables[x1].dxf_390);
			Query1.bindValue(":dxf_391",DXF_code_tables[x1].dxf_391);
			Query1.bindValue(":dxf_392",DXF_code_tables[x1].dxf_392);
			Query1.bindValue(":dxf_393",DXF_code_tables[x1].dxf_393);
			Query1.bindValue(":dxf_394",DXF_code_tables[x1].dxf_394);
			Query1.bindValue(":dxf_395",DXF_code_tables[x1].dxf_395);
			Query1.bindValue(":dxf_396",DXF_code_tables[x1].dxf_396);
			Query1.bindValue(":dxf_397",DXF_code_tables[x1].dxf_397);
			Query1.bindValue(":dxf_398",DXF_code_tables[x1].dxf_398);
			Query1.bindValue(":dxf_399",DXF_code_tables[x1].dxf_399);
			Query1.bindValue(":dxf_400",DXF_code_tables[x1].dxf_400);
			Query1.bindValue(":dxf_401",DXF_code_tables[x1].dxf_401);
			Query1.bindValue(":dxf_402",DXF_code_tables[x1].dxf_402);
			Query1.bindValue(":dxf_403",DXF_code_tables[x1].dxf_403);
			Query1.bindValue(":dxf_404",DXF_code_tables[x1].dxf_404);
			Query1.bindValue(":dxf_405",DXF_code_tables[x1].dxf_405);
			Query1.bindValue(":dxf_406",DXF_code_tables[x1].dxf_406);
			Query1.bindValue(":dxf_407",DXF_code_tables[x1].dxf_407);
			Query1.bindValue(":dxf_408",DXF_code_tables[x1].dxf_408);
			Query1.bindValue(":dxf_409",DXF_code_tables[x1].dxf_409);
			Query1.bindValue(":dxf_410",DXF_code_tables[x1].dxf_410);
			Query1.bindValue(":dxf_411",DXF_code_tables[x1].dxf_411);
			Query1.bindValue(":dxf_412",DXF_code_tables[x1].dxf_412);
			Query1.bindValue(":dxf_413",DXF_code_tables[x1].dxf_413);
			Query1.bindValue(":dxf_414",DXF_code_tables[x1].dxf_414);
			Query1.bindValue(":dxf_415",DXF_code_tables[x1].dxf_415);
			Query1.bindValue(":dxf_416",DXF_code_tables[x1].dxf_416);
			Query1.bindValue(":dxf_417",DXF_code_tables[x1].dxf_417);
			Query1.bindValue(":dxf_418",DXF_code_tables[x1].dxf_418);
			Query1.bindValue(":dxf_419",DXF_code_tables[x1].dxf_419);
			Query1.bindValue(":dxf_420",DXF_code_tables[x1].dxf_420);
			Query1.bindValue(":dxf_421",DXF_code_tables[x1].dxf_421);
			Query1.bindValue(":dxf_422",DXF_code_tables[x1].dxf_422);
			Query1.bindValue(":dxf_423",DXF_code_tables[x1].dxf_423);
			Query1.bindValue(":dxf_424",DXF_code_tables[x1].dxf_424);
			Query1.bindValue(":dxf_425",DXF_code_tables[x1].dxf_425);
			Query1.bindValue(":dxf_426",DXF_code_tables[x1].dxf_426);
			Query1.bindValue(":dxf_427",DXF_code_tables[x1].dxf_427);
			Query1.bindValue(":dxf_428",DXF_code_tables[x1].dxf_428);
			Query1.bindValue(":dxf_429",DXF_code_tables[x1].dxf_429);
			Query1.bindValue(":dxf_430",DXF_code_tables[x1].dxf_430);
			Query1.bindValue(":dxf_431",DXF_code_tables[x1].dxf_431);
			Query1.bindValue(":dxf_432",DXF_code_tables[x1].dxf_432);
			Query1.bindValue(":dxf_433",DXF_code_tables[x1].dxf_433);
			Query1.bindValue(":dxf_434",DXF_code_tables[x1].dxf_434);
			Query1.bindValue(":dxf_435",DXF_code_tables[x1].dxf_435);
			Query1.bindValue(":dxf_436",DXF_code_tables[x1].dxf_436);
			Query1.bindValue(":dxf_437",DXF_code_tables[x1].dxf_437);
			Query1.bindValue(":dxf_438",DXF_code_tables[x1].dxf_438);
			Query1.bindValue(":dxf_439",DXF_code_tables[x1].dxf_439);
			Query1.bindValue(":dxf_440",DXF_code_tables[x1].dxf_440);
			Query1.bindValue(":dxf_441",DXF_code_tables[x1].dxf_441);
			Query1.bindValue(":dxf_442",DXF_code_tables[x1].dxf_442);
			Query1.bindValue(":dxf_443",DXF_code_tables[x1].dxf_443);
			Query1.bindValue(":dxf_444",DXF_code_tables[x1].dxf_444);
			Query1.bindValue(":dxf_445",DXF_code_tables[x1].dxf_445);
			Query1.bindValue(":dxf_446",DXF_code_tables[x1].dxf_446);
			Query1.bindValue(":dxf_447",DXF_code_tables[x1].dxf_447);
			Query1.bindValue(":dxf_448",DXF_code_tables[x1].dxf_448);
			Query1.bindValue(":dxf_449",DXF_code_tables[x1].dxf_449);
			Query1.bindValue(":dxf_450",DXF_code_tables[x1].dxf_450);
			Query1.bindValue(":dxf_451",DXF_code_tables[x1].dxf_451);
			Query1.bindValue(":dxf_452",DXF_code_tables[x1].dxf_452);
			Query1.bindValue(":dxf_453",DXF_code_tables[x1].dxf_453);
			Query1.bindValue(":dxf_454",DXF_code_tables[x1].dxf_454);
			Query1.bindValue(":dxf_455",DXF_code_tables[x1].dxf_455);
			Query1.bindValue(":dxf_456",DXF_code_tables[x1].dxf_456);
			Query1.bindValue(":dxf_457",DXF_code_tables[x1].dxf_457);
			Query1.bindValue(":dxf_458",DXF_code_tables[x1].dxf_458);
			Query1.bindValue(":dxf_459",DXF_code_tables[x1].dxf_459);


			Query1.bindValue(":dxf_460",DXF_code_tables[x1].dxf_460);
			Query1.bindValue(":dxf_461",DXF_code_tables[x1].dxf_461);
			Query1.bindValue(":dxf_462",DXF_code_tables[x1].dxf_462);
			Query1.bindValue(":dxf_463",DXF_code_tables[x1].dxf_463);
			Query1.bindValue(":dxf_464",DXF_code_tables[x1].dxf_464);
			Query1.bindValue(":dxf_465",DXF_code_tables[x1].dxf_465);
			Query1.bindValue(":dxf_466",DXF_code_tables[x1].dxf_466);
			Query1.bindValue(":dxf_467",DXF_code_tables[x1].dxf_467);
			Query1.bindValue(":dxf_468",DXF_code_tables[x1].dxf_468);
			Query1.bindValue(":dxf_469",DXF_code_tables[x1].dxf_469);
			Query1.bindValue(":dxf_470",DXF_code_tables[x1].dxf_470);
			Query1.bindValue(":dxf_471",DXF_code_tables[x1].dxf_471);
			Query1.bindValue(":dxf_472",DXF_code_tables[x1].dxf_472);
			Query1.bindValue(":dxf_473",DXF_code_tables[x1].dxf_473);
			Query1.bindValue(":dxf_474",DXF_code_tables[x1].dxf_474);
			Query1.bindValue(":dxf_475",DXF_code_tables[x1].dxf_475);
			Query1.bindValue(":dxf_476",DXF_code_tables[x1].dxf_476);
			Query1.bindValue(":dxf_477",DXF_code_tables[x1].dxf_477);
			Query1.bindValue(":dxf_478",DXF_code_tables[x1].dxf_478);
			Query1.bindValue(":dxf_479",DXF_code_tables[x1].dxf_479);
			Query1.bindValue(":dxf_480",DXF_code_tables[x1].dxf_480);
			Query1.bindValue(":dxf_481",DXF_code_tables[x1].dxf_481);
			Query1.bindValue(":dxf_482",DXF_code_tables[x1].dxf_482);
			Query1.bindValue(":dxf_483",DXF_code_tables[x1].dxf_483);
			Query1.bindValue(":dxf_484",DXF_code_tables[x1].dxf_484);
			Query1.bindValue(":dxf_485",DXF_code_tables[x1].dxf_485);
			Query1.bindValue(":dxf_486",DXF_code_tables[x1].dxf_486);
			Query1.bindValue(":dxf_487",DXF_code_tables[x1].dxf_487);
			Query1.bindValue(":dxf_488",DXF_code_tables[x1].dxf_488);
			Query1.bindValue(":dxf_489",DXF_code_tables[x1].dxf_489);


			Query1.bindValue(":dxf_999",DXF_code_tables[x1].dxf_999);


			Query1.bindValue(":dxf_1000",DXF_code_tables[x1].dxf_1000);
			Query1.bindValue(":dxf_1001",DXF_code_tables[x1].dxf_1001);
			Query1.bindValue(":dxf_1002",DXF_code_tables[x1].dxf_1002);
			Query1.bindValue(":dxf_1003",DXF_code_tables[x1].dxf_1003);
			Query1.bindValue(":dxf_1004",DXF_code_tables[x1].dxf_1004);
			Query1.bindValue(":dxf_1005",DXF_code_tables[x1].dxf_1005);
			Query1.bindValue(":dxf_1006",DXF_code_tables[x1].dxf_1006);
			Query1.bindValue(":dxf_1007",DXF_code_tables[x1].dxf_1007);
			Query1.bindValue(":dxf_1008",DXF_code_tables[x1].dxf_1008);
			Query1.bindValue(":dxf_1009",DXF_code_tables[x1].dxf_1009);
			Query1.bindValue(":dxf_1010",DXF_code_tables[x1].dxf_1010);
			Query1.bindValue(":dxf_1011",DXF_code_tables[x1].dxf_1011);
			Query1.bindValue(":dxf_1012",DXF_code_tables[x1].dxf_1012);
			Query1.bindValue(":dxf_1013",DXF_code_tables[x1].dxf_1013);
			Query1.bindValue(":dxf_1014",DXF_code_tables[x1].dxf_1014);
			Query1.bindValue(":dxf_1015",DXF_code_tables[x1].dxf_1015);
			Query1.bindValue(":dxf_1016",DXF_code_tables[x1].dxf_1016);
			Query1.bindValue(":dxf_1017",DXF_code_tables[x1].dxf_1017);
			Query1.bindValue(":dxf_1018",DXF_code_tables[x1].dxf_1018);
			Query1.bindValue(":dxf_1019",DXF_code_tables[x1].dxf_1019);
			Query1.bindValue(":dxf_1020",DXF_code_tables[x1].dxf_1020);
			Query1.bindValue(":dxf_1021",DXF_code_tables[x1].dxf_1021);
			Query1.bindValue(":dxf_1022",DXF_code_tables[x1].dxf_1022);
			Query1.bindValue(":dxf_1023",DXF_code_tables[x1].dxf_1023);
			Query1.bindValue(":dxf_1024",DXF_code_tables[x1].dxf_1024);
			Query1.bindValue(":dxf_1025",DXF_code_tables[x1].dxf_1025);
			Query1.bindValue(":dxf_1026",DXF_code_tables[x1].dxf_1026);
			Query1.bindValue(":dxf_1027",DXF_code_tables[x1].dxf_1027);
			Query1.bindValue(":dxf_1028",DXF_code_tables[x1].dxf_1028);
			Query1.bindValue(":dxf_1029",DXF_code_tables[x1].dxf_1029);
			Query1.bindValue(":dxf_1030",DXF_code_tables[x1].dxf_1030);
			Query1.bindValue(":dxf_1031",DXF_code_tables[x1].dxf_1031);
			Query1.bindValue(":dxf_1032",DXF_code_tables[x1].dxf_1032);
			Query1.bindValue(":dxf_1033",DXF_code_tables[x1].dxf_1033);
			Query1.bindValue(":dxf_1034",DXF_code_tables[x1].dxf_1034);
			Query1.bindValue(":dxf_1035",DXF_code_tables[x1].dxf_1035);
			Query1.bindValue(":dxf_1036",DXF_code_tables[x1].dxf_1036);
			Query1.bindValue(":dxf_1037",DXF_code_tables[x1].dxf_1037);
			Query1.bindValue(":dxf_1038",DXF_code_tables[x1].dxf_1038);
			Query1.bindValue(":dxf_1039",DXF_code_tables[x1].dxf_1039);
			Query1.bindValue(":dxf_1040",DXF_code_tables[x1].dxf_1040);
			Query1.bindValue(":dxf_1041",DXF_code_tables[x1].dxf_1041);
			Query1.bindValue(":dxf_1042",DXF_code_tables[x1].dxf_1042);
			Query1.bindValue(":dxf_1043",DXF_code_tables[x1].dxf_1043);
			Query1.bindValue(":dxf_1044",DXF_code_tables[x1].dxf_1044);
			Query1.bindValue(":dxf_1045",DXF_code_tables[x1].dxf_1045);
			Query1.bindValue(":dxf_1046",DXF_code_tables[x1].dxf_1046);
			Query1.bindValue(":dxf_1047",DXF_code_tables[x1].dxf_1047);
			Query1.bindValue(":dxf_1048",DXF_code_tables[x1].dxf_1048);
			Query1.bindValue(":dxf_1049",DXF_code_tables[x1].dxf_1049);
			Query1.bindValue(":dxf_1050",DXF_code_tables[x1].dxf_1050);
			Query1.bindValue(":dxf_1051",DXF_code_tables[x1].dxf_1051);
			Query1.bindValue(":dxf_1052",DXF_code_tables[x1].dxf_1052);
			Query1.bindValue(":dxf_1053",DXF_code_tables[x1].dxf_1053);
			Query1.bindValue(":dxf_1054",DXF_code_tables[x1].dxf_1054);
			Query1.bindValue(":dxf_1055",DXF_code_tables[x1].dxf_1055);
			Query1.bindValue(":dxf_1056",DXF_code_tables[x1].dxf_1056);
			Query1.bindValue(":dxf_1057",DXF_code_tables[x1].dxf_1057);
			Query1.bindValue(":dxf_1058",DXF_code_tables[x1].dxf_1058);
			Query1.bindValue(":dxf_1059",DXF_code_tables[x1].dxf_1059);
			Query1.bindValue(":dxf_1060",DXF_code_tables[x1].dxf_1060);
			Query1.bindValue(":dxf_1061",DXF_code_tables[x1].dxf_1061);
			Query1.bindValue(":dxf_1062",DXF_code_tables[x1].dxf_1062);
			Query1.bindValue(":dxf_1063",DXF_code_tables[x1].dxf_1063);
			Query1.bindValue(":dxf_1064",DXF_code_tables[x1].dxf_1064);
			Query1.bindValue(":dxf_1065",DXF_code_tables[x1].dxf_1065);
			Query1.bindValue(":dxf_1066",DXF_code_tables[x1].dxf_1066);
			Query1.bindValue(":dxf_1067",DXF_code_tables[x1].dxf_1067);
			Query1.bindValue(":dxf_1068",DXF_code_tables[x1].dxf_1068);
			Query1.bindValue(":dxf_1069",DXF_code_tables[x1].dxf_1069);
			Query1.bindValue(":dxf_1070",DXF_code_tables[x1].dxf_1070);
			Query1.bindValue(":dxf_1071",DXF_code_tables[x1].dxf_1071);

			//x10++;
			x2=Query1.exec();

		//x2=Query1.exec();
		x1++;
        //m_db.commit();

	}


	//m_db.exec(QsqlString);

	m_db.commit();
	return Record_count_lines;
}


int dbManager::DB_dbManager_added_records(const QString &pathname, int32_t *Max_lines, int32_t *Record_count, QString dxf_type)
{
    QString path = pathname;
	connect (this ,SIGNAL (send_log(const QString &)),this,SLOT(update_log(const QString &)));

	m_db.transaction();
	QSqlQuery Query1;

	Signal_log1.clear();
	Signal_log1.append(" DB add records : ");
	Signal_log1.append("\n");
	Signal_log1.append("============================================================================");
	//Signal_log1.append("\n");

	emit send_log(Signal_log1);

	x1=0;
	//x10=0;

	QsqlString="INSERT INTO ";
	QsqlString.append(dxf_type);
	QsqlString.append(" (Index_count, Section");
	QsqlString.append(", dxfbase, Command, ID_instruction, Command_count");
	QsqlString.append(", dxf_m1, dxf_m2, dxf_m3, dxf_m4, dxf_m5");
	QsqlString.append(", dxf_0, dxf_1, dxf_2, dxf_3, dxf_4, dxf_5, dxf_6, dxf_7, dxf_8, dxf_9");
	QsqlString.append(", dxf_10, dxf_11, dxf_12, dxf_13, dxf_14, dxf_15, dxf_16, dxf_17, dxf_18, dxf_19");
	QsqlString.append(", dxf_20, dxf_21, dxf_22, dxf_23, dxf_24, dxf_25, dxf_26, dxf_27, dxf_28, dxf_29");
	QsqlString.append(", dxf_30, dxf_31, dxf_32, dxf_33, dxf_34, dxf_35, dxf_36, dxf_37, dxf_38, dxf_39");
	QsqlString.append(", dxf_40, dxf_41, dxf_42, dxf_43, dxf_44, dxf_45, dxf_46, dxf_47, dxf_48, dxf_49");
	QsqlString.append(", dxf_50, dxf_51, dxf_52, dxf_53, dxf_54, dxf_55, dxf_56, dxf_57, dxf_58, dxf_59");
	QsqlString.append(", dxf_60, dxf_61, dxf_62, dxf_63, dxf_64, dxf_65, dxf_66, dxf_67, dxf_68, dxf_69");
	QsqlString.append(", dxf_70, dxf_71, dxf_72, dxf_73, dxf_74, dxf_75, dxf_76, dxf_77, dxf_78, dxf_79");
	QsqlString.append(", dxf_90, dxf_91, dxf_92, dxf_93, dxf_94, dxf_95, dxf_96, dxf_97, dxf_98, dxf_99");
	QsqlString.append(", dxf_100, dxf_102, dxf_105");
	QsqlString.append(", dxf_110, dxf_111, dxf_112, dxf_113, dxf_114, dxf_115, dxf_116, dxf_117, dxf_118, dxf_119");
	QsqlString.append(", dxf_120, dxf_121, dxf_122, dxf_123, dxf_124, dxf_125, dxf_126, dxf_127, dxf_128, dxf_129");
	QsqlString.append(", dxf_130, dxf_131, dxf_132, dxf_133, dxf_134, dxf_135, dxf_136, dxf_137, dxf_138, dxf_139");
	QsqlString.append(", dxf_140, dxf_141, dxf_142, dxf_143, dxf_144, dxf_145, dxf_146, dxf_147, dxf_148, dxf_149");

	QsqlString.append(", dxf_160, dxf_161, dxf_162, dxf_163, dxf_164, dxf_165, dxf_166, dxf_167, dxf_168, dxf_169");
	QsqlString.append(", dxf_170, dxf_171, dxf_172, dxf_173, dxf_174, dxf_175, dxf_176, dxf_177, dxf_178, dxf_179");

	QsqlString.append(", dxf_210, dxf_211, dxf_212, dxf_213, dxf_214, dxf_215, dxf_216, dxf_217, dxf_218, dxf_219");
	QsqlString.append(", dxf_220, dxf_221, dxf_222, dxf_223, dxf_224, dxf_225, dxf_226, dxf_227, dxf_228, dxf_229");
	QsqlString.append(", dxf_230, dxf_231, dxf_232, dxf_233, dxf_234, dxf_235, dxf_236, dxf_237, dxf_238, dxf_239");

	QsqlString.append(", dxf_270, dxf_271, dxf_272, dxf_273, dxf_274, dxf_275, dxf_276, dxf_277, dxf_278, dxf_279");
	QsqlString.append(", dxf_280, dxf_281, dxf_282, dxf_283, dxf_284, dxf_285, dxf_286, dxf_287, dxf_288, dxf_289");
	QsqlString.append(", dxf_290, dxf_291, dxf_292, dxf_293, dxf_294, dxf_295, dxf_296, dxf_297, dxf_298, dxf_299");
	QsqlString.append(", dxf_300, dxf_301, dxf_302, dxf_303, dxf_304, dxf_305, dxf_306, dxf_307, dxf_308, dxf_309");
	QsqlString.append(", dxf_310, dxf_311, dxf_312, dxf_313, dxf_314, dxf_315, dxf_316, dxf_317, dxf_318, dxf_319");
	QsqlString.append(", dxf_320, dxf_321, dxf_322, dxf_323, dxf_324, dxf_325, dxf_326, dxf_327, dxf_328, dxf_329");
	QsqlString.append(", dxf_330, dxf_331, dxf_332, dxf_333, dxf_334, dxf_335, dxf_336, dxf_337, dxf_338, dxf_339");
	QsqlString.append(", dxf_340, dxf_341, dxf_342, dxf_343, dxf_344, dxf_345, dxf_346, dxf_347, dxf_348, dxf_349");
	QsqlString.append(", dxf_350, dxf_351, dxf_352, dxf_353, dxf_354, dxf_355, dxf_356, dxf_357, dxf_358, dxf_359");
	QsqlString.append(", dxf_360, dxf_361, dxf_362, dxf_363, dxf_364, dxf_365, dxf_366, dxf_367, dxf_368, dxf_369");
	QsqlString.append(", dxf_370, dxf_371, dxf_372, dxf_373, dxf_374, dxf_375, dxf_376, dxf_377, dxf_378, dxf_379");
	QsqlString.append(", dxf_380, dxf_381, dxf_382, dxf_383, dxf_384, dxf_385, dxf_386, dxf_387, dxf_388, dxf_389");
	QsqlString.append(", dxf_390, dxf_391, dxf_392, dxf_393, dxf_394, dxf_395, dxf_396, dxf_397, dxf_398, dxf_399");
	QsqlString.append(", dxf_400, dxf_401, dxf_402, dxf_403, dxf_404, dxf_405, dxf_406, dxf_407, dxf_408, dxf_409");
	QsqlString.append(", dxf_410, dxf_411, dxf_412, dxf_413, dxf_414, dxf_415, dxf_416, dxf_417, dxf_418, dxf_419");
	QsqlString.append(", dxf_420, dxf_421, dxf_422, dxf_423, dxf_424, dxf_425, dxf_426, dxf_427, dxf_428, dxf_429");
	QsqlString.append(", dxf_430, dxf_431, dxf_432, dxf_433, dxf_434, dxf_435, dxf_436, dxf_437, dxf_438, dxf_439");
	QsqlString.append(", dxf_440, dxf_441, dxf_442, dxf_443, dxf_444, dxf_445, dxf_446, dxf_447, dxf_448, dxf_449");
	QsqlString.append(", dxf_450, dxf_451, dxf_452, dxf_453, dxf_454, dxf_455, dxf_456, dxf_457, dxf_458, dxf_459");
	QsqlString.append(", dxf_460, dxf_461, dxf_462, dxf_463, dxf_464, dxf_465, dxf_466, dxf_467, dxf_468, dxf_469");
	QsqlString.append(", dxf_470, dxf_471, dxf_472, dxf_473, dxf_474, dxf_475, dxf_476, dxf_477, dxf_478, dxf_479");
	QsqlString.append(", dxf_480, dxf_481, dxf_482, dxf_483, dxf_484, dxf_485, dxf_486, dxf_487, dxf_488, dxf_489");
	QsqlString.append(", dxf_999");
	QsqlString.append(", dxf_1000, dxf_1001, dxf_1002, dxf_1003, dxf_1004, dxf_1005, dxf_1006, dxf_1007, dxf_1008, dxf_1009");
	QsqlString.append(", dxf_1010, dxf_1011, dxf_1012, dxf_1013, dxf_1014, dxf_1015, dxf_1016, dxf_1017, dxf_1018, dxf_1019");
	QsqlString.append(", dxf_1020, dxf_1021, dxf_1022, dxf_1023, dxf_1024, dxf_1025, dxf_1026, dxf_1027, dxf_1028, dxf_1029");
	QsqlString.append(", dxf_1030, dxf_1031, dxf_1032, dxf_1033, dxf_1034, dxf_1035, dxf_1036, dxf_1037, dxf_1038, dxf_1039");
	QsqlString.append(", dxf_1040, dxf_1041, dxf_1042, dxf_1043, dxf_1044, dxf_1045, dxf_1046, dxf_1047, dxf_1048, dxf_1049");
	QsqlString.append(", dxf_1050, dxf_1051, dxf_1052, dxf_1053, dxf_1054, dxf_1055, dxf_1056, dxf_1057, dxf_1058, dxf_1059");
	QsqlString.append(", dxf_1060, dxf_1061, dxf_1062, dxf_1063, dxf_1064, dxf_1065, dxf_1066, dxf_1067, dxf_1068, dxf_1069");
	QsqlString.append(", dxf_1070, dxf_1071");
	QsqlString.append(")");
	QsqlString.append(" VALUES (:Index_count, :Section");
	QsqlString.append(", :dxfbase, :Command, :ID_instruction, :Command_count");
	QsqlString.append(", :dxf_m1, :dxf_m2, :dxf_m3, :dxf_m4, :dxf_m5");
	QsqlString.append(", :dxf_0, :dxf_1, :dxf_2, :dxf_3, :dxf_4, :dxf_5, :dxf_6, :dxf_7, :dxf_8, :dxf_9");//dxf_0
	QsqlString.append(", :dxf_10, :dxf_11, :dxf_12, :dxf_13, :dxf_14, :dxf_15, :dxf_16, :dxf_17, :dxf_18, :dxf_19");
	QsqlString.append(", :dxf_20, :dxf_21, :dxf_22, :dxf_23, :dxf_24, :dxf_25, :dxf_26, :dxf_27, :dxf_28, :dxf_29");
	QsqlString.append(", :dxf_30, :dxf_31, :dxf_32, :dxf_33, :dxf_34, :dxf_35, :dxf_36, :dxf_37, :dxf_38, :dxf_39");
	QsqlString.append(", :dxf_40, :dxf_41, :dxf_42, :dxf_43, :dxf_44, :dxf_45, :dxf_46, :dxf_47, :dxf_48, :dxf_49");
	QsqlString.append(", :dxf_50, :dxf_51, :dxf_52, :dxf_53, :dxf_54, :dxf_55, :dxf_56, :dxf_57, :dxf_58, :dxf_59");
	QsqlString.append(", :dxf_60, :dxf_61, :dxf_62, :dxf_63, :dxf_64, :dxf_65, :dxf_66, :dxf_67, :dxf_68, :dxf_69");
	QsqlString.append(", :dxf_70, :dxf_71, :dxf_72, :dxf_73, :dxf_74, :dxf_75, :dxf_76, :dxf_77, :dxf_78, :dxf_79");
	QsqlString.append(", :dxf_90, :dxf_91, :dxf_92, :dxf_93, :dxf_94, :dxf_95, :dxf_96, :dxf_97, :dxf_98, :dxf_99");
	QsqlString.append(", :dxf_100, :dxf_102, :dxf_105");
	QsqlString.append(", :dxf_110, :dxf_111, :dxf_112, :dxf_113, :dxf_114, :dxf_115, :dxf_116, :dxf_117, :dxf_118, :dxf_119");
	QsqlString.append(", :dxf_120, :dxf_121, :dxf_122, :dxf_123, :dxf_124, :dxf_125, :dxf_126, :dxf_127, :dxf_128, :dxf_129");
	QsqlString.append(", :dxf_130, :dxf_131, :dxf_132, :dxf_133, :dxf_134, :dxf_135, :dxf_136, :dxf_137, :dxf_138, :dxf_139");
	QsqlString.append(", :dxf_140, :dxf_141, :dxf_142, :dxf_143, :dxf_144, :dxf_145, :dxf_146, :dxf_147, :dxf_148, :dxf_149");

	QsqlString.append(", :dxf_160, :dxf_161, :dxf_162, :dxf_163, :dxf_164, :dxf_165, :dxf_166, :dxf_167, :dxf_168, :dxf_169");
	QsqlString.append(", :dxf_170, :dxf_171, :dxf_172, :dxf_173, :dxf_174, :dxf_175, :dxf_176, :dxf_177, :dxf_178, :dxf_179");


	QsqlString.append(", :dxf_210, :dxf_211, :dxf_212, :dxf_213, :dxf_214, :dxf_215, :dxf_216, :dxf_217, :dxf_218, :dxf_219");
	QsqlString.append(", :dxf_220, :dxf_221, :dxf_222, :dxf_223, :dxf_224, :dxf_225, :dxf_226, :dxf_227, :dxf_228, :dxf_229");
	QsqlString.append(", :dxf_230, :dxf_231, :dxf_232, :dxf_233, :dxf_234, :dxf_235, :dxf_236, :dxf_237, :dxf_238, :dxf_239");

	QsqlString.append(", :dxf_270, :dxf_271, :dxf_272, :dxf_273, :dxf_274, :dxf_275, :dxf_276, :dxf_277, :dxf_278, :dxf_279");
	QsqlString.append(", :dxf_280, :dxf_281, :dxf_282, :dxf_283, :dxf_284, :dxf_285, :dxf_286, :dxf_287, :dxf_288, :dxf_289");
	QsqlString.append(", :dxf_290, :dxf_291, :dxf_292, :dxf_293, :dxf_294, :dxf_295, :dxf_296, :dxf_297, :dxf_298, :dxf_299");
	QsqlString.append(", :dxf_300, :dxf_301, :dxf_302, :dxf_303, :dxf_304, :dxf_305, :dxf_306, :dxf_307, :dxf_308, :dxf_309");
	QsqlString.append(", :dxf_310, :dxf_311, :dxf_312, :dxf_313, :dxf_314, :dxf_315, :dxf_316, :dxf_317, :dxf_318, :dxf_319");
	QsqlString.append(", :dxf_320, :dxf_321, :dxf_322, :dxf_323, :dxf_324, :dxf_325, :dxf_326, :dxf_327, :dxf_328, :dxf_329");
	QsqlString.append(", :dxf_330, :dxf_331, :dxf_332, :dxf_333, :dxf_334, :dxf_335, :dxf_336, :dxf_337, :dxf_338, :dxf_339");
	QsqlString.append(", :dxf_340, :dxf_341, :dxf_342, :dxf_343, :dxf_344, :dxf_345, :dxf_346, :dxf_347, :dxf_348, :dxf_349");
	QsqlString.append(", :dxf_350, :dxf_351, :dxf_352, :dxf_353, :dxf_354, :dxf_355, :dxf_356, :dxf_357, :dxf_358, :dxf_359");
	QsqlString.append(", :dxf_360, :dxf_361, :dxf_362, :dxf_363, :dxf_364, :dxf_365, :dxf_366, :dxf_367, :dxf_368, :dxf_369");
	QsqlString.append(", :dxf_370, :dxf_371, :dxf_372, :dxf_373, :dxf_374, :dxf_375, :dxf_376, :dxf_377, :dxf_378, :dxf_379");
	QsqlString.append(", :dxf_380, :dxf_381, :dxf_382, :dxf_383, :dxf_384, :dxf_385, :dxf_386, :dxf_387, :dxf_388, :dxf_389");
	QsqlString.append(", :dxf_390, :dxf_391, :dxf_392, :dxf_393, :dxf_394, :dxf_395, :dxf_396, :dxf_397, :dxf_398, :dxf_399");
	QsqlString.append(", :dxf_400, :dxf_401, :dxf_402, :dxf_403, :dxf_404, :dxf_405, :dxf_406, :dxf_407, :dxf_408, :dxf_409");
	QsqlString.append(", :dxf_410, :dxf_411, :dxf_412, :dxf_413, :dxf_414, :dxf_415, :dxf_416, :dxf_417, :dxf_418, :dxf_419");
	QsqlString.append(", :dxf_420, :dxf_421, :dxf_422, :dxf_423, :dxf_424, :dxf_425, :dxf_426, :dxf_427, :dxf_428, :dxf_429");
	QsqlString.append(", :dxf_430, :dxf_431, :dxf_432, :dxf_433, :dxf_434, :dxf_435, :dxf_436, :dxf_437, :dxf_438, :dxf_439");
	QsqlString.append(", :dxf_440, :dxf_441, :dxf_442, :dxf_443, :dxf_444, :dxf_445, :dxf_446, :dxf_447, :dxf_448, :dxf_449");
	QsqlString.append(", :dxf_450, :dxf_451, :dxf_452, :dxf_453, :dxf_454, :dxf_455, :dxf_456, :dxf_457, :dxf_458, :dxf_459");
	QsqlString.append(", :dxf_460, :dxf_461, :dxf_462, :dxf_463, :dxf_464, :dxf_465, :dxf_466, :dxf_467, :dxf_468, :dxf_469");
	QsqlString.append(", :dxf_470, :dxf_471, :dxf_472, :dxf_473, :dxf_474, :dxf_475, :dxf_476, :dxf_477, :dxf_478, :dxf_479");
	QsqlString.append(", :dxf_480, :dxf_481, :dxf_482, :dxf_483, :dxf_484, :dxf_485, :dxf_486, :dxf_487, :dxf_488, :dxf_489");
	QsqlString.append(", :dxf_999");
	QsqlString.append(", :dxf_1000, :dxf_1001, :dxf_1002, :dxf_1003, :dxf_1004, :dxf_1005, :dxf_1006, :dxf_1007, :dxf_1008, :dxf_1009");
	QsqlString.append(", :dxf_1010, :dxf_1011, :dxf_1012, :dxf_1013, :dxf_1014, :dxf_1015, :dxf_1016, :dxf_1017, :dxf_1018, :dxf_1019");
	QsqlString.append(", :dxf_1020, :dxf_1021, :dxf_1022, :dxf_1023, :dxf_1024, :dxf_1025, :dxf_1026, :dxf_1027, :dxf_1028, :dxf_1029");
	QsqlString.append(", :dxf_1030, :dxf_1031, :dxf_1032, :dxf_1033, :dxf_1034, :dxf_1035, :dxf_1036, :dxf_1037, :dxf_1038, :dxf_1039");
	QsqlString.append(", :dxf_1040, :dxf_1041, :dxf_1042, :dxf_1043, :dxf_1044, :dxf_1045, :dxf_1046, :dxf_1047, :dxf_1048, :dxf_1049");
	QsqlString.append(", :dxf_1050, :dxf_1051, :dxf_1052, :dxf_1053, :dxf_1054, :dxf_1055, :dxf_1056, :dxf_1057, :dxf_1058, :dxf_1059");
	QsqlString.append(", :dxf_1060, :dxf_1061, :dxf_1062, :dxf_1063, :dxf_1064, :dxf_1065, :dxf_1066, :dxf_1067, :dxf_1068, :dxf_1069");
	QsqlString.append(", :dxf_1070, :dxf_1071");

	QsqlString.append(")");


	Query1.prepare(QsqlString);

	Command_Count=-1;
	Max_count_lines=*Max_lines;
	Record_count_lines=*Record_count;
	x1=0;

	Signal_log1.clear();
	Signal_log1.append(" index : ");
	Signal_log1.append(QString::number(Record_count_lines));
	Signal_log1.append(DXF_code_tables[0].Section);
	Signal_log1.append(DXF_code_tables[0].Command);


	//Signal_log1.append(" DB add records : ");
	//Signal_log1.append("\n");
	//Signal_log1.append("============================================================================");
	Signal_log1.append("\n");

	emit send_log(Signal_log1);

	while ((x1<Max_count_lines) and (x1<DXF_codes_set))
	{
		//DXF_code_tables[x1].ID_instruction=1;
		//Record_count_lines++;
		//x10++;
		if(Command_Count>=Max_count_lines)
		{
			Command_Count=-1;
		}

		Command_Count++;
		//Record_count_lines++;
		x2=0;

		//while (x10<Max_count_lines)
		//{

		//Record_count_lines++;



			//RecordNr=(QString::number(Record_count_lines));
			//Query1.bindValue(":Index_count",RecordNr);
			Query1.bindValue(":Index_count",Record_count_lines);
			Query1.bindValue(":Section",DXF_code_tables[0].Section);
			Query1.bindValue(":Command",DXF_code_tables[0].Command);


			Record_count_lines++;

			/*if (DXF_code_tables[0].dxf_5!="")
			{
				Query1.bindValue(":ID_instruction",DXF_code_tables[0].dxf_5);

			}
			else
			{
				Query1.bindValue(":ID_instruction",DXF_code_tables[0].ID_instruction);
			}*/

			Query1.bindValue(":ID_instruction",DXF_code_tables[0].ID_instruction);
			Query1.bindValue(":dxfbase",BlockNaamID);
			Query1.bindValue(":Command_count",QString::number(Command_Count));
			//Query1.bindValue(":dxf_m1",DXF_code_tables[x1].dxf_m1);
			//Query1.bindValue(":dxf_m2",DXF_code_tables[x1].dxf_m2);
			//Query1.bindValue(":dxf_m3",DXF_code_tables[x1].dxf_m3);
			//Query1.bindValue(":dxf_m4",DXF_code_tables[x1].dxf_m4);
			//Query1.bindValue(":dxf_m1",DXF_code_tables[x1].dxf_m5);

			Query1.bindValue(":dxf_0",DXF_main_base[0].split_list_1[0][x1]);
			Query1.bindValue(":dxf_1",DXF_main_base[0].split_list_1[1][x1]);
			Query1.bindValue(":dxf_2",DXF_main_base[0].split_list_1[2][x1]);
			Query1.bindValue(":dxf_3",DXF_main_base[0].split_list_1[3][x1]);
			Query1.bindValue(":dxf_4",DXF_main_base[0].split_list_1[4][x1]);
			Query1.bindValue(":dxf_5",DXF_main_base[0].split_list_1[5][x1]);
			Query1.bindValue(":dxf_6",DXF_main_base[0].split_list_1[6][x1]);
			Query1.bindValue(":dxf_7",DXF_main_base[0].split_list_1[7][x1]);
			Query1.bindValue(":dxf_8",DXF_main_base[0].split_list_1[8][x1]);
			Query1.bindValue(":dxf_9",DXF_main_base[0].split_list_1[9][x1]);
			Query1.bindValue(":dxf_10",DXF_main_base[0].split_list_1[10][x1]);
			Query1.bindValue(":dxf_11",DXF_main_base[0].split_list_1[11][x1]);
			Query1.bindValue(":dxf_12",DXF_main_base[0].split_list_1[12][x1]);
			Query1.bindValue(":dxf_13",DXF_main_base[0].split_list_1[13][x1]);
			Query1.bindValue(":dxf_14",DXF_main_base[0].split_list_1[14][x1]);
			Query1.bindValue(":dxf_15",DXF_main_base[0].split_list_1[15][x1]);
			Query1.bindValue(":dxf_16",DXF_main_base[0].split_list_1[16][x1]);
			Query1.bindValue(":dxf_17",DXF_main_base[0].split_list_1[17][x1]);
			Query1.bindValue(":dxf_18",DXF_main_base[0].split_list_1[18][x1]);
			Query1.bindValue(":dxf_19",DXF_main_base[0].split_list_1[19][x1]);
			Query1.bindValue(":dxf_20",DXF_main_base[0].split_list_1[20][x1]);
			Query1.bindValue(":dxf_21",DXF_main_base[0].split_list_1[21][x1]);
			Query1.bindValue(":dxf_22",DXF_main_base[0].split_list_1[22][x1]);
			Query1.bindValue(":dxf_23",DXF_main_base[0].split_list_1[23][x1]);
			Query1.bindValue(":dxf_24",DXF_main_base[0].split_list_1[24][x1]);
			Query1.bindValue(":dxf_25",DXF_main_base[0].split_list_1[25][x1]);
			Query1.bindValue(":dxf_26",DXF_main_base[0].split_list_1[26][x1]);
			Query1.bindValue(":dxf_27",DXF_main_base[0].split_list_1[27][x1]);
			Query1.bindValue(":dxf_28",DXF_main_base[0].split_list_1[28][x1]);
			Query1.bindValue(":dxf_29",DXF_main_base[0].split_list_1[29][x1]);
			Query1.bindValue(":dxf_30",DXF_main_base[0].split_list_1[30][x1]);
			Query1.bindValue(":dxf_31",DXF_main_base[0].split_list_1[31][x1]);
			Query1.bindValue(":dxf_32",DXF_main_base[0].split_list_1[32][x1]);
			Query1.bindValue(":dxf_33",DXF_main_base[0].split_list_1[33][x1]);
			Query1.bindValue(":dxf_34",DXF_main_base[0].split_list_1[34][x1]);
			Query1.bindValue(":dxf_35",DXF_main_base[0].split_list_1[35][x1]);
			Query1.bindValue(":dxf_36",DXF_main_base[0].split_list_1[36][x1]);
			Query1.bindValue(":dxf_37",DXF_main_base[0].split_list_1[37][x1]);
			Query1.bindValue(":dxf_38",DXF_main_base[0].split_list_1[38][x1]);
			Query1.bindValue(":dxf_39",DXF_main_base[0].split_list_1[39][x1]);
			Query1.bindValue(":dxf_40",DXF_main_base[0].split_list_1[40][x1]);
			Query1.bindValue(":dxf_41",DXF_main_base[0].split_list_1[41][x1]);
			Query1.bindValue(":dxf_42",DXF_main_base[0].split_list_1[42][x1]);
			Query1.bindValue(":dxf_43",DXF_main_base[0].split_list_1[43][x1]);
			Query1.bindValue(":dxf_44",DXF_main_base[0].split_list_1[44][x1]);
			Query1.bindValue(":dxf_45",DXF_main_base[0].split_list_1[45][x1]);
			Query1.bindValue(":dxf_46",DXF_main_base[0].split_list_1[46][x1]);
			Query1.bindValue(":dxf_47",DXF_main_base[0].split_list_1[47][x1]);
			Query1.bindValue(":dxf_48",DXF_main_base[0].split_list_1[48][x1]);
			Query1.bindValue(":dxf_49",DXF_main_base[0].split_list_1[49][x1]);
			Query1.bindValue(":dxf_50",DXF_main_base[0].split_list_1[50][x1]);
			Query1.bindValue(":dxf_51",DXF_main_base[0].split_list_1[51][x1]);
			Query1.bindValue(":dxf_52",DXF_main_base[0].split_list_1[52][x1]);
			Query1.bindValue(":dxf_53",DXF_main_base[0].split_list_1[53][x1]);
			Query1.bindValue(":dxf_54",DXF_main_base[0].split_list_1[54][x1]);
			Query1.bindValue(":dxf_55",DXF_main_base[0].split_list_1[55][x1]);
			Query1.bindValue(":dxf_56",DXF_main_base[0].split_list_1[56][x1]);
			Query1.bindValue(":dxf_57",DXF_main_base[0].split_list_1[57][x1]);
			Query1.bindValue(":dxf_58",DXF_main_base[0].split_list_1[58][x1]);
			Query1.bindValue(":dxf_59",DXF_main_base[0].split_list_1[59][x1]);
			Query1.bindValue(":dxf_60",DXF_main_base[0].split_list_1[60][x1]);
			Query1.bindValue(":dxf_61",DXF_main_base[0].split_list_1[61][x1]);
			Query1.bindValue(":dxf_62",DXF_main_base[0].split_list_1[62][x1]);
			Query1.bindValue(":dxf_63",DXF_main_base[0].split_list_1[63][x1]);
			Query1.bindValue(":dxf_64",DXF_main_base[0].split_list_1[64][x1]);
			Query1.bindValue(":dxf_65",DXF_main_base[0].split_list_1[65][x1]);
			Query1.bindValue(":dxf_66",DXF_main_base[0].split_list_1[66][x1]);
			Query1.bindValue(":dxf_67",DXF_main_base[0].split_list_1[67][x1]);
			Query1.bindValue(":dxf_68",DXF_main_base[0].split_list_1[68][x1]);
			Query1.bindValue(":dxf_69",DXF_main_base[0].split_list_1[69][x1]);
			Query1.bindValue(":dxf_70",DXF_main_base[0].split_list_1[70][x1]);
			Query1.bindValue(":dxf_71",DXF_main_base[0].split_list_1[71][x1]);
			Query1.bindValue(":dxf_72",DXF_main_base[0].split_list_1[72][x1]);
			Query1.bindValue(":dxf_73",DXF_main_base[0].split_list_1[73][x1]);
			Query1.bindValue(":dxf_74",DXF_main_base[0].split_list_1[74][x1]);
			Query1.bindValue(":dxf_75",DXF_main_base[0].split_list_1[75][x1]);
			Query1.bindValue(":dxf_76",DXF_main_base[0].split_list_1[76][x1]);
			Query1.bindValue(":dxf_77",DXF_main_base[0].split_list_1[77][x1]);
			Query1.bindValue(":dxf_78",DXF_main_base[0].split_list_1[78][x1]);
			Query1.bindValue(":dxf_79",DXF_main_base[0].split_list_1[79][x1]);
			/*Query1.bindValue(":dxf_80",DXF_main_base[0].split_list_1[80][x1]);
			Query1.bindValue(":dxf_81",DXF_main_base[0].split_list_1[81][x1]);
			Query1.bindValue(":dxf_82",DXF_main_base[0].split_list_1[82][x1]);
			Query1.bindValue(":dxf_83",DXF_main_base[0].split_list_1[83][x1]);
			Query1.bindValue(":dxf_84",DXF_main_base[0].split_list_1[84][x1]);
			Query1.bindValue(":dxf_85",DXF_main_base[0].split_list_1[85][x1]);
			Query1.bindValue(":dxf_86",DXF_main_base[0].split_list_1[86][x1]);
			Query1.bindValue(":dxf_87",DXF_main_base[0].split_list_1[87][x1]);
			Query1.bindValue(":dxf_88",DXF_main_base[0].split_list_1[88][x1]);
			Query1.bindValue(":dxf_89",DXF_main_base[0].split_list_1[89][x1]);*/
			Query1.bindValue(":dxf_90",DXF_main_base[0].split_list_1[90][x1]);
			Query1.bindValue(":dxf_91",DXF_main_base[0].split_list_1[91][x1]);
			Query1.bindValue(":dxf_92",DXF_main_base[0].split_list_1[92][x1]);
			Query1.bindValue(":dxf_93",DXF_main_base[0].split_list_1[93][x1]);
			Query1.bindValue(":dxf_94",DXF_main_base[0].split_list_1[94][x1]);
			Query1.bindValue(":dxf_95",DXF_main_base[0].split_list_1[95][x1]);
			Query1.bindValue(":dxf_96",DXF_main_base[0].split_list_1[96][x1]);
			Query1.bindValue(":dxf_97",DXF_main_base[0].split_list_1[97][x1]);
			Query1.bindValue(":dxf_98",DXF_main_base[0].split_list_1[98][x1]);
			Query1.bindValue(":dxf_99",DXF_main_base[0].split_list_1[99][x1]);
			Query1.bindValue(":dxf_100",DXF_main_base[0].split_list_1[100][x1]);
			//Query1.bindValue(":dxf_101",DXF_main_base[0].split_list_1[101][x1]);
			Query1.bindValue(":dxf_102",DXF_main_base[0].split_list_1[102][x1]);
			/*Query1.bindValue(":dxf_103",DXF_main_base[0].split_list_1[103][x1]);
			Query1.bindValue(":dxf_104",DXF_main_base[0].split_list_1[104][x1]);*/
			Query1.bindValue(":dxf_105",DXF_main_base[0].split_list_1[105][x1]);
			/*Query1.bindValue(":dxf_106",DXF_main_base[0].split_list_1[106][x1]);
			Query1.bindValue(":dxf_107",DXF_main_base[0].split_list_1[107][x1]);
			Query1.bindValue(":dxf_108",DXF_main_base[0].split_list_1[108][x1]);
			Query1.bindValue(":dxf_109",DXF_main_base[0].split_list_1[109][x1]);*/
			Query1.bindValue(":dxf_110",DXF_main_base[0].split_list_1[110][x1]);
			Query1.bindValue(":dxf_111",DXF_main_base[0].split_list_1[111][x1]);
			Query1.bindValue(":dxf_112",DXF_main_base[0].split_list_1[112][x1]);
			Query1.bindValue(":dxf_113",DXF_main_base[0].split_list_1[113][x1]);
			Query1.bindValue(":dxf_114",DXF_main_base[0].split_list_1[114][x1]);
			Query1.bindValue(":dxf_115",DXF_main_base[0].split_list_1[115][x1]);
			Query1.bindValue(":dxf_116",DXF_main_base[0].split_list_1[116][x1]);
			Query1.bindValue(":dxf_117",DXF_main_base[0].split_list_1[117][x1]);
			Query1.bindValue(":dxf_118",DXF_main_base[0].split_list_1[118][x1]);
			Query1.bindValue(":dxf_119",DXF_main_base[0].split_list_1[119][x1]);
			Query1.bindValue(":dxf_120",DXF_main_base[0].split_list_1[120][x1]);
			Query1.bindValue(":dxf_121",DXF_main_base[0].split_list_1[121][x1]);
			Query1.bindValue(":dxf_122",DXF_main_base[0].split_list_1[122][x1]);
			Query1.bindValue(":dxf_123",DXF_main_base[0].split_list_1[123][x1]);
			Query1.bindValue(":dxf_124",DXF_main_base[0].split_list_1[124][x1]);
			Query1.bindValue(":dxf_125",DXF_main_base[0].split_list_1[125][x1]);
			Query1.bindValue(":dxf_126",DXF_main_base[0].split_list_1[126][x1]);
			Query1.bindValue(":dxf_127",DXF_main_base[0].split_list_1[127][x1]);
			Query1.bindValue(":dxf_128",DXF_main_base[0].split_list_1[128][x1]);
			Query1.bindValue(":dxf_129",DXF_main_base[0].split_list_1[129][x1]);
			Query1.bindValue(":dxf_130",DXF_main_base[0].split_list_1[130][x1]);
			Query1.bindValue(":dxf_131",DXF_main_base[0].split_list_1[131][x1]);
			Query1.bindValue(":dxf_132",DXF_main_base[0].split_list_1[132][x1]);
			Query1.bindValue(":dxf_133",DXF_main_base[0].split_list_1[133][x1]);
			Query1.bindValue(":dxf_134",DXF_main_base[0].split_list_1[134][x1]);
			Query1.bindValue(":dxf_135",DXF_main_base[0].split_list_1[135][x1]);
			Query1.bindValue(":dxf_136",DXF_main_base[0].split_list_1[136][x1]);
			Query1.bindValue(":dxf_137",DXF_main_base[0].split_list_1[137][x1]);
			Query1.bindValue(":dxf_138",DXF_main_base[0].split_list_1[138][x1]);
			Query1.bindValue(":dxf_139",DXF_main_base[0].split_list_1[139][x1]);
			Query1.bindValue(":dxf_140",DXF_main_base[0].split_list_1[140][x1]);
			Query1.bindValue(":dxf_141",DXF_main_base[0].split_list_1[141][x1]);
			Query1.bindValue(":dxf_142",DXF_main_base[0].split_list_1[142][x1]);
			Query1.bindValue(":dxf_143",DXF_main_base[0].split_list_1[143][x1]);
			Query1.bindValue(":dxf_144",DXF_main_base[0].split_list_1[144][x1]);
			Query1.bindValue(":dxf_145",DXF_main_base[0].split_list_1[145][x1]);
			Query1.bindValue(":dxf_146",DXF_main_base[0].split_list_1[146][x1]);
			Query1.bindValue(":dxf_147",DXF_main_base[0].split_list_1[147][x1]);
			Query1.bindValue(":dxf_148",DXF_main_base[0].split_list_1[148][x1]);
			Query1.bindValue(":dxf_149",DXF_main_base[0].split_list_1[149][x1]);
			/*Query1.bindValue(":dxf_150",DXF_main_base[0].split_list_1[150][x1]);
			Query1.bindValue(":dxf_151",DXF_main_base[0].split_list_1[151][x1]);
			Query1.bindValue(":dxf_152",DXF_main_base[0].split_list_1[152][x1]);
			Query1.bindValue(":dxf_153",DXF_main_base[0].split_list_1[153][x1]);
			Query1.bindValue(":dxf_154",DXF_main_base[0].split_list_1[154][x1]);
			Query1.bindValue(":dxf_155",DXF_main_base[0].split_list_1[155][x1]);
			Query1.bindValue(":dxf_156",DXF_main_base[0].split_list_1[156][x1]);
			Query1.bindValue(":dxf_157",DXF_main_base[0].split_list_1[157][x1]);
			Query1.bindValue(":dxf_158",DXF_main_base[0].split_list_1[158][x1]);
			Query1.bindValue(":dxf_159",DXF_main_base[0].split_list_1[159][x1]);*/
			Query1.bindValue(":dxf_160",DXF_main_base[0].split_list_1[160][x1]);
			Query1.bindValue(":dxf_161",DXF_main_base[0].split_list_1[161][x1]);
			Query1.bindValue(":dxf_162",DXF_main_base[0].split_list_1[162][x1]);
			Query1.bindValue(":dxf_163",DXF_main_base[0].split_list_1[163][x1]);
			Query1.bindValue(":dxf_164",DXF_main_base[0].split_list_1[164][x1]);
			Query1.bindValue(":dxf_165",DXF_main_base[0].split_list_1[165][x1]);
			Query1.bindValue(":dxf_166",DXF_main_base[0].split_list_1[166][x1]);
			Query1.bindValue(":dxf_167",DXF_main_base[0].split_list_1[167][x1]);
			Query1.bindValue(":dxf_168",DXF_main_base[0].split_list_1[168][x1]);
			Query1.bindValue(":dxf_169",DXF_main_base[0].split_list_1[169][x1]);
			Query1.bindValue(":dxf_170",DXF_main_base[0].split_list_1[170][x1]);
			Query1.bindValue(":dxf_171",DXF_main_base[0].split_list_1[171][x1]);
			Query1.bindValue(":dxf_172",DXF_main_base[0].split_list_1[172][x1]);
			Query1.bindValue(":dxf_173",DXF_main_base[0].split_list_1[173][x1]);
			Query1.bindValue(":dxf_174",DXF_main_base[0].split_list_1[174][x1]);
			Query1.bindValue(":dxf_175",DXF_main_base[0].split_list_1[175][x1]);
			Query1.bindValue(":dxf_176",DXF_main_base[0].split_list_1[176][x1]);
			Query1.bindValue(":dxf_177",DXF_main_base[0].split_list_1[177][x1]);
			Query1.bindValue(":dxf_178",DXF_main_base[0].split_list_1[178][x1]);
			Query1.bindValue(":dxf_179",DXF_main_base[0].split_list_1[179][x1]);
			/*Query1.bindValue(":dxf_180",DXF_main_base[0].split_list_1[180][x1]);
			Query1.bindValue(":dxf_181",DXF_main_base[0].split_list_1[181][x1]);
			Query1.bindValue(":dxf_182",DXF_main_base[0].split_list_1[182][x1]);
			Query1.bindValue(":dxf_183",DXF_main_base[0].split_list_1[183][x1]);
			Query1.bindValue(":dxf_184",DXF_main_base[0].split_list_1[184][x1]);
			Query1.bindValue(":dxf_185",DXF_main_base[0].split_list_1[185][x1]);
			Query1.bindValue(":dxf_186",DXF_main_base[0].split_list_1[186][x1]);
			Query1.bindValue(":dxf_187",DXF_main_base[0].split_list_1[187][x1]);
			Query1.bindValue(":dxf_188",DXF_main_base[0].split_list_1[188][x1]);
			Query1.bindValue(":dxf_189",DXF_main_base[0].split_list_1[189][x1]);
			Query1.bindValue(":dxf_190",DXF_main_base[0].split_list_1[190][x1]);
			Query1.bindValue(":dxf_191",DXF_main_base[0].split_list_1[191][x1]);
			Query1.bindValue(":dxf_192",DXF_main_base[0].split_list_1[192][x1]);
			Query1.bindValue(":dxf_193",DXF_main_base[0].split_list_1[193][x1]);
			Query1.bindValue(":dxf_194",DXF_main_base[0].split_list_1[194][x1]);
			Query1.bindValue(":dxf_195",DXF_main_base[0].split_list_1[195][x1]);
			Query1.bindValue(":dxf_196",DXF_main_base[0].split_list_1[196][x1]);
			Query1.bindValue(":dxf_197",DXF_main_base[0].split_list_1[197][x1]);
			Query1.bindValue(":dxf_198",DXF_main_base[0].split_list_1[198][x1]);
			Query1.bindValue(":dxf_199",DXF_main_base[0].split_list_1[199][x1]);
			Query1.bindValue(":dxf_200",DXF_main_base[0].split_list_1[200][x1]);
			Query1.bindValue(":dxf_201",DXF_main_base[0].split_list_1[201][x1]);
			Query1.bindValue(":dxf_202",DXF_main_base[0].split_list_1[202][x1]);
			Query1.bindValue(":dxf_203",DXF_main_base[0].split_list_1[203][x1]);
			Query1.bindValue(":dxf_204",DXF_main_base[0].split_list_1[204][x1]);
			Query1.bindValue(":dxf_205",DXF_main_base[0].split_list_1[205][x1]);
			Query1.bindValue(":dxf_206",DXF_main_base[0].split_list_1[206][x1]);
			Query1.bindValue(":dxf_207",DXF_main_base[0].split_list_1[207][x1]);
			Query1.bindValue(":dxf_208",DXF_main_base[0].split_list_1[208][x1]);
			Query1.bindValue(":dxf_209",DXF_main_base[0].split_list_1[209][x1]);*/
			Query1.bindValue(":dxf_210",DXF_main_base[0].split_list_1[210][x1]);
			Query1.bindValue(":dxf_211",DXF_main_base[0].split_list_1[211][x1]);
			Query1.bindValue(":dxf_212",DXF_main_base[0].split_list_1[212][x1]);
			Query1.bindValue(":dxf_213",DXF_main_base[0].split_list_1[213][x1]);
			Query1.bindValue(":dxf_214",DXF_main_base[0].split_list_1[214][x1]);
			Query1.bindValue(":dxf_215",DXF_main_base[0].split_list_1[215][x1]);
			Query1.bindValue(":dxf_216",DXF_main_base[0].split_list_1[216][x1]);
			Query1.bindValue(":dxf_217",DXF_main_base[0].split_list_1[217][x1]);
			Query1.bindValue(":dxf_218",DXF_main_base[0].split_list_1[218][x1]);
			Query1.bindValue(":dxf_219",DXF_main_base[0].split_list_1[219][x1]);
			Query1.bindValue(":dxf_220",DXF_main_base[0].split_list_1[220][x1]);
			Query1.bindValue(":dxf_221",DXF_main_base[0].split_list_1[221][x1]);
			Query1.bindValue(":dxf_222",DXF_main_base[0].split_list_1[222][x1]);
			Query1.bindValue(":dxf_223",DXF_main_base[0].split_list_1[223][x1]);
			Query1.bindValue(":dxf_224",DXF_main_base[0].split_list_1[224][x1]);
			Query1.bindValue(":dxf_225",DXF_main_base[0].split_list_1[225][x1]);
			Query1.bindValue(":dxf_226",DXF_main_base[0].split_list_1[226][x1]);
			Query1.bindValue(":dxf_227",DXF_main_base[0].split_list_1[227][x1]);
			Query1.bindValue(":dxf_228",DXF_main_base[0].split_list_1[228][x1]);
			Query1.bindValue(":dxf_229",DXF_main_base[0].split_list_1[229][x1]);
			Query1.bindValue(":dxf_230",DXF_main_base[0].split_list_1[230][x1]);
			Query1.bindValue(":dxf_231",DXF_main_base[0].split_list_1[231][x1]);
			Query1.bindValue(":dxf_232",DXF_main_base[0].split_list_1[232][x1]);
			Query1.bindValue(":dxf_233",DXF_main_base[0].split_list_1[233][x1]);
			Query1.bindValue(":dxf_234",DXF_main_base[0].split_list_1[234][x1]);
			Query1.bindValue(":dxf_235",DXF_main_base[0].split_list_1[235][x1]);
			Query1.bindValue(":dxf_236",DXF_main_base[0].split_list_1[236][x1]);
			Query1.bindValue(":dxf_237",DXF_main_base[0].split_list_1[237][x1]);
			Query1.bindValue(":dxf_238",DXF_main_base[0].split_list_1[238][x1]);
			Query1.bindValue(":dxf_239",DXF_main_base[0].split_list_1[239][x1]);
			/*Query1.bindValue(":dxf_240",DXF_main_base[0].split_list_1[240][x1]);
			Query1.bindValue(":dxf_241",DXF_main_base[0].split_list_1[241][x1]);
			Query1.bindValue(":dxf_242",DXF_main_base[0].split_list_1[242][x1]);
			Query1.bindValue(":dxf_243",DXF_main_base[0].split_list_1[243][x1]);
			Query1.bindValue(":dxf_244",DXF_main_base[0].split_list_1[244][x1]);
			Query1.bindValue(":dxf_245",DXF_main_base[0].split_list_1[245][x1]);
			Query1.bindValue(":dxf_246",DXF_main_base[0].split_list_1[246][x1]);
			Query1.bindValue(":dxf_247",DXF_main_base[0].split_list_1[247][x1]);
			Query1.bindValue(":dxf_248",DXF_main_base[0].split_list_1[248][x1]);
			Query1.bindValue(":dxf_249",DXF_main_base[0].split_list_1[249][x1]);
			Query1.bindValue(":dxf_250",DXF_main_base[0].split_list_1[250][x1]);
			Query1.bindValue(":dxf_251",DXF_main_base[0].split_list_1[251][x1]);
			Query1.bindValue(":dxf_252",DXF_main_base[0].split_list_1[252][x1]);
			Query1.bindValue(":dxf_253",DXF_main_base[0].split_list_1[253][x1]);
			Query1.bindValue(":dxf_254",DXF_main_base[0].split_list_1[254][x1]);
			Query1.bindValue(":dxf_255",DXF_main_base[0].split_list_1[255][x1]);
			Query1.bindValue(":dxf_256",DXF_main_base[0].split_list_1[256][x1]);
			Query1.bindValue(":dxf_257",DXF_main_base[0].split_list_1[257][x1]);
			Query1.bindValue(":dxf_258",DXF_main_base[0].split_list_1[258][x1]);
			Query1.bindValue(":dxf_259",DXF_main_base[0].split_list_1[259][x1]);
			Query1.bindValue(":dxf_260",DXF_main_base[0].split_list_1[260][x1]);
			Query1.bindValue(":dxf_261",DXF_main_base[0].split_list_1[261][x1]);
			Query1.bindValue(":dxf_262",DXF_main_base[0].split_list_1[262][x1]);
			Query1.bindValue(":dxf_263",DXF_main_base[0].split_list_1[263][x1]);
			Query1.bindValue(":dxf_264",DXF_main_base[0].split_list_1[264][x1]);
			Query1.bindValue(":dxf_265",DXF_main_base[0].split_list_1[265][x1]);
			Query1.bindValue(":dxf_266",DXF_main_base[0].split_list_1[266][x1]);
			Query1.bindValue(":dxf_267",DXF_main_base[0].split_list_1[267][x1]);
			Query1.bindValue(":dxf_268",DXF_main_base[0].split_list_1[268][x1]);
			Query1.bindValue(":dxf_269",DXF_main_base[0].split_list_1[269][x1]);*/
			Query1.bindValue(":dxf_270",DXF_main_base[0].split_list_1[270][x1]);
			Query1.bindValue(":dxf_271",DXF_main_base[0].split_list_1[271][x1]);
			Query1.bindValue(":dxf_272",DXF_main_base[0].split_list_1[272][x1]);
			Query1.bindValue(":dxf_273",DXF_main_base[0].split_list_1[273][x1]);
			Query1.bindValue(":dxf_274",DXF_main_base[0].split_list_1[274][x1]);
			Query1.bindValue(":dxf_275",DXF_main_base[0].split_list_1[275][x1]);
			Query1.bindValue(":dxf_276",DXF_main_base[0].split_list_1[276][x1]);
			Query1.bindValue(":dxf_277",DXF_main_base[0].split_list_1[277][x1]);
			Query1.bindValue(":dxf_278",DXF_main_base[0].split_list_1[278][x1]);
			Query1.bindValue(":dxf_279",DXF_main_base[0].split_list_1[279][x1]);
			Query1.bindValue(":dxf_280",DXF_main_base[0].split_list_1[280][x1]);
			Query1.bindValue(":dxf_281",DXF_main_base[0].split_list_1[281][x1]);
			Query1.bindValue(":dxf_282",DXF_main_base[0].split_list_1[282][x1]);
			Query1.bindValue(":dxf_283",DXF_main_base[0].split_list_1[283][x1]);
			Query1.bindValue(":dxf_284",DXF_main_base[0].split_list_1[284][x1]);
			Query1.bindValue(":dxf_285",DXF_main_base[0].split_list_1[285][x1]);
			Query1.bindValue(":dxf_286",DXF_main_base[0].split_list_1[286][x1]);
			Query1.bindValue(":dxf_287",DXF_main_base[0].split_list_1[287][x1]);
			Query1.bindValue(":dxf_288",DXF_main_base[0].split_list_1[288][x1]);
			Query1.bindValue(":dxf_289",DXF_main_base[0].split_list_1[289][x1]);
			Query1.bindValue(":dxf_290",DXF_main_base[0].split_list_1[290][x1]);
			Query1.bindValue(":dxf_291",DXF_main_base[0].split_list_1[291][x1]);
			Query1.bindValue(":dxf_292",DXF_main_base[0].split_list_1[292][x1]);
			Query1.bindValue(":dxf_293",DXF_main_base[0].split_list_1[293][x1]);
			Query1.bindValue(":dxf_294",DXF_main_base[0].split_list_1[294][x1]);
			Query1.bindValue(":dxf_295",DXF_main_base[0].split_list_1[295][x1]);
			Query1.bindValue(":dxf_296",DXF_main_base[0].split_list_1[296][x1]);
			Query1.bindValue(":dxf_297",DXF_main_base[0].split_list_1[297][x1]);
			Query1.bindValue(":dxf_298",DXF_main_base[0].split_list_1[298][x1]);
			Query1.bindValue(":dxf_299",DXF_main_base[0].split_list_1[299][x1]);
			Query1.bindValue(":dxf_300",DXF_main_base[0].split_list_1[300][x1]);
			Query1.bindValue(":dxf_301",DXF_main_base[0].split_list_1[301][x1]);
			Query1.bindValue(":dxf_302",DXF_main_base[0].split_list_1[302][x1]);
			Query1.bindValue(":dxf_303",DXF_main_base[0].split_list_1[303][x1]);
			Query1.bindValue(":dxf_304",DXF_main_base[0].split_list_1[304][x1]);
			Query1.bindValue(":dxf_305",DXF_main_base[0].split_list_1[305][x1]);
			Query1.bindValue(":dxf_306",DXF_main_base[0].split_list_1[306][x1]);
			Query1.bindValue(":dxf_307",DXF_main_base[0].split_list_1[307][x1]);
			Query1.bindValue(":dxf_308",DXF_main_base[0].split_list_1[308][x1]);
			Query1.bindValue(":dxf_309",DXF_main_base[0].split_list_1[309][x1]);
			Query1.bindValue(":dxf_310",DXF_main_base[0].split_list_1[310][x1]);
			Query1.bindValue(":dxf_311",DXF_main_base[0].split_list_1[311][x1]);
			Query1.bindValue(":dxf_312",DXF_main_base[0].split_list_1[312][x1]);
			Query1.bindValue(":dxf_313",DXF_main_base[0].split_list_1[313][x1]);
			Query1.bindValue(":dxf_314",DXF_main_base[0].split_list_1[314][x1]);
			Query1.bindValue(":dxf_315",DXF_main_base[0].split_list_1[315][x1]);
			Query1.bindValue(":dxf_316",DXF_main_base[0].split_list_1[316][x1]);
			Query1.bindValue(":dxf_317",DXF_main_base[0].split_list_1[317][x1]);
			Query1.bindValue(":dxf_318",DXF_main_base[0].split_list_1[318][x1]);
			Query1.bindValue(":dxf_319",DXF_main_base[0].split_list_1[319][x1]);
			Query1.bindValue(":dxf_320",DXF_main_base[0].split_list_1[320][x1]);
			Query1.bindValue(":dxf_321",DXF_main_base[0].split_list_1[321][x1]);
			Query1.bindValue(":dxf_322",DXF_main_base[0].split_list_1[322][x1]);
			Query1.bindValue(":dxf_323",DXF_main_base[0].split_list_1[323][x1]);
			Query1.bindValue(":dxf_324",DXF_main_base[0].split_list_1[324][x1]);
			Query1.bindValue(":dxf_325",DXF_main_base[0].split_list_1[325][x1]);
			Query1.bindValue(":dxf_326",DXF_main_base[0].split_list_1[326][x1]);
			Query1.bindValue(":dxf_327",DXF_main_base[0].split_list_1[327][x1]);
			Query1.bindValue(":dxf_328",DXF_main_base[0].split_list_1[328][x1]);
			Query1.bindValue(":dxf_329",DXF_main_base[0].split_list_1[329][x1]);
			Query1.bindValue(":dxf_330",DXF_main_base[0].split_list_1[330][x1]);
			Query1.bindValue(":dxf_331",DXF_main_base[0].split_list_1[331][x1]);
			Query1.bindValue(":dxf_332",DXF_main_base[0].split_list_1[332][x1]);
			Query1.bindValue(":dxf_333",DXF_main_base[0].split_list_1[333][x1]);
			Query1.bindValue(":dxf_334",DXF_main_base[0].split_list_1[334][x1]);
			Query1.bindValue(":dxf_335",DXF_main_base[0].split_list_1[335][x1]);
			Query1.bindValue(":dxf_336",DXF_main_base[0].split_list_1[336][x1]);
			Query1.bindValue(":dxf_337",DXF_main_base[0].split_list_1[337][x1]);
			Query1.bindValue(":dxf_338",DXF_main_base[0].split_list_1[338][x1]);
			Query1.bindValue(":dxf_339",DXF_main_base[0].split_list_1[339][x1]);
			Query1.bindValue(":dxf_340",DXF_main_base[0].split_list_1[340][x1]);
			Query1.bindValue(":dxf_341",DXF_main_base[0].split_list_1[341][x1]);
			Query1.bindValue(":dxf_342",DXF_main_base[0].split_list_1[342][x1]);
			Query1.bindValue(":dxf_343",DXF_main_base[0].split_list_1[343][x1]);
			Query1.bindValue(":dxf_344",DXF_main_base[0].split_list_1[344][x1]);
			Query1.bindValue(":dxf_345",DXF_main_base[0].split_list_1[345][x1]);
			Query1.bindValue(":dxf_346",DXF_main_base[0].split_list_1[346][x1]);
			Query1.bindValue(":dxf_347",DXF_main_base[0].split_list_1[347][x1]);
			Query1.bindValue(":dxf_348",DXF_main_base[0].split_list_1[348][x1]);
			Query1.bindValue(":dxf_349",DXF_main_base[0].split_list_1[349][x1]);
			Query1.bindValue(":dxf_350",DXF_main_base[0].split_list_1[350][x1]);
			Query1.bindValue(":dxf_351",DXF_main_base[0].split_list_1[351][x1]);
			Query1.bindValue(":dxf_352",DXF_main_base[0].split_list_1[352][x1]);
			Query1.bindValue(":dxf_353",DXF_main_base[0].split_list_1[353][x1]);
			Query1.bindValue(":dxf_354",DXF_main_base[0].split_list_1[354][x1]);
			Query1.bindValue(":dxf_355",DXF_main_base[0].split_list_1[355][x1]);
			Query1.bindValue(":dxf_356",DXF_main_base[0].split_list_1[356][x1]);
			Query1.bindValue(":dxf_357",DXF_main_base[0].split_list_1[357][x1]);
			Query1.bindValue(":dxf_358",DXF_main_base[0].split_list_1[358][x1]);
			Query1.bindValue(":dxf_359",DXF_main_base[0].split_list_1[359][x1]);
			Query1.bindValue(":dxf_360",DXF_main_base[0].split_list_1[360][x1]);
			Query1.bindValue(":dxf_361",DXF_main_base[0].split_list_1[361][x1]);
			Query1.bindValue(":dxf_362",DXF_main_base[0].split_list_1[362][x1]);
			Query1.bindValue(":dxf_363",DXF_main_base[0].split_list_1[363][x1]);
			Query1.bindValue(":dxf_364",DXF_main_base[0].split_list_1[364][x1]);
			Query1.bindValue(":dxf_365",DXF_main_base[0].split_list_1[365][x1]);
			Query1.bindValue(":dxf_366",DXF_main_base[0].split_list_1[366][x1]);
			Query1.bindValue(":dxf_367",DXF_main_base[0].split_list_1[367][x1]);
			Query1.bindValue(":dxf_368",DXF_main_base[0].split_list_1[368][x1]);
			Query1.bindValue(":dxf_369",DXF_main_base[0].split_list_1[369][x1]);
			Query1.bindValue(":dxf_370",DXF_main_base[0].split_list_1[370][x1]);
			Query1.bindValue(":dxf_371",DXF_main_base[0].split_list_1[371][x1]);
			Query1.bindValue(":dxf_372",DXF_main_base[0].split_list_1[372][x1]);
			Query1.bindValue(":dxf_373",DXF_main_base[0].split_list_1[373][x1]);
			Query1.bindValue(":dxf_374",DXF_main_base[0].split_list_1[374][x1]);
			Query1.bindValue(":dxf_375",DXF_main_base[0].split_list_1[375][x1]);
			Query1.bindValue(":dxf_376",DXF_main_base[0].split_list_1[376][x1]);
			Query1.bindValue(":dxf_377",DXF_main_base[0].split_list_1[377][x1]);
			Query1.bindValue(":dxf_378",DXF_main_base[0].split_list_1[378][x1]);
			Query1.bindValue(":dxf_379",DXF_main_base[0].split_list_1[379][x1]);
			Query1.bindValue(":dxf_380",DXF_main_base[0].split_list_1[380][x1]);
			Query1.bindValue(":dxf_381",DXF_main_base[0].split_list_1[381][x1]);
			Query1.bindValue(":dxf_382",DXF_main_base[0].split_list_1[382][x1]);
			Query1.bindValue(":dxf_383",DXF_main_base[0].split_list_1[383][x1]);
			Query1.bindValue(":dxf_384",DXF_main_base[0].split_list_1[384][x1]);
			Query1.bindValue(":dxf_385",DXF_main_base[0].split_list_1[385][x1]);
			Query1.bindValue(":dxf_386",DXF_main_base[0].split_list_1[386][x1]);
			Query1.bindValue(":dxf_387",DXF_main_base[0].split_list_1[387][x1]);
			Query1.bindValue(":dxf_388",DXF_main_base[0].split_list_1[388][x1]);
			Query1.bindValue(":dxf_389",DXF_main_base[0].split_list_1[389][x1]);
			Query1.bindValue(":dxf_390",DXF_main_base[0].split_list_1[390][x1]);
			Query1.bindValue(":dxf_391",DXF_main_base[0].split_list_1[391][x1]);
			Query1.bindValue(":dxf_392",DXF_main_base[0].split_list_1[392][x1]);
			Query1.bindValue(":dxf_393",DXF_main_base[0].split_list_1[393][x1]);
			Query1.bindValue(":dxf_394",DXF_main_base[0].split_list_1[394][x1]);
			Query1.bindValue(":dxf_395",DXF_main_base[0].split_list_1[395][x1]);
			Query1.bindValue(":dxf_396",DXF_main_base[0].split_list_1[396][x1]);
			Query1.bindValue(":dxf_397",DXF_main_base[0].split_list_1[397][x1]);
			Query1.bindValue(":dxf_398",DXF_main_base[0].split_list_1[398][x1]);
			Query1.bindValue(":dxf_399",DXF_main_base[0].split_list_1[399][x1]);
			Query1.bindValue(":dxf_400",DXF_main_base[0].split_list_1[400][x1]);
			Query1.bindValue(":dxf_401",DXF_main_base[0].split_list_1[401][x1]);
			Query1.bindValue(":dxf_402",DXF_main_base[0].split_list_1[402][x1]);
			Query1.bindValue(":dxf_403",DXF_main_base[0].split_list_1[403][x1]);
			Query1.bindValue(":dxf_404",DXF_main_base[0].split_list_1[404][x1]);
			Query1.bindValue(":dxf_405",DXF_main_base[0].split_list_1[405][x1]);
			Query1.bindValue(":dxf_406",DXF_main_base[0].split_list_1[406][x1]);
			Query1.bindValue(":dxf_407",DXF_main_base[0].split_list_1[407][x1]);
			Query1.bindValue(":dxf_408",DXF_main_base[0].split_list_1[408][x1]);
			Query1.bindValue(":dxf_409",DXF_main_base[0].split_list_1[409][x1]);
			Query1.bindValue(":dxf_410",DXF_main_base[0].split_list_1[410][x1]);
			Query1.bindValue(":dxf_411",DXF_main_base[0].split_list_1[411][x1]);
			Query1.bindValue(":dxf_412",DXF_main_base[0].split_list_1[412][x1]);
			Query1.bindValue(":dxf_413",DXF_main_base[0].split_list_1[413][x1]);
			Query1.bindValue(":dxf_414",DXF_main_base[0].split_list_1[414][x1]);
			Query1.bindValue(":dxf_415",DXF_main_base[0].split_list_1[415][x1]);
			Query1.bindValue(":dxf_416",DXF_main_base[0].split_list_1[416][x1]);
			Query1.bindValue(":dxf_417",DXF_main_base[0].split_list_1[417][x1]);
			Query1.bindValue(":dxf_418",DXF_main_base[0].split_list_1[418][x1]);
			Query1.bindValue(":dxf_419",DXF_main_base[0].split_list_1[419][x1]);
			Query1.bindValue(":dxf_420",DXF_main_base[0].split_list_1[420][x1]);
			Query1.bindValue(":dxf_421",DXF_main_base[0].split_list_1[421][x1]);
			Query1.bindValue(":dxf_422",DXF_main_base[0].split_list_1[422][x1]);
			Query1.bindValue(":dxf_423",DXF_main_base[0].split_list_1[423][x1]);
			Query1.bindValue(":dxf_424",DXF_main_base[0].split_list_1[424][x1]);
			Query1.bindValue(":dxf_425",DXF_main_base[0].split_list_1[425][x1]);
			Query1.bindValue(":dxf_426",DXF_main_base[0].split_list_1[426][x1]);
			Query1.bindValue(":dxf_427",DXF_main_base[0].split_list_1[427][x1]);
			Query1.bindValue(":dxf_428",DXF_main_base[0].split_list_1[428][x1]);
			Query1.bindValue(":dxf_429",DXF_main_base[0].split_list_1[429][x1]);
			Query1.bindValue(":dxf_430",DXF_main_base[0].split_list_1[430][x1]);
			Query1.bindValue(":dxf_431",DXF_main_base[0].split_list_1[431][x1]);
			Query1.bindValue(":dxf_432",DXF_main_base[0].split_list_1[432][x1]);
			Query1.bindValue(":dxf_433",DXF_main_base[0].split_list_1[433][x1]);
			Query1.bindValue(":dxf_434",DXF_main_base[0].split_list_1[434][x1]);
			Query1.bindValue(":dxf_435",DXF_main_base[0].split_list_1[435][x1]);
			Query1.bindValue(":dxf_436",DXF_main_base[0].split_list_1[436][x1]);
			Query1.bindValue(":dxf_437",DXF_main_base[0].split_list_1[437][x1]);
			Query1.bindValue(":dxf_438",DXF_main_base[0].split_list_1[438][x1]);
			Query1.bindValue(":dxf_439",DXF_main_base[0].split_list_1[439][x1]);
			Query1.bindValue(":dxf_440",DXF_main_base[0].split_list_1[440][x1]);
			Query1.bindValue(":dxf_441",DXF_main_base[0].split_list_1[441][x1]);
			Query1.bindValue(":dxf_442",DXF_main_base[0].split_list_1[442][x1]);
			Query1.bindValue(":dxf_443",DXF_main_base[0].split_list_1[443][x1]);
			Query1.bindValue(":dxf_444",DXF_main_base[0].split_list_1[444][x1]);
			Query1.bindValue(":dxf_445",DXF_main_base[0].split_list_1[445][x1]);
			Query1.bindValue(":dxf_446",DXF_main_base[0].split_list_1[446][x1]);
			Query1.bindValue(":dxf_447",DXF_main_base[0].split_list_1[447][x1]);
			Query1.bindValue(":dxf_448",DXF_main_base[0].split_list_1[448][x1]);
			Query1.bindValue(":dxf_449",DXF_main_base[0].split_list_1[449][x1]);
			Query1.bindValue(":dxf_450",DXF_main_base[0].split_list_1[450][x1]);
			Query1.bindValue(":dxf_451",DXF_main_base[0].split_list_1[451][x1]);
			Query1.bindValue(":dxf_452",DXF_main_base[0].split_list_1[452][x1]);
			Query1.bindValue(":dxf_453",DXF_main_base[0].split_list_1[453][x1]);
			Query1.bindValue(":dxf_454",DXF_main_base[0].split_list_1[454][x1]);
			Query1.bindValue(":dxf_455",DXF_main_base[0].split_list_1[455][x1]);
			Query1.bindValue(":dxf_456",DXF_main_base[0].split_list_1[456][x1]);
			Query1.bindValue(":dxf_457",DXF_main_base[0].split_list_1[457][x1]);
			Query1.bindValue(":dxf_458",DXF_main_base[0].split_list_1[458][x1]);
			Query1.bindValue(":dxf_459",DXF_main_base[0].split_list_1[459][x1]);
			Query1.bindValue(":dxf_460",DXF_main_base[0].split_list_1[460][x1]);
			Query1.bindValue(":dxf_461",DXF_main_base[0].split_list_1[461][x1]);
			Query1.bindValue(":dxf_462",DXF_main_base[0].split_list_1[462][x1]);
			Query1.bindValue(":dxf_463",DXF_main_base[0].split_list_1[463][x1]);
			Query1.bindValue(":dxf_464",DXF_main_base[0].split_list_1[464][x1]);
			Query1.bindValue(":dxf_465",DXF_main_base[0].split_list_1[465][x1]);
			Query1.bindValue(":dxf_466",DXF_main_base[0].split_list_1[466][x1]);
			Query1.bindValue(":dxf_467",DXF_main_base[0].split_list_1[467][x1]);
			Query1.bindValue(":dxf_468",DXF_main_base[0].split_list_1[468][x1]);
			Query1.bindValue(":dxf_469",DXF_main_base[0].split_list_1[469][x1]);
			Query1.bindValue(":dxf_470",DXF_main_base[0].split_list_1[470][x1]);
			Query1.bindValue(":dxf_471",DXF_main_base[0].split_list_1[471][x1]);
			Query1.bindValue(":dxf_472",DXF_main_base[0].split_list_1[472][x1]);
			Query1.bindValue(":dxf_473",DXF_main_base[0].split_list_1[473][x1]);
			Query1.bindValue(":dxf_474",DXF_main_base[0].split_list_1[474][x1]);
			Query1.bindValue(":dxf_475",DXF_main_base[0].split_list_1[475][x1]);
			Query1.bindValue(":dxf_476",DXF_main_base[0].split_list_1[476][x1]);
			Query1.bindValue(":dxf_477",DXF_main_base[0].split_list_1[477][x1]);
			Query1.bindValue(":dxf_478",DXF_main_base[0].split_list_1[478][x1]);
			Query1.bindValue(":dxf_479",DXF_main_base[0].split_list_1[479][x1]);
			Query1.bindValue(":dxf_480",DXF_main_base[0].split_list_1[480][x1]);
			Query1.bindValue(":dxf_481",DXF_main_base[0].split_list_1[481][x1]);
			Query1.bindValue(":dxf_482",DXF_main_base[0].split_list_1[482][x1]);
			Query1.bindValue(":dxf_483",DXF_main_base[0].split_list_1[483][x1]);
			Query1.bindValue(":dxf_484",DXF_main_base[0].split_list_1[484][x1]);
			Query1.bindValue(":dxf_485",DXF_main_base[0].split_list_1[485][x1]);
			Query1.bindValue(":dxf_486",DXF_main_base[0].split_list_1[486][x1]);
			Query1.bindValue(":dxf_487",DXF_main_base[0].split_list_1[487][x1]);
			Query1.bindValue(":dxf_488",DXF_main_base[0].split_list_1[488][x1]);
			Query1.bindValue(":dxf_489",DXF_main_base[0].split_list_1[489][x1]);
			Query1.bindValue(":dxf_490",DXF_main_base[0].split_list_1[490][x1]);
			/*Query1.bindValue(":dxf_491",DXF_main_base[0].split_list_1[491][x1]);
			Query1.bindValue(":dxf_492",DXF_main_base[0].split_list_1[492][x1]);
			Query1.bindValue(":dxf_493",DXF_main_base[0].split_list_1[493][x1]);
			Query1.bindValue(":dxf_494",DXF_main_base[0].split_list_1[494][x1]);
			Query1.bindValue(":dxf_495",DXF_main_base[0].split_list_1[495][x1]);
			Query1.bindValue(":dxf_496",DXF_main_base[0].split_list_1[496][x1]);
			Query1.bindValue(":dxf_497",DXF_main_base[0].split_list_1[497][x1]);
			Query1.bindValue(":dxf_498",DXF_main_base[0].split_list_1[498][x1]);
			Query1.bindValue(":dxf_499",DXF_main_base[0].split_list_1[499][x1]);
			Query1.bindValue(":dxf_500",DXF_main_base[0].split_list_1[500][x1]);
			Query1.bindValue(":dxf_501",DXF_main_base[0].split_list_1[501][x1]);
			Query1.bindValue(":dxf_502",DXF_main_base[0].split_list_1[502][x1]);
			Query1.bindValue(":dxf_503",DXF_main_base[0].split_list_1[503][x1]);
			Query1.bindValue(":dxf_504",DXF_main_base[0].split_list_1[504][x1]);
			Query1.bindValue(":dxf_505",DXF_main_base[0].split_list_1[505][x1]);
			Query1.bindValue(":dxf_506",DXF_main_base[0].split_list_1[506][x1]);
			Query1.bindValue(":dxf_507",DXF_main_base[0].split_list_1[507][x1]);
			Query1.bindValue(":dxf_508",DXF_main_base[0].split_list_1[508][x1]);
			Query1.bindValue(":dxf_509",DXF_main_base[0].split_list_1[509][x1]);
			Query1.bindValue(":dxf_510",DXF_main_base[0].split_list_1[510][x1]);
			Query1.bindValue(":dxf_511",DXF_main_base[0].split_list_1[511][x1]);
			Query1.bindValue(":dxf_512",DXF_main_base[0].split_list_1[512][x1]);
			Query1.bindValue(":dxf_513",DXF_main_base[0].split_list_1[513][x1]);
			Query1.bindValue(":dxf_514",DXF_main_base[0].split_list_1[514][x1]);
			Query1.bindValue(":dxf_515",DXF_main_base[0].split_list_1[515][x1]);
			Query1.bindValue(":dxf_516",DXF_main_base[0].split_list_1[516][x1]);
			Query1.bindValue(":dxf_517",DXF_main_base[0].split_list_1[517][x1]);
			Query1.bindValue(":dxf_518",DXF_main_base[0].split_list_1[518][x1]);
			Query1.bindValue(":dxf_519",DXF_main_base[0].split_list_1[519][x1]);
			Query1.bindValue(":dxf_520",DXF_main_base[0].split_list_1[520][x1]);
			Query1.bindValue(":dxf_521",DXF_main_base[0].split_list_1[521][x1]);
			Query1.bindValue(":dxf_522",DXF_main_base[0].split_list_1[522][x1]);
			Query1.bindValue(":dxf_523",DXF_main_base[0].split_list_1[523][x1]);
			Query1.bindValue(":dxf_524",DXF_main_base[0].split_list_1[524][x1]);
			Query1.bindValue(":dxf_525",DXF_main_base[0].split_list_1[525][x1]);
			Query1.bindValue(":dxf_526",DXF_main_base[0].split_list_1[526][x1]);
			Query1.bindValue(":dxf_527",DXF_main_base[0].split_list_1[527][x1]);
			Query1.bindValue(":dxf_528",DXF_main_base[0].split_list_1[528][x1]);
			Query1.bindValue(":dxf_529",DXF_main_base[0].split_list_1[529][x1]);
			Query1.bindValue(":dxf_530",DXF_main_base[0].split_list_1[530][x1]);
			Query1.bindValue(":dxf_531",DXF_main_base[0].split_list_1[531][x1]);
			Query1.bindValue(":dxf_532",DXF_main_base[0].split_list_1[532][x1]);
			Query1.bindValue(":dxf_533",DXF_main_base[0].split_list_1[533][x1]);
			Query1.bindValue(":dxf_534",DXF_main_base[0].split_list_1[534][x1]);
			Query1.bindValue(":dxf_535",DXF_main_base[0].split_list_1[535][x1]);
			Query1.bindValue(":dxf_536",DXF_main_base[0].split_list_1[536][x1]);
			Query1.bindValue(":dxf_537",DXF_main_base[0].split_list_1[537][x1]);
			Query1.bindValue(":dxf_538",DXF_main_base[0].split_list_1[538][x1]);
			Query1.bindValue(":dxf_539",DXF_main_base[0].split_list_1[539][x1]);
			Query1.bindValue(":dxf_540",DXF_main_base[0].split_list_1[540][x1]);
			Query1.bindValue(":dxf_541",DXF_main_base[0].split_list_1[541][x1]);
			Query1.bindValue(":dxf_542",DXF_main_base[0].split_list_1[542][x1]);
			Query1.bindValue(":dxf_543",DXF_main_base[0].split_list_1[543][x1]);
			Query1.bindValue(":dxf_544",DXF_main_base[0].split_list_1[544][x1]);
			Query1.bindValue(":dxf_545",DXF_main_base[0].split_list_1[545][x1]);
			Query1.bindValue(":dxf_546",DXF_main_base[0].split_list_1[546][x1]);
			Query1.bindValue(":dxf_547",DXF_main_base[0].split_list_1[547][x1]);
			Query1.bindValue(":dxf_548",DXF_main_base[0].split_list_1[548][x1]);
			Query1.bindValue(":dxf_549",DXF_main_base[0].split_list_1[549][x1]);
			Query1.bindValue(":dxf_550",DXF_main_base[0].split_list_1[550][x1]);
			Query1.bindValue(":dxf_551",DXF_main_base[0].split_list_1[551][x1]);
			Query1.bindValue(":dxf_552",DXF_main_base[0].split_list_1[552][x1]);
			Query1.bindValue(":dxf_553",DXF_main_base[0].split_list_1[553][x1]);
			Query1.bindValue(":dxf_554",DXF_main_base[0].split_list_1[554][x1]);
			Query1.bindValue(":dxf_555",DXF_main_base[0].split_list_1[555][x1]);
			Query1.bindValue(":dxf_556",DXF_main_base[0].split_list_1[556][x1]);
			Query1.bindValue(":dxf_557",DXF_main_base[0].split_list_1[557][x1]);
			Query1.bindValue(":dxf_558",DXF_main_base[0].split_list_1[558][x1]);
			Query1.bindValue(":dxf_559",DXF_main_base[0].split_list_1[559][x1]);
			Query1.bindValue(":dxf_560",DXF_main_base[0].split_list_1[560][x1]);
			Query1.bindValue(":dxf_561",DXF_main_base[0].split_list_1[561][x1]);
			Query1.bindValue(":dxf_562",DXF_main_base[0].split_list_1[562][x1]);
			Query1.bindValue(":dxf_563",DXF_main_base[0].split_list_1[563][x1]);
			Query1.bindValue(":dxf_564",DXF_main_base[0].split_list_1[564][x1]);
			Query1.bindValue(":dxf_565",DXF_main_base[0].split_list_1[565][x1]);
			Query1.bindValue(":dxf_566",DXF_main_base[0].split_list_1[566][x1]);
			Query1.bindValue(":dxf_567",DXF_main_base[0].split_list_1[567][x1]);
			Query1.bindValue(":dxf_568",DXF_main_base[0].split_list_1[568][x1]);
			Query1.bindValue(":dxf_569",DXF_main_base[0].split_list_1[569][x1]);
			Query1.bindValue(":dxf_570",DXF_main_base[0].split_list_1[570][x1]);
			Query1.bindValue(":dxf_571",DXF_main_base[0].split_list_1[571][x1]);
			Query1.bindValue(":dxf_572",DXF_main_base[0].split_list_1[572][x1]);
			Query1.bindValue(":dxf_573",DXF_main_base[0].split_list_1[573][x1]);
			Query1.bindValue(":dxf_574",DXF_main_base[0].split_list_1[574][x1]);
			Query1.bindValue(":dxf_575",DXF_main_base[0].split_list_1[575][x1]);
			Query1.bindValue(":dxf_576",DXF_main_base[0].split_list_1[576][x1]);
			Query1.bindValue(":dxf_577",DXF_main_base[0].split_list_1[577][x1]);
			Query1.bindValue(":dxf_578",DXF_main_base[0].split_list_1[578][x1]);
			Query1.bindValue(":dxf_579",DXF_main_base[0].split_list_1[579][x1]);
			Query1.bindValue(":dxf_580",DXF_main_base[0].split_list_1[580][x1]);
			Query1.bindValue(":dxf_581",DXF_main_base[0].split_list_1[581][x1]);
			Query1.bindValue(":dxf_582",DXF_main_base[0].split_list_1[582][x1]);
			Query1.bindValue(":dxf_583",DXF_main_base[0].split_list_1[583][x1]);
			Query1.bindValue(":dxf_584",DXF_main_base[0].split_list_1[584][x1]);
			Query1.bindValue(":dxf_585",DXF_main_base[0].split_list_1[585][x1]);
			Query1.bindValue(":dxf_586",DXF_main_base[0].split_list_1[586][x1]);
			Query1.bindValue(":dxf_587",DXF_main_base[0].split_list_1[587][x1]);
			Query1.bindValue(":dxf_588",DXF_main_base[0].split_list_1[588][x1]);
			Query1.bindValue(":dxf_589",DXF_main_base[0].split_list_1[589][x1]);
			Query1.bindValue(":dxf_590",DXF_main_base[0].split_list_1[590][x1]);
			Query1.bindValue(":dxf_591",DXF_main_base[0].split_list_1[591][x1]);
			Query1.bindValue(":dxf_592",DXF_main_base[0].split_list_1[592][x1]);
			Query1.bindValue(":dxf_593",DXF_main_base[0].split_list_1[593][x1]);
			Query1.bindValue(":dxf_594",DXF_main_base[0].split_list_1[594][x1]);
			Query1.bindValue(":dxf_595",DXF_main_base[0].split_list_1[595][x1]);
			Query1.bindValue(":dxf_596",DXF_main_base[0].split_list_1[596][x1]);
			Query1.bindValue(":dxf_597",DXF_main_base[0].split_list_1[597][x1]);
			Query1.bindValue(":dxf_598",DXF_main_base[0].split_list_1[598][x1]);
			Query1.bindValue(":dxf_599",DXF_main_base[0].split_list_1[599][x1]);
			Query1.bindValue(":dxf_600",DXF_main_base[0].split_list_1[600][x1]);
			Query1.bindValue(":dxf_601",DXF_main_base[0].split_list_1[601][x1]);
			Query1.bindValue(":dxf_602",DXF_main_base[0].split_list_1[602][x1]);
			Query1.bindValue(":dxf_603",DXF_main_base[0].split_list_1[603][x1]);
			Query1.bindValue(":dxf_604",DXF_main_base[0].split_list_1[604][x1]);
			Query1.bindValue(":dxf_605",DXF_main_base[0].split_list_1[605][x1]);
			Query1.bindValue(":dxf_606",DXF_main_base[0].split_list_1[606][x1]);
			Query1.bindValue(":dxf_607",DXF_main_base[0].split_list_1[607][x1]);
			Query1.bindValue(":dxf_608",DXF_main_base[0].split_list_1[608][x1]);
			Query1.bindValue(":dxf_609",DXF_main_base[0].split_list_1[609][x1]);
			Query1.bindValue(":dxf_610",DXF_main_base[0].split_list_1[610][x1]);
			Query1.bindValue(":dxf_611",DXF_main_base[0].split_list_1[611][x1]);
			Query1.bindValue(":dxf_612",DXF_main_base[0].split_list_1[612][x1]);
			Query1.bindValue(":dxf_613",DXF_main_base[0].split_list_1[613][x1]);
			Query1.bindValue(":dxf_614",DXF_main_base[0].split_list_1[614][x1]);
			Query1.bindValue(":dxf_615",DXF_main_base[0].split_list_1[615][x1]);
			Query1.bindValue(":dxf_616",DXF_main_base[0].split_list_1[616][x1]);
			Query1.bindValue(":dxf_617",DXF_main_base[0].split_list_1[617][x1]);
			Query1.bindValue(":dxf_618",DXF_main_base[0].split_list_1[618][x1]);
			Query1.bindValue(":dxf_619",DXF_main_base[0].split_list_1[619][x1]);
			Query1.bindValue(":dxf_620",DXF_main_base[0].split_list_1[620][x1]);
			Query1.bindValue(":dxf_621",DXF_main_base[0].split_list_1[621][x1]);
			Query1.bindValue(":dxf_622",DXF_main_base[0].split_list_1[622][x1]);
			Query1.bindValue(":dxf_623",DXF_main_base[0].split_list_1[623][x1]);
			Query1.bindValue(":dxf_624",DXF_main_base[0].split_list_1[624][x1]);
			Query1.bindValue(":dxf_625",DXF_main_base[0].split_list_1[625][x1]);
			Query1.bindValue(":dxf_626",DXF_main_base[0].split_list_1[626][x1]);
			Query1.bindValue(":dxf_627",DXF_main_base[0].split_list_1[627][x1]);
			Query1.bindValue(":dxf_628",DXF_main_base[0].split_list_1[628][x1]);
			Query1.bindValue(":dxf_629",DXF_main_base[0].split_list_1[629][x1]);
			Query1.bindValue(":dxf_630",DXF_main_base[0].split_list_1[630][x1]);
			Query1.bindValue(":dxf_631",DXF_main_base[0].split_list_1[631][x1]);
			Query1.bindValue(":dxf_632",DXF_main_base[0].split_list_1[632][x1]);
			Query1.bindValue(":dxf_633",DXF_main_base[0].split_list_1[633][x1]);
			Query1.bindValue(":dxf_634",DXF_main_base[0].split_list_1[634][x1]);
			Query1.bindValue(":dxf_635",DXF_main_base[0].split_list_1[635][x1]);
			Query1.bindValue(":dxf_636",DXF_main_base[0].split_list_1[636][x1]);
			Query1.bindValue(":dxf_637",DXF_main_base[0].split_list_1[637][x1]);
			Query1.bindValue(":dxf_638",DXF_main_base[0].split_list_1[638][x1]);
			Query1.bindValue(":dxf_639",DXF_main_base[0].split_list_1[639][x1]);
			Query1.bindValue(":dxf_640",DXF_main_base[0].split_list_1[640][x1]);
			Query1.bindValue(":dxf_641",DXF_main_base[0].split_list_1[641][x1]);
			Query1.bindValue(":dxf_642",DXF_main_base[0].split_list_1[642][x1]);
			Query1.bindValue(":dxf_643",DXF_main_base[0].split_list_1[643][x1]);
			Query1.bindValue(":dxf_644",DXF_main_base[0].split_list_1[644][x1]);
			Query1.bindValue(":dxf_645",DXF_main_base[0].split_list_1[645][x1]);
			Query1.bindValue(":dxf_646",DXF_main_base[0].split_list_1[646][x1]);
			Query1.bindValue(":dxf_647",DXF_main_base[0].split_list_1[647][x1]);
			Query1.bindValue(":dxf_648",DXF_main_base[0].split_list_1[648][x1]);
			Query1.bindValue(":dxf_649",DXF_main_base[0].split_list_1[649][x1]);
			Query1.bindValue(":dxf_650",DXF_main_base[0].split_list_1[650][x1]);
			Query1.bindValue(":dxf_651",DXF_main_base[0].split_list_1[651][x1]);
			Query1.bindValue(":dxf_652",DXF_main_base[0].split_list_1[652][x1]);
			Query1.bindValue(":dxf_653",DXF_main_base[0].split_list_1[653][x1]);
			Query1.bindValue(":dxf_654",DXF_main_base[0].split_list_1[654][x1]);
			Query1.bindValue(":dxf_655",DXF_main_base[0].split_list_1[655][x1]);
			Query1.bindValue(":dxf_656",DXF_main_base[0].split_list_1[656][x1]);
			Query1.bindValue(":dxf_657",DXF_main_base[0].split_list_1[657][x1]);
			Query1.bindValue(":dxf_658",DXF_main_base[0].split_list_1[658][x1]);
			Query1.bindValue(":dxf_659",DXF_main_base[0].split_list_1[659][x1]);
			Query1.bindValue(":dxf_660",DXF_main_base[0].split_list_1[660][x1]);
			Query1.bindValue(":dxf_661",DXF_main_base[0].split_list_1[661][x1]);
			Query1.bindValue(":dxf_662",DXF_main_base[0].split_list_1[662][x1]);
			Query1.bindValue(":dxf_663",DXF_main_base[0].split_list_1[663][x1]);
			Query1.bindValue(":dxf_664",DXF_main_base[0].split_list_1[664][x1]);
			Query1.bindValue(":dxf_665",DXF_main_base[0].split_list_1[665][x1]);
			Query1.bindValue(":dxf_666",DXF_main_base[0].split_list_1[666][x1]);
			Query1.bindValue(":dxf_667",DXF_main_base[0].split_list_1[667][x1]);
			Query1.bindValue(":dxf_668",DXF_main_base[0].split_list_1[668][x1]);
			Query1.bindValue(":dxf_669",DXF_main_base[0].split_list_1[669][x1]);
			Query1.bindValue(":dxf_670",DXF_main_base[0].split_list_1[670][x1]);
			Query1.bindValue(":dxf_671",DXF_main_base[0].split_list_1[671][x1]);
			Query1.bindValue(":dxf_672",DXF_main_base[0].split_list_1[672][x1]);
			Query1.bindValue(":dxf_673",DXF_main_base[0].split_list_1[673][x1]);
			Query1.bindValue(":dxf_674",DXF_main_base[0].split_list_1[674][x1]);
			Query1.bindValue(":dxf_675",DXF_main_base[0].split_list_1[675][x1]);
			Query1.bindValue(":dxf_676",DXF_main_base[0].split_list_1[676][x1]);
			Query1.bindValue(":dxf_677",DXF_main_base[0].split_list_1[677][x1]);
			Query1.bindValue(":dxf_678",DXF_main_base[0].split_list_1[678][x1]);
			Query1.bindValue(":dxf_679",DXF_main_base[0].split_list_1[679][x1]);
			Query1.bindValue(":dxf_680",DXF_main_base[0].split_list_1[680][x1]);
			Query1.bindValue(":dxf_681",DXF_main_base[0].split_list_1[681][x1]);
			Query1.bindValue(":dxf_682",DXF_main_base[0].split_list_1[682][x1]);
			Query1.bindValue(":dxf_683",DXF_main_base[0].split_list_1[683][x1]);
			Query1.bindValue(":dxf_684",DXF_main_base[0].split_list_1[684][x1]);
			Query1.bindValue(":dxf_685",DXF_main_base[0].split_list_1[685][x1]);
			Query1.bindValue(":dxf_686",DXF_main_base[0].split_list_1[686][x1]);
			Query1.bindValue(":dxf_687",DXF_main_base[0].split_list_1[687][x1]);
			Query1.bindValue(":dxf_688",DXF_main_base[0].split_list_1[688][x1]);
			Query1.bindValue(":dxf_689",DXF_main_base[0].split_list_1[689][x1]);
			Query1.bindValue(":dxf_690",DXF_main_base[0].split_list_1[690][x1]);
			Query1.bindValue(":dxf_691",DXF_main_base[0].split_list_1[691][x1]);
			Query1.bindValue(":dxf_692",DXF_main_base[0].split_list_1[692][x1]);
			Query1.bindValue(":dxf_693",DXF_main_base[0].split_list_1[693][x1]);
			Query1.bindValue(":dxf_694",DXF_main_base[0].split_list_1[694][x1]);
			Query1.bindValue(":dxf_695",DXF_main_base[0].split_list_1[695][x1]);
			Query1.bindValue(":dxf_696",DXF_main_base[0].split_list_1[696][x1]);
			Query1.bindValue(":dxf_697",DXF_main_base[0].split_list_1[697][x1]);
			Query1.bindValue(":dxf_698",DXF_main_base[0].split_list_1[698][x1]);
			Query1.bindValue(":dxf_699",DXF_main_base[0].split_list_1[699][x1]);
			Query1.bindValue(":dxf_700",DXF_main_base[0].split_list_1[700][x1]);
			Query1.bindValue(":dxf_701",DXF_main_base[0].split_list_1[701][x1]);
			Query1.bindValue(":dxf_702",DXF_main_base[0].split_list_1[702][x1]);
			Query1.bindValue(":dxf_703",DXF_main_base[0].split_list_1[703][x1]);
			Query1.bindValue(":dxf_704",DXF_main_base[0].split_list_1[704][x1]);
			Query1.bindValue(":dxf_705",DXF_main_base[0].split_list_1[705][x1]);
			Query1.bindValue(":dxf_706",DXF_main_base[0].split_list_1[706][x1]);
			Query1.bindValue(":dxf_707",DXF_main_base[0].split_list_1[707][x1]);
			Query1.bindValue(":dxf_708",DXF_main_base[0].split_list_1[708][x1]);
			Query1.bindValue(":dxf_709",DXF_main_base[0].split_list_1[709][x1]);
			Query1.bindValue(":dxf_710",DXF_main_base[0].split_list_1[710][x1]);
			Query1.bindValue(":dxf_711",DXF_main_base[0].split_list_1[711][x1]);
			Query1.bindValue(":dxf_712",DXF_main_base[0].split_list_1[712][x1]);
			Query1.bindValue(":dxf_713",DXF_main_base[0].split_list_1[713][x1]);
			Query1.bindValue(":dxf_714",DXF_main_base[0].split_list_1[714][x1]);
			Query1.bindValue(":dxf_715",DXF_main_base[0].split_list_1[715][x1]);
			Query1.bindValue(":dxf_716",DXF_main_base[0].split_list_1[716][x1]);
			Query1.bindValue(":dxf_717",DXF_main_base[0].split_list_1[717][x1]);
			Query1.bindValue(":dxf_718",DXF_main_base[0].split_list_1[718][x1]);
			Query1.bindValue(":dxf_719",DXF_main_base[0].split_list_1[719][x1]);
			Query1.bindValue(":dxf_720",DXF_main_base[0].split_list_1[720][x1]);
			Query1.bindValue(":dxf_721",DXF_main_base[0].split_list_1[721][x1]);
			Query1.bindValue(":dxf_722",DXF_main_base[0].split_list_1[722][x1]);
			Query1.bindValue(":dxf_723",DXF_main_base[0].split_list_1[723][x1]);
			Query1.bindValue(":dxf_724",DXF_main_base[0].split_list_1[724][x1]);
			Query1.bindValue(":dxf_725",DXF_main_base[0].split_list_1[725][x1]);
			Query1.bindValue(":dxf_726",DXF_main_base[0].split_list_1[726][x1]);
			Query1.bindValue(":dxf_727",DXF_main_base[0].split_list_1[727][x1]);
			Query1.bindValue(":dxf_728",DXF_main_base[0].split_list_1[728][x1]);
			Query1.bindValue(":dxf_729",DXF_main_base[0].split_list_1[729][x1]);
			Query1.bindValue(":dxf_730",DXF_main_base[0].split_list_1[730][x1]);
			Query1.bindValue(":dxf_731",DXF_main_base[0].split_list_1[731][x1]);
			Query1.bindValue(":dxf_732",DXF_main_base[0].split_list_1[732][x1]);
			Query1.bindValue(":dxf_733",DXF_main_base[0].split_list_1[733][x1]);
			Query1.bindValue(":dxf_734",DXF_main_base[0].split_list_1[734][x1]);
			Query1.bindValue(":dxf_735",DXF_main_base[0].split_list_1[735][x1]);
			Query1.bindValue(":dxf_736",DXF_main_base[0].split_list_1[736][x1]);
			Query1.bindValue(":dxf_737",DXF_main_base[0].split_list_1[737][x1]);
			Query1.bindValue(":dxf_738",DXF_main_base[0].split_list_1[738][x1]);
			Query1.bindValue(":dxf_739",DXF_main_base[0].split_list_1[739][x1]);
			Query1.bindValue(":dxf_740",DXF_main_base[0].split_list_1[740][x1]);
			Query1.bindValue(":dxf_741",DXF_main_base[0].split_list_1[741][x1]);
			Query1.bindValue(":dxf_742",DXF_main_base[0].split_list_1[742][x1]);
			Query1.bindValue(":dxf_743",DXF_main_base[0].split_list_1[743][x1]);
			Query1.bindValue(":dxf_744",DXF_main_base[0].split_list_1[744][x1]);
			Query1.bindValue(":dxf_745",DXF_main_base[0].split_list_1[745][x1]);
			Query1.bindValue(":dxf_746",DXF_main_base[0].split_list_1[746][x1]);
			Query1.bindValue(":dxf_747",DXF_main_base[0].split_list_1[747][x1]);
			Query1.bindValue(":dxf_748",DXF_main_base[0].split_list_1[748][x1]);
			Query1.bindValue(":dxf_749",DXF_main_base[0].split_list_1[749][x1]);
			Query1.bindValue(":dxf_750",DXF_main_base[0].split_list_1[750][x1]);
			Query1.bindValue(":dxf_751",DXF_main_base[0].split_list_1[751][x1]);
			Query1.bindValue(":dxf_752",DXF_main_base[0].split_list_1[752][x1]);
			Query1.bindValue(":dxf_753",DXF_main_base[0].split_list_1[753][x1]);
			Query1.bindValue(":dxf_754",DXF_main_base[0].split_list_1[754][x1]);
			Query1.bindValue(":dxf_755",DXF_main_base[0].split_list_1[755][x1]);
			Query1.bindValue(":dxf_756",DXF_main_base[0].split_list_1[756][x1]);
			Query1.bindValue(":dxf_757",DXF_main_base[0].split_list_1[757][x1]);
			Query1.bindValue(":dxf_758",DXF_main_base[0].split_list_1[758][x1]);
			Query1.bindValue(":dxf_759",DXF_main_base[0].split_list_1[759][x1]);
			Query1.bindValue(":dxf_760",DXF_main_base[0].split_list_1[760][x1]);
			Query1.bindValue(":dxf_761",DXF_main_base[0].split_list_1[761][x1]);
			Query1.bindValue(":dxf_762",DXF_main_base[0].split_list_1[762][x1]);
			Query1.bindValue(":dxf_763",DXF_main_base[0].split_list_1[763][x1]);
			Query1.bindValue(":dxf_764",DXF_main_base[0].split_list_1[764][x1]);
			Query1.bindValue(":dxf_765",DXF_main_base[0].split_list_1[765][x1]);
			Query1.bindValue(":dxf_766",DXF_main_base[0].split_list_1[766][x1]);
			Query1.bindValue(":dxf_767",DXF_main_base[0].split_list_1[767][x1]);
			Query1.bindValue(":dxf_768",DXF_main_base[0].split_list_1[768][x1]);
			Query1.bindValue(":dxf_769",DXF_main_base[0].split_list_1[769][x1]);
			Query1.bindValue(":dxf_770",DXF_main_base[0].split_list_1[770][x1]);
			Query1.bindValue(":dxf_771",DXF_main_base[0].split_list_1[771][x1]);
			Query1.bindValue(":dxf_772",DXF_main_base[0].split_list_1[772][x1]);
			Query1.bindValue(":dxf_773",DXF_main_base[0].split_list_1[773][x1]);
			Query1.bindValue(":dxf_774",DXF_main_base[0].split_list_1[774][x1]);
			Query1.bindValue(":dxf_775",DXF_main_base[0].split_list_1[775][x1]);
			Query1.bindValue(":dxf_776",DXF_main_base[0].split_list_1[776][x1]);
			Query1.bindValue(":dxf_777",DXF_main_base[0].split_list_1[777][x1]);
			Query1.bindValue(":dxf_778",DXF_main_base[0].split_list_1[778][x1]);
			Query1.bindValue(":dxf_779",DXF_main_base[0].split_list_1[779][x1]);
			Query1.bindValue(":dxf_780",DXF_main_base[0].split_list_1[780][x1]);
			Query1.bindValue(":dxf_781",DXF_main_base[0].split_list_1[781][x1]);
			Query1.bindValue(":dxf_782",DXF_main_base[0].split_list_1[782][x1]);
			Query1.bindValue(":dxf_783",DXF_main_base[0].split_list_1[783][x1]);
			Query1.bindValue(":dxf_784",DXF_main_base[0].split_list_1[784][x1]);
			Query1.bindValue(":dxf_785",DXF_main_base[0].split_list_1[785][x1]);
			Query1.bindValue(":dxf_786",DXF_main_base[0].split_list_1[786][x1]);
			Query1.bindValue(":dxf_787",DXF_main_base[0].split_list_1[787][x1]);
			Query1.bindValue(":dxf_788",DXF_main_base[0].split_list_1[788][x1]);
			Query1.bindValue(":dxf_789",DXF_main_base[0].split_list_1[789][x1]);
			Query1.bindValue(":dxf_790",DXF_main_base[0].split_list_1[790][x1]);
			Query1.bindValue(":dxf_791",DXF_main_base[0].split_list_1[791][x1]);
			Query1.bindValue(":dxf_792",DXF_main_base[0].split_list_1[792][x1]);
			Query1.bindValue(":dxf_793",DXF_main_base[0].split_list_1[793][x1]);
			Query1.bindValue(":dxf_794",DXF_main_base[0].split_list_1[794][x1]);
			Query1.bindValue(":dxf_795",DXF_main_base[0].split_list_1[795][x1]);
			Query1.bindValue(":dxf_796",DXF_main_base[0].split_list_1[796][x1]);
			Query1.bindValue(":dxf_797",DXF_main_base[0].split_list_1[797][x1]);
			Query1.bindValue(":dxf_798",DXF_main_base[0].split_list_1[798][x1]);
			Query1.bindValue(":dxf_799",DXF_main_base[0].split_list_1[799][x1]);
			Query1.bindValue(":dxf_800",DXF_main_base[0].split_list_1[800][x1]);
			Query1.bindValue(":dxf_801",DXF_main_base[0].split_list_1[801][x1]);
			Query1.bindValue(":dxf_802",DXF_main_base[0].split_list_1[802][x1]);
			Query1.bindValue(":dxf_803",DXF_main_base[0].split_list_1[803][x1]);
			Query1.bindValue(":dxf_804",DXF_main_base[0].split_list_1[804][x1]);
			Query1.bindValue(":dxf_805",DXF_main_base[0].split_list_1[805][x1]);
			Query1.bindValue(":dxf_806",DXF_main_base[0].split_list_1[806][x1]);
			Query1.bindValue(":dxf_807",DXF_main_base[0].split_list_1[807][x1]);
			Query1.bindValue(":dxf_808",DXF_main_base[0].split_list_1[808][x1]);
			Query1.bindValue(":dxf_809",DXF_main_base[0].split_list_1[809][x1]);
			Query1.bindValue(":dxf_810",DXF_main_base[0].split_list_1[810][x1]);
			Query1.bindValue(":dxf_811",DXF_main_base[0].split_list_1[811][x1]);
			Query1.bindValue(":dxf_812",DXF_main_base[0].split_list_1[812][x1]);
			Query1.bindValue(":dxf_813",DXF_main_base[0].split_list_1[813][x1]);
			Query1.bindValue(":dxf_814",DXF_main_base[0].split_list_1[814][x1]);
			Query1.bindValue(":dxf_815",DXF_main_base[0].split_list_1[815][x1]);
			Query1.bindValue(":dxf_816",DXF_main_base[0].split_list_1[816][x1]);
			Query1.bindValue(":dxf_817",DXF_main_base[0].split_list_1[817][x1]);
			Query1.bindValue(":dxf_818",DXF_main_base[0].split_list_1[818][x1]);
			Query1.bindValue(":dxf_819",DXF_main_base[0].split_list_1[819][x1]);
			Query1.bindValue(":dxf_820",DXF_main_base[0].split_list_1[820][x1]);
			Query1.bindValue(":dxf_821",DXF_main_base[0].split_list_1[821][x1]);
			Query1.bindValue(":dxf_822",DXF_main_base[0].split_list_1[822][x1]);
			Query1.bindValue(":dxf_823",DXF_main_base[0].split_list_1[823][x1]);
			Query1.bindValue(":dxf_824",DXF_main_base[0].split_list_1[824][x1]);
			Query1.bindValue(":dxf_825",DXF_main_base[0].split_list_1[825][x1]);
			Query1.bindValue(":dxf_826",DXF_main_base[0].split_list_1[826][x1]);
			Query1.bindValue(":dxf_827",DXF_main_base[0].split_list_1[827][x1]);
			Query1.bindValue(":dxf_828",DXF_main_base[0].split_list_1[828][x1]);
			Query1.bindValue(":dxf_829",DXF_main_base[0].split_list_1[829][x1]);
			Query1.bindValue(":dxf_830",DXF_main_base[0].split_list_1[830][x1]);
			Query1.bindValue(":dxf_831",DXF_main_base[0].split_list_1[831][x1]);
			Query1.bindValue(":dxf_832",DXF_main_base[0].split_list_1[832][x1]);
			Query1.bindValue(":dxf_833",DXF_main_base[0].split_list_1[833][x1]);
			Query1.bindValue(":dxf_834",DXF_main_base[0].split_list_1[834][x1]);
			Query1.bindValue(":dxf_835",DXF_main_base[0].split_list_1[835][x1]);
			Query1.bindValue(":dxf_836",DXF_main_base[0].split_list_1[836][x1]);
			Query1.bindValue(":dxf_837",DXF_main_base[0].split_list_1[837][x1]);
			Query1.bindValue(":dxf_838",DXF_main_base[0].split_list_1[838][x1]);
			Query1.bindValue(":dxf_839",DXF_main_base[0].split_list_1[839][x1]);
			Query1.bindValue(":dxf_840",DXF_main_base[0].split_list_1[840][x1]);
			Query1.bindValue(":dxf_841",DXF_main_base[0].split_list_1[841][x1]);
			Query1.bindValue(":dxf_842",DXF_main_base[0].split_list_1[842][x1]);
			Query1.bindValue(":dxf_843",DXF_main_base[0].split_list_1[843][x1]);
			Query1.bindValue(":dxf_844",DXF_main_base[0].split_list_1[844][x1]);
			Query1.bindValue(":dxf_845",DXF_main_base[0].split_list_1[845][x1]);
			Query1.bindValue(":dxf_846",DXF_main_base[0].split_list_1[846][x1]);
			Query1.bindValue(":dxf_847",DXF_main_base[0].split_list_1[847][x1]);
			Query1.bindValue(":dxf_848",DXF_main_base[0].split_list_1[848][x1]);
			Query1.bindValue(":dxf_849",DXF_main_base[0].split_list_1[849][x1]);
			Query1.bindValue(":dxf_850",DXF_main_base[0].split_list_1[850][x1]);
			Query1.bindValue(":dxf_851",DXF_main_base[0].split_list_1[851][x1]);
			Query1.bindValue(":dxf_852",DXF_main_base[0].split_list_1[852][x1]);
			Query1.bindValue(":dxf_853",DXF_main_base[0].split_list_1[853][x1]);
			Query1.bindValue(":dxf_854",DXF_main_base[0].split_list_1[854][x1]);
			Query1.bindValue(":dxf_855",DXF_main_base[0].split_list_1[855][x1]);
			Query1.bindValue(":dxf_856",DXF_main_base[0].split_list_1[856][x1]);
			Query1.bindValue(":dxf_857",DXF_main_base[0].split_list_1[857][x1]);
			Query1.bindValue(":dxf_858",DXF_main_base[0].split_list_1[858][x1]);
			Query1.bindValue(":dxf_859",DXF_main_base[0].split_list_1[859][x1]);
			Query1.bindValue(":dxf_860",DXF_main_base[0].split_list_1[860][x1]);
			Query1.bindValue(":dxf_861",DXF_main_base[0].split_list_1[861][x1]);
			Query1.bindValue(":dxf_862",DXF_main_base[0].split_list_1[862][x1]);
			Query1.bindValue(":dxf_863",DXF_main_base[0].split_list_1[863][x1]);
			Query1.bindValue(":dxf_864",DXF_main_base[0].split_list_1[864][x1]);
			Query1.bindValue(":dxf_865",DXF_main_base[0].split_list_1[865][x1]);
			Query1.bindValue(":dxf_866",DXF_main_base[0].split_list_1[866][x1]);
			Query1.bindValue(":dxf_867",DXF_main_base[0].split_list_1[867][x1]);
			Query1.bindValue(":dxf_868",DXF_main_base[0].split_list_1[868][x1]);
			Query1.bindValue(":dxf_869",DXF_main_base[0].split_list_1[869][x1]);
			Query1.bindValue(":dxf_870",DXF_main_base[0].split_list_1[870][x1]);
			Query1.bindValue(":dxf_871",DXF_main_base[0].split_list_1[871][x1]);
			Query1.bindValue(":dxf_872",DXF_main_base[0].split_list_1[872][x1]);
			Query1.bindValue(":dxf_873",DXF_main_base[0].split_list_1[873][x1]);
			Query1.bindValue(":dxf_874",DXF_main_base[0].split_list_1[874][x1]);
			Query1.bindValue(":dxf_875",DXF_main_base[0].split_list_1[875][x1]);
			Query1.bindValue(":dxf_876",DXF_main_base[0].split_list_1[876][x1]);
			Query1.bindValue(":dxf_877",DXF_main_base[0].split_list_1[877][x1]);
			Query1.bindValue(":dxf_878",DXF_main_base[0].split_list_1[878][x1]);
			Query1.bindValue(":dxf_879",DXF_main_base[0].split_list_1[879][x1]);
			Query1.bindValue(":dxf_880",DXF_main_base[0].split_list_1[880][x1]);
			Query1.bindValue(":dxf_881",DXF_main_base[0].split_list_1[881][x1]);
			Query1.bindValue(":dxf_882",DXF_main_base[0].split_list_1[882][x1]);
			Query1.bindValue(":dxf_883",DXF_main_base[0].split_list_1[883][x1]);
			Query1.bindValue(":dxf_884",DXF_main_base[0].split_list_1[884][x1]);
			Query1.bindValue(":dxf_885",DXF_main_base[0].split_list_1[885][x1]);
			Query1.bindValue(":dxf_886",DXF_main_base[0].split_list_1[886][x1]);
			Query1.bindValue(":dxf_887",DXF_main_base[0].split_list_1[887][x1]);
			Query1.bindValue(":dxf_888",DXF_main_base[0].split_list_1[888][x1]);
			Query1.bindValue(":dxf_889",DXF_main_base[0].split_list_1[889][x1]);
			Query1.bindValue(":dxf_890",DXF_main_base[0].split_list_1[890][x1]);
			Query1.bindValue(":dxf_891",DXF_main_base[0].split_list_1[891][x1]);
			Query1.bindValue(":dxf_892",DXF_main_base[0].split_list_1[892][x1]);
			Query1.bindValue(":dxf_893",DXF_main_base[0].split_list_1[893][x1]);
			Query1.bindValue(":dxf_894",DXF_main_base[0].split_list_1[894][x1]);
			Query1.bindValue(":dxf_895",DXF_main_base[0].split_list_1[895][x1]);
			Query1.bindValue(":dxf_896",DXF_main_base[0].split_list_1[896][x1]);
			Query1.bindValue(":dxf_897",DXF_main_base[0].split_list_1[897][x1]);
			Query1.bindValue(":dxf_898",DXF_main_base[0].split_list_1[898][x1]);
			Query1.bindValue(":dxf_899",DXF_main_base[0].split_list_1[899][x1]);
			Query1.bindValue(":dxf_900",DXF_main_base[0].split_list_1[900][x1]);
			Query1.bindValue(":dxf_901",DXF_main_base[0].split_list_1[901][x1]);
			Query1.bindValue(":dxf_902",DXF_main_base[0].split_list_1[902][x1]);
			Query1.bindValue(":dxf_903",DXF_main_base[0].split_list_1[903][x1]);
			Query1.bindValue(":dxf_904",DXF_main_base[0].split_list_1[904][x1]);
			Query1.bindValue(":dxf_905",DXF_main_base[0].split_list_1[905][x1]);
			Query1.bindValue(":dxf_906",DXF_main_base[0].split_list_1[906][x1]);
			Query1.bindValue(":dxf_907",DXF_main_base[0].split_list_1[907][x1]);
			Query1.bindValue(":dxf_908",DXF_main_base[0].split_list_1[908][x1]);
			Query1.bindValue(":dxf_909",DXF_main_base[0].split_list_1[909][x1]);
			Query1.bindValue(":dxf_910",DXF_main_base[0].split_list_1[910][x1]);
			Query1.bindValue(":dxf_911",DXF_main_base[0].split_list_1[911][x1]);
			Query1.bindValue(":dxf_912",DXF_main_base[0].split_list_1[912][x1]);
			Query1.bindValue(":dxf_913",DXF_main_base[0].split_list_1[913][x1]);
			Query1.bindValue(":dxf_914",DXF_main_base[0].split_list_1[914][x1]);
			Query1.bindValue(":dxf_915",DXF_main_base[0].split_list_1[915][x1]);
			Query1.bindValue(":dxf_916",DXF_main_base[0].split_list_1[916][x1]);
			Query1.bindValue(":dxf_917",DXF_main_base[0].split_list_1[917][x1]);
			Query1.bindValue(":dxf_918",DXF_main_base[0].split_list_1[918][x1]);
			Query1.bindValue(":dxf_919",DXF_main_base[0].split_list_1[919][x1]);
			Query1.bindValue(":dxf_920",DXF_main_base[0].split_list_1[920][x1]);
			Query1.bindValue(":dxf_921",DXF_main_base[0].split_list_1[921][x1]);
			Query1.bindValue(":dxf_922",DXF_main_base[0].split_list_1[922][x1]);
			Query1.bindValue(":dxf_923",DXF_main_base[0].split_list_1[923][x1]);
			Query1.bindValue(":dxf_924",DXF_main_base[0].split_list_1[924][x1]);
			Query1.bindValue(":dxf_925",DXF_main_base[0].split_list_1[925][x1]);
			Query1.bindValue(":dxf_926",DXF_main_base[0].split_list_1[926][x1]);
			Query1.bindValue(":dxf_927",DXF_main_base[0].split_list_1[927][x1]);
			Query1.bindValue(":dxf_928",DXF_main_base[0].split_list_1[928][x1]);
			Query1.bindValue(":dxf_929",DXF_main_base[0].split_list_1[929][x1]);
			Query1.bindValue(":dxf_930",DXF_main_base[0].split_list_1[930][x1]);
			Query1.bindValue(":dxf_931",DXF_main_base[0].split_list_1[931][x1]);
			Query1.bindValue(":dxf_932",DXF_main_base[0].split_list_1[932][x1]);
			Query1.bindValue(":dxf_933",DXF_main_base[0].split_list_1[933][x1]);
			Query1.bindValue(":dxf_934",DXF_main_base[0].split_list_1[934][x1]);
			Query1.bindValue(":dxf_935",DXF_main_base[0].split_list_1[935][x1]);
			Query1.bindValue(":dxf_936",DXF_main_base[0].split_list_1[936][x1]);
			Query1.bindValue(":dxf_937",DXF_main_base[0].split_list_1[937][x1]);
			Query1.bindValue(":dxf_938",DXF_main_base[0].split_list_1[938][x1]);
			Query1.bindValue(":dxf_939",DXF_main_base[0].split_list_1[939][x1]);
			Query1.bindValue(":dxf_940",DXF_main_base[0].split_list_1[940][x1]);
			Query1.bindValue(":dxf_941",DXF_main_base[0].split_list_1[941][x1]);
			Query1.bindValue(":dxf_942",DXF_main_base[0].split_list_1[942][x1]);
			Query1.bindValue(":dxf_943",DXF_main_base[0].split_list_1[943][x1]);
			Query1.bindValue(":dxf_944",DXF_main_base[0].split_list_1[944][x1]);
			Query1.bindValue(":dxf_945",DXF_main_base[0].split_list_1[945][x1]);
			Query1.bindValue(":dxf_946",DXF_main_base[0].split_list_1[946][x1]);
			Query1.bindValue(":dxf_947",DXF_main_base[0].split_list_1[947][x1]);
			Query1.bindValue(":dxf_948",DXF_main_base[0].split_list_1[948][x1]);
			Query1.bindValue(":dxf_949",DXF_main_base[0].split_list_1[949][x1]);
			Query1.bindValue(":dxf_950",DXF_main_base[0].split_list_1[950][x1]);
			Query1.bindValue(":dxf_951",DXF_main_base[0].split_list_1[951][x1]);
			Query1.bindValue(":dxf_952",DXF_main_base[0].split_list_1[952][x1]);
			Query1.bindValue(":dxf_953",DXF_main_base[0].split_list_1[953][x1]);
			Query1.bindValue(":dxf_954",DXF_main_base[0].split_list_1[954][x1]);
			Query1.bindValue(":dxf_955",DXF_main_base[0].split_list_1[955][x1]);
			Query1.bindValue(":dxf_956",DXF_main_base[0].split_list_1[956][x1]);
			Query1.bindValue(":dxf_957",DXF_main_base[0].split_list_1[957][x1]);
			Query1.bindValue(":dxf_958",DXF_main_base[0].split_list_1[958][x1]);
			Query1.bindValue(":dxf_959",DXF_main_base[0].split_list_1[959][x1]);
			Query1.bindValue(":dxf_960",DXF_main_base[0].split_list_1[960][x1]);
			Query1.bindValue(":dxf_961",DXF_main_base[0].split_list_1[961][x1]);
			Query1.bindValue(":dxf_962",DXF_main_base[0].split_list_1[962][x1]);
			Query1.bindValue(":dxf_963",DXF_main_base[0].split_list_1[963][x1]);
			Query1.bindValue(":dxf_964",DXF_main_base[0].split_list_1[964][x1]);
			Query1.bindValue(":dxf_965",DXF_main_base[0].split_list_1[965][x1]);
			Query1.bindValue(":dxf_966",DXF_main_base[0].split_list_1[966][x1]);
			Query1.bindValue(":dxf_967",DXF_main_base[0].split_list_1[967][x1]);
			Query1.bindValue(":dxf_968",DXF_main_base[0].split_list_1[968][x1]);
			Query1.bindValue(":dxf_969",DXF_main_base[0].split_list_1[969][x1]);
			Query1.bindValue(":dxf_970",DXF_main_base[0].split_list_1[970][x1]);
			Query1.bindValue(":dxf_971",DXF_main_base[0].split_list_1[971][x1]);
			Query1.bindValue(":dxf_972",DXF_main_base[0].split_list_1[972][x1]);
			Query1.bindValue(":dxf_973",DXF_main_base[0].split_list_1[973][x1]);
			Query1.bindValue(":dxf_974",DXF_main_base[0].split_list_1[974][x1]);
			Query1.bindValue(":dxf_975",DXF_main_base[0].split_list_1[975][x1]);
			Query1.bindValue(":dxf_976",DXF_main_base[0].split_list_1[976][x1]);
			Query1.bindValue(":dxf_977",DXF_main_base[0].split_list_1[977][x1]);
			Query1.bindValue(":dxf_978",DXF_main_base[0].split_list_1[978][x1]);
			Query1.bindValue(":dxf_979",DXF_main_base[0].split_list_1[979][x1]);
			Query1.bindValue(":dxf_980",DXF_main_base[0].split_list_1[980][x1]);
			Query1.bindValue(":dxf_981",DXF_main_base[0].split_list_1[981][x1]);
			Query1.bindValue(":dxf_982",DXF_main_base[0].split_list_1[982][x1]);
			Query1.bindValue(":dxf_983",DXF_main_base[0].split_list_1[983][x1]);
			Query1.bindValue(":dxf_984",DXF_main_base[0].split_list_1[984][x1]);
			Query1.bindValue(":dxf_985",DXF_main_base[0].split_list_1[985][x1]);
			Query1.bindValue(":dxf_986",DXF_main_base[0].split_list_1[986][x1]);
			Query1.bindValue(":dxf_987",DXF_main_base[0].split_list_1[987][x1]);
			Query1.bindValue(":dxf_988",DXF_main_base[0].split_list_1[988][x1]);
			Query1.bindValue(":dxf_989",DXF_main_base[0].split_list_1[989][x1]);
			Query1.bindValue(":dxf_990",DXF_main_base[0].split_list_1[990][x1]);
			Query1.bindValue(":dxf_991",DXF_main_base[0].split_list_1[991][x1]);
			Query1.bindValue(":dxf_992",DXF_main_base[0].split_list_1[992][x1]);
			Query1.bindValue(":dxf_993",DXF_main_base[0].split_list_1[993][x1]);
			Query1.bindValue(":dxf_994",DXF_main_base[0].split_list_1[994][x1]);
			Query1.bindValue(":dxf_995",DXF_main_base[0].split_list_1[995][x1]);
			Query1.bindValue(":dxf_996",DXF_main_base[0].split_list_1[996][x1]);
			Query1.bindValue(":dxf_997",DXF_main_base[0].split_list_1[997][x1]);
			Query1.bindValue(":dxf_998",DXF_main_base[0].split_list_1[998][x1]);*/
			Query1.bindValue(":dxf_999",DXF_main_base[0].split_list_1[999][x1]);
			Query1.bindValue(":dxf_1000",DXF_main_base[0].split_list_1[1000][x1]);
			Query1.bindValue(":dxf_1001",DXF_main_base[0].split_list_1[1001][x1]);
			Query1.bindValue(":dxf_1002",DXF_main_base[0].split_list_1[1002][x1]);
			Query1.bindValue(":dxf_1003",DXF_main_base[0].split_list_1[1003][x1]);
			Query1.bindValue(":dxf_1004",DXF_main_base[0].split_list_1[1004][x1]);
			Query1.bindValue(":dxf_1005",DXF_main_base[0].split_list_1[1005][x1]);
			Query1.bindValue(":dxf_1006",DXF_main_base[0].split_list_1[1006][x1]);
			Query1.bindValue(":dxf_1007",DXF_main_base[0].split_list_1[1007][x1]);
			Query1.bindValue(":dxf_1008",DXF_main_base[0].split_list_1[1008][x1]);
			Query1.bindValue(":dxf_1009",DXF_main_base[0].split_list_1[1009][x1]);
			Query1.bindValue(":dxf_1010",DXF_main_base[0].split_list_1[1010][x1]);
			Query1.bindValue(":dxf_1011",DXF_main_base[0].split_list_1[1011][x1]);
			Query1.bindValue(":dxf_1012",DXF_main_base[0].split_list_1[1012][x1]);
			Query1.bindValue(":dxf_1013",DXF_main_base[0].split_list_1[1013][x1]);
			Query1.bindValue(":dxf_1014",DXF_main_base[0].split_list_1[1014][x1]);
			Query1.bindValue(":dxf_1015",DXF_main_base[0].split_list_1[1015][x1]);
			Query1.bindValue(":dxf_1016",DXF_main_base[0].split_list_1[1016][x1]);
			Query1.bindValue(":dxf_1017",DXF_main_base[0].split_list_1[1017][x1]);
			Query1.bindValue(":dxf_1018",DXF_main_base[0].split_list_1[1018][x1]);
			Query1.bindValue(":dxf_1019",DXF_main_base[0].split_list_1[1019][x1]);
			Query1.bindValue(":dxf_1020",DXF_main_base[0].split_list_1[1020][x1]);
			Query1.bindValue(":dxf_1021",DXF_main_base[0].split_list_1[1021][x1]);
			Query1.bindValue(":dxf_1022",DXF_main_base[0].split_list_1[1022][x1]);
			Query1.bindValue(":dxf_1023",DXF_main_base[0].split_list_1[1023][x1]);
			Query1.bindValue(":dxf_1024",DXF_main_base[0].split_list_1[1024][x1]);
			Query1.bindValue(":dxf_1025",DXF_main_base[0].split_list_1[1025][x1]);
			Query1.bindValue(":dxf_1026",DXF_main_base[0].split_list_1[1026][x1]);
			Query1.bindValue(":dxf_1027",DXF_main_base[0].split_list_1[1027][x1]);
			Query1.bindValue(":dxf_1028",DXF_main_base[0].split_list_1[1028][x1]);
			Query1.bindValue(":dxf_1029",DXF_main_base[0].split_list_1[1029][x1]);
			Query1.bindValue(":dxf_1030",DXF_main_base[0].split_list_1[1030][x1]);
			Query1.bindValue(":dxf_1031",DXF_main_base[0].split_list_1[1031][x1]);
			Query1.bindValue(":dxf_1032",DXF_main_base[0].split_list_1[1032][x1]);
			Query1.bindValue(":dxf_1033",DXF_main_base[0].split_list_1[1033][x1]);
			Query1.bindValue(":dxf_1034",DXF_main_base[0].split_list_1[1034][x1]);
			Query1.bindValue(":dxf_1035",DXF_main_base[0].split_list_1[1035][x1]);
			Query1.bindValue(":dxf_1036",DXF_main_base[0].split_list_1[1036][x1]);
			Query1.bindValue(":dxf_1037",DXF_main_base[0].split_list_1[1037][x1]);
			Query1.bindValue(":dxf_1038",DXF_main_base[0].split_list_1[1038][x1]);
			Query1.bindValue(":dxf_1039",DXF_main_base[0].split_list_1[1039][x1]);
			Query1.bindValue(":dxf_1040",DXF_main_base[0].split_list_1[1040][x1]);
			Query1.bindValue(":dxf_1041",DXF_main_base[0].split_list_1[1041][x1]);
			Query1.bindValue(":dxf_1042",DXF_main_base[0].split_list_1[1042][x1]);
			Query1.bindValue(":dxf_1043",DXF_main_base[0].split_list_1[1043][x1]);
			Query1.bindValue(":dxf_1044",DXF_main_base[0].split_list_1[1044][x1]);
			Query1.bindValue(":dxf_1045",DXF_main_base[0].split_list_1[1045][x1]);
			Query1.bindValue(":dxf_1046",DXF_main_base[0].split_list_1[1046][x1]);
			Query1.bindValue(":dxf_1047",DXF_main_base[0].split_list_1[1047][x1]);
			Query1.bindValue(":dxf_1048",DXF_main_base[0].split_list_1[1048][x1]);
			Query1.bindValue(":dxf_1049",DXF_main_base[0].split_list_1[1049][x1]);
			Query1.bindValue(":dxf_1050",DXF_main_base[0].split_list_1[1050][x1]);
			Query1.bindValue(":dxf_1051",DXF_main_base[0].split_list_1[1051][x1]);
			Query1.bindValue(":dxf_1052",DXF_main_base[0].split_list_1[1052][x1]);
			Query1.bindValue(":dxf_1053",DXF_main_base[0].split_list_1[1053][x1]);
			Query1.bindValue(":dxf_1054",DXF_main_base[0].split_list_1[1054][x1]);
			Query1.bindValue(":dxf_1055",DXF_main_base[0].split_list_1[1055][x1]);
			Query1.bindValue(":dxf_1056",DXF_main_base[0].split_list_1[1056][x1]);
			Query1.bindValue(":dxf_1057",DXF_main_base[0].split_list_1[1057][x1]);
			Query1.bindValue(":dxf_1058",DXF_main_base[0].split_list_1[1058][x1]);
			Query1.bindValue(":dxf_1059",DXF_main_base[0].split_list_1[1059][x1]);
			Query1.bindValue(":dxf_1060",DXF_main_base[0].split_list_1[1060][x1]);
			Query1.bindValue(":dxf_1061",DXF_main_base[0].split_list_1[1061][x1]);
			Query1.bindValue(":dxf_1062",DXF_main_base[0].split_list_1[1062][x1]);
			Query1.bindValue(":dxf_1063",DXF_main_base[0].split_list_1[1063][x1]);
			Query1.bindValue(":dxf_1064",DXF_main_base[0].split_list_1[1064][x1]);
			Query1.bindValue(":dxf_1065",DXF_main_base[0].split_list_1[1065][x1]);
			Query1.bindValue(":dxf_1066",DXF_main_base[0].split_list_1[1066][x1]);
			Query1.bindValue(":dxf_1067",DXF_main_base[0].split_list_1[1067][x1]);
			Query1.bindValue(":dxf_1068",DXF_main_base[0].split_list_1[1068][x1]);
			Query1.bindValue(":dxf_1069",DXF_main_base[0].split_list_1[1069][x1]);
			Query1.bindValue(":dxf_1070",DXF_main_base[0].split_list_1[1070][x1]);
			Query1.bindValue(":dxf_1071",DXF_main_base[0].split_list_1[1071][x1]);
			/*Query1.bindValue(":dxf_1072",DXF_main_base[0].split_list_1[1072][x1]);
			Query1.bindValue(":dxf_1073",DXF_main_base[0].split_list_1[1073][x1]);
			Query1.bindValue(":dxf_1074",DXF_main_base[0].split_list_1[1074][x1]);*/


			//x10++;
			x2=Query1.exec();

		//x2=Query1.exec();
		x1++;

	}


	//m_db.exec(QsqlString);

	m_db.commit();
	return Record_count_lines;
}



void dbManager::dbManager_load_dxf(const QString &pathname)
{
    QString path = pathname;
	//m_db.database().transaction();
	m_db.transaction();

	QSqlTableModel dxf_tabel1;
	dxf_tabel1.setTable("dxf_file");
	dxf_tabel1.select();

	QTableView dxf_table_view;
	dxf_table_view.setModel(&dxf_tabel1);


	QSqlRecord dxf_lines=dxf_tabel1.record();

	dxf_line_count=0;
	count_input=0;
	dxf_line_count_max=DXF_main_base[0].dxf_input.count();

	dxf_list1.clear();
	dxf_list2.clear();
	dxf_list3.clear();
	dxf_list4.clear();

	//dxf_tabel1.database().transaction();

	while (dxf_line_count<dxf_line_count_max-1)
	{
		if ((QString(DXF_main_base[0].dxf_input[dxf_line_count]).toInt()==0) and (DXF_main_base[0].dxf_input[dxf_line_count+1]=="SECTION"))
		{
			dxf_section=DXF_main_base[0].dxf_input[dxf_line_count+3];
		}


		dxf_lines.setValue("Index_count", QString::number(count_input));
		//dxf_list1.append(QString::number(count_input));

		dxf_lines.setValue("Code",DXF_main_base[0].dxf_input[dxf_line_count]);
		//dxf_list2.append(DXF_main_base[0].dxf_input[dxf_line_count]);

		dxf_lines.setValue("Waarde",DXF_main_base[0].dxf_input[dxf_line_count+1]);
		//dxf_list3.append(DXF_main_base[0].dxf_input[dxf_line_count+1]);

		dxf_lines.setValue("Section",dxf_section);
		//dxf_list4.append(dxf_section);



		dxf_line_count++;

		dxf_line_count++;


		count_input++;

		//dxf_table_view<-dxf_lines;



		dxf_tabel1.insertRecord(-1,dxf_lines);
		dxf_tabel1.submit();
		//m_db.database().commit();

	}
	//dxf_tabel1.submitAll();

	//m_db.database().commit();
	m_db.database().commit();


}

void dbManager::dbManager_create_elmt_entitie (const QString &pathname, int32_t Index_count_1,QString Block_naam_1, QString Block_value_1)
{
    QString path = pathname;

	QSqlQuery Query_entitie;

	Qsql_entitie = "INSERT INTO table_elmt_entities (Index_count, Block_Naam, Block_value";
	Qsql_entitie.append(")");
	Qsql_entitie.append(" VALUES (:Index_count, :Block_Naam, :Block_value");
	Qsql_entitie.append(")");

	Query_entitie.prepare(Qsql_entitie);

	Query_entitie.bindValue(":Index_count",Index_count_1);
	Query_entitie.bindValue("Block_Naam",Block_naam_1);
	Query_entitie.bindValue(":Block_value",Block_value_1);

	//Query_entitie.prepare(Qsql_entitie);

	Query_entitie.exec();


}

void dbManager::dbManager_create_elmt_block (const QString &pathname, int32_t Index_count_2,QString Block_naam_2, QString Block_value_2)
{
    QString path = pathname;
	QSqlQuery Query_block;

	Qsql_Block = "INSERT INTO table_elmt_entities (Index_count, Block_Naam, Block_value";
	Qsql_Block.append(")");
	Qsql_Block.append(" VALUES (:Index_count, :Block_Naam, :Block_value");
	Qsql_Block.append(")");

	Query_block.prepare(Qsql_Block);

	Query_block.bindValue(":Index_count",Index_count_2);
	Query_block.bindValue("Block_Naam",Block_naam_2);
	Query_block.bindValue(":Block_value",Block_value_2);

	//Query_block.prepare(Qsql_Block);

	Query_block.exec();
}

void dbManager::dbManager_load_dxf_list(const QString &pathname)
{
    QString path = pathname;
	m_db.transaction();

	QSqlQuery Query_List;

	//QsqlString="create table dxf_list (Index_count primary key, Code)";

	Qsql_List="INSERT INTO dxf_list (Index_count, Code) ";
	Qsql_List.append("VALUES (:Index_count, :Code)");

	Query_List.prepare(Qsql_List);

	dxf_line_count_max=DXF_main_base[0].dxf_input.count();
	count_input=0;

	//dxf_list1.clear();

	while (count_input<dxf_line_count_max-1)
	{

		Query_List.bindValue(":Index_count", count_input);
		Query_List.bindValue(":Code", DXF_main_base[0].dxf_input[count_input]);

		//dxf_list1.append(count_input);
		//dxf_list1.append(DXF_main_base[0].dxf_input[count_input]);
		count_input++;
		Query_List.exec();




	}

	//Query_List.addBindValue(dxf_list1);
	//Query_List.exec();

	m_db.database().commit();
}

QString dbManager::db_split_header(const QString &pathname)
{
    QString path = pathname;
	/*m_db.transaction();

	QSqlTableModel dxf_tabel1;
	dxf_tabel1.setTable("dxf_file");
	dxf_tabel1.setFilter(Section='HEADER');
	dxf_tabel1.select();

	QSqlRecord dxf_file_lines=dxf_tabel1.record();


	QSqlTableModel dxf_header1;
	dxf_header1.setTable("dxf_header");
	dxf_header1.select();

	dxf_header1.clear();

	QSqlRecord dxf_header_lines=dxfheader1.record();



	m_db.commit();*/

	return "false";
}

void dbManager::dbManager_transfer_dxf(const QString &pathname)
{
    QString path = pathname;
	connect (this ,SIGNAL (send_log(const QString &)),parent(),SLOT(update_log(const QString &)));

	m_db.transaction();

	//QsqlString="create table dxf_file (Index_count primary key, Code, Waarde, Section, Commando )";
	//QsqlString="create table dxf_list (Index_count primary key, Code)";

	//Qsql_List="INSERT INTO dxf_list (Index_count, Code) ";
	//Qsql_List.append("VALUES (:Index_count, :Code)");

	transfer_count=1;
	Transfer_Code="";
	Transfer_waarde="";
	Transfer_Section="";
	Transfer_Commando="";

	QSqlQuery Read_list("SELECT * FROM dxf_list");
	QSqlQuery Write_transfer;

	//QSql_dxf_list="SELECT * FROM dxf_list";

	//Read_list.prepare(QSql_dxf_list);

	QSql_transfer= "INSERT INTO dxf_file (Index_count, Code, Waarde, Section, Commando, AcadValue )";
	QSql_transfer.append("VALUES (:Index_count, :Code, :Waarde, :Section, :Commando, :AcadValue)");

	Write_transfer.prepare(QSql_transfer);

	Transfer_AcadValue=0;

	while (Read_list.next())
	{
		List_1=Read_list.value(1).toInt();

		Read_list.next();

		List_2=Read_list.value(1).toString();

		if (List_1==0 and List_2=="SECTION")
		{
			Read_list.next();
			List_3=Read_list.value(1).toInt();

			Read_list.next();
			List_4=Read_list.value(1).toString();

			Transfer_AcadValue=0;

			if (List_3==2)
			{

				Transfer_Section=List_4;
			}

		}

		if (List_1==0)
		{
			Transfer_Commando=List_2;
		}

		if (List_1==0 and List_2!="SECTION")
		{
			Transfer_AcadValue++;
		}

		if (List_1==9)
		{
			Transfer_AcadValue++;
		}


		Write_transfer.bindValue(":Index_count",transfer_count);
		Write_transfer.bindValue(":Code",List_1);
		Write_transfer.bindValue(":Waarde",List_2);
		Write_transfer.bindValue(":Section",Transfer_Section);
		Write_transfer.bindValue(":Commando",Transfer_Commando);
		Write_transfer.bindValue(":AcadValue",Transfer_AcadValue);

		Signal_log1.clear();
		Signal_log1.append(" index count : ");
		Signal_log1.append(QString::number(transfer_count));
		Signal_log1.append(" dxf code : ");
		Signal_log1.append(QString::number(List_1));
		Signal_log1.append(" Value : ");
		Signal_log1.append(List_2);
		Signal_log1.append(" Section : ");
		Signal_log1.append(Transfer_Section);
		Signal_log1.append(" Commando : ");
		Signal_log1.append(Transfer_Commando);
		Signal_log1.append(" AcadValue : ");
		Signal_log1.append(QString::number(Transfer_AcadValue));



		//Signal_log1.append("\n");

		emit send_log(Signal_log1);

		Write_transfer.exec();

		transfer_count++;


	}

	m_db.database().commit();


}
