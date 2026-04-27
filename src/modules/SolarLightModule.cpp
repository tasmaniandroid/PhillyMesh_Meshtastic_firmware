#include "SolarLightModule.h"
#include "MeshService.h"
#include "configuration.h"
#include <Arduino.h>

/*
Emulates an outdoor solar light using charging state, ramps brightness
*/
SolarLightModule *solarLightModule;

SolarLightModule::SolarLightModule() : concurrency::OSThread("SolarLightModule") {}

int32_t SolarLightModule::runOnce()
{

    bool enabled = true;
    if (!enabled)
        return disable();

    if (firstTime) {
        // do something the first time we run
        firstTime = 0;
        analogWrite(NMOS_2,20);
        LOG_INFO("first time SolarLight running");
    }
    else
    {
        LOG_INFO("SolarLight executing PhillyMesh MicroNode");
        charging_state = digitalRead(EXT_CHRG_DETECT);
        if (charging_state != previous_charging_state || lowbat_state != previous_lowbat_state)
        {
            previous_charging_state = charging_state;
            previous_lowbat_state = lowbat_state;
            if (charging_state && !lowbat_state)
            {
                     pwm_value = 50; // roughly 20% brightness
            }
            else
            {
                pwm_value = 0; // off
            }
        stall_for_time = true;
        LOG_INFO("Setting PWM target of %d", pwm_value);
        analogWrite(NMOS_2,pwm_value);

        }

    }
    if (stall_for_time)
    {
        LOG_INFO("Delaying state changes");

        stall_for_time = false;
        return (stall_interval);
    }
    else
    {
        LOG_INFO("my_interval");
        return (my_interval);
    }
}
