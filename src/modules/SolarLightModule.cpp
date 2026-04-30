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

    if (!moduleConfig.solar_light.enabled)
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
        //digitalWrite(NMOS_2, digitalRead(EXT_CHRG_DETECT));  // Match charge state
        bool Not_Charging = digitalRead(EXT_CHRG_DETECT);
        if (Not_Charging != previous_state && !ramping)
        {
            previous_state = Not_Charging;
            if (Not_Charging)
            {
                ramp_target_value = 50; // fade up
            }
            else
            {
                ramp_target_value = 0; //fade down
            }
        start_ramp = true;
        LOG_INFO("Initiating Ramp with target of %d", ramp_target_value);

        }

        if (ramping || start_ramp)
        {  
            start_ramp = 0;
            if (ramp_target_value == ramp_value)
            {
                ramping = 0;
                LOG_INFO("Ending Ramp");
                stall_for_time = 1;
            }
            else
            {
                ramping = 1;
                if (ramp_target_value < ramp_value)
                ramp_value = ramp_value - 1;
                if (ramp_target_value > ramp_value)
                ramp_value = ramp_value + 1;
                LOG_INFO("ramp value is %d",ramp_value);
            }
            
            analogWrite(NMOS_2,ramp_value);
            
        }


    }
    if (ramping)
    {
        LOG_INFO("tenh of second");
        return (100);  
    }
    else if (stall_for_time)
    {
        LOG_INFO("ten seconds");

        stall_for_time = false;
        return (10000);
    }
    else
    {
        LOG_INFO("my_interval");
        return (my_interval);
    }
}
