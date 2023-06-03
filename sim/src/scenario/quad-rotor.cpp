
#include "scenario/quad-rotor.hpp"

#define WHEEL_COUNT 1
#define CUBE_FRAME_MASS 0.25

static const dVector3 xunit = {1, 0, 0}, yunit = {0, 1, 0}, zunit = {0, 0, 1};


void quad_rotor::setup()
{
    dMass mass;

    auto& root_space = space["root"];
    body["avionics"] = dBodyCreate(world);
    geometry["avionics"] = dCreateBox(root_space, 0.06, 0.06, 0.02);
    dGeomSetBody(geometry["avionics"], body["avionics"]);
    dMassSetBox(&mass, 1, 0.06, 0.06, 0.02);
    dBodySetMass(body["avionics"], &mass);
    dBodySetPosition(body["avionics"], 0, 0, 1);

    // create each rotor arm
    for (unsigned i = 0; i < 4; i++)
    {
        const auto dtheta = (M_PI / 2);
        auto t = dtheta * i;
        auto arm_name = "arm" + std::to_string(i);
        auto landing_leg_name = arm_name + "_landing_leg";

        dQuaternion q;
        dQFromAxisAndAngle (q, 0, 0, 1, t);

        { // create arms and landing legs
            body[arm_name] = dBodyCreate(world);
            geometry[arm_name] = dCreateBox(root_space, .16, 0.01, 0.01);
            dGeomSetBody(geometry[arm_name], body[arm_name]);
            dMassSetBox(&mass, 1, .16, 0.01, 0.01);
            dBodySetMass(body[arm_name], &mass);
            dBodySetPosition(body[arm_name], -0.05 * cos(t), -0.05 * sin(t), 1);
            dBodySetQuaternion (body[arm_name], q);

            joint[arm_name] = dJointCreateFixed(world, 0);
            dJointAttach(joint[arm_name], body[arm_name], body["avionics"]);
            dJointSetFixed (joint[arm_name]);

            body[landing_leg_name] = dBodyCreate(world);
            geometry[landing_leg_name] = dCreateBox(root_space, .01, 0.01, 0.05);
            dGeomSetBody(geometry[landing_leg_name], body[landing_leg_name]);
            dMassSetBox(&mass, 1, .01, 0.01, 0.1);
            dBodySetMass(body[landing_leg_name], &mass);
            dBodySetPosition(body[landing_leg_name], -0.13 * cos(t), -0.13 * sin(t), 1 - 0.025);

            joint[landing_leg_name] = dJointCreateFixed(world, 0);
            dJointAttach(joint[landing_leg_name], body[landing_leg_name], body[arm_name]);
            dJointSetFixed (joint[landing_leg_name]);
        }

        { // create props and joints
            auto prop_name = arm_name + "_prop";
            body[prop_name] = dBodyCreate(world);
            geometry[prop_name] = dCreateBox(root_space, .08, 0.01, 0.002);
            dGeomSetBody(geometry[prop_name], body[prop_name]);
            dMassSetBox(&mass, 1, .08, 0.01, 0.002);
            dBodySetMass(body[prop_name], &mass);
            dBodySetPosition(body[prop_name], -0.13 * cos(t), -0.13 * sin(t), 1 + 0.01);

            // create joint and attach to cube
            joint[prop_name] = dJointCreateHinge(world,0);

            const dReal* a = dBodyGetPosition(body[prop_name]);
            dJointAttach(joint[prop_name], body[arm_name], body[prop_name]);
            dJointSetHingeAnchor(joint[prop_name], a[0], a[1], a[2]);
            dJointSetHingeAxis(joint[prop_name], 0, 0, 1);
            // dJointSetHingeParam(joint[prop_name],dParamLoStop,0);
            // dJointSetHingeParam(joint[prop_name],dParamHiStop,0);
        }
    }
}

double thrust = 0;

void quad_rotor::command(int cmd)
{
    auto torque = 0.0;
    switch (cmd) 
    {
        case 'j': case 'J':
            torque = 0.0001;
            thrust += 0.0001;
          break;
        case 'l': case 'L':
            torque = -0.0001;
            thrust -= 0.0001;
          break;
    }

    for (unsigned i = 0; i < 4; i++)
    {
        dJointAddHingeTorque(joint["arm" + std::to_string(i) + "_prop"], torque * (i & 0x1 ? 1 : -1));
    }

}

std::vector<dReal> quad_rotor::observables()
{
    return std::vector<dReal>{};
}

void quad_rotor::apply_action(const std::vector<dReal>& a)
{
    // TODO:
}

void quad_rotor::user_step(dReal step_size)
{
    // TODO:
    // apply forces to each rotor based upon angular velocity
    for (unsigned i = 0; i < 4; i++)
    {
        auto prop_name = "arm" + std::to_string(i) + "_prop";
        auto leg_name = "arm" + std::to_string(i) + "_landing_leg";
        auto rot_vel = dJointGetHingeAngleRate(joint[prop_name]);
        
        dBodyAddRelForceAtRelPos(body[leg_name], 0, 0, thrust, 0, 0, 0);
    }
}
