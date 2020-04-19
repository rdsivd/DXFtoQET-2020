#include "baseelmt.h"


BaseELMT::BaseELMT(QWidget *parent) : QWidget(parent)
{
}

QString BaseELMT::DefinitionStart()
{
	/* Base values */



	Result="";

	/* <definition width="40" version="0.4"
	 * hotspot_x="18" hotspot_y="24" height="50"
	 * link_type="master" type="element" orientation="dyyy"> */

	Result.append("<definition");
	Result.append(" width=");
	Result.append(QChar(34));
	Result.append(ELMT_definition_width);
	Result.append(QChar(34));
	Result.append(" version=");
	Result.append(QChar(34));
	Result.append(ELMT_definition_version);
	Result.append(QChar(34));
	Result.append(" hotspot_x=");
	Result.append(QChar(34));
	Result.append(ELMT_definition_hotspot_x);
	Result.append(QChar(34));
	Result.append(" hotspot_y=");
	Result.append(QChar(34));
	Result.append(ELMT_definition_hotspot_y);
	Result.append(QChar(34));
	Result.append(" height=");
	Result.append(QChar(34));
	Result.append(ELMT_definition_height);
	Result.append(QChar(34));
	Result.append(" link_type=");
	Result.append(QChar(34));
	Result.append(ELMT_definition_link_type);
	Result.append(QChar(34));
	Result.append(" type=");
	Result.append(QChar(34));
	Result.append(ELMT_definition_type);
	Result.append(QChar(34));
	Result.append(" orientation=");
	Result.append(QChar(34));
	Result.append(ELMT_definition_orientation);
	Result.append(QChar(34));

	Result.append(" >");
	Result.append('\n');

	return Result;

}

QString BaseELMT::DefinitionEnd()
{

	Result="";

	/* </definition> */



	Result.append("</definition>");
	Result.append('\n');

	return Result;

}

QString BaseELMT::Uuid()
{

	Result="";

	/*  <uuid uuid="{687262D2-B8A1-4CD6-B56F-4547577EFD01}"/> */

	Uuidstring=QUuid::createUuid();

	Result.append("<uuid");
	Result.append(" uuid=");
	Result.append(QChar(34));
	Result.append(Uuidstring.toString());
	Result.append(QChar(34));

	Result.append(" />");
	Result.append('\n');

	return Result;

}
QString BaseELMT::Uuid2()
{

    Result="";

    /*  <uuid uuid="{687262D2-B8A1-4CD6-B56F-4547577EFD01}"/> */

    Uuidstring=QUuid::createUuid();

    //Result.append("<uuid");
    //Result.append(" uuid=");
    Result.append(QChar(34));
    Result.append(Uuidstring.toString());
    Result.append(QChar(34));

    //Result.append(" />");
    //Result.append('\n');

    return Result;

}
QString BaseELMT::Names()
{

	/* Base values */

	/*ELMT_Name_ar="ar";
	ELMT_Name_de="de";
	ELMT_Name_en="en";
	ELMT_Name_it="it";
	ELMT_Name_fr="fr";
	ELMT_Name_pl="pl";
	ELMT_Name_es="es";
	ELMT_Name_nl="nl";
	ELMT_Name_cs="cs";
	ELMT_Name_be_nl="be_nl";*/

	Result="";

	/* <names>
		<name lang="ar">قاطع أحادي الوجه</name>
		<name lang="de">Lastschalter 2P</name>
		<name lang="en">Circuit-breaker</name>
		<name lang="it">Sezionatore 2P</name>
		<name lang="fr">Disjoncteur mono</name>
		<name lang="pl">Wyłącznik</name>
		<name lang="es">Interruptor magnetotérmico</name>
		<name lang="nl">Lastscheider 2</name>
		<name lang="cs">Jistič 2</name>
	   </names> */

	Result.append("<names>\n");


	if (ELMT_Name_en != "")
	{
		Result.append("    ");
		Result.append("<name lang=");
		Result.append(QChar(34));
		Result.append(ELMT_Name_en);
		Result.append(QChar(34));
		Result.append(">");
		Result.append(ELMT_Name_text_en);
		Result.append("</name>\n");
	}

	if (ELMT_Name_fr != "-")
	{

		Result.append("    ");
		Result.append("<name lang=");
		Result.append(QChar(34));
		Result.append(ELMT_Name_fr);
		Result.append(QChar(34));
		Result.append(">");
		Result.append(ELMT_Name_text_fr);
		Result.append("</name>\n");
	}

	if (ELMT_Name_be_nl != "")
	{
		Result.append("    ");
		Result.append("<name lang=");
		Result.append(QChar(34));
		Result.append(ELMT_Name_be_nl);
		Result.append(QChar(34));
		Result.append(">");
		Result.append(ELMT_Name_text_be_nl);
		Result.append("</name>\n");
	}

	if (ELMT_Name_ar != "")
	{
		Result.append("    ");
		Result.append("<name lang=");
		Result.append(QChar(34));
		Result.append(ELMT_Name_ar);
		Result.append(QChar(34));
		Result.append(">");
		Result.append(ELMT_Name_text_ar);
		Result.append("</name>\n");
	}

	if (ELMT_Name_de != "")
	{
		Result.append("    ");
		Result.append("<name lang=");
		Result.append(QChar(34));
		Result.append(ELMT_Name_de);
		Result.append(QChar(34));
		Result.append(">");
		Result.append(ELMT_Name_text_de);
		Result.append("</name>\n");
	}

	if (ELMT_Name_it != "")
	{
		Result.append("    ");
		Result.append("<name lang=");
		Result.append(QChar(34));
		Result.append(ELMT_Name_it);
		Result.append(QChar(34));
		Result.append(">");
		Result.append(ELMT_Name_text_it);
		Result.append("</name>\n");
	}

	if (ELMT_Name_pl != "")
	{
		Result.append("    ");
		Result.append("<name lang=");
		Result.append(QChar(34));
		Result.append(ELMT_Name_pl);
		Result.append(QChar(34));
		Result.append(">");
		Result.append(ELMT_Name_text_pl);
		Result.append("</name>\n");
	}

	if (ELMT_Name_es != "")
	{
		Result.append("    ");
		Result.append("<name lang=");
		Result.append(QChar(34));
		Result.append(ELMT_Name_es);
		Result.append(QChar(34));
		Result.append(">");
		Result.append(ELMT_Name_text_es);
		Result.append("</name>\n");
	}

	if (ELMT_Name_cs != "")
	{
		Result.append("    ");
		Result.append("<name lang=");
		Result.append(QChar(34));
		Result.append(ELMT_Name_cs);
		Result.append(QChar(34));
		Result.append(">");
		Result.append(ELMT_Name_text_cs);
		Result.append("</name>\n");
	}

	if (ELMT_Name_nl != "")
	{
		Result.append("    ");
		Result.append("<name lang=");
		Result.append(QChar(34));
		Result.append(ELMT_Name_nl);
		Result.append(QChar(34));
		Result.append(">");
		Result.append(ELMT_Name_text_nl);
		Result.append("</name>\n");
	}

	Result.append("</names>");
	Result.append('\n');

	return Result;

}

QString BaseELMT::KindInformation()
{
	/* Base values */

	ELMT_kind_name="type";
	ELMT_kind_show="1";
	ELMT_kind_type="protection";

	Result="";

	/*	<kindInformations>
		<kindInformation name="type" show="1">protection</kindInformation>
		</kindInformations> */

	Result.append("<kindInformations>\n");

	Result.append("<kindInformation");
	Result.append(" name=");
	Result.append(QChar(34));
	Result.append(ELMT_kind_name);
	Result.append(QChar(34));
	Result.append(" show=");
	Result.append(QChar(34));
	Result.append(ELMT_kind_show);
	Result.append(QChar(34));
	Result.append(">");
	Result.append(ELMT_kind_type);
	Result.append("</kindInformation>\n");

	Result.append("</kindInformations>\n");

	return Result;
}

QString BaseELMT::Informations()
{

	/* Base values */

	Result="";

	/*ELMT_informations_Author="The QElectroTech team";
	ELMT_informations_License=" see http://qelectrotech.org/wiki/doc/elements_license";
	ELMT_converter_by=" Ronny Desmedt";
	ELMT_converter_version=" V3.0 db";*/


	/*		<informations>Author: The QElectroTech team
			License: see http://qelectrotech.org/wiki/doc/elements_license
			</informations> */


	Result.append("<informations>\n");

	Result.append("     ");
	Result.append("Author: ");
	Result.append(ELMT_informations_Author);
	Result.append("\n");
	Result.append("     ");
	Result.append("License:");
	Result.append(ELMT_informations_License);
	Result.append("\n");
	Result.append("     ");
	Result.append("Converter version:");
	Result.append(ELMT_converter_version);
	Result.append("\n");
	// Result.append("     ");
	// Result.append("Converter by:");
	// Result.append(ELMT_converter_by);
	Result.append("\n");

	Result.append("</informations>\n");

	return Result;
}

QString BaseELMT::DescriptionStart()
{
	/* base var */

	Result="";

	/* <description> */



	Result.append("<description>");
	Result.append('\n');

	return Result;
}

QString BaseELMT::DescriptionEnd()
{
	/*  base var */

	Result="";

	/* </description> */



	Result.append("</description>");
	Result.append('\n');

	return Result;

}
