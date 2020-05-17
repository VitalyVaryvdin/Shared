#include "Buffer.h"

#include <cstring>

struct Buffer::BufferData
{
	size_t	Size;
	size_t	Capacity;
	char*	Pointer;
	char*	Data;

	BufferData()
	{
		Size		= 0;
		Capacity	= 0;
		Pointer		= 0;
		Data		= 0;
	}

	~BufferData()
	{
		Size		= 0;
		Capacity	= 0;
		Pointer		= 0;
		delete [] Pointer;
		delete [] Data;
	}
};

Buffer::Buffer(IN size_t Size)
{
	mData = new BufferData();

	Allocate(Size);
}

Buffer::~Buffer()
{
	Clear();

	delete mData;
}

void Buffer::Write(IN void* Data, IN size_t Size)
{
	if(mData->Size)
	{
		size_t BytesToEnd = mData->Size - (mData->Pointer - mData->Data);

		if(Size > BytesToEnd)
			Resize(mData->Size + (int)(Size - BytesToEnd));
	}

	memcpy(mData->Pointer, Data, Size);
	delete Data;

	mData->Pointer += Size;
	mData->Size += Size;
}

void Buffer::Read(OUT void* Data, IN size_t Size)
{
	size_t BytesToEnd = mData->Size - (mData->Pointer - mData->Data);

	if(Size <= BytesToEnd)
	{
		memcpy(Data, mData->Pointer, Size);

		mData->Pointer += Size;
	}
	else
	{
		memcpy(Data, mData->Pointer, BytesToEnd);

		mData->Pointer += BytesToEnd;
	}
}

bool Buffer::IsOpened()
{
	if(mData->Size)
		return true;

	return false;
}

char* Buffer::Data()
{
	return mData->Data;
}

size_t Buffer::Size()
{
	return mData->Size;
}

size_t Buffer::Capacity()
{
	return mData->Capacity;
}

void Buffer::Allocate(IN size_t Capacity)
{
	if(Capacity == 0)
		return;

	mData->Capacity = Capacity;

	mData->Data = new char[Capacity];
	memset(mData->Data, 0, Capacity);
	mData->Pointer = mData->Data;
}

void Buffer::Resize(IN size_t Capacity)
{
	if(mData->Capacity == Capacity)
		return;

	if(mData->Size)
	{
		// copy current data to temporary buffer
		size_t TempSize = mData->Size;
		u8* Temp = new u8[TempSize];
		memset(Temp, 0, TempSize);
		memcpy(Temp, mData->Data, TempSize);

		// delete current data
		Clear();

		// allocate new buffer with specified size
		Allocate(Capacity);
		// move data from temporary buffer to newly allocated one
		memcpy(mData->Data, Temp, TempSize);
		mData->Size = TempSize;

		// delete temporary buffer
		delete [] Temp;

		// set the pointer to the end of written data
		mData->Pointer += TempSize;
	}
	else
		Allocate(Capacity);
}

void Buffer::Clear()
{
	// make sure we allocated memory before, if else - we have nothing to clear
	if(mData->Capacity == 0)
		return;

	mData->Size = 0;
	mData->Capacity = 0;

	delete [] mData->Data;

	mData->Data = 0;
	mData->Pointer = 0;
}

int Buffer::Tell()
{
	return (int)(mData->Pointer - mData->Data);
}

void Buffer::Seek(IN int Offset, IN int SeekBase)
{
	switch(SeekBase)
	{
	case Set:
		//mData->Pointer = mData->Data + Offset;
		mData->Pointer += Offset;
		break;
	case Begin:
		//mData->Pointer = (char*)(0 + Offset);
		mData->Pointer = mData->Data + Offset;
		break;
	case End:
		mData->Pointer = mData->Data + mData->Capacity - Offset;
		break;
	case Current:
		mData->Pointer += Offset;
		break;
	default:
		break;
	}
}

bool Buffer::IsEOF()
{
	return (mData->Pointer - mData->Data >= mData->Size);
}