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
		add_sensors<SENSORS...>();
	}

	// static std::shared_ptr<Core<X_SIZE, Z_SIZE, U_SIZE

	void tick(bh::Context& ctx)
	{
		// for each polling device, poll. for any event driven sensors capture queued observations. agergate into measurement vector
		for (auto& s : sensors)
		{
			if (!s.is_polling()) { continue; }

			s.poll();
		}
		
		float dt = 0.01;//get_time(); // TODO

		auto& predicted_state = estimator.predict(dt, controller.last_control());
		controller.step(predicted_state);
	}

private:
	template<>
	void add_sensors() {}

	template<size_t idx, typename SEN, typename... SENS>
	void add_sensors()
	{
		sensors.push_back(SEN::make(estimator));
		add_sensors<SENS...>();
	}

	std::vector<std::shared_ptr<Sensor<Z_SIZE>>> sensors;
	EST estimator;
	CON controller;
};

} // namespace bh
