# Internet connection survey

Goal : detect internet connection status and send a morse code.

You need 2 ESP32 modules, one for the status detection (mod1) and one for the morse code beeper (mod2).

- If internet is up, mod1 sends "E" to mod2 to have a beep every minute. The blue LED stays ON.

- If internet is down, send "SOS" to the beeper. The blue LED is set OFF.

Before compiling and loading to the modules :

- You have to enter your ssid credentials

- You have to enter your chosen MQTT broker and the topic to be used

#### Module 1 : Internet connection status detector

<img src="http://jean.david.free.fr/images/IMG_20230402_121434.jpg" width="250">

#### Module 2 : Morse code beeper

<img src="http://jean.david.free.fr/images/IMG_20230402_121524.jpg" height="250">
