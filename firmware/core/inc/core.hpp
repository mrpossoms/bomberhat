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

template<Estimator EST, typename CON, typename... SENSORS>
struct Core
{
	Core()
	{
		add_sensors<SENSORS>();
	}

	void tick(bh::Context& ctx)
	{
		// for each polling device, poll. for any event driven sensors capture queued observations. agergate into measurement vector
		for (auto& s : sensors)
		{
			if (!s.is_polling()) { continue; }

			s.poll();
		}
		
		float dt = get_time(); // TODO

		auto& predicted_state = estimator.predict(dt, controller.last_control());
		controller.step(predicted_state);
	}

private:
	template<size_t idx>
	void add_sensors() {}

	template<typename SEN, typename... SENS>
	void add_sensors()
	{
		sensors.push_back(std::make_shared<SEN>({estimator}));
		add_sensors<SENS>();
	}

	std::vector<std::shared_ptr<bh::Sensor>> sensors;
	EST estimator;
	CON controller;
};

} // namespace bh
