# CPET_253_Final_project
This will be the database to store all the code for my final project in Micro-controller systems class at Rochester Institue of Technology.
This code will be used to control the Garmin Lidar Lite V3 using a MSP432 micro-controller. 
This code will currently work with MSP432 Launchpad kit that is used at RIT.

# What will this project include
This project will include the use of bluetooth module on the msp432 and oled display, leds and the lidar sensor and motors. This project will also require 3d printing those parts will be realitively cheap.

# Folders
Final code will hold the code used in the demonstration and is done
The example code is going to have examples that were used to complete the files and referenced too from labs
Datasheets will hold the datasheets used to program with or to be used to reference functions used for setting ports
3d print files has the mounting bracket for the garmin lidar V3 will take 4 m3 nuts and socket cap screws of a certain size and 2 screws to hold it onto the servo mounting point the 3mf is the presliced version of the file with the proper filament settings for pla and the step file is if you want to use your own type of filament. These files are under the https://creativecommons.org/licenses/by-nc-sa/4.0/ where it allows remix culture but cannot be used for commerical use.

# What is LIDAR
LIDAR stands for "Light Detection and Ranging" which uses lasers pulses to create a map of the enviroment. It calculates the distance via the time it takes for the laser to hit the object then to bounce back and get recieved by the sensor. 
It is commonly used in aviation or terrestrial scanning. 

# What is required
- Arduino or MSP432 or Raspberry PI
- Some Sort of power source for the boards
- Any other sensors required
- Dupont connectors wires
- 1kΩ resistor if PWM mode
- 680μF capacitor if I2C protocol
- 3d printed mount for the sensor
- LIDAR Lite V3 sensor from Garmin

If you want to draw your own OLED display if you use a Adafruit 1306 0.96 display you will need to use ms paint to create a bmp file to upload to https://javl.github.io/image2cpp/ which will convert it into a splash function.
The settings I used 
- 128x64 pixels (I drew on a 128x64 pixel size mspaint image)
- Code output format was the Adafruit GFXbitmapFont
- Draw mode vertical 1 bit per pixel (THIS IS IMPORTANT) or else your image will look funky on the display



# Where to purchase Materials
Sensor:
- https://www.garmin.com/en-US/p/557294/pn/010-01722-00/#additional

Where to buy:
- 1k Resistor: https://a.co/d/01NSEAg6
- 680 microF Capacitor: https://www.digikey.com/en/products/detail/panasonic-electronic-components/EEU-FR1E681L/2433555
- Dupont connectors: https://a.co/d/09Fhr68s
- BreadBoard: https://mou.sr/4smcnqw
- MSP432: The board used is no longer sold but chip still is
- Arduino UNO: https://store-usa.arduino.cc/products/arduino-uno-rev3


# Repositories for reference from Garmin
These repositories contain examples for different uses of the LIDAR Lite V3
- https://github.com/garmin/LIDARLite_Arduino_Library
- https://github.com/garmin/LIDARLite_RaspberryPi_Library
- https://github.com/garmin/LIDARLite_ANT_Library




