#include <cassert>
#include <thread>
#include <random>
#include <iostream>
#include <chrono>

#define XMTYPE float

#include "core.hpp"
#include "estimators/kalman-filter.hpp"

using namespace std::chrono_literals;

constexpr size_t X = 6;
constexpr size_t Z = 6;
constexpr size_t U = 3;

vec<3> truth_ypr = {};
vec<3> truth_ypr_dot = {};

std::default_random_engine rng;

vec<3> rand_vec(const vec<3>& std_dev)
{
	return {
		std::normal_distribution<float>{0,std_dev[0]}(rng),
		std::normal_distribution<float>{0,std_dev[1]}(rng),
		std::normal_distribution<float>{0,std_dev[2]}(rng)
	};
}

template <size_t X_SIZE, size_t U_SIZE>
struct DummyController
{
	void target(const vec<X_SIZE>& target_x)
	{
		goal_x = target_x;
	}

	const vec<U_SIZE>& step(const mat<X_SIZE, 1> x, float dt, bh::Context& ctx)
	{
		std::cout << x.template slice<3,1>().to_string() << std::endl;
		std::cout << "true ypr: " << truth_ypr.to_string() << std::endl;
		return last_u;
	}

	const vec<U_SIZE>& last_control()
	{
		return last_u;
	}

private:
	vec<U_SIZE> last_u;
	vec<X_SIZE> goal_x;
};

struct Gyro : public bh::interface::Sensor<Z>
{
	Gyro(bh::estimators::KalmanFilter<X,Z,U>& est) : estimator(est)
	{
		std::cout << "gyro constructed" << std::endl;

		poller = std::thread([&]()
		{
			while(true)
			{
				std::cout << "tick" << std::endl;
				std::this_thread::sleep_for(100ms);
				poll();
			}
		});
	}

	static Gyro* make(bh::estimators::KalmanFilter<X,Z,U>& est)
	{
		return new Gyro(est);
	}

	void poll() override
	{
		auto gyro_noisy = truth_ypr_dot + rand_vec({0.1f,0.1f,0.1f});
		estimator.observe(, {0,0,0,1,1,1});
	}

	bool is_polling() const override { return false; }

private:
	std::thread poller;
	bh::estimators::KalmanFilter<X,Z,U>& estimator;
};

struct TestFilter : public bh::estimators::KalmanFilter<X,Z,U>
{
	const mat<Z, X, float>& state_to_measurement() override
	{
		// state: rpy, rpy dot
		// measurement: acc, rpy dot
		// rpy -> acc
		// 
		X2Z = {
			{ 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 0, 0, 1 },
		};
		return X2Z;
	}

	const mat<Z, Z, float>& measurement_noise_covariance() override
	{
		float s = 0.1f;
		Q = mat<Z, Z>::diagonal(s);
		return Q;
	}

	const mat<X, X, float>& state_transition() override
	{
		float t = 0.1f;
		STM = {
			{ 1, 0, 0, t, 0, 0 },
			{ 0, 1, 0, 0, t, 0 },
			{ 0, 0, 1, 0, 0, t },
			{ 0, 0, 0, 1, 0, 0 },
			{ 0, 0, 0, 0, 1, 0 },
			{ 0, 0, 0, 0, 0, 1 },
		};
		return STM;
	}

	const mat<X, X, float>& process_noise_covariance() override
	{
		P = {
			{ 0.1, 0, 0, 0, 0, 0 },
			{ 0, 0.1, 0, 0, 0, 0 },
			{ 0, 0, 0.1, 0, 0, 0 },
			{ 0, 0, 0, 0.1, 0, 0 },
			{ 0, 0, 0, 0, 0.1, 0 },
			{ 0, 0, 0, 0, 0, 0.1 },
		};
		return P;
	}

	const mat<X, U, float>& control_to_state() override
	{
		U2X = {
			{ 0, 0, 0 },
			{ 0, 0, 0 },
			{ 0, 0, 0 },
			{ 1, 0, 0 },
			{ 0, 1, 0 },
			{ 0, 0, 1 },
		};
		return U2X;
	}

private:
	mat<Z, X, float> X2Z;
	mat<X, U, float> U2X;
	mat<X, X, float> P, STM;
	mat<Z, Z, float> Q;
};

int main()
{
	std::vector<bh::interface::Bus> busses;
	bh::Context ctx = {busses};
	bh::Core<X, Z, U, TestFilter, DummyController<X,U>, Gyro> core;

	for(unsigned i=1000;i--;)
	{
		core.step(ctx);
		std::this_thread::sleep_for(10ms);
	}

	return 0;
}
