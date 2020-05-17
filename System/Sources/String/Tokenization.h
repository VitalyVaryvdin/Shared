#pragma once

#include "Config.h"

#include "Types.h"
#include "Defines.h"

//template<char Delimiter = '\\'>
class Tokenizer
{
public:
	Tokenizer();
	~Tokenizer();

	template<char Delimiter>
	static unsigned Tokenize(IN const char* String);

	static std::string GetToken(IN int TokenNumber);
	static std::string GetTokens(IN int From, IN int To, IN bool AddDelimiter = true);
private:
	static std::vector<std::string> mTokens;
	static char						mDelimiter;
};

template<char Delimiter>
unsigned Tokenizer/*<Delimiter>*/::Tokenize(IN const char* String)
{
	if(Delimiter == 0)
		mDelimiter = '\\';
	else
		mDelimiter = Delimiter;

	std::string StrBuffer(String);

	unsigned PrevPos = 0;
	unsigned Pos = 0;
	unsigned NumberOfTokens = 0;

	mTokens.clear();

	Pos = StrBuffer.find_first_of(Delimiter, Pos);

	if(Pos == std::string::npos)
		return 0;

	while(Pos != std::string::npos)
	{
		std::string Token = StrBuffer.substr(PrevPos, Pos - PrevPos);

		if(Token != "")
		{
			mTokens.push_back(StrBuffer.substr(PrevPos, Pos - PrevPos));
			NumberOfTokens++;
		}

		Pos++;
		PrevPos = Pos;
		Pos = StrBuffer.find_first_of(Delimiter, Pos);
	}

	if(PrevPos < StrBuffer.length())
	{
		mTokens.push_back(StrBuffer.substr(PrevPos));
		NumberOfTokens++;
	}

	return NumberOfTokens;
}