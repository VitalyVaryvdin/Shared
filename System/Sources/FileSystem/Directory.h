#pragma once

#include "Config.h"

#include "Types.h"
#include "Defines.h"

class Directory
{
public:
	Directory(const char* Path = ".");
	~Directory();

	void						Open(IN const char* Name);
	void						Close();

	bool						IsOpened();

	size_t						FilesNum();
	size_t						DirectoriesNum();

	char*						RootDirectory();

	std::vector<std::string>	Files(IN bool Relative = false);
	std::vector<std::string>	Directories(IN bool Relative = false);


	char*						FindFile(IN const char* Name);
	char*						FindDirectory(IN const char* Name);
private:
	struct DirectoryData;
	DirectoryData*	mData;
};