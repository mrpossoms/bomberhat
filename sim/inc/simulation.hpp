#pragma once
#include <xmath.h>
#include <ode/ode.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace xmath;

struct simulation
{
	dWorldID world;

	std::unordered_map<std::string, dSpaceID> space;
	std::unordered_map<std::string, dGeomID> geometry;
	std::unordered_map<std::string, dBodyID> body;
	std::unordered_map<std::string, dJointID> joint;

	dJointGroupID contact_group;

	simulation();

	virtual std::vector<dReal> observables() = 0;

	virtual void apply_action(const std::vector<dReal>& a) = 0;

	virtual void setup() = 0;

	virtual void command(int c) {}

	virtual void user_step(dReal step_size=0.005) = 0;

	void step(dReal step_size=0.005);

private:
	dReal t;
};
