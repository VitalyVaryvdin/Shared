#include "Directory.h"

#include "Utils.h"

#ifdef WINDOWS
#include <Windows.h>
#include "dirent\dirent.h"
#else
#include <dirent.h>
#endif

#include <cstring>
#include <map>

struct Directory::DirectoryData
{
	bool							IsOpened;
	
	std::string						RootPath;

	std::vector<std::string>		Files;
	std::vector<std::string>		Directories;

	std::vector<std::string>		FilesRelative;
	std::vector<std::string>		DirectoriesRelative;

	std::map<std::string, bool>		CachedFiles;
	std::map<std::string, bool>		CachedDirectories;

	DirectoryData()
	{
		IsOpened = false;
	}

	~DirectoryData()
	{
		IsOpened = false;
	}
};

char* AppendEntry(IN const char* RootPath, IN const char* DirEntry)
{
	size_t		NameSZ		= 0;
	size_t		DirEntrySZ	= 0;
	size_t		TmpSZ		= 0;
	char*		Tmp			= 0;
	bool		Slash		= false;

	NameSZ		= strlen(RootPath);
	DirEntrySZ	= strlen(DirEntry);
	// 2 characters to store separator and null terminating character
	TmpSZ		= NameSZ + DirEntrySZ + 2;

	Tmp = new char[TmpSZ];
	memset(Tmp, 0, TmpSZ);

	strcpy(Tmp, RootPath);

	int PTRLen	= strlen(Tmp);

	// if last character is slash
	if(Tmp[PTRLen - 1] == '\\' || Tmp[PTRLen - 1] == '/')
		Slash = true;

	if(Slash == false)
	{
   		Tmp[strlen(RootPath)] = '\\';
		NameSZ += 1; /* so we put file directory entry after slash
					  * as if we add slash manually, pointer is set exact to this slash
					  * if slash has been set before, pointer is set to the character after the slash
					  */
	}

	for(size_t i = NameSZ, n = 0; i < TmpSZ, n < DirEntrySZ; i++, n++)
	{
		Tmp[i] = DirEntry[n];
	}

	Tmp[TmpSZ - 1] = '\0';

	return Tmp;
}

Directory::Directory(IN const char* Path /* = "." */)
{
	mData = new DirectoryData();
}

Directory::~Directory()
{
	if(mData->IsOpened)
		Close();
}

void Directory::Open(IN const char* Name)
{
	DIR* Dir = opendir(Name);

	if(mData->RootPath.empty())
		mData->RootPath = Name;

	int RootTokCount = GetTokensCount(mData->RootPath.c_str());

	dirent* DirEntry;

	if(Dir == 0)
		return;

	std::string Buffer = "";

	mData->IsOpened = true;

	while((DirEntry = readdir(Dir)) != 0)
	{
		if((strcmp(DirEntry->d_name, ".") != 0)	 &&	 (strcmp(DirEntry->d_name, "..") != 0)) 
		{
			int TokCount = GetTokensCount(Name);

			/* adding 1 to make sure we put last token aswell. 
			 * little hack for loop, not for tokenization function itself */
			for(int n = RootTokCount; n < TokCount + 1; n++)
			{
				Buffer.append(GetToken(Name, n));
				Buffer.append("\\");
			}

			switch(DirEntry->d_type)
			{
			case DT_REG:
				mData->Files.push_back(AppendEntry(Name, DirEntry->d_name));
				mData->FilesRelative.push_back(AppendEntry(Buffer.c_str(), DirEntry->d_name));
				break;
			case DT_DIR:
				mData->Directories.push_back(AppendEntry(Name, DirEntry->d_name));
				mData->DirectoriesRelative.push_back(AppendEntry(Buffer.c_str(), DirEntry->d_name));
				Open(AppendEntry(Name, DirEntry->d_name));
				break;
			default:
				break;
			}

			Buffer.clear();
		}
	}

	closedir(Dir);
}

void Directory::Close()
{
	delete mData;
}

bool Directory::IsOpened()
{
	return mData->IsOpened;
}

size_t Directory::FilesNum()
{
	return mData->Files.size();
}
size_t Directory::DirectoriesNum()
{
	return mData->Directories.size();
}

char* Directory::RootDirectory()
{
	return GetToken(mData->RootPath.c_str(), GetTokensCount(mData->RootPath.c_str()));
}

std::vector<std::string> Directory::Files(IN bool Relative)
{
	if(Relative)
		return mData->FilesRelative;

	return mData->Files;
}

std::vector<std::string> Directory::Directories(IN bool Relative)
{
	if(Relative)
		return mData->DirectoriesRelative;

	return mData->Directories;
}

char* Directory::FindFile(IN const char* Name)
{
	if(mData->IsOpened)
	{
		if(mData->Files.size() != 0)
		{
			for(size_t i = 0; i < mData->Files.size(); i++)
			{
				if(mData->Files[i].find(Name) != std::string::npos)
				{ 
					if(!mData->CachedFiles.empty())
					{
						if(mData->CachedFiles[mData->Files[i]] == false)
						{ 
							mData->CachedFiles[mData->Files[i]] = true;
							return (char*)mData->Files[i].c_str();
						}
					}
					else
					{
						mData->CachedFiles[mData->Files[i]] = true;
						return (char*)mData->Files[i].c_str();
					}
				}
			}
		}
	}

	return 0;
}

char* Directory::FindDirectory(IN const char* Name)
{
	if(mData->IsOpened)
	{
		if(mData->Directories.size() != 0)
		{
			for(size_t i = 0; i < mData->Directories.size(); i++)
			{
				if(mData->Directories[i].find(Name) != std::string::npos)
				{ 
					if(!mData->CachedDirectories.empty())
					{
						if(mData->CachedDirectories[mData->Directories[i]] == false)
						{ 
							mData->CachedDirectories[mData->Directories[i]] = true;
							return (char*)mData->Directories[i].c_str();
						}
					}
					else
					{
						mData->CachedDirectories[mData->Directories[i]] = true;
						return (char*)mData->Directories[i].c_str();
					}
				}
			}
		}
	}

	return 0;
}