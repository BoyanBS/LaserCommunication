# LaserCommunication
Two microcontrollers communicating via a laser

The point of this project is to show how light can be used to transfer information. In this project we have two separate microcontrollers that communicate with a laser. The communication is very simple and slow to be honest, it's just a message in morse code.

For the project you will need:
1. One esp32 and one arduino (or two esp32s, in my case I didn't have)
2. 16X2 I2C LCD display
3. Photoresistor
4. Resistor (10 kOhms)
5. Laser diode


Firsly let's start with the microcontroller that sends the message. The microcontroller must be esp32 because we are using it to create a Wifi network and a server. We need the server because we want to send the messages wirelessly and we need the Wifi for the server IP adress.
After uploading the code we should connect to the newly created wifi called "WifiName1234", the password is "WifiPassword1234" 
	
