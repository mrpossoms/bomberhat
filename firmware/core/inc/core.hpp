#pragma once
#include <ostream>

namespace bh
{

template<typename EST, typename CON, typename... SENSORS>
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
