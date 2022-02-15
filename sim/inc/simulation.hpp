#include <ode/ode.h>


struct simulation
{
	std::unordered_map<std::string, dSpaceID> space;
	std::unordered_map<std::string, dGeomID> geometry;
	std::unordered_map<std::string, dBodyID> body;
	std::unordered_map<std::string, dJointID> joint;

	dJointGroupID contact_group;

	virtual void setup() = 0;

	void sim_loop(int pause);

private:
	dReal t;
};