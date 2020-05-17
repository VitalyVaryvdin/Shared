#pragma once

// Some helpers

#define IN
#define OUT
#define INOUT

// Stream related macroses

// Declare

// Write

#define DECLARE_WRITE(Type, Name) \
void Name(Type Value);

#define DECLARE_WRITE_ARRAY(Type, Name) \
void Name(Type* Value, size_t Size);

// Read

#define DECLARE_READ(Type, Name) \
Type Name();

#define DECLARE_READ_ARRAY(Type, Name) \
Type* Name(size_t Size);

// Implement

// Write

#define IMPLEMENT_WRITE(Type, Name) \
void Stream::Name(Type Value) \
{ \
    Write(&Value, sizeof(Value)); \
} 

#define IMPLEMENT_WRITE_ARRAY(Type, Name) \
void Stream::Name(Type* Value, size_t Size) \
{ \
    Write(Value, (sizeof(Type) * Size)); \
}

// Read

#define IMPLEMENT_READ(Type, Name) \
Type Stream::Name() \
{ \
	Type Rtn = 0; \
	Read(&Rtn, sizeof(Type)); \
	return Rtn; \
}

#define IMPLEMENT_READ_ARRAY(Type, Name) \
Type* Stream::Name(size_t Size) \
{ \
    Type* Rtn = new Type[Size]; \
    memset(Rtn, 0, Size); \
    Read(Rtn, (sizeof(Type) * Size)); \
    return Rtn; \
}

// Constant numbers

static const int MaxStringLength = 4096;