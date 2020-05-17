#pragma once

#include "Config.h"

#include "Types.h"
#include "Defines.h"

#include "Stream.h"

class Buffer : public Stream
{
public:
	Buffer(IN size_t Size = 8192);
	virtual ~Buffer();

	virtual void	Write(IN void* Data, IN size_t Size);
	virtual void	Read(OUT void* Data, IN size_t Size);

	virtual bool	IsOpened();

	virtual char*	Data();
	virtual size_t	Size();
	size_t			Capacity();

	virtual int		Tell();
	virtual void	Seek(IN int Offset, IN int SeekBase = Set);

	void			Allocate(IN size_t Capacity);
	void			Resize(IN size_t Capactiy);

	void			Clear();

	bool			IsEOF();
private:
	struct BufferData;
	BufferData* mData;
};
