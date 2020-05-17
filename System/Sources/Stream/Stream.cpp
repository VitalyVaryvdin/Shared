#include "Stream.h"

#include "Buffer.h"
#include "Utils.h"

#include <cstdio>
#include <cstring>

void Stream::WriteString(IN const char* Str, IN bool NullTerminated)
{
	if(NullTerminated)
	{
		u32 Length = strlen(Str) + 1;

		Write((void*)Str, Length);
	}
	else
	{
		u32 Length = strlen(Str);

		WriteU32(Length); 

		Write((void*)Str, Length);
	}
}

char* Stream::ReadString(IN bool NullTerminated)
{
	if(NullTerminated)
	{
		bool		NT		= false;
		char		Tmp		= 0;
		int			Count	= 0;
		// 512 bytes is kinda enought for largest possible string in the binary
		char		Buffer[MaxStringLength];

		while(NT == false)
		{
			// read one byte from stream
			Read(&Tmp, sizeof(Tmp));
			// if byte is not null-terminating character
			if(Tmp != '\0')
			{
				// add character to the buffer
				Buffer[Count] = Tmp;
			}
			else // we've reached null-terminating character - end of string
			{
				NT = true;
				Buffer[Count] = '\0';
			}

			Count++;
		}

		return Strdup(Buffer);
	}

	u32 Length = ReadU32();

	char* Buffer = new char[Length];
	memset(Buffer, 0, sizeof(*Buffer) * Length);

	Read(Buffer, Length);

	Buffer[Length - 1] = '\0';

	return Buffer;	
}

char* Stream::ReadString(IN size_t Size)
{
	char* Buffer = new char[Size];
	memset(Buffer, 0, sizeof(*Buffer) * Size);

	Read(Buffer, Size);

	Buffer[Size - 1] = '\0';

	return Buffer;
}

void Stream::WriteRaw(IN void* Buffer, IN size_t Size)
{
	Write(Buffer, Size);
}

char* Stream::ReadRaw(IN size_t Size)
{
	char		Tmp		= 0;
	int			Count	= 0;

	char*		Buffer	= new char[Size];
	memset(Buffer, 0, sizeof(*Buffer) * Size);

	while(Count != Size)
	{
		Read(&Tmp, sizeof(Tmp));

		Buffer[Count] = Tmp;
	 
		Count++;
	}
	 
	return Buffer;
}

void Stream::WriteToBuffer(OUT Buffer* Buf)
{
	Buf->WriteRaw(ReadRaw(Size()), Size());
}

void Stream::WriteFromBuffer(IN Buffer* Buf)
{
	//char* TempData = new char[Buf->Size()];
	char* TempData = Buf->ReadRaw(Buf->Size());

	WriteRaw(TempData, Buf->Size());

	delete TempData;

	//WriteRaw(Buf->ReadRaw(Buf->Size()), Buf->Size());
}

IMPLEMENT_WRITE			(s8,		WriteS8)
IMPLEMENT_READ			(s8,		ReadS8)
IMPLEMENT_WRITE_ARRAY	(s8,		WriteS8)
IMPLEMENT_READ_ARRAY	(s8,		ReadS8)

IMPLEMENT_WRITE			(u8,		WriteU8)
IMPLEMENT_READ			(u8,		ReadU8)
IMPLEMENT_WRITE_ARRAY	(u8,		WriteU8)
IMPLEMENT_READ_ARRAY	(u8,		ReadU8)
	
IMPLEMENT_WRITE			(s16,		WriteS16)
IMPLEMENT_READ			(s16,		ReadS16)
IMPLEMENT_WRITE_ARRAY	(s16,		WriteS16)
IMPLEMENT_READ_ARRAY	(s16,		ReadS16)

IMPLEMENT_WRITE			(u16,		WriteU16)
IMPLEMENT_READ			(u16,		ReadU16)
IMPLEMENT_WRITE_ARRAY	(u16,		WriteU16)
IMPLEMENT_READ_ARRAY	(u16,		ReadU16)

IMPLEMENT_WRITE			(s32,		WriteS32)
IMPLEMENT_READ			(s32,		ReadS32)
IMPLEMENT_WRITE_ARRAY	(s32,		WriteS32)
IMPLEMENT_READ_ARRAY	(s32,		ReadS32)

IMPLEMENT_WRITE			(u32,		WriteU32)
IMPLEMENT_READ			(u32,		ReadU32)
IMPLEMENT_WRITE_ARRAY	(u32,		WriteU32)
IMPLEMENT_READ_ARRAY	(u32,		ReadU32)

IMPLEMENT_WRITE			(s64,		WriteS64)
IMPLEMENT_READ			(s64,		ReadS64)
IMPLEMENT_WRITE_ARRAY	(s64,		WriteS64)
IMPLEMENT_READ_ARRAY	(s64,		ReadS64)

IMPLEMENT_WRITE			(u64,		WriteU64)
IMPLEMENT_READ			(u64,		ReadU64)
IMPLEMENT_WRITE_ARRAY	(u64,		WriteU64)
IMPLEMENT_READ_ARRAY	(u64,		ReadU64)

IMPLEMENT_WRITE			(f32,		WriteF32)
IMPLEMENT_READ			(f32,		ReadF32)
IMPLEMENT_WRITE_ARRAY	(f32,		WriteF32)
IMPLEMENT_READ_ARRAY	(f32,		ReadF32)

IMPLEMENT_WRITE			(f64,		WriteF64)
IMPLEMENT_READ			(f64,		ReadF64)
IMPLEMENT_WRITE_ARRAY	(f64,		WriteF64)
IMPLEMENT_READ_ARRAY	(f64,		ReadF64)