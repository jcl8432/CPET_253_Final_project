# CPET_253_Final_project
This will be the database to store all the code for my final project in Micro-controller systems class at Rochester Institue of Technology.
This code will be used to control the Garmin Lidar Lite V3 using a MSP432 micro-controller. 
This code will currently work with MSP432 Launchpad kit that is used at RIT.

# What will this project include
This project will include the use of and oled display, leds and the lidar sensor and motors and timers and I2C. This project will also require 3d printing those parts will be realitively cheap.

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
If you cannot find a 680µF capacitor you can multiple other capacitors in parallel to make a single capacitor.
I used 1 470µF capacitor, 2 100µF capacitors, and 1 10µF capacitor.

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

# Problems I ran into during this project
I2C Protocol:
- learning I2C was difficult there was a lot of trial and error the biggest problem was getting the sensor to take the measurement and have enough time to output the right number or a number at all. I found that even though there is a theoretical value of 2ms that isnt really possible for something like this sensor I found that 30ms was a better because it was in the reccomended sweet spot of 20ms-40ms.
- Another problem I encountered was the biasing or non biasing that the sensor allowed you to do. I chose the non biased reading option due to the fact I built in a averaging function which did the same thing as biasing but was quicker.
- Some of the time when I was using the I2C protocol I would forget to put a delay inbetween data aqquistion and when the data is recieved by the mdp432. this let do straight up wrong readings and it was not correct at all and was causing problems. Also related was having to many sends or recieves in a row it would give weird readings or crash.
- Another was not reading before getting into the main loop so it would be double reading and was giving incorrect data.
- smaller things was learning how to properly set up the I2C buffers.

OLED Display:
- One problem was trying to output measured values to the screen. I learned that you cannot like in arduino set the cursor in a spot for where you want it to start writing and that would output the string you want. I had to create the helper function value out to make it display properly
- Another was when I was setting up the start up splash I was using the wrong part of the converter I was not setting the pixels and bits properly so it was shown wierdly.

State machine:
- Trying to use other state machines as an example didn't work out too well so I spend a good portion of time debugging the state machine.
- Some of the states were using a state timer but it was going to fast and it needed multiple states to go to if one didn't pass.
- Some of the states are a bit rough and I tried to make it as simple as possible but the main problem I ran into is that the servo would not be able to handle the weight of the lidar sensor and swing it without it falling off. 

Lidar:
- The sensor was a bit of a learning curve. I first got it running on the PWM mode I tried using the modes from the ultrasonic lab but that didnt work and it need to change a lot. I didn't include that code in the file because it was super buggy and I struggled with it a lot.
- The I2C portion of the sensor was already explained above but to bounce off that I struggled to get it run at points sometimes messing with one thing would change how the whole thing functioned all together.

3D modeling:
- I struggled with the modeling aspect of this I went through 8 iterations to get to the final 3d print I got to. I struggled a lot with the print tolerances and getting the right sized holes and placement of the holes to make it so that the screws fit onto the sensor and held it up. I found later on that someone already did the cad of the actual sensor so I used that to do all the parameters ot make it so everything fit well.

# Big takeaways 
This project was overall a lot of fun and a big learning experience and I learned a lot about LIDAR and I2C protocol. I also learned a lot about how to work on a project to make it work. I found a lot of times to be going back to resources to read up on them and learning how to make it work. I think I also was outside my comfort zone on this project almost all the time.


# Repositories for reference from Garmin
These repositories contain examples for different uses of the LIDAR Lite V3
- https://github.com/garmin/LIDARLite_Arduino_Library
- https://github.com/garmin/LIDARLite_RaspberryPi_Library
- https://github.com/garmin/LIDARLite_ANT_Library




