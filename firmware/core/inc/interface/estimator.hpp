#pragma once
#include <concepts>

#include "xmath.h"

using namespace xmath;

namespace bh
{

namespace interface 
{

// template <size_t X_SIZE, size_t U_SIZE, typename S=float>
// struct Estimator
// {
// 	template <size_t Z_S, size_t N>
// 	virtual void observe(const vec<N>& z) = 0;

// 	virtual vec<X_SIZE>& predict(S dt, const vec<U_SIZE,S>& u={}) = 0;

// 	virtual vec<X_SIZE>& state() const = 0;

// 	virtual uint32_t timestamp() const = 0;
// };	

template<typename T, size_t X_SIZE, size_t Z_SIZE, size_t U_SIZE, typename S=float>
concept Estimator = requires(T est, const vec<U_SIZE, S>& u, const vec<Z_SIZE, S>& z, const vec<Z_SIZE, S>& z_mask)
{
	est.observe(z, z_mask);

	{ est.predict(u) } -> std::same_as<mat<X_SIZE, 1, S>>;

	{ est.timestamp() } -> std::convertible_to<uint32_t>;
};

} // namespace interface

} // namespace bh