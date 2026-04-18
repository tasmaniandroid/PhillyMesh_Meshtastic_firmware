#pragma once

#include "MeshModule.h"
#include "concurrency/OSThread.h"
#include "configuration.h"
#include <Arduino.h>
#include <functional>

class SolarLightModule : private concurrency::OSThread
{
    bool firstTime = 1;
    bool previous_state = 1;
    bool ramping = 0;
    bool start_ramp = 0;
    bool stall_for_time = 0;
    unsigned int ramp_target_value = 0;
    unsigned int ramp_value = 0;

  public:
    SolarLightModule();

  protected:
    unsigned int my_interval = 2000; // interval in millisconds
    virtual int32_t runOnce() override;
};

extern SolarLightModule *solarLightModule;
