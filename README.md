# car-project
This project is a 4-wheel drive robot car controlled via Bluetooth using an Arduino Uno, L293D Motor Shield, and HC-05 Bluetooth module. The car can be controlled using any Bluetooth controller app that can send simple character commands.
Components Required
Electronics

    1× Arduino Uno R3
    1× L293D Motor Shield
    1× HC-05 Bluetooth Module
    4× DC Motors (3-6V)
    1× Battery Holder (for 4 AA batteries)
    4× AA Batteries
    1× 9V Battery (for Arduino)
    1× 9V Battery Connector

Assembly Instructions
Step 1: Electronics Assembly

    Stack L293D Motor Shield onto Arduino Uno
        Ensure all pins are properly aligned
        Press firmly but gently to seat the shield

    Connect HC-05 Bluetooth Module to Arduino:

    HC-05    ->  Arduino
    VCC      ->  5V
    GND      ->  GND
    TXD      ->  RX (Pin 0)
    RXD      ->  TX (Pin 1)

    Connect Motors to Shield:
        M1: Front Left Motor
        M2: Front Right Motor
        M3: Rear Left Motor
        M4: Rear Right Motor

    Note: Test each motor's direction. If any motor runs backwards, swap its connections.

    Power Connections:
        Connect 9V battery to Arduino's power jack
        Connect 4×AA battery pack to motor shield's power terminal
        Double-check all power connections before turning on

Step 2: Software Setup

    Install Required Libraries:
        AFMotor Library (for L293D shield)
        Download from: https://github.com/adafruit/Adafruit-Motor-Shield-library
        wdt.h Library (for watchdog)
        Download from: https://github.com/vancegroup-mirrors/avr-libc/blob/master/avr-libc/include/avr/wdt.h
    Upload Code:
        Open car.ino in Arduino IDE
        Select "Arduino Uno" from Tools > Board menu
        Select correct COM port
        Click Upload button

Operation Instructions
Bluetooth Control Commands

    'F': Move Forward
    'B': Move Backward
    'L': Turn Left
    'R': Turn Right
    'G': Forward Left
    'I': Forward Right
    'H': Down Left
    'J': Down Right
    'S': Stop
    '1'-'9': Speed Control (1=slowest, 9=fast)
    'q': Maximum Speed

Recommended Mobile Apps

    Arduino Bluetooth RC Car
    Bluetooth RC Controller
    Any app capable of sending single character commands

Safety Features

    Watchdog timer prevents lockups
    Command timeout stops motors if connection is lost
    Speed ramping prevents sudden movements
    Emergency stop with 'S' command

Maintenance

    Regular Checks:
        Battery voltage
        Loose connections

    Battery Care:
        Remove batteries when not in use
        Replace batteries when performance drops

Last Updated

December 2024
