#pragma once

#include "Config.h"

#include "Types.h"
#include "Defines.h"

class Buffer;

class Stream
{
public:
	enum
	{
		Set,
		Begin,
		Current,
		End
	};

	virtual ~Stream() { }

	virtual void	Write(IN void* Data, IN size_t Size) = 0;
	virtual void	Read(OUT void* Data, IN size_t Size) = 0;

	virtual bool	IsOpened() = 0;

	virtual char*	Data() = 0;
	virtual size_t	Size() = 0;

	virtual	int		Tell() = 0;
	virtual void	Seek(int Offset, int SeekBase = Set) = 0;

	virtual bool	IsEOF() = 0;

	void			WriteString(IN const char* Str, IN bool NullTerminated = false);
	char*			ReadString(IN bool NullTerminated = false);
	char*			ReadString(IN size_t Size);

 	void			WriteRaw(IN void* Buffer, size_t Size);
 	char*			ReadRaw(IN size_t Size);

	void			WriteToBuffer(OUT Buffer* Buf);
	void			WriteFromBuffer(IN Buffer* Buf);

	DECLARE_WRITE		(s8,	WriteS8);
	DECLARE_READ		(s8,	ReadS8)
	DECLARE_WRITE_ARRAY (s8,	WriteS8);
	DECLARE_READ_ARRAY	(s8,	ReadS8);
	
	DECLARE_WRITE		(u8,	WriteU8);
	DECLARE_READ		(u8,	ReadU8)
	DECLARE_WRITE_ARRAY (u8,	WriteU8);
	DECLARE_READ_ARRAY	(u8,	ReadU8);
	
	DECLARE_WRITE		(s16,	WriteS16);
	DECLARE_READ		(s16,	ReadS16)
	DECLARE_WRITE_ARRAY (s16,	WriteS16);
	DECLARE_READ_ARRAY	(s16,	ReadS16);

	DECLARE_WRITE		(u16,	WriteU16);
	DECLARE_READ		(u16,	ReadU16)
	DECLARE_WRITE_ARRAY (u16,	WriteU16);
	DECLARE_READ_ARRAY	(u16,	ReadU16);

	DECLARE_WRITE		(s32,	WriteS32);
	DECLARE_READ		(s32,	ReadS32)
	DECLARE_WRITE_ARRAY (s32,	WriteS32);
	DECLARE_READ_ARRAY	(s32,	ReadS32);

	DECLARE_WRITE		(u32,	WriteU32);
	DECLARE_READ		(u32,	ReadU32)
	DECLARE_WRITE_ARRAY (u32,	WriteU32);
	DECLARE_READ_ARRAY	(u32,	ReadU32);

	DECLARE_WRITE		(s64,	WriteS64);
	DECLARE_READ		(s64,	ReadS64)
	DECLARE_WRITE_ARRAY (s64,	WriteS64);
	DECLARE_READ_ARRAY	(s64,	ReadS64);

	DECLARE_WRITE		(u64,	WriteU64);
	DECLARE_READ		(u64,	ReadU64)
	DECLARE_WRITE_ARRAY (u64,	WriteU64);
	DECLARE_READ_ARRAY	(u64,	ReadU64);

	DECLARE_WRITE		(f32,	WriteF32);
	DECLARE_READ		(f32,	ReadF32)
	DECLARE_WRITE_ARRAY (f32,	WriteF32);
	DECLARE_READ_ARRAY	(f32,	ReadF32);

	DECLARE_WRITE		(f64,	WriteF64);
	DECLARE_READ		(f64,	ReadF64)
	DECLARE_WRITE_ARRAY (f64,	WriteF64);
	DECLARE_READ_ARRAY	(f64,	ReadF64);
};
