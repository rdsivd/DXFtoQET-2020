#ifndef DATA_H
#define DATA_H

#include <QtCore>
#include <QWidget>

//#include "db/dbmanager.h"

#define DXF_base_set 1
#define DXF_item_split 50000 //dxf split tables
#define DXF_codes_set 10000
#define DXF_codeset_copies 10000
#define QET_L_POLYLINE 2000
#define QSTRING_max_lengt 1900000
#define DXF_layers_set 500

struct DXF_base
{
	QString dxf_openfile;
	QString dxf_dir;
	QString dxf_filepath; // dxf file path
	QString dxf_text_all;
	QString dxf_filetype;
	QString dxf_savepath; // QET elements path

	QString QDXF_line_color;
	QString QDXF_circle_color;
	QString QDXF_arc_color;
	QString QDXF_ellipse_color;
	QString QDXF_input_color;
	QString QDXF_polyline_color;
	QString QDXF_rectangel_color;
	QString QDXF_terminal_color;
	QString QDXF_text_color;
	QString QDXF_lwpolyline_color;
	QString QDXF_solid_color;

	QString QDXF_entitie_line_color;
	QString QDXF_entitie_circle_color;
	QString QDXF_entitie_arc_color;
	QString QDXF_entitie_ellipse_color;
	QString QDXF_entitie_input_color;
	QString QDXF_entitie_polyline_color;
	QString QDXF_entitie_rectangel_color;
	QString QDXF_entitie_terminal_color;
	QString QDXF_entitie_text_color;
	QString QDXF_entitie_lwpolyline_color;
	QString QDXF_entitie_solid_color;

	QString QDXF_block_line_color;
	QString QDXF_block_circle_color;
	QString QDXF_block_arc_color;
	QString QDXF_block_ellipse_color;
	QString QDXF_block_input_color;
	QString QDXF_block_polyline_color;
	QString QDXF_block_rectangel_color;
	QString QDXF_block_terminal_color;
	QString QDXF_block_text_color;
	QString QDXF_block_lwpolyline_color;
	QString QDXF_block_solid_color;

	int32_t DXF_Header_count;
	int32_t DXF_Classes_count;
	int32_t DXF_Tables_count;
	int32_t DXF_blocks_count;
	int32_t DXF_Entities_count;
	int32_t DXF_Objects_count;
	int32_t DXF_Thumbnail_count;

	QStringList dxf_input;

	int32_t dxf_line_count;
	int32_t dxf_csv_line_count;

	QStringList split_list_1[1200];

	int DXF_file_loaded_into_table;
};

struct DXF_codes
{
	int64_t index_count;

	QString Section; //section of dxf file
	QString Command; //dxf instructie
	QString ID_instruction; // unic id to select instruction
	int Command_count; //

	QString dxfbase;

	QString dxf_m1;
	QString dxf_m2;
	QString dxf_m3;
	QString dxf_m4;
	QString dxf_m5;

	QString dxf_0; //entitie type

	QString dxf_1;
	QString dxf_2;
	QString dxf_3;
	QString dxf_4;
	QString dxf_5;
	QString dxf_6;
	QString dxf_7;
	QString dxf_8;
	QString dxf_9;

	QString dxf_10;
	QString dxf_11;
	QString dxf_12;
	QString dxf_13;
	QString dxf_14;
	QString dxf_15;
	QString dxf_16;
	QString dxf_17;
	QString dxf_18;
	QString dxf_19;

	QString dxf_20;
	QString dxf_21;
	QString dxf_22;
	QString dxf_23;
	QString dxf_24;
	QString dxf_25;
	QString dxf_26;
	QString dxf_27;
	QString dxf_28;
	QString dxf_29;

	QString dxf_30;
	QString dxf_31;
	QString dxf_32;
	QString dxf_33;
	QString dxf_34;
	QString dxf_35;
	QString dxf_36;
	QString dxf_37;
	QString dxf_38;
	QString dxf_39;

	QString dxf_40;
	QString dxf_41;
	QString dxf_42;
	QString dxf_43;
	QString dxf_44;
	QString dxf_45;
	QString dxf_46;
	QString dxf_47;
	QString dxf_48;
	QString dxf_49;

	QString dxf_50;
	QString dxf_51;
	QString dxf_52;
	QString dxf_53;
	QString dxf_54;
	QString dxf_55;
	QString dxf_56;
	QString dxf_57;
	QString dxf_58;
	QString dxf_59;

	QString dxf_60;
	QString dxf_61;
	QString dxf_62;
	QString dxf_63;
	QString dxf_64;
	QString dxf_65;
	QString dxf_66;
	QString dxf_67;
	QString dxf_68;
	QString dxf_69;
	QString dxf_70;
	QString dxf_71;
	QString dxf_72;
	QString dxf_73;
	QString dxf_74;
	QString dxf_75;
	QString dxf_76;
	QString dxf_77;
	QString dxf_78;
	QString dxf_79;

