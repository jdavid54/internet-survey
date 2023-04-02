# internet-survey

Goal : detect internet connection status and send a morse code.

You need 2 ESP32 modules, one for the detection and one for the morse code beeper.

- If internet is up, send E to have a beep avery minute

- If internet is down, send SOS to the beeper.

Before compiling and loading to the modules :

- You have to enter your ssid credentials

- You have to enter your chosen MQTT broker and the topic to be used



