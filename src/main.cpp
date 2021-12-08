#include <Arduino.h>
#include <LittleFS.h>


#include "_server.h"

void flashSystem(const char* _file)
{
	if (!LittleFS.begin())
	{
		Serial.println("[error] failed to mount LittleFS");
		return;
	}

	File file = LittleFS.open(_file, "r");
	if (!file)
	{
		Serial.println("[error] failed to open file");
		return;
	}

	Serial.println("file content: ");
	while (file.available())
	{
		Serial.write(file.read());
	}
	file.close();


}

String processor(const String& var)
{
	Serial.println(var);
	return String();
}
 
void setup()
{
	Serial.begin(115200);
	flashSystem("/sample.txt");

	// Connect to Wi-Fi
  	WiFi.begin(ssid, password);
  	while (WiFi.status() != WL_CONNECTED)
	{
    	delay(1000);
    	Serial.println("Connecting to WiFi..");
  	}

  	Serial.println(WiFi.localIP());

	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
		request->send(LittleFS, "index.html", String());
	});

	server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
  		request->send(LittleFS, "/style.css","text/css");
	});

	server.begin();
}

void loop()
{

}