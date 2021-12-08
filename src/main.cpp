#include <Arduino.h>
#include "webserver.h"

void setup()
{
	Serial.begin(115200);

	WebServer::Setup();
	WebServer::Start();

	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);

}

void loop()
{


}