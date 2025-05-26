# LaserCommunication

The point of this project is to show how light can be used to transfer information (in this case messages). For the project we are sending a message from an esp32 to an arduino with a laser by Morse code. 

For the project I am using:
1. One esp32 and one arduino (or two esp32s, in my case I didn't have)
2. 16X2 I2C LCD display
3. Photoresistor
4. Resistor (10 kOhms)
5. Laser diode


Firsly let's start with the microcontroller that sends the message. The microcontroller must be esp32 because we are using it to create a Wifi network and a server. We need the server because we want to send the messages wirelessly and we need the Wifi for the server IP address.
After uploading the code we should connect to the newly created wifi called "WifiName1234", the password is "WifiPassword1234" (you can change the name and the password from the 4th and the 5th row in the main.cpp file). Then you should go in your browser to the address "192.168.4.1" from where you can send messages. When you are sending a message from the server, you are sending it to esp, where the message is translated into morse code and after that the dots/dashes are transformed into short/long beams of light through the laser diode.

The messages are being captured by the photoresistor that is connected to the arduino. After receiving the light signals, the arduino translates them into morse code and then into characters. After that the characters are shown on the LCD display. 
	
