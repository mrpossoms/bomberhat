
#include "scenario/reaction-wheels.hpp"

#define WHEEL_COUNT 1
#define CUBE_FRAME_MASS 0.25

static const dVector3 xunit = {1, 0, 0}, yunit = {0, 1, 0}, zunit = {0, 0, 1};


void reaction_wheels::setup() override
{
    dMass mass;

    auto& root_space = space["root"];
    body["cube"] = dBodyCreate(world);
    geometry["cube"] = dCreateBox(root_space, 0.1, 0.1, 0.1);
    dGeomSetBody(geometry["cube"], body["cube"]);
    dMassSetBox(&mass, 0.5, 0.1, 0.1, 0.1);
    dBodySetMass(body["cube"], &mass);
    dBodySetPosition(body["cube"], 0, 0, 1);

    // create each wheel
    for (unsigned i = 0; i < WHEEL_COUNT; i++)
    {
        auto wheel_name = "wheel" + std::to_string(i);
        body[wheel_name] = dBodyCreate(world);
        geometry[wheel_name] = dCreateCylinder(root_space, 0.04, 0.02);
        dGeomSetBody(geometry[wheel_name], body[wheel_name]);
        dMassSetCylinder(&mass, 7.85, 1, 0.04, 0.02);
        dBodySetMass(body[wheel_name], &mass);
        dBodySetPosition(body[wheel_name], -0.05, 0, 1);

        dQuaternion q;
        dQFromAxisAndAngle (q, 0, 1, 0, M_PI*0.5);
        dBodySetQuaternion (body[wheel_name], q);

        // create joint and attach to cube
        joint[wheel_name] = dJointCreateHinge2(world,0);
        dJointAttach(joint[wheel_name], body[wheel_name], body["cube"]);
        const dReal* a = dBodyGetPosition(body["cube"]);
        dJointSetHinge2Anchor(joint[wheel_name], a[0], a[1], a[2]);
        dJointSetHinge2Axes(joint[wheel_name], zunit, xunit);
        dJointSetHinge2Param(joint[wheel_name],dParamLoStop,0);
        dJointSetHinge2Param(joint[wheel_name],dParamHiStop,0);
    }
}

void reaction_wheels::command(int cmd) override
{
    switch (cmd) {
    case 'j': case 'J':
      dJointAddHinge2Torques(joint["wheel0"], 0, 0.01);
      break;
    case 'l': case 'L':
      dJointAddHinge2Torques(joint["wheel0"], 0, -0.01);
      break;
    }
}

std::vector<dReal> reaction_wheels::observables() override
{
    return std::vector<dReal>{};
}

void reaction_wheels::apply_action(const std::vector<dReal>& a) override
{
    // TODO:
}

void reaction_wheels::user_step(dReal step_size=0.005) override
{
    // TODO:
}
