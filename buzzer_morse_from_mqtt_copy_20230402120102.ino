#include <WiFi.h>
#include <PubSubClient.h>

// Replace with your network credentials
const char* ssid = "your_ssid";
const char* password = "your_password";

// Replace with your MQTT broker IP address
const char* mqtt_server = "your_mqtt_broker";

// Replace with your MQTT topic
const char* mqtt_topic = "your_topic";

WiFiClient espClient;
PubSubClient client(espClient);

int LED = 2;
int buzzer = 4; // Assign buzzer to pin 4
int note = 1000; // Set the pitch for the buzzer tone

int timeUnit = 100; // This variable will be used to measure dots, dashes, breaks, and pauses
char input; // Variable to save the input to

void setup () {
   WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  pinMode(LED,OUTPUT);
  // Connect to MQTT broker
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  reconnect();

Serial.begin(115200);//for the connect with the board

}

void loop() {
  reconnect();
  client.loop();
}


void generate_morse(char input) 
{
if (input == 'a' || input == 'A') {lA();}//if the input is a or A go to function lA
if (input == 'b' || input == 'B') {lB();}//same but with b letter
if (input == 'c' || input == 'C') {lC();}
if (input == 'd' || input == 'D') {lD();}
if (input == 'e' || input == 'E') {lE();}
if (input == 'f' || input == 'F') {lF();}
if (input == 'g' || input == 'G') {lG();}
if (input == 'h' || input == 'H') {lH();}
if (input == 'i' || input == 'I') {lI();}
if (input == 'j' || input == 'J') {lJ();}
if (input == 'k' || input == 'K') {lK();}
if (input == 'l' || input == 'L') {lL();}
if (input == 'm' || input == 'M') {lM();}
if (input == 'n' || input == 'N') {lN();}
if (input == 'o' || input == 'O') {lO();}
if (input == 'p' || input == 'P') {lP();}
if (input == 'q' || input == 'Q') {lQ();}
if (input == 'r' || input == 'R') {lR();}
if (input == 's' || input == 'S') {lS();}
if (input == 't' || input == 'T') {lT();}
if (input == 'u' || input == 'U') {lU();}
if (input == 'v' || input == 'V') {lV();}
if (input == 'w' || input == 'W') {lW();}
if (input == 'x' || input == 'X') {lX();}
if (input == 'y' || input == 'Y') {lY();}
if (input == 'z' || input == 'Z') {lZ();}


// numbers
if (input == '1') {dot();dash();dash();dash();dash();letterPause();}
if (input == '2') {dot();dot();dash();dash();dash();letterPause();}
if (input == '3') {dot();dot();dot();dash();dash();letterPause();}
if (input == '4') {dot();dot();dot();dot();dash();letterPause();}
if (input == '5') {dot();dot();dot();dot();dot();letterPause();}
if (input == '6') {dash();dot();dot();dot();dot();letterPause();}
if (input == '7') {dash();dash();dot();dot();dot();letterPause();}
if (input == '8') {dash();dash();dash();dot();dot();letterPause();}
if (input == '9') {dash();dash();dash();dash();dot();letterPause();}
if (input == '0') {dash();dash();dash();dash();dash();letterPause();}

if (input == ' ') {wordPause();}


}

//Letter functions
void lA () {dot();dash();letterPause();}//letter A in morse code!
void lB () {dash();dot();dot();dot();letterPause();}//same for B
void lC () {dash();dot();dash();dot();letterPause();}
void lD () {dash();dot();dot();letterPause();}
void lE () {dot();letterPause();}
void lF () {dot();dot();dash();dot();letterPause();}
void lG () {dash();dash();dot();letterPause();}
void lH () {dot();dot();dot();dot();letterPause();}
void lI () {dot();dot();letterPause();}
void lJ () {dot();dash();dash();dash();letterPause();}
void lK () {dash();dot();dash();letterPause();}
void lL () {dot();dash();dot();dot();letterPause();}
void lM () {dash();dash();letterPause();}
void lN () {dash();dot();letterPause();}
void lO () {dash();dash();dash();letterPause();}
void lP () {dot();dash();dash();dot();letterPause();}
void lQ () {dash();dash();dot();dash();letterPause();}
void lR () {dot();dash();dot();letterPause();}
void lS () {dot();dot();dot();letterPause();}
void lT () {dash();letterPause();}
void lU () {dot();dot();dash();letterPause();}
void lV () {dot();dot();dot();dash();letterPause();}
void lW () {dot();dash();dash();letterPause();}
void lX () {dash();dot();dot();dash();letterPause();}
void lY () {dash();dot();dash();dash();letterPause();}
void lZ () {dash();dash();dot();dot();letterPause();}

void dot() //Emit sound for 100 milliseconds
{
tone(buzzer, note, timeUnit);
Serial.print('.');
digitalWrite(LED,HIGH);
delay(timeUnit);
digitalWrite(LED,LOW);
delay(timeUnit/2);
}

void dash() //Emit sound for 300 milliseconds
{
tone(buzzer, note, timeUnit * 3);
Serial.print('-');
digitalWrite(LED,HIGH);
delay(timeUnit * 3);
digitalWrite(LED,LOW);
delay(timeUnit/2);
}

void letterPause() //Delay between letters for 300 milliseconds
{
delay(timeUnit);
}

void wordPause()
{
  Serial.print(' ');  
  delay (timeUnit * 7);
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Handle MQTT message
  Serial.print("MQTT message received: ");
  payload[length] = 0;
  String recv_payload = String(( char *) payload);
  Serial.println(recv_payload);
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    generate_morse((char)payload[i]);
  }
  Serial.println();
}

void reconnect(){
  while (!client.connected()) {
    if (client.connect("arduino_client")) {
      Serial.println("Connected to MQTT broker");
      client.subscribe(mqtt_topic);
    } else {
      delay(1000);
    }
  }
}