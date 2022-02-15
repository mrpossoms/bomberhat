#pragma once

#include <ode/ode.h>
#include <string>
#include <unordered_map>


struct simulation
{
	dWorldID world;

	std::unordered_map<std::string, dSpaceID> space;
	std::unordered_map<std::string, dGeomID> geometry;
	std::unordered_map<std::string, dBodyID> body;
	std::unordered_map<std::string, dJointID> joint;

	dJointGroupID contact_group;

	virtual void setup();

	void step(dReal step_size=0.005);

protected:
	void init();

private:
	dReal t;
};