#include "simulation.hpp"

static void near_callback (void* ctx, dGeomID o1, dGeomID o2)
{
  int i,n;

  auto& sim = *static_cast<simulation*>(ctx);

  // only collide things with the ground
  int g1 = (o1 == sim.geometry["ground"]);
  int g2 = (o2 == sim.geometry["ground"]);

  if (!(g1 ^ g2)) return;

  const int N = 10;
  dContact contact[N];
  n = dCollide (o1,o2,N,&contact[0].geom,sizeof(dContact));
  if (n > 0)
  {
    for (i=0; i<n; i++)
    {
        contact[i].surface.mode = dContactSlip1 | dContactSlip2 |
        dContactSoftERP | dContactSoftCFM | dContactApprox1;
        contact[i].surface.mu = dInfinity;
        contact[i].surface.slip1 = 0.1;
        contact[i].surface.slip2 = 0.1;
        contact[i].surface.soft_erp = 0.5;
        contact[i].surface.soft_cfm = 0.3;
        dJointID c = dJointCreateContact (sim.world, sim.contact_group, &contact[i]);
        dJointAttach (c,
            dGeomGetBody(contact[i].geom.g1),
            dGeomGetBody(contact[i].geom.g2));
    }
  }
}


void simulation::step(dReal step_size)
{
    const unsigned nsteps = 4;

    for (unsigned i=0; i<nsteps; ++i)
    {
        t += step_size;

        for (auto& kvp : space)
        {
            auto space_id = kvp.second;
            dSpaceCollide(space_id, (void*)this, near_callback);

        }

        user_step(step_size);
        dWorldQuickStep(world, step_size);

        // remove all contact joints
        dJointGroupEmpty (contact_group);
    }
}


simulation::simulation()
{
    // create world
    dInitODE();

    world = dWorldCreate();
    space["root"] = dHashSpaceCreate (0);

    dWorldSetGravity (world,0,0,-9.8);
    dWorldSetDamping(world, 1e-4, 1e-5);

    contact_group = dJointGroupCreate(0);

    geometry["ground"] = dCreatePlane (space["root"], 0, 0, 1, 0);

}
