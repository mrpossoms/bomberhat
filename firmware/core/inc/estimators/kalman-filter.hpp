#pragma once


#include "core.hpp"
using namespace xmath


template <size_t STATE_SIZE, size_t OBSERVATION_SIZE, size_t CONTROL_SIZE, typename S=float>
struct KalmanFilter : public filter::kalman<OBSERVATION_SIZE, STATE_SIZE, S>
{
	virtual const mat<Z_SIZE, X_SIZE, S>& state_to_measurement() = 0;

	virtual const mat<Z_SIZE, Z_SIZE, S>& measurement_noise_covariance() = 0;

	virtual const mat<X_SIZE, X_SIZE, S>& state_transition() = 0;

	virtual const mat<X_SIZE, X_SIZE, S>& process_noise_covariance() = 0;

	virtual const mat<X_SIZE, U_SIZE, S>& control_to_state() = 0;

	void observe(const vec<OBSERVATION_SIZE>& z, const vec<OBSERVATION_SIZE>& z_mask)
	{
		auto mask_diag = mat<Z_SIZE, Z_SIZE>::diagonal(z_mask);

		measurement_update(
			state_transition(),
			mask_diag * state_to_measurement(),
			mask_diag * measurement_noise_covariance()
		);	
	}

	mat<X, 1, S>& predict(const vec<U_SIZE,S>& u={})
	{
		time_update(
			state_transition(),
			control_to_state(),
			mat<1, U_SIZE, S>{ u }.transpose(), // TODO: too many copies
			process_noise_covariance()
		);

		return estimated.state;
	}

	uint32_t timestamp() const
	{
		return 0;
	}
};