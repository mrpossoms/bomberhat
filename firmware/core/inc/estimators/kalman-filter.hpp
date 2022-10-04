#pragma once


#include "core.hpp"

#define STATE_SIZE 3
#define CONTROL_SIZE 4

struct KalmanFilter : public bh::Estimator<STATE_SIZE, CONTROL_SIZE>
{

};