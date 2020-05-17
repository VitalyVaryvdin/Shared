#include "Options.h"

#include "Tokenization.h"

OptionsMap OptionsParser::Parse(IN OptionsList OptionsDescription, IN char** Options, IN int OptionsCount)
{	
	OptionsMap OM;

	if(OptionsCount == 0)
		return OM;

	std::map<std::string, std::vector<std::string> > KeyPairs;

	for(OptionsList::iterator it = OptionsDescription.begin(); it != OptionsDescription.end(); ++it)
	{
		Tokenizer::Tokenize<'|'>(it->Name.c_str());

		std::string Full = "--" + Tokenizer::GetToken(0);
		std::string Short = "--" + Tokenizer::GetToken(1);

		KeyPairs[it->Name].push_back(Full);
		KeyPairs[it->Name].push_back(Short);
	}

	for(size_t i = 0; i < OptionsCount; i++)
	{
		for(OptionsList::iterator it = OptionsDescription.begin(); it != OptionsDescription.end(); ++it)
		{
			if(	(strcmp(Options[i], KeyPairs[it->Name][0].c_str()) == 0)  // --arg
				||
				(strcmp(Options[i], KeyPairs[it->Name][1].c_str()) == 0)) // --a
			{
				OM[it->Name] = Value(Options[i + 1]);
			}
		}
	}

	return OM;
}

bool OptionsMap::Check(IN const char* Name)
{
	for(OptionsMap::iterator it = this->begin(); it != this->end(); ++it)
	{
		Tokenizer::Tokenize<'|'>(Name);

		std::string FullName	= "--" + Tokenizer::GetToken(0);
		std::string ShortName	= "--" + Tokenizer::GetToken(1);

		Tokenizer::Tokenize<'|'>(it->first.c_str());

		std::string FullOption	= "--" + Tokenizer::GetToken(0);
		std::string ShortOption	= "--" + Tokenizer::GetToken(1);

		if( (strcmp(FullOption.c_str(), FullName.c_str()) == 0)
			|| 
			(strcmp(ShortOption.c_str(), ShortName.c_str()) == 0))
		{
			return true;
		}
	}

	return false;
}