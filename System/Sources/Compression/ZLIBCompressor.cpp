#include "ZLIBCompressor.h"

#include <zlib.h>
#include <cstring>

size_t ZLIBCompressor::Compress(OUT char* Dest, IN size_t DestLen, IN const char* Src, IN size_t SrcLen, int CompressionLevel)
{
	z_stream ZStr;
	memset(&ZStr, 0, sizeof(z_stream));
	
	deflateInit(&ZStr, CompressionLevel);

	ZStr.next_in = (Bytef*)Src;
	ZStr.avail_in = (unsigned int)SrcLen;
	ZStr.next_out = (Bytef*)Dest;
	ZStr.avail_out = (unsigned int)DestLen;

	deflate(&ZStr, Z_FINISH);

	int TotalOut = ZStr.total_out;

	deflateEnd(&ZStr);

	return TotalOut;
}

size_t ZLIBCompressor::Decompress(OUT char* Dest, IN size_t DestLen, IN const char* Src, IN size_t SrcLen)
{
	z_stream ZStr;
	memset(&ZStr, 0, sizeof(z_stream));

	inflateInit(&ZStr);

	ZStr.next_in = (Bytef*)Src;
	ZStr.avail_in = (unsigned int)SrcLen;
	ZStr.next_out = (Bytef*)Dest;
	ZStr.avail_out = (unsigned int)DestLen;

	inflate(&ZStr, Z_FINISH);

	int TotalOut = ZStr.total_out;

	inflateEnd(&ZStr);

	return TotalOut;
}