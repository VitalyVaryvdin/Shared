#include "Log.h"

#include <ctime>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Utils.h"

static const char* WarningMessage	= "Warning";
static const char* ErrorMessage		= "Error";
static const char* FatalMessage		= "Fatal";
static const char* TimeFormat		= "[%X]"; // 23:59:59

static const char* HTMLHeader		=
"<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n \
<html>\n \
<head>\n \
<title>Log file</title>\n \
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/>\n \
<style type=\"text/css\">\n \
	body { background: #eee; color: #b4c8d2; margin-right: 20px; margin-left: 20px; font-size: 14px; font-family: Helvetica; }\n \
	h1 { text-align: left; color: #626569; }\n \
	tt { align: center; text-align: center; color: #626569; font-size: 16; }\n \
	.m, .w, .e, .f { padding: 3px; }\n \
	.m { background-color: #333; color: #ffffff; }\n \
	.w { background-color: #FFF0AA; color: #626569; }\n \
	.e { background-color: #FD794B; color: #FDEDD0; }\n \
	.f { background-color: #FF4229; color: #FDEDD0; }\n \
	dl { padding: 0 0 0 10px; }\n \
	dl.section { margin-left: 0px; padding-left: 0px; }\n \
	dl.warning { margin-left: 0px; padding-left: 3px; border-left: 5px solid; border-color: #FFF0AA; }\n \
	dl.error { margin-left: 0px; padding-left: 3px; border-left: 5px solid; border-color: #FD794B; }\n \
	dl.fatal { margin-left: 0px; padding-left: 3px; border-left: 5px solid; border-color: #FF4229; }\n \
	dl.section dd { padding-left: 15px; padding-right: 3px; }\n \
</style>\n \
</head>\n \
<body>\n \
<h1>Log file</h1>\n";

std::string Log::mFileName			= "";
bool		Log::mInitialised		= false;

std::string ConvertToHTML(IN const char* Str)
{
	std::string ReturnString;
	const char* Ptr = Str;

	while(*Ptr)
	{
		switch(*Ptr)
		{
		case '\t':
			ReturnString += "&nbsp; &nbsp; ";
			break;
		case '<':
			ReturnString += "&lt;";
			break;
		case '>':
			ReturnString += "&gt;";
			break;
		case '\n':
			ReturnString += "<br>";
			break;
		default:
			ReturnString += *Ptr;
			break;
		}

		Ptr++;
	}

	return ReturnString;
}

void Log::FileName(IN std::string Name)
{
	mFileName = Name;
}

std::string Log::FileName()
{
	return mFileName;
}

void Log::Output(IN std::string Message, IN int LogLevel /* = Info */)
{
	std::stringstream	Buffer;

	/* getting current time */
	time_t	RawTime;
	tm*		TimeInfo;
	char	Time[128];
	char    FileName[256];

	time(&RawTime);
	TimeInfo = localtime(&RawTime);

	strftime(Time, 128, TimeFormat, TimeInfo);
	/*******************************************/

	if(!mInitialised)
	{
		strftime(FileName, 256, "%H-%M-%S %d.%m.%Y", TimeInfo);

		mFileName += "Log ";
		mFileName += FileName;
		mFileName += ".html";

		Buffer	<< HTMLHeader;

		mInitialised = true;
	}

	switch(LogLevel)
	{
	case Info:
		Buffer	<< "<div class=\"m\">"
				<< Time << " " << ConvertToHTML(Message.c_str())
				<< "</div>";
		break;
	case Warning:
		Buffer	<< "<div class=\"m\">"
				<< "<dl class=\"section warning\">"
				<< "<dt>" << WarningMessage << "</dt>"
				<< "<dd>" << ConvertToHTML(Message.c_str()) << "</dd>"
				<< "</dl>"
				<< "</div>";
		break;
	case Error:
		Buffer	<< "<div class=\"m\">"
				<< "<dl class=\"section error\">"
				<< "<dt>" << ErrorMessage << "</dt>"
				<< "<dd>" << ConvertToHTML(Message.c_str()) << "</dd>"
				<< "</dl>"
				<< "</div>";
		break;
	case Fatal:
		Buffer	<< "<div class=\"m\">"
				<< "<dl class=\"section fatal\">"
				<< "<dt>" << FatalMessage << "</dt>"
				<< "<dd>" << ConvertToHTML(Message.c_str()) << "</dd>"
				<< "</dl>"
				<< "</div>";
		break;
	default:
		break;
	}

	std::fstream File(mFileName.c_str(), std::ios::app|std::ios::out);
	File << Buffer.str();

	File.close();
}

std::string ComposeError(IN std::string ErrorMessage, IN const char* Function, IN const char* File, IN int Line)
{
	std::stringstream Buffer;

	Buffer << ErrorMessage << "<br>";
	Buffer << "File: " << File << " " << "Function: " << Function << "() " << "Line: " << Line;

	return Buffer.str();
}