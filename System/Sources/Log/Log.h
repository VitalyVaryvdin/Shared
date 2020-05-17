#pragma once

#include "Config.h"

#include "Types.h"
#include "Defines.h"

#include <string>

class Log
{
public:
	enum
	{
		Info,
		Warning,
		Error,
		Fatal
	};

	static void			FileName(IN std::string Name);
	static std::string	FileName();

	static void			Output(IN std::string Message, IN int LogLevel = Info);
private:
	static std::string	mFileName;
	static bool			mInitialised;
};

std::string ComposeError(IN std::string ErrorMessage, IN const char* Function, IN const char* File, IN int Line);

#define Error(ErrorMessage) ComposeError(ErrorMessage, __FUNCTION__, __FILE__, __LINE__)