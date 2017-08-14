#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "itim";
const char* password = "ilovecpe";
const char* host = "iLight_host";

int led_pin = D1;


void setup() {
  pinMode(led_pin,OUTPUT);
   Serial.begin(115200);
   Serial.println("Booting");

   Serial.println("Booting");
   WiFi.mode(WIFI_STA);

   WiFi.begin(ssid, password);   

   while (WiFi.waitForConnectResult() != WL_CONNECTED){
     WiFi.begin(ssid, password);
     Serial.println("Retrying connection...");
  }


  /* configure dimmers, and OTA server events */
  ArduinoOTA.setHostname(host);
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });

   ArduinoOTA.onError([](ota_error_t error) {
    //ESP.restart();
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
    
    });

   /* setup the OTA server */
   ArduinoOTA.begin();
   Serial.println("Ready");
   Serial.print("IP address: ");
   Serial.println(WiFi.localIP());

}

void loop() {
  ArduinoOTA.handle();
  digitalWrite(D1,HIGH);
  delay(1000);
  digitalWrite(D1,LOW);
  delay(1000);
  Serial.print("KK");
}
