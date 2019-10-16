# NITELITE
### Arduino controller RGB LED 5050 night light
copyright: Micah Martin / Airworthy, LLC 2019

### Development 

Uses platformio.

Shell commands located in the arduino/bin directory simply tasks 

After the first compile fails (missing SHI.h file) edit .piolibdeps/ssd1306_ID1904/src/ssd1306_hal/UserSettings.h.  Comment out the line:

    #define CONFIG_PLATFORM_SPI_ENABLE
    
### Features

Nite light stuff    
      
    