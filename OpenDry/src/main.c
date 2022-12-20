#include "opendry.h"

Opendry_Handle_t opendry_h; // opendry struct handle

void app_main()
 {
   opendryInit(&opendry_h);
   opendryBegin(&opendry_h);
   serial_init();

  // Super loop 
   for(;;)
   {  
      readSensors(&opendry_h);
      updateMenu(&opendry_h);
      vTaskDelay(30/portTICK_PERIOD_MS);
      updateDisplay(&opendry_h);
      controller(&opendry_h);
   }
 }
