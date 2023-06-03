#pragma once
#include "simulation.hpp"

struct quad_rotor final : public simulation
{
    quad_rotor() : simulation() {}

    void setup() override;

    void command(int cmd) override;

    std::vector<dReal> observables() override;

    void apply_action(const std::vector<dReal>& a) override;

    void user_step(dReal step_size=0.001) override;
};
