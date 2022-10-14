#pragma once


#include "core.hpp"
using namespace xmath;

namespace bh
{

namespace estimators
{

template <size_t STATE_SIZE, size_t OBSERVATION_SIZE, size_t CONTROL_SIZE, typename S=float>
struct KalmanFilter : public filter::kalman<OBSERVATION_SIZE, STATE_SIZE, CONTROL_SIZE, S>
{
	virtual const mat<OBSERVATION_SIZE, STATE_SIZE, S>& state_to_measurement() = 0;

	virtual const mat<OBSERVATION_SIZE, OBSERVATION_SIZE, S>& measurement_noise_covariance() = 0;

	virtual const mat<STATE_SIZE, STATE_SIZE, S>& state_transition() = 0;

	virtual const mat<STATE_SIZE, STATE_SIZE, S>& process_noise_covariance() = 0;

	virtual const mat<STATE_SIZE, CONTROL_SIZE, S>& control_to_state() = 0;

	void observe(const vec<OBSERVATION_SIZE,S>& z, const vec<OBSERVATION_SIZE,S>& z_mask)
	{
		auto mask_diag = mat<OBSERVATION_SIZE, OBSERVATION_SIZE,S>::diagonal(z_mask);

		this->measurement_update(
			state_transition(),
			mask_diag * state_to_measurement(),
			z,
			mask_diag * measurement_noise_covariance()
		);	
	}

	mat<STATE_SIZE, 1, S>& predict(const vec<CONTROL_SIZE,S>& u={})
	{
		this->time_update(
			state_transition(),
			control_to_state(),
			mat<1, CONTROL_SIZE, S>{ u }.transpose(), // TODO: too many copies
			process_noise_covariance()
		);

		return this->estimated.state;
	}

	uint32_t timestamp() const
	{
		return 0;
	}
};

} // namespace estimators

} // namespace bh