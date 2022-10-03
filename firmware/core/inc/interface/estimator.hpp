#pragma once
#include "xmath.h"

using namespace xmath;

namespace bh
{

namespace interface 
{

template <size_t X_SIZE, size_t U_SIZE, typename S=float>
struct Estimator
{
	virtual Estimator(bh::Context& ctx) = 0;

	template <size_t Z_S, size_t N>
	virtual void observe(const vec<N>& z) = 0;

	virtual vec<X_SIZE>& predict(S dt, const vec<U_SIZE,S>& u={}) = 0;

	virtual vec<X_SIZE>& state() const = 0;

	virtual uint32_t timestamp() const = 0;
};	

} // namespace interface

} // namespace bh