#include "EspMQTTClient.h"
#include <WiFi.h>
#include <ESP32Ping.h>
#include <Arduino.h>



EspMQTTClient client(
  "Routeur Main Robotisee",
  "0123456789",
  "192.168.1.70",  // MQTT Broker server ip
  "",   // Can be omitted if not needed
  "",   // Can be omitted if not needed
  "Testpub",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

void onConnectionEstablished(){
  // Publish a message to "mytopic/test"
  client.publish("mytopic/test", "maxime = homme heureux"); // You can activate the retain flag by setting the third parameter to true
}

//definition des PINS
const int sensorPin1 = 39;
const int sensorPin2 = 35;
const int sensorPin3 = 36;
const int sensorPin4 = 34;
const int sensorPin5 = 32; 

//initialisation des tableaux
char  texte1 [40] ;
char  texte2 [40] ;
char  texte3 [40] ;
char  texte4 [40] ;
char  texte5 [40] ;


void setup() {
  //Initialisation de la vitesse du terminal à 115200 bauds
  Serial.begin(115200);

  delay(1000);
    Serial.begin(115200);
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("Testpub/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true

  //PINS ADC mis en entée
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);
  pinMode(sensorPin5, INPUT);

  while (!Serial) {
    ; 
  }
}

void loop() {

  //récupération des valeurs des capteurs
  int sensorValue1 = analogRead(sensorPin1);
  int sensorValue2 = analogRead(sensorPin2);
  int sensorValue3 = analogRead(sensorPin3);
  int sensorValue4 = analogRead(sensorPin4);
  int sensorValue5 = analogRead(sensorPin5);

  //transformation de ces valeurs en %
  sensorValue1 = (sensorValue1 - 1650)/(6.5);
  sensorValue2 = (sensorValue2 - 1600)/(7.5);
  sensorValue3 = (sensorValue3 - 1600)/(8.3);
  sensorValue4 = (sensorValue4 - 1650)/(6.6);
  sensorValue5 = (sensorValue5 - 1650)/(6.5);

  //Stauration des capteurs si valeurs trop petite
  if (sensorValue1 <0)
  {
    sensorValue1 = 0;
  }
  if (sensorValue2 <0)
  {
    sensorValue2 = 0;
  }
  if (sensorValue3 <0)
  {
    sensorValue3 = 0;
  }
  if (sensorValue4 <0)
  {
    sensorValue4 = 0;
  }
  if (sensorValue5 <0)
  {
    sensorValue5 = 0;
  }

  //Stauration des capteurs si valeurs trop grande
  if (sensorValue1 > 100)
  {
    sensorValue1 = 100;
  }
  if (sensorValue2 > 100)
  {
    sensorValue2 = 100;
  }
  if (sensorValue3 > 100)
  {
    sensorValue3 = 100;
  }
  if (sensorValue4 > 100)
  {
    sensorValue4 = 100;
  }
  if (sensorValue5 > 100)
  {
    sensorValue5 = 100;
  }

  //création du texte à afficher dans une chaine de caractères
  sprintf (texte1,"%d",sensorValue1) ;
  sprintf (texte2,"%d",sensorValue2) ;
  sprintf (texte3,"%d",sensorValue3) ;
  sprintf (texte4,"%d",sensorValue4) ;
  sprintf (texte5,"%d  \n ",sensorValue5) ;
  
  
  
  client.loop();

  client.publish("mytopic/doigt1", texte1); 
  
  client.publish("mytopic/doigt2", texte2);
  
  client.publish("mytopic/doigt3", texte3);
  
  client.publish("mytopic/doigt4", texte4);
  
  client.publish("mytopic/doigt5", texte5);
  delay(250);
}
