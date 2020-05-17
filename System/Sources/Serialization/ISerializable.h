#pragma once

#include "Config.h"

#include "Types.h"
#include "Defines.h"

class Stream;

class ISerializable
{
public:
	virtual void Serialize(Stream* Destination) = 0;
	virtual void Deserialize(Stream* Source) = 0;
};