#include "simulation.hpp"


void simulation::sim_loop(int pause)
{
    if (pause) { return; }

    const dReal step = 0.005;
    const unsigned nsteps = 4;

    for (unsigned i=0; i<nsteps; ++i)
    {
        t += step;

        dSpaceCollide(space, nullptr, nearCallback);
        dWorldQuickStep(world, step);

        // remove all contact joints
        dJointGroupEmpty (contactgroup);
    }
}