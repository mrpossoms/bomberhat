#include <ode/ode.h>
#include <drawstuff/drawstuff.h>

#ifndef DRAWSTUFF_TEXTURE_PATH
#define DRAWSTUFF_TEXTURE_PATH "../../gitman_sources/ode/drawstuff/textures"
#endif

#ifdef dDOUBLE
#define dsDrawSphere dsDrawSphereD
#define dsDrawBox dsDrawBoxD
#define dsDrawLine dsDrawLineD
#endif

#define WHEEL_COUNT 1

#define CUBE_FRAME_MASS 0.25

dWorldID world;
dSpaceID space, cube_space;

dGeomID ground;
dBodyID cube_body;
dBodyID wheel_bodies[WHEEL_COUNT];
dGeomID wheel_geoms[WHEEL_COUNT];
dJointID wheel_axels[WHEEL_COUNT];
dJointGroupID contactgroup;

static const dVector3 xunit = {1, 0, 0}, yunit = {0, 1, 0}, zunit = {0, 0, 1};

static void nearCallback (void *, dGeomID o1, dGeomID o2)
{
  int i,n;

  // only collide things with the ground
  int g1 = (o1 == ground);
  int g2 = (o2 == ground);

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
        dJointID c = dJointCreateContact (world,contactgroup,&contact[i]);
        dJointAttach (c,
            dGeomGetBody(contact[i].geom.g1),
            dGeomGetBody(contact[i].geom.g2));
    }
  }
}

void start()
{
    dGeomID g;
    dMass mass;

    world = dWorldCreate();
    space = dHashSpaceCreate (0);

    dWorldSetGravity (world,0,0,-9.8);
    dWorldSetDamping(world, 1e-4, 1e-5);

    ground = dCreatePlane (space, 0, 0, 1, 0);

    contactgroup = dJointGroupCreate(0);

    cube_body = dBodyCreate(world);
    g = dCreateBox(space, 0.1, 0.1, 0.1);
    dGeomSetBody(g, cube_body);
    dMassSetBox(&mass, 0.5, 0.1, 0.1, 0.1);
    dBodySetMass(cube_body, &mass);
    dBodySetPosition(cube_body, 0, 0, 1);

    // create each wheel
    for (unsigned i = 0; i < WHEEL_COUNT; i++)
    {
        wheel_bodies[i] = dBodyCreate(world);
        wheel_geoms[i] = dCreateCylinder(space, 0.04, 0.02);
        dGeomSetBody(wheel_geoms[i], wheel_bodies[i]);
        dMassSetCylinder(&mass, 7.85, 1, 0.04, 0.02);
        dBodySetMass(wheel_bodies[i], &mass);
        dBodySetPosition(wheel_bodies[i], -0.05, 0, 1);

        dQuaternion q;
        dQFromAxisAndAngle (q, 0, 1, 0, M_PI*0.5);
        dBodySetQuaternion (wheel_bodies[i], q);

        // create joint and attach to cube
        wheel_axels[i] = dJointCreateHinge2(world,0);
        dJointAttach(wheel_axels[i], wheel_bodies[0], cube_body);
        const dReal* a = dBodyGetPosition(cube_body);
        dJointSetHinge2Anchor(wheel_axels[i], a[0], a[1], a[2]);
        dJointSetHinge2Axes(wheel_axels[i], zunit, xunit);
        dJointSetHinge2Param(wheel_axels[i],dParamLoStop,0);
        dJointSetHinge2Param(wheel_axels[i],dParamHiStop,0);
    }

    // initial camera position
    float xyz[3] = {-0.6174,-0.8838,1.0300};
    float hpr[3] = {54.0000,-40.0000,0.0000};
    dsSetViewpoint (xyz,hpr);
}

void stop()
{
    dSpaceDestroy(space);
    dWorldDestroy(world);
}


void drawGeom(dGeomID g)
{
    int gclass = dGeomGetClass(g);

    if (gclass == dPlaneClass) { return; }

    const dReal *pos = dGeomGetPosition(g);
    const dReal *rot = dGeomGetRotation(g);

    switch (gclass) {
        case dSphereClass:
            dsSetColorAlpha(0, 0.75, 0.5, 1);
            dsSetTexture (DS_CHECKERED);
            dsDrawSphere(pos, rot, dGeomSphereGetRadius(g));
            break;
        case dBoxClass:
        {
            dVector3 lengths;
            dsSetColorAlpha(1, 1, 0, 1);
            dsSetTexture (DS_WOOD);
            dGeomBoxGetLengths(g, lengths);
            dsDrawBox(pos, rot, lengths);
            break;
        }
        case dCylinderClass:
        {
            dReal rad, len;
            dsSetColorAlpha(1, 0, 0, 1);
            dsSetTexture (DS_WOOD);
            dGeomCylinderGetParams(g, &rad, &len);
            dsDrawCylinderD(pos, rot, len, rad);
            break;
        }

        default:
        {}
    }
}

void command (int cmd)
{
  switch (cmd) {
  case 'j': case 'J':
    dJointAddHinge2Torques(wheel_axels[0], 0, 0.01);
    break;
  case 'l': case 'L':
    dJointAddHinge2Torques(wheel_axels[0], 0, -0.01);
    break;
  }
}

void simLoop(int pause)
{
    if (!pause)
    {

        static dReal t = 0;

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

    // now we draw everything
    unsigned ngeoms = dSpaceGetNumGeoms(space);
    for (unsigned i=0; i<ngeoms; ++i)
    {
        dGeomID g = dSpaceGetGeom(space, i);
        drawGeom(g);
    }
}



int main(int argc, char **argv)
{
    // setup pointers to drawstuff callback functions
    dsFunctions fn;
    fn.version = DS_VERSION;
    fn.start = &start;
    fn.step = &simLoop;
    fn.command = &command;
    fn.stop = stop;
    fn.path_to_textures = DRAWSTUFF_TEXTURE_PATH;

    // create world
    dInitODE();

    // run demo
    dsSimulationLoop (argc, argv, DS_SIMULATION_DEFAULT_WIDTH, DS_SIMULATION_DEFAULT_HEIGHT, &fn);

    dCloseODE();
    return 0;
}
