#pragma once
#include <interface/bus.hpp>

namespace bh
{

struct Context
{
	std::vector<bh::interface::Bus>& busses;
};

} // namespace bh