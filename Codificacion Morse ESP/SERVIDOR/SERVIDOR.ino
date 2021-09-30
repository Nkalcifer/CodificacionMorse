#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <WiFiUDP.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "Server.hpp"
#include "ESP8266_Utils.hpp"
//#include "UDP.hpp"
//#include "ESP8266_Utils_UDP.hpp"


void setup(void)
{
  Serial.begin(115200);
  SPIFFS.begin();

  ConnectWiFi_STA();
  InitServer();
  //ConnectUDP();
  
}

void loop(void)
{
  
}
