#include "dxf_text_control.h"

DXF_Text_control::DXF_Text_control(QWidget *parent) : QWidget(parent)
{
}


QString DXF_Text_control::Text_control()
{

	if(TextToCheck.contains("<"))
	{
		TextToCheck.replace("<","&lt;");
	}
	if(TextToCheck.contains(">"))
	{
		TextToCheck.replace(">","&gt;");
	}
	if(TextToCheck.contains("&"))
	{
		TextToCheck.replace("&","-");
	}
	if(TextToCheck.contains(QChar(39)))
	{
		TextToCheck.replace(QChar(39),"&apos;");
	}
	if(TextToCheck.contains(QChar(34)))
	{
		TextToCheck.replace(QChar(34),"&quot;");
	}

	if(TextToCheck.contains("/"))
	{
		TextToCheck.replace("/","-");
	}

	if(TextToCheck.contains(QChar(92)))
	{
		TextToCheck.replace(QChar(92),"-");
	}

	/*if(TextToCheck.contains("*"))
	{
		TextToCheck.replace("*","x");
	}*/

	if(TextToCheck.contains("?"))
	{
		TextToCheck.replace("?","...");
	}

	if(TextToCheck.contains("|"))
	{
		TextToCheck.replace("|","-");
	}


	return TextToCheck;



}
