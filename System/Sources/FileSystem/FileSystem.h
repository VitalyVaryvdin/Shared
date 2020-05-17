#pragma once

#include "Config.h"

#include "Types.h"
#include "Defines.h"

class FileSystem
{
public:
	static bool		IsExists(IN const char* Path);

	static void		CreateDirectoryTreeFromPath(IN const char* Path);

	static void		RemoveFile(IN const char* Name);
	static void		RenameFile(IN const char* SrcName, IN const char* DstName);
	static void		CopyFile(IN const char* SrcPath, IN const char* DstPath);
	static void		MoveFile(IN const char* SrcPath, IN const char* DstPath);

	static std::string	HomeDirectory();
	static std::string	WorkingDirectory();

	static void		CreateDirectory(IN const char* Path);
	static void		RemoveDirectory(IN const char* Path);
};