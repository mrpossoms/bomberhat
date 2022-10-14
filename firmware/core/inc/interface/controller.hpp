#pragma once
#include <xmath.h>

using namespace xmath;

namespace bh
{

namespace interface 
{

// template <size_t X_SIZE, size_t U_SIZE, typename S=float>
// struct Controller
// {
// 	virtual vec<U_SIZE>& step(vec<X_SIZE>& x, const S dt, bh::Context& ctx) = 0;

// 	virtual vec<U_SIZE>& last_control() const = 0;
// };	

template<typename CON, size_t X_SIZE, size_t U_SIZE, typename S=float>
concept IController = requires(CON c, const vec<X_SIZE, S>& x, const mat<X_SIZE, 1, S>& xm, bh::Context& ctx, const S dt)
{
	c.target(x);

	{ c.step(xm, dt, ctx) } -> std::template same_as<const vec<U_SIZE, S>&>;

	{ c.last_control() } -> std::template same_as<const vec<U_SIZE, S>&>;
};

} // namespace interface

} // namespace bh