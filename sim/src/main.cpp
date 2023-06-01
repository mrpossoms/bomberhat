#include "simulation.hpp"
#include "render.hpp"

#include "scenario/reaction-wheels.hpp"
#include "scenario/quad-rotor.hpp"

#define WHEEL_COUNT 1
#define CUBE_FRAME_MASS 0.25

static const dVector3 xunit = {1, 0, 0}, yunit = {0, 1, 0}, zunit = {0, 0, 1};


int main(int argc, char **argv)
{
    quad_rotor sim;

    sim.setup();

    render(argc, argv, sim);

    return 0;
}
