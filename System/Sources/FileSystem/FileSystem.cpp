#include "FileSystem.h"

#include "Utils.h"

#include "File.h"

#ifdef WINDOWS
#include <direct.h>
#endif

#ifdef LINUX
#include <unistd.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>

bool FileSystem::IsExists(IN const char* Path)
{
	/*	   struct stat fileinfo;

		   return !stat(filename, &fileinfo);
	 **/
	struct stat St;
	memset(&St, 0, sizeof(St));
	stat(Path, &St);

	if( (((St.st_mode) & S_IFMT) == S_IFDIR) ||
		(((St.st_mode) & S_IFMT) == S_IFREG) )
		return true;

	return false;
}

void FileSystem::CreateDirectoryTreeFromPath(IN const char* Path)
{
	int TokensCount = GetTokensCount(Path) + 1;
	std::string Temp;

	for(size_t i = 2; i <= TokensCount; i++)
	{
		for(size_t n = 1; n < i; n++)
		{
			Temp.append(GetToken(Path, n));
			Temp.append("\\");
		}

		if(!IsExists(Temp.c_str()))
			CreateDirectory(Temp.c_str());

		Temp.clear();
	}
}

void FileSystem::RemoveFile(IN const char* Name)
{
	remove(Name);
}

void FileSystem::RenameFile(IN const char* SrcName, IN const char* DstName)
{
	rename(SrcName, DstName);
}

void FileSystem::CopyFile(IN const char* SrcPath, IN const char* DstPath)
{
	if(!IsExists(SrcPath))
		return;

	File Input,
		 Output;

	Input.Open(SrcPath);
	Output.Open(DstPath);

	size_t Size = Input.Size();

	char* Buffer = new char[Size];
	memset(Buffer, 0, sizeof(*Buffer) * Size);

	Buffer = Input.ReadRaw(Size);

	Output.WriteRaw(Buffer, sizeof(*Buffer) * Size);

	delete Buffer;

	Input.Close();
	Output.Close();
}

void FileSystem::MoveFile(IN const char* SrcPath, IN const char* DstPath)
{
	if(!IsExists(SrcPath) || IsExists(DstPath))
		return;

	CopyFile(SrcPath, DstPath);

	RemoveFile(SrcPath);
}

std::string FileSystem::HomeDirectory()
{
	static char Buffer[1024];

#ifdef WINDOWS
	strcpy(Buffer, getenv("USERPROFILE"));
#else if LINUX
	strcpy(Buffer, getenv("HOME"));
#endif

	Buffer[sizeof(Buffer) - 1] = '\0';

	return Buffer;
}

std::string FileSystem::WorkingDirectory()
{
	static char Buffer[1024];
#ifdef WINDOWS
	getcwd(Buffer, 1024);
#else if LINUX
	strcpy(Buffer, getenv("PWD"));
#endif

	Buffer[sizeof(Buffer) - 1] = '\0';

	return Buffer;
}

void FileSystem::CreateDirectory(IN const char* Path)
{
#ifdef WINDOWS
	mkdir(Path);
#else if LINUX
    mkdir(Path, 0755);
#endif
}

void FileSystem::RemoveDirectory(IN const char* Path)
{
	rmdir(Path);
}