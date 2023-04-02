#include <WiFi.h>
#include <NTPClient.h>    //use the library from https://github.com/taranais/NTPClient
#include <WiFiUdp.h>
#include <PubSubClient.h>
//#include <ArduinoMqttClient.h>
#include <ESP32Ping.h>

#define googleOnlineLED 9
#define googleOfflineLED 10
#define LED 2

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;

const char* ssid = "your_SSID";
const char* pass = "Your_password";
const char* google = "google.com";
const char* AlertString = "Internet Down";

// Add your MQTT Broker IP address, example:
const char* mqtt_server = "your_mqtt_broker";
const char* topic ="your_topic";


WiFiClient client;
PubSubClient mqttclient(client);
//MqttClient mqttClient(client);

void setup() {
  //pinMode(googleOnlineLED, OUTPUT);
  //pinMode(googleOfflineLED, OUTPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  Serial.print("Attempting to connect to Network named: ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.print("Default Gateway: ");
  Serial.println(gateway);

  // Initialize a NTPClient to get time
  timeClient.begin();
  timeClient.setTimeOffset(3600);

  mqttclient.setServer(mqtt_server, 1883);
  reconnect();
  
  mqttclient.publish(topic, "S");
  // if subscribing for msg
  //client.setCallback(callback);
  
  // with ArduinoMqttClient library
  /*mqttClient.connect(mqtt_server, 1883);
  if (!mqttClient.connect(mqtt_server, 1883)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }*/
  //Serial.println("Go to loop");
}

void loop() {
  // call poll() regularly to allow the library to send MQTT keep alives which
  // avoids being disconnected by the broker
  // mqttClient.poll();
  
  //Serial.print("Looping "); 
  mqttclient.loop();

  // ping method
  bool success = Ping.ping("www.google.com", 3);
 
  if(!success){
      Serial.println("Ping failed");
      Serial.println(AlertString);
      digitalWrite(LED, LOW);
      // publish 
      reconnect();
      mqttclient.publish(topic, "SOS"); 
  }
  else {
    Serial.println("Ping succesful.");
    get_datetime();
    if (client.connect(google, 80)) {
      Serial.print("Google is ONLINE at:  ");
      Serial.println(client.remoteIP());
           
      reconnect();
      mqttclient.publish(topic, "E");
      /*mqttClient.beginMessage("esp32/output");
      mqttClient.print("OK");
      mqttClient.endMessage();*/
      digitalWrite(LED, HIGH);

    }
    
  }

  delay(60000);
}

void get_datetime() {
   while(!timeClient.update()) {
    //Serial.print("*");
    timeClient.forceUpdate();
  }
  
  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
  formattedDate = timeClient.getFormattedDate();
  //Serial.println(formattedDate);

  // Extract date
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  Serial.print("DATE: ");
  Serial.println(dayStamp);
  // Extract time
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
  Serial.print("HOUR: ");
  Serial.println(timeStamp);
}

void reconnect() {
  // Loop until we're reconnected
  while (!mqttclient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttclient.connect("ESP32Client")) {
      Serial.println("connected");
      // Subscribe
      //mqttclient.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttclient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
