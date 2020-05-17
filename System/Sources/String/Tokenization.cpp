#include "Tokenization.h"

std::vector<std::string> Tokenizer/*<>*/::mTokens = std::vector<std::string>();
char Tokenizer::mDelimiter = 0;

//template<char Delimiter>
Tokenizer/*<Delimiter>*/::Tokenizer()
{
}

//template<char Delimiter>
Tokenizer/*<Delimiter>*/::~Tokenizer()
{
	mTokens.clear();
}

//template<char Delimiter>
std::string Tokenizer/*<Delimiter>*/::GetToken(IN int TokenNumber)
{
	if(mTokens.size() == 0 || mTokens[TokenNumber].length() == 0)
		return "";

	return mTokens[TokenNumber];
}

//template<char Delimiter>
std::string Tokenizer/*<Delimiter>*/::GetTokens(IN int From, IN int To, IN bool AddDelimiter)
{
	if(mTokens.size() == 0 || mTokens[From].length() ==  0)
		return "";

	std::string StrBuffer;

	for(int i = From; i < To; i++)
	{
		StrBuffer.append(mTokens[i]);

		if(AddDelimiter == true)
			if(i != To - 1)
				StrBuffer.append(1, mDelimiter);
	}

	return StrBuffer;
}