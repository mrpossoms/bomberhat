#pragma once
#include <ostream>
#include "context.hpp"
#include "error.hpp"
#include "interface/bus.hpp"
#include "interface/estimator.hpp"
#include "interface/controller.hpp"
#include "interface/sensor.hpp"

namespace bh
{

using namespace bh::interface;

template<size_t X_SIZE, size_t Z_SIZE, size_t U_SIZE, IEstimator<X_SIZE, Z_SIZE, U_SIZE> EST, IController<X_SIZE, U_SIZE> CON, typename... SENSORS>
struct Core
{
	Core()
	{
		add_sensors<0, SENSORS...>();
	}

	void step(bh::Context& ctx)
	{
		// for each polling device, poll. for any event driven sensors capture queued observations. agergate into measurement vector
		for (auto& s : sensors)
		{
			if (!s->is_polling()) { continue; }

			s->poll();
		}
		
		float dt = 0.01;//get_time(); // TODO

		auto& predicted_state = estimator.predict(controller.last_control());
		controller.step(predicted_state, dt, ctx);
	}

private:
	template<size_t idx>
	void add_sensors() {}

	template<size_t idx, typename SEN, typename... SENS>
	void add_sensors()
	{
		sensors.push_back(SEN::make(estimator));
		add_sensors<idx + 1, SENS...>();
	}

	std::vector<Sensor<Z_SIZE>*> sensors;
	EST estimator;
	CON controller;
};

} // namespace bh
