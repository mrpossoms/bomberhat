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

	template <size_t Z_S, size_t N>
	void observe(const vec<N>& z) = 0;

	vec<X_SIZE>& predict(S dt) = 0;


};	

} // namespace interface

} // namespace bh