	//dxf_80;
	//dxf_81;
	//dxf_82;
	//dxf_83;
	//dxf_84;
	//dxf_85;
	//dxf_86;
	//dxf_87;
	//dxf_88;
	//dxf_89;

	QString dxf_90;
	QString dxf_91;
	QString dxf_92;
	QString dxf_93;
	QString dxf_94;
	QString dxf_95;
	QString dxf_96;
	QString dxf_97;
	QString dxf_98;
	QString dxf_99;

	QString dxf_100;
	// dxf_101;
	QString dxf_102;
	// dxf_103;
	// dxf_104;
	QString dxf_105;
	//dxf_106;
	//dxf_107;
	//dxf_108;
	//dxf_109;


	QString dxf_110;
	QString dxf_111;
	QString dxf_112;
	QString dxf_113;
	QString dxf_114;
	QString dxf_115;
	QString dxf_116;
	QString dxf_117;
	QString dxf_118;
	QString dxf_119;

	QString dxf_120;
	QString dxf_121;
	QString dxf_122;
	QString dxf_123;
	QString dxf_124;
	QString dxf_125;
	QString dxf_126;
	QString dxf_127;
	QString dxf_128;
	QString dxf_129;

	QString dxf_130;
	QString dxf_131;
	QString dxf_132;
	QString dxf_133;
	QString dxf_134;
	QString dxf_135;
	QString dxf_136;
	QString dxf_137;
	QString dxf_138;
	QString dxf_139;

	QString dxf_140;
	QString dxf_141;
	QString dxf_142;
	QString dxf_143;
	QString dxf_144;
	QString dxf_145;
	QString dxf_146;
	QString dxf_147;
	QString dxf_148;
	QString dxf_149;

	// dxf_150;
	// dxf_151;
	// dxf_152;
	// dxf_153;
	// dxf_154;
	// dxf_155;
	// dxf_156;
	// dxf_157;
	// dxf_158;
	// dxf_159;

	QString dxf_160;
	QString dxf_161;
	QString dxf_162;
	QString dxf_163;
	QString dxf_164;
	QString dxf_165;
	QString dxf_166;
	QString dxf_167;
	QString dxf_168;
	QString dxf_169;

	QString dxf_170;
	QString dxf_171;
	QString dxf_172;
	QString dxf_173;
	QString dxf_174;
	QString dxf_175;
	QString dxf_176;
	QString dxf_177;
	QString dxf_178;
	QString dxf_179;

	// dxf_180;
	// dxf_181;
	// dxf_182;
	// dxf_183;
	// dxf_184;
	// dxf_185;
	// dxf_186;
	// dxf_187;
	// dxf_188;
	// dxf_189;
	// dxf_190;
	// dxf_191;
	// dxf_192;
	// dxf_193;
	// dxf_194;
	// dxf_195;
	// dxf_196;
	// dxf_197;
	// dxf_198;
	// dxf_199;
	// dxf_200;
	// dxf_201;
	// dxf_202;
	// dxf_203;
	// dxf_204;
	// dxf_205;
	// dxf_206;
	// dxf_207;
	// dxf_208;
	// dxf_209;

	QString dxf_210;
	QString dxf_211;
	QString dxf_212;
	QString dxf_213;
	QString dxf_214;
	QString dxf_215;
	QString dxf_216;
	QString dxf_217;
	QString dxf_218;
	QString dxf_219;
	QString dxf_220;
	QString dxf_221;
	QString dxf_222;
	QString dxf_223;
	QString dxf_224;
	QString dxf_225;
	QString dxf_226;
	QString dxf_227;
	QString dxf_228;
	QString dxf_229;
	QString dxf_230;
	QString dxf_231;
	QString dxf_232;
	QString dxf_233;
	QString dxf_234;
	QString dxf_235;
	QString dxf_236;
	QString dxf_237;
	QString dxf_238;
	QString dxf_239;

	// dxf_240;
	// dxf_241;
	// dxf_242;
	// dxf_243;
	// dxf_244;
	// dxf_245;
	// dxf_246;
	// dxf_247;
	// dxf_248;
	// dxf_249;
	// dxf_250;
	// dxf_251;
	// dxf_252;
	// dxf_253;
	// dxf_254;
	// dxf_255;
	// dxf_256;
	// dxf_257;
	// dxf_258;
	// dxf_259;
	// dxf_260;
	// dxf_261;
	// dxf_262;
	// dxf_263;
	// dxf_264;
	// dxf_265;
	// dxf_266;
	// dxf_267;
	// dxf_268;
	// dxf_269;

