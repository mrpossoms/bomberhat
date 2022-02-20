#pragma once
#include <drawstuff/drawstuff.h>
#include "simulation.hpp"

#ifndef DRAWSTUFF_TEXTURE_PATH
#define DRAWSTUFF_TEXTURE_PATH "../../gitman_sources/ode/drawstuff/textures"
#endif

#ifdef dDOUBLE
#define dsDrawSphere dsDrawSphereD
#define dsDrawBox dsDrawBoxD
#define dsDrawLine dsDrawLineD
#endif


static simulation* current_sim;

static void draw(dGeomID g)
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

static void command (int cmd)
{
    current_sim->command(cmd);
}

static void start()
{
    // initial camera position
    float xyz[3] = {-0.6174,-0.8838,1.0300};
    float hpr[3] = {54.0000,-40.0000,0.0000};
    dsSetViewpoint (xyz,hpr);
}

static void step(int pause)
{
    if (!pause)
    {
        current_sim->step();
    }

    // now we draw everything
    for (auto& kvp : current_sim->geometry)
    {
        draw(kvp.second);
    }
}


void render(int argc, char* argv[], simulation& s)
{
    current_sim = &s;

    // setup pointers to drawstuff callback functions
    dsFunctions fn;
    fn.version = DS_VERSION;
    fn.start = &start;
    fn.step = &step;
    fn.command = &command;
    fn.path_to_textures = DRAWSTUFF_TEXTURE_PATH;

    // run demo
    dsSimulationLoop (argc, argv, DS_SIMULATION_DEFAULT_WIDTH, DS_SIMULATION_DEFAULT_HEIGHT, &fn);
}
