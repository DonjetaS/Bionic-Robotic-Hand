## Bionic-Hand-Roboter
# Overviev
This project focuses on the design and construction of a bionic hand using a cable-driven (tendon-based) mechanism powered by servo motors. The system enables controlled finger flexion and extension, as well as forward movement of the thumb to simulate basic grasping actions.

The goal is to create a functional, affordable, and modular robotic hand that demonstrates fundamental principles of bio-inspired engineering.

# Features
- Cable-driven (tendon-like) finger actuation with servos
- Finger flexion and extension
- Thumb opposition (forward movement<)

# Hardware Components
- Servo motors (SG90 9g Micro Servomotor, 6x)
- Microcontroller (ESP32, 1x)
- Adafruit PCA9685 (Servo-driver, 1x)
- Fishing line (1x)
- Power supply (for servos and ESP32, therefore 2x)
- 3D-printed hand structure (can be found in the STL-folder)

# Software
The system can be controlled using a micocontroler such as an Arduino or ESP32. I'm using the ESP32 with WiFi and Bluetooth compability with the Arduino IDE software. To be exact I'm using the Web-Interface for real-time controlling.

# How it works
Each finger is connected to a servo motor via a cable (tendon). When the servo rotates, it pulls the cable, causing the finger to bend (flexion). Releasing the cable allows the finger to extend back to its original position.

The thumb includes an additional movement axis, allowing it to move forward and create more realistic gripping motions.
The movement is controlled via a website to recieve the users inputs.

# Future Improvemts
- Controlling via a glove with flex-sensors
- Cable-managment in the palm

# Setup
- For the Setup see Bionic_Hand_Schaltplan

# Usage
- Control the servos via the website and perform basic grasping and release motions
# Author
Donjeta S.
