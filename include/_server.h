#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Wifi@Home";
const char* password = "02062000";
const int port = 80;

AsyncWebServer server(port);