	QString dxf_270;
	QString dxf_271;
	QString dxf_272;
	QString dxf_273;
	QString dxf_274;
	QString dxf_275;
	QString dxf_276;
	QString dxf_277;
	QString dxf_278;
	QString dxf_279;

	QString dxf_280;
	QString dxf_281;
	QString dxf_282;
	QString dxf_283;
	QString dxf_284;
	QString dxf_285;
	QString dxf_286;
	QString dxf_287;
	QString dxf_288;
	QString dxf_289;

	QString dxf_290;
	QString dxf_291;
	QString dxf_292;
	QString dxf_293;
	QString dxf_294;
	QString dxf_295;
	QString dxf_296;
	QString dxf_297;
	QString dxf_298;
	QString dxf_299;


	QString dxf_300;
	QString dxf_301;
	QString dxf_302;
	QString dxf_303;
	QString dxf_304;
	QString dxf_305;
	QString dxf_306;
	QString dxf_307;
	QString dxf_308;
	QString dxf_309;

	QString dxf_310;
	QString dxf_311;
	QString dxf_312;
	QString dxf_313;
	QString dxf_314;
	QString dxf_315;
	QString dxf_316;
	QString dxf_317;
	QString dxf_318;
	QString dxf_319;

	QString dxf_320;
	QString dxf_321;
	QString dxf_322;
	QString dxf_323;
	QString dxf_324;
	QString dxf_325;
	QString dxf_326;
	QString dxf_327;
	QString dxf_328;
	QString dxf_329;

	QString dxf_330;
	QString dxf_331;
	QString dxf_332;
	QString dxf_333;
	QString dxf_334;
	QString dxf_335;
	QString dxf_336;
	QString dxf_337;
	QString dxf_338;
	QString dxf_339;
	QString dxf_340;
	QString dxf_341;
	QString dxf_342;
	QString dxf_343;
	QString dxf_344;
	QString dxf_345;
	QString dxf_346;
	QString dxf_347;
	QString dxf_348;
	QString dxf_349;
	QString dxf_350;
	QString dxf_351;
	QString dxf_352;
	QString dxf_353;
	QString dxf_354;
	QString dxf_355;
	QString dxf_356;
	QString dxf_357;
	QString dxf_358;
	QString dxf_359;
	QString dxf_360;
	QString dxf_361;
	QString dxf_362;
	QString dxf_363;
	QString dxf_364;
	QString dxf_365;
	QString dxf_366;
	QString dxf_367;
	QString dxf_368;
	QString dxf_369;

	QString dxf_370;
	QString dxf_371;
	QString dxf_372;
	QString dxf_373;
	QString dxf_374;
	QString dxf_375;
	QString dxf_376;
	QString dxf_377;
	QString dxf_378;
	QString dxf_379;

	QString dxf_380;
	QString dxf_381;
	QString dxf_382;
	QString dxf_383;
	QString dxf_384;
	QString dxf_385;
	QString dxf_386;
	QString dxf_387;
	QString dxf_388;
	QString dxf_389;

	QString dxf_390;
	QString dxf_391;
	QString dxf_392;
	QString dxf_393;
	QString dxf_394;
	QString dxf_395;
	QString dxf_396;
	QString dxf_397;
	QString dxf_398;
	QString dxf_399;

	QString dxf_400;
	QString dxf_401;
	QString dxf_402;
	QString dxf_403;
	QString dxf_404;
	QString dxf_405;
	QString dxf_406;
	QString dxf_407;
	QString dxf_408;
	QString dxf_409;

	QString dxf_410;
	QString dxf_411;
	QString dxf_412;
	QString dxf_413;
	QString dxf_414;
	QString dxf_415;
	QString dxf_416;
	QString dxf_417;
	QString dxf_418;
	QString dxf_419;

	QString dxf_420;
	QString dxf_421;
	QString dxf_422;
	QString dxf_423;
	QString dxf_424;
	QString dxf_425;
	QString dxf_426;
	QString dxf_427;
	QString dxf_428;
	QString dxf_429;


	QString dxf_430;
	QString dxf_431;
	QString dxf_432;
	QString dxf_433;
	QString dxf_434;
	QString dxf_435;
	QString dxf_436;
	QString dxf_437;
	QString dxf_438;
	QString dxf_439;

	QString dxf_440;
	QString dxf_441;
	QString dxf_442;
	QString dxf_443;
	QString dxf_444;
	QString dxf_445;
	QString dxf_446;
	QString dxf_447;
	QString dxf_448;
	QString dxf_449;

	QString dxf_450;
	QString dxf_451;
	QString dxf_452;
	QString dxf_453;
	QString dxf_454;
	QString dxf_455;
	QString dxf_456;
	QString dxf_457;
	QString dxf_458;
	QString dxf_459;

	QString dxf_460;
	QString dxf_461;
	QString dxf_462;
	QString dxf_463;
	QString dxf_464;
	QString dxf_465;
	QString dxf_466;
	QString dxf_467;
	QString dxf_468;
	QString dxf_469;


	QString dxf_470;
	QString dxf_471;
	QString dxf_472;
	QString dxf_473;
	QString dxf_474;
	QString dxf_475;
	QString dxf_476;
	QString dxf_477;
	QString dxf_478;
	QString dxf_479;

	QString dxf_480;
	QString dxf_481;
	QString dxf_482;
	QString dxf_483;
	QString dxf_484;
	QString dxf_485;
	QString dxf_486;
	QString dxf_487;
	QString dxf_488;
	QString dxf_489;

	QString dxf_999;

	QString dxf_1000;
	QString dxf_1001;
	QString dxf_1002;
	QString dxf_1003;
	QString dxf_1004;
	QString dxf_1005;
	QString dxf_1006;
	QString dxf_1007;
	QString dxf_1008;
	QString dxf_1009;

	QString dxf_1010;
	QString dxf_1011;
	QString dxf_1012;
	QString dxf_1013;
	QString dxf_1014;
	QString dxf_1015;
	QString dxf_1016;
	QString dxf_1017;
	QString dxf_1018;
	QString dxf_1019;
	QString dxf_1020;
	QString dxf_1021;
	QString dxf_1022;
	QString dxf_1023;
	QString dxf_1024;
	QString dxf_1025;
	QString dxf_1026;
	QString dxf_1027;
	QString dxf_1028;
	QString dxf_1029;
	QString dxf_1030;
	QString dxf_1031;
	QString dxf_1032;
	QString dxf_1033;
	QString dxf_1034;
	QString dxf_1035;
	QString dxf_1036;
	QString dxf_1037;
	QString dxf_1038;
	QString dxf_1039;
	QString dxf_1040;
	QString dxf_1041;
	QString dxf_1042;
	QString dxf_1043;
	QString dxf_1044;
	QString dxf_1045;
	QString dxf_1046;
	QString dxf_1047;
	QString dxf_1048;
	QString dxf_1049;
	QString dxf_1050;
	QString dxf_1051;
	QString dxf_1052;
	QString dxf_1053;
	QString dxf_1054;
	QString dxf_1055;
	QString dxf_1056;
	QString dxf_1057;
	QString dxf_1058;
	QString dxf_1059;

	QString dxf_1060;
	QString dxf_1061;
	QString dxf_1062;
	QString dxf_1063;
	QString dxf_1064;
	QString dxf_1065;
	QString dxf_1066;
	QString dxf_1067;
	QString dxf_1068;
	QString dxf_1069;
	QString dxf_1070;

	QString dxf_1071;


};

struct DXF_var
{
	QString DXF_ACADVER;
	QString DXF_ACADMAINTVER;
	QString DXF_DWGCODEPAGE;
	QString DXF_COMMENTS;
	QString DXF_INSBASE_X;
	QString DXF_INSBASE_Y;
	QString DXF_EXTMIN_X;
	QString DXF_EXTMIN_Y;
	QString DXF_EXTMAX_X;
	QString DXF_EXTMAX_Y;
	QString DXF_LIMMIN_X;
	QString DXF_LIMMIN_Y;
	QString DXF_LIMMAX_X;
	QString DXF_LIMMAX_Y;
	QString DXF_ORTHOMODE;
	QString DXF_REGENMODE;
	QString DXF_FILLMODE;
	QString DXF_QTEXTMODE;
	QString DXF_MIRRTEXT;
	QString DXF_LTSCALE;
	QString DXF_ATTMODE;
	QString DXF_TEXTSIZE;
	QString DXF_TRACEWID;
	QString DXF_TEXTSTYLE;
	QString DXF_CLAYER;
	QString DXF_CELTYPE;


};

struct DXF_Layers
{
	QString DXF_Layer_naam;
	QString DXF_Layer_linetype;
	QString DXF_Layer_color;

};

struct DXF_Entities
{
	QString DXF_Result;
    QString DXF_ResultBegin;
    QString DXF_ResultEinde;
    QString DXF_ResultEntitie;
    QString DXF_ResultEntitieLine;
    QString DXF_ResultEntitiePolyline;
    QString DXF_ResultEntitieLwpolyline;
    QString DXF_ResultEntitieSpline;
    QString DXF_ResultEntitieSolid;
    QString DXF_ResultEntitieHatch;
    QString DXF_ResultBlock;
    QString DXF_ResultBlock2;

};

struct dxf_file1
{
	QString ID;
	QString Code;
	QString Waarde;
	QString	Sectie;
};

class data : public QWidget
{
	Q_OBJECT
	public:
    explicit data(QWidget *parent = nullptr);

	signals:

	public slots:
};



#endif // DATA_H
