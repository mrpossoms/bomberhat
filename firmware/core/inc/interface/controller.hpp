#pragma once
#include <xmath.h>

using namespace xmath;

namespace bh
{

namespace interface 
{

template <size_t X_SIZE, size_t U_SIZE, typename S=float>
struct Controller
{

	virtual Controller(bh::Context& ctx) = 0;

	virtual vec<U_SIZE>& step(vec<X_SIZE>& x, const S dt) = 0;

};	

} // namespace interface

} // namespace bh