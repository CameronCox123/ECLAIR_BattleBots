- Plug in your ESP32 to your computer
- Open Arduino IDE
- Go to Board Manager and install ESP32 by Espressif Systems
- Select: ESP32 Wrover Module from boards and select the appropriate COM port from your device
- MAC_Address.ino code 
- Compile the MAC_Address.ino code using the check circle in the top left, and upload to the ESP32 using the arrow in the top left
- Wait till the Output terminal displays: Hard resetting via RTS pin… 
- Open the Serial Monitor using Ctrl + Shift + M
- Press the EN button on the ESP32, this will display the devices MAC address down at the bottom of the Serial Monitor panel, it should look something like: [DEFAULT] ESP32 Board MAC Address: c8:2e:18:f7:4c:e8
- Go to this site: https://network.utexas.edu and click Register WiFi-Device
- Input the MAC address that was printed in the Serial Monitor
- Set Netowrk Profile to Unprotected and click Register
- We’re going to create a new sketch for the webserver, open a new sketch using Ctrl + N and upload Blue_Light_Test.ino to the board 
- This will create a webserver that lights up the blue LED on your ESP32 when you press W on the keyboard while in the webserver
- Make sure you replace the password with the PSK you got in the UT Network Portal, remove the spaces
- Compile the code and upload it to the ESP32
- Open the Serial Monitor and you should see Connecting to WiFi....
- After it connects you will have to scroll down to see your ESP’s IP address
- Copy and paste the into the web browser and it should connect ot a web page
- Press W and watch the LED light up!!!
