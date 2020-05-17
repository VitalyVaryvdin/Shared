#include "Utils.h"

#include <cstdio>
#include <cstring>
#include <cstdarg>

char* Strdup(IN const char* Str)
{
	if(Str == 0)
		return 0;

	char* Dest = new char[strlen(Str) + 1]; // adding 1 to the length of the string to put null-terminating character at the end

	strcpy(Dest, Str);

	return Dest;
}

char* Strndup(const char* Str, size_t MaxCount)
{
	if(!Str || MaxCount <= 0)
		return 0;

	if(strlen(Str) < MaxCount)
		return Strdup(Str);

	char* Dest = new char[MaxCount + 1]; // adding 1 to the length of the string to put null-terminating character at the end

	memcpy(Dest, Str, MaxCount);

	Dest[MaxCount] = 0;

	return Dest;
}

char* GetToken(IN const char* Path, IN int Token)
{
	size_t	Length			= strlen(Path);
	int		Count			= 0;
	int		CountToken		= 0;
	int*	Tokens			= new int[128];
	memset(Tokens, 0, sizeof(int) * 128);

	const char* Ptr;
	Ptr = Path;

	for(;;)
	{
		switch(*Ptr)
		{
		case '\0':
		case '/':
		case '\\':
			CountToken++;
			Tokens[CountToken] = Count + 1;

			break;
		default:
			break;
		}

		if(*Ptr == '\0')
			break;

		Ptr++;
		Count++;
	}

	char* Buffer = new char[Length];
	memset(Buffer, 0, Length);

	if(Token <= CountToken)
	{
		// -1 is to delete slash out of path
		// as Tokens[x] contains something like this: "path\"
		int TokenLength = Tokens[Token] - Tokens[Token - 1] - 1;

		// n = position of first character that belong to selected token
		// i is used only to fill the buffer
		for(size_t n = Tokens[Token - 1], i = 0; n < Tokens[Token], i < TokenLength; n++, i++)
		{
			Buffer[i] = Path[n];
		}

		delete Tokens;

		Buffer[Length] = '\0';

		return Buffer;
	}
	else
		return 0;
}

int GetTokensCount(IN const char* Path)
{
	int Result = 0;

	for(;;)
	{
		switch(*Path)
		{
		case '\0':
		case '/':
		case '\\':
			Result++;
			break;
		default:
			break;
		}

		// if we write something like while(*Path != '\0'), 
		// we would not be able to count last token as loop will break immediately upon reaching null
		if(*Path == '\0')
			break;

		Path++;
	}

	return Result;
}

char* GetPath(const char* FileName)
{
	int TokensCount = GetTokensCount(FileName);
	std::string Temp;

	// we don't add 1 to tokenscount as we don't want the filename to be append
	for(size_t i = 1; i < TokensCount; i++)
	{
		Temp.append(GetToken(FileName, i));
		Temp.append("\\");
	}

	return Strdup(Temp.c_str());
}

char* GetFileName(const char* Path)
{
	int TokensCount = GetTokensCount(Path);

	return GetToken(Path, TokensCount);
}

char* GetExtension(const char* Path)
{
	std::string Temp;
	int TokensCount = GetTokensCount(Path);

	Temp = GetToken(Path, TokensCount); // get last token from path

	int DotPos = 0;

	if((DotPos = Temp.find(".")) == std::string::npos) // if we have dot in our token - we got an extension
		return Strdup(Temp.c_str());

	// FIXME: for fuck sake why the hell is it here? i've already forgot (rofl)
	int BufferSize = Temp.size() - DotPos;

	char* Buffer = new char[BufferSize];
	Temp.copy(Buffer, BufferSize, DotPos);
	Buffer[BufferSize] = '\0';

	return Buffer;
}

void ConvertSlash(INOUT char* String)
{
	int Count = 0;

	char* Ptr = Strdup(String);
	char* Start = Ptr;

	while(*Ptr != '\0')
	{
		switch(*Ptr)
		{
		case '/':
			String[Count] = '\\';
			break;
		case '\\':
			String[Count] = '/';
			break;
		default:
			break;
		}

		Ptr++;
		Count++;
	}

	delete [] Start;
	Start	= 0;
	Ptr		= 0;
}

std::string MakePathRelative(IN const char* RootPath, IN const char* FileName)
{
	int RootTokCount = GetTokensCount(RootPath);
	int TokCount = GetTokensCount(FileName);

	std::string Buffer;

	for(int n = RootTokCount; n < TokCount + 1; n++)
	{
		Buffer.append(GetToken(RootPath, n));

		if(n != TokCount)
			Buffer.append("\\");
	}

	return Buffer;
}

std::string Format(const char* String, ...)
{
	size_t Size = 512;

	char* Buffer = new char[Size];

	va_list VaList;
	va_start(VaList, String);

	size_t NSize = vsnprintf(Buffer, Size, String, VaList);

	if(Size <= NSize)
	{
		delete[] Buffer;

		Buffer = new char[NSize + 1];

		vsnprintf(Buffer, Size, String, VaList);
	}

	std::string Ret(Buffer);

	va_end(VaList);

	delete[] Buffer;

	return Ret;
}