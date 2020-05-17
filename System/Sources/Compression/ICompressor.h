#pragma once

#include "Config.h"

#include "Types.h"
#include "Defines.h"

class ICompressor
{
public:
	virtual size_t	Compress(OUT char* Dest, IN size_t DestLen, IN const char* Src, IN size_t SrcLen, IN int CompressionLevel = 9) = 0;
	virtual size_t	Decompress(OUT char* Dest, IN size_t DestLen, IN const char* Src, IN size_t SrcLen) = 0;
};