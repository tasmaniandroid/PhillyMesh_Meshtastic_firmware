#include "GenericThreadModule.h"
#include "MeshService.h"
#include "configuration.h"
#include <Arduino.h>

/*
Generic Thread Module allows for the execution of custom code at a set interval.
*/
GenericThreadModule *genericThreadModule;

GenericThreadModule::GenericThreadModule() : concurrency::OSThread("GenericThreadModule") {}

int32_t GenericThreadModule::runOnce()
{

    bool enabled = true;
    if (!enabled)
        return disable();

    if (firstTime) {
        // do something the first time we run
        firstTime = 0;
        LOG_INFO("first time GenericThread running");
    }
    LOG_INFO("GenericThread executing PhillyMesh MicroNode");
    digitalWrite(NMOS_2, digitalRead(EXT_CHRG_DETECT));  // Match charge state
    LOG_INFO("NMOS_2 is %d and EXT_CHRG_DETECT is %d", !digitalRead(NMOS_2),digitalRead(EXT_CHRG_DETECT));

    return (my_interval);
}
