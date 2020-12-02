#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <WakeOnLan.h>
#include <ESP8266Ping.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "Cop08gzP38ADLfc7QaxTKB06NhxivT19";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "TIM-02520154";
char pass[] = "sDFsbKcXEe7UfpNRquzzFQ6d";

long previousMillis = 0;

WiFiUDP UDP;

BLYNK_APP_CONNECTED() {

}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
  UDP.begin(9);
}

void loop()
{
  Blynk.run();
  if (millis() - previousMillis >= 15000) {
    previousMillis = millis();
    digitalWrite(2, HIGH);
    pingServers();
    digitalWrite(2, LOW);
  }
}

BLYNK_WRITE(V0) 
{
  IPAddress computer_ip(255, 255, 255, 255); 

  byte mac[] = { 0xA8, 0xA1, 0x59, 0x2D, 0x2A, 0xB6 };

  WakeOnLan::sendWOL(computer_ip, UDP, mac, sizeof mac);
}

void pingServers() {
  IPAddress DNS(1, 1, 1, 1);
  bool ping1 = Ping.ping(DNS, 1);
  int time1 = Ping.averageTime();
  if (ping1) {
      Blynk.virtualWrite(V1, time1);
  }
  bool ping2 = Ping.ping("discord.com");
  int time2 = Ping.averageTime();
  if (ping2) {
      Blynk.virtualWrite(V2, time2);
  }
}
