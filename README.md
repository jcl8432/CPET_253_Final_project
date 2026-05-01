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

# Repositories for reference from Garmin
These repositories contain examples for different uses of the LIDAR Lite V3
- https://github.com/garmin/LIDARLite_Arduino_Library
- https://github.com/garmin/LIDARLite_RaspberryPi_Library
- https://github.com/garmin/LIDARLite_ANT_Library


# Project Reflections

## Overview
This project involved developing an embedded systems-based LiDAR scanning platform using I2C communication, an MSP432 microcontroller, an OLED display, and servo-driven mechanical integration. The system was intended to explore basic room mapping concepts and real-time sensor integration.

---

## Technical Challenges

### I2C Communication
Implementing I2C communication was one of the most complex aspects of the project. Significant debugging was required to ensure reliable sensor readings.

Key issues included:
- Timing inconsistencies between sensor measurement and data retrieval
- Initial assumptions about theoretical timing (~2 ms) proved unreliable; a 20–40 ms window was required, with 30 ms providing stable results
- Incorrect or missing delays between acquisition and read cycles resulted in invalid sensor data
- Excessive or rapid sequential I2C transactions caused unstable readings or system crashes
- Improper initialization sequence led to double-reading issues in the main loop
- Buffer configuration required iterative debugging to achieve stable communication

A software-based averaging approach was implemented, allowing the use of non-biased sensor readings while maintaining stability.

---

### OLED Display Integration
OLED output required custom formatting logic due to limitations in cursor-based rendering compared to Arduino-style libraries.

Key challenges included:
- Developing a custom output formatting function to properly align numerical data
- Resolving incorrect pixel mapping during the startup splash screen due to improper bit-level configuration
- Ensuring consistent spacing and alignment of dynamic runtime values

---

### State Machine Design
The state machine required multiple redesign iterations due to timing and hardware constraints.

Key issues included:
- Over-reliance on external state machine examples that did not fully align with system requirements
- Timer-based state transitions executing too quickly under certain conditions
- Need to restructure logic to support multi-step validation across states
- Mechanical limitation: servo torque was insufficient to reliably support and rotate the LiDAR assembly, impacting system stability

---

### LiDAR Sensor Integration
LiDAR integration required significant adaptation from initial assumptions.

Key challenges included:
- PWM mode implementation required major modifications from prior ultrasonic sensor experience
- I2C mode behavior was highly sensitive to configuration changes, requiring iterative debugging
- Sensor response inconsistencies were often linked to timing and communication sequence issues

---

### Mechanical Design (3D Modeling)
Mechanical integration required multiple design iterations.

Key challenges included:
- Approximately 8 prototype iterations were required to achieve functional fit
- Tolerance miscalculations impacted screw alignment and sensor mounting stability
- Final design was improved significantly by referencing an existing CAD model of the sensor, which improved accuracy and fit

---

## System Testing and Validation
Testing was performed iteratively across hardware and software components.

### Validation Methods:
- Oscilloscope verification of PWM signal integrity for LiDAR output
- Cross-validation of OLED display behavior using a known working reference display
- LED-based state indicators used to verify system state transitions
- Real-time monitoring of RPM and distance values via OLED output

### System-Level Testing:
- Full system integration testing using combined sensor, display, and control logic
- Iterative tuning to reduce noise and improve data stability in I2C acquisition

---

## Original System Concept
The initial design objective was to build a room-mapping robot capable of generating a point cloud representation of its environment and performing autonomous navigation to avoid obstacles.

This would have required:
- A continuously rotating sensor platform
- Additional actuation hardware for controlled scanning
- More advanced path planning and mapping algorithms

Due to system complexity and time constraints, the project was scaled down to focus on sensor integration and real-time data acquisition.

---

## Future Improvements
If further development were pursued, key improvements would include:
- Refactoring and modularizing embedded code for scalability and maintainability
- Improving LiDAR calibration and measurement accuracy through deeper sensor-level investigation
- Redesigning the mechanical mount for improved stability and reduced vibration sensitivity
- Implementing a controlled rotation mechanism for consistent scanning
- Expanding system logic toward full environmental mapping and navigation

---

## Key Takeaways
This project provided practical experience in embedded systems development, particularly in:
- I2C communication debugging and timing sensitivity
- Real-time sensor integration and data filtering
- Hardware-software co-design constraints
- Iterative system debugging under physical and electrical limitations

The project reinforced the importance of systematic debugging, hardware validation tools (oscilloscope, visual indicators), and incremental system integration.

---
