#pragma once

#include "Config.h"

#include "Types.h"
#include "Defines.h"

class HTTPFileDownloader
{
public:
	HTTPFileDownloader();
	~HTTPFileDownloader();

	bool Download(IN const char* URL, IN const char* OutputFileName);
};