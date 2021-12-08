#include <Arduino.h>
#include <LittleFS.h>

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

 
void setup()
{
	Serial.begin(115200);
	flashSystem("/sample.txt");
}

void loop()
{

}