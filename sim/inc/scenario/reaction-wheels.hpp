#pragma once
#include "simulation.hpp"

struct reaction_wheels final : public simulation
{
    reaction_wheels() : simulation() {}

    void setup() override;

    void command(int cmd) override;

    std::vector<dReal> observables() override;

    void apply_action(const std::vector<dReal>& a) override;

    void user_step(dReal step_size=0.005) override;
};
