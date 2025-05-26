
 LaserCommunication
A demonstration of optical data transmission using Morse code between two microcontrollers via a laser beam. This project showcases how light can be utilized to transfer information wirelessly.


 Overview
This project illustrates the transmission of messages from an ESP32 microcontroller to an Arduino (or another ESP32) using a laser diode. The messages are encoded in Morse code and decoded on the receiving end. The ESP32 also sets up a Wi-Fi network and server to allow users to input messages wirelessly.


 Components
1 × ESP32 (transmitter)
1 × Arduino Uno or second ESP32 (receiver)
1 × 16×2 I2C LCD display
1 × Laser diode
1 × Photoresistor (LDR)
1 × 10 kΩ resistor


 How It Works
Transmitter (ESP32):
Establishes a Wi-Fi network named WifiName1234 with the password WifiPassword1234.
Hosts a web server where users can input messages.
Converts the input message into Morse code.
Controls the laser diode to emit pulses corresponding to the Morse code.
Receiver (Arduino or ESP32):
Uses a photoresistor to detect the laser pulses.
Decodes the received Morse code into readable text.
Displays the decoded message on the 16×2 I2C LCD.


Prerequisites:
Arduino IDE installed on your computer.


Setup Instructions
Transmitter Setup:

1. Open main.cpp in the Arduino IDE.
2. Upload the code to the ESP32.
3. Connect to the Wi-Fi network WifiName1234 using the password WifiPassword1234.
4. Access the web server hosted by the ESP32 to input your message (usually the address is "192.168.4.1", if it's not working check the address from the serial monitor).


Receiver Setup:
1. Open MorseDecoderI2C.ino in the Arduino IDE.
2. Upload the code to the Arduino or second ESP32.
3. Ensure the photoresistor is aligned to detect the laser pulses.
4. Connect the LCD display to the microcontroller.


Circuit Diagram
A schematic diagram illustrating the connections between components will be beneficial here.

![image](https://github.com/user-attachments/assets/b526476e-d2fe-48fd-96c9-19cdfefa338e)

![image](https://github.com/user-attachments/assets/60b440ec-26b8-4d46-9f6e-300f6a448ee1)


 Project Structure
main.cpp: Code for the ESP32 transmitter, including Wi-Fi setup and Morse code transmission.
MorseDecoderI2C.ino: Code for the receiver to decode Morse code and display messages.
