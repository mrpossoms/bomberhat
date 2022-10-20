#pragma once
#include "error.hpp"

namespace bh
{

namespace interface
{

struct Bus
{
	virtual ~Bus()                                        = 0;
	virtual Error write(const void* buffer, size_t bytes) = 0;
	virtual Error read(void* buffer, size_t bytes)        = 0;
	virtual Bus&  operator[](int address)                 = 0;
};

} // namespace interface

} // namespace bh