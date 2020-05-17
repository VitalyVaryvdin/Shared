#pragma once

#include "Config.h"

#include "Types.h"
#include "Defines.h"

struct Option
{
	Option(std::string Name, std::string Description)
 	{
 		this->Name = Name;
 		this->Description = Description;
 	}

	std::string Name;
	std::string	Description;
};

class OptionsList : public std::vector<Option>
{
public:
	void AddOption(IN Option& OptionToAdd)
	{
		push_back(OptionToAdd);
	}
};

class Value
{
public:
	Value(IN char* OptionValue = 0)
	{
		this->OptionValue = OptionValue;
	}

	int AsInt()
	{
		return atoi(OptionValue);
	}

	char* AsString()
	{
		return OptionValue;
	}

	std::string AsSTLString()
	{
		return std::string(OptionValue);
	}
private:
	char* OptionValue;
};

class OptionsMap : public std::map<std::string, Value>
{
public:
	bool Check(IN const char* Name);
};

class OptionsParser
{
public:
	static OptionsMap Parse(IN OptionsList OptionsDescription, IN char** Options, IN int OptionsCount);
};