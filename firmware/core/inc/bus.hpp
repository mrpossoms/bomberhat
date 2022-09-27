#pragma once

namespace bh
{

struct Bus
{
	virtual Error write(const void* buffer, size_t bytes) = 0;
	virtual Error read(void* buffer, size_t bytes) = 0;
	virtual Bus& operator[](int address) = 0;
};

} // namespace bh