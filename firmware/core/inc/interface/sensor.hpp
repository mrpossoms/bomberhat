#pragma once


namespace bh
{

namespace interface
{

struct Sensor
{
	virtual Sensor(Estimator& est, bh::Context& ctx) = 0;

	virtual poll() = 0;

	virtual bool is_polling() const = 0;
};

} // namespace interface

} // namespace bh