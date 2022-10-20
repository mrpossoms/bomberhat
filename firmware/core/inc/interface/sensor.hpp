#pragma once
#include "error.hpp"
#include "estimator.hpp"

namespace bh
{

namespace interface
{

template <size_t Z_SIZE>
struct Sensor
{
	// template<bh::interface::Observer<Z_SIZE> Obs>
	// virtual Sensor* make(Obs& estimator)

	virtual void poll() = 0;

	virtual bool is_polling() const = 0;
};

template <typename SEN, size_t Z_SIZE>
concept ISensor = requires(SEN s)
{
	{
		SEN::make()
		} -> std::same_as<SEN*>;

	{
		s.poll()
		} -> std::same_as<bh::Error>;

	{
		s.event_driven()
		} -> std::same_as<bool>;
};

} // namespace interface

} // namespace bh