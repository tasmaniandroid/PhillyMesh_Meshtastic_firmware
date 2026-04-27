#pragma once

#include "MeshModule.h"
#include "concurrency/OSThread.h"
#include "configuration.h"
#include <Arduino.h>
#include <functional>

class SolarLightModule : private concurrency::OSThread
{
    bool firstTime = 1;
    bool charging_state = 0;
    bool lowbat_state = 0;
    bool previous_charging_state = 1;
    bool previous_lowbat_state = 0;
    bool stall_for_time = 0;
    unsigned int pwm_value = 0;

  public:
    SolarLightModule();

  protected:
    unsigned int my_interval = 10000; // interval in millisconds
	unsigned int stall_interval = 30000; // interval in millisconds
    virtual int32_t runOnce() override;
};

extern SolarLightModule *solarLightModule;
