#include <math.h>
#include "DHT.h"

#define DHTPIN 3 
#define DHTTYPE DHT11
#define LIGHT_SENSOR A6

int ledPin = 4;

DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
	Serial.begin(9600);
	pinMode(ledPin, OUTPUT);
	dht.begin();
}

void loop() {
	digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(1000);                       // wait for a second
	digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
	delay(1000);                       // wait for a second

	//temperature sensor

	//humidity value in Fahrenheit
	float h = dht.readHumidity();

	//temperature value in Fahrenheit
	float f = dht.readTemperature(true);

	// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(f)) 
	{
		Serial.println(F("Sensor failure."));
		return;
	}

	// Heat Index (Fahrenheit)
	float hif = dht.computeHeatIndex(f, h);

	Serial.print(F("\n\nTemperature Readings: "));

	Serial.print(F("\n\tHumidity: "));
	Serial.print(h);
	Serial.print(F("\n\tTemperature: "));
	Serial.print(f);
	Serial.print(F("\n\tHeat Index: "));
	Serial.print(hif);
	Serial.println(F("\n"));

	
	if (f < 32) { Serial.println(F("\n\t\tIt is cold, bring your coat!")); }
	if (f < 50){Serial.println(F("\n\t\tIt is chilly today, pack a jacket"));}
	if (f < 75) { Serial.println(F("\n\t\tIt is warm, long sleeves will do!"));}
	else { Serial.println(F("\n\t\tIt is hot, bust out the sunscreen!")); }

	//brightness value
	int analogValue = analogRead(LIGHT_SENSOR);

	Serial.println("\n\nBrightness Readings:  \n\t");
	Serial.print(analogValue);

	if (analogValue < 10) {Serial.println(": It is dark, wear something bright to stand out!");}

	else if (analogValue < 200) {Serial.println(": It is cloudy today, dress cozy - there may be rain!");}

	else if (analogValue < 500) {Serial.println(": It is partially sunny, wear something fashionable!");}
	
	else if (analogValue < 800) {Serial.println(": The sun is out! Bring sunglasses.");}

	else {Serial.println(": It is very bright, wear sunscreen!");}
}
