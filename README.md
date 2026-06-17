# Smart Energy Efficient Home Automation Using ATmega32 Microcontroller

## Project Overview

This project is a Smart Home Automation System developed using the ATmega32 Microcontroller. The system monitors environmental conditions such as temperature, light intensity, and gas levels, and automatically controls household devices to improve energy efficiency, comfort, and safety.

## Features

* Temperature Monitoring using LM35 Sensor
* Light Level Detection using LDR
* Gas Detection Simulation using Potentiometer
* Automatic Fan Control
* Automatic Light Control
* Gas Leak Alert using Sounder/Buzzer
* Real-Time Status Display on 16x2 LCD
* Energy-Efficient Home Automation

## Hardware Components

### Input Sensors

* LM35 Temperature Sensor
* LDR (Light Dependent Resistor)
* Potentiometer (Gas Sensor Simulation)

### Output Devices

* DC Fan Motor
* Red LED (Fan Status Indicator)
* Green LED (Light Status Indicator)
* Sounder/Buzzer (Gas Alert)
* 16x2 LCD Display

### Main Controller

* ATmega32 Microcontroller

## System Operation

1. Sensors collect environmental data.
2. The ATmega32 reads analog sensor values through its ADC channels.
3. Sensor readings are compared with predefined threshold values.
4. Outputs are automatically controlled:

   * Temperature > 30°C → Fan ON
   * Light Level < 30% → Light ON
   * Gas Level > 20% → Sounder ON
5. Sensor values and system status are displayed on the LCD.

## Software Tools

* Microchip Studio
* Proteus Design Suite
* Embedded C Programming

## Screenshots


### Circuit Simulation in Proteus

![Proteus Circuit](https://github.com/reezmahanan/Smart-Home/blob/main/Screenshot%204.png)



## Project Team

* M. R. Hanan- Me  (Team Leader)
* M. D. B. Amarakoon
* D. G. D. Dilshan
* S. M. R. Kaveeshwara
* B. A. P. Nethmi
* B. M. N. Sewwandi

## Learning Outcomes

This project enhanced our understanding of:

* Microcontroller Programming
* Analog-to-Digital Conversion (ADC)
* Sensor Interfacing
* Embedded Systems Development
* Home Automation Technologies
* Teamwork and Project Management

## License

This project was developed for academic and educational purposes.
