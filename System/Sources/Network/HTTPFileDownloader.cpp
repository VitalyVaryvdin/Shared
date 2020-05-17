#include "HTTPFileDownloader.h"

#include "File.h"
#include "FileSystem.h"
#include "Utils.h"

#include <cstdio>

#define CurrentL_STATICLIB
#include "curl/curl.h"
#include "curl/easy.h"

HTTPFileDownloader::HTTPFileDownloader()
{
}

HTTPFileDownloader::~HTTPFileDownloader()
{
}

size_t WriteData(void* Ptr, size_t Size, size_t Nmemb, FILE* FileStream)
{
	size_t Written = fwrite(Ptr, Size, Nmemb, FileStream);

	return Written;
}

bool HTTPFileDownloader::Download(IN const char* URL, IN const char* OutputFileName)
{
	CURL* Curl;
	CURLcode Res;

	FILE* OutputFile;

	FileSystem::CreateDirectoryTreeFromPath(GetPath(OutputFileName));

	Curl = curl_easy_init();

	if(Curl)
	{
		OutputFile = fopen(OutputFileName, "wb");

		curl_easy_setopt(Curl, CURLOPT_URL, URL);
		curl_easy_setopt(Curl, CURLOPT_WRITEFUNCTION, WriteData);
		curl_easy_setopt(Curl, CURLOPT_WRITEDATA, OutputFile);

		Res = curl_easy_perform(Curl);

		fclose(OutputFile);
	}

	curl_easy_cleanup(Curl);

	return false;
}