#pragma once

#include "Config.h"

#include "Types.h"
#include "Defines.h"

namespace Endianness
{
	enum
	{
		Big,
		Little
	};

	int Check()
	{
		short Word = 0x0001;
		char* Byte = (char*)&Word;

		return(Byte[0] ? Little : Big);
	}

	std::string ToString(IN int Type)
	{
		switch(Type)
		{
		case Big:
			return "Big Endian";
			break;
		case Little:
			return "Little Endian";
			break;
		default:
			return "Unknown Endian";
			break;
		}
	}

	u16 Swap(IN u16& Value)
	{
		u16 Return = Value;
		Return	=	(Return >> 8) |
					(Return << 8);

		return Return;
	}

	u32 Swap(IN u32& Value)
	{
		u32 Return = Value;
		Return =	(Return		>>	24)					|
					((Return	<<	8)	& 0x00FF0000)	|
					((Return	>>	8)	& 0x0000FF00)	|
					(Return		<<	24);

		return Return;
	}

	u64 Swap(IN u64& Value)
	{
		u64 Return = Value;
		Return =	(Return		>>	56)							|
					((Return	<<	40)	& 0x00FF000000000000)	|
					((Return	<<	24)	& 0x0000FF0000000000)	|
					((Return	<<	8)	& 0x000000FF00000000)	|
					((Return	>>	8)	& 0x00000000FF000000)	|
					((Return	>>	24)	& 0x0000000000FF0000)	|
					((Return	>>	40)	& 0x000000000000FF00)	|
					(Return		<<	56);

		return Return;
	}

	s16 Swap(IN s16& Value)
	{
		s16 Return = Value;
		Return =	(Return >> 8) |
					(Return << 8);

		return Return;
	}

	s32 Swap(IN s32& Value)
	{
		s32 Return = Value;
		Return =	(Return		>>	24)					|
					((Return	<<	8)	& 0x00FF0000)	|
					((Return	>>	8)	& 0x0000FF00)	|
					(Return		<<	24);

		return Return;
	}

	s64 Swap(IN s64& Value)
	{
		s64 Return = Value;
		Return =	(Return		>>	56)							|
					((Return	<<	40)	& 0x00FF000000000000)	|
					((Return	<<	24)	& 0x0000FF0000000000)	|
					((Return	<<	8)	& 0x000000FF00000000)	|
					((Return	>>	8)	& 0x00000000FF000000)	|
					((Return	>>	24)	& 0x0000000000FF0000)	|
					((Return	>>	40)	& 0x000000000000FF00)	|
					(Return		<<	56);

		return Return;
	}
}