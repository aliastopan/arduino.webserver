#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Wifi@Home";
const char* password = "02062000";
const int port = 80;

AsyncWebServer server(port);

String processor(const String& var)
{
	Serial.println(var);
	return String();
}

class WebServer
{
    public:
    static void Setup()
    {
        WiFi.begin(ssid, password);
  	    while (WiFi.status() != WL_CONNECTED)
	    {
    	    delay(1000);
    	    Serial.println("Connecting to WiFi...");
  	    }

  	    Serial.println(WiFi.localIP());
    }

    static void Start()
    {
        if (!LittleFS.begin())
	    {
		    Serial.println("[ERROR] Failed to mount FlashSystem");
		    return;
	    }

        server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
		    request->send(LittleFS, "/index.html", String());
	    });

	    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
  		    request->send(LittleFS, "/style.css","text/css");
	    });

        server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
            digitalWrite(LED_BUILTIN, LOW);
            request->send(LittleFS, "/index.html", String());
        });
        
        server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
            digitalWrite(LED_BUILTIN, HIGH);
            request->send(LittleFS, "/index.html", String());
        });

	    server.begin();
    }
};