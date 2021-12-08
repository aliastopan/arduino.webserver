#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Wifi@Home";
const char* password = "02062000";
const int port = 80;

AsyncWebServer server(port);

class WebServer
{
    public:
    static void Setup(Stream &serialstream)
    {
        WiFi.begin(ssid, password);
  	    while (WiFi.status() != WL_CONNECTED)
	    {
    	    delay(1000);
    	    serialstream.println("Connecting to WiFi...");
  	    }

  	    serialstream.println(WiFi.localIP());
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

	    server.begin();
    }
};