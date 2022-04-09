
#include <math.h>
#include "DHT.h"

#define DHTPIN 3 
#define DHTTYPE DHT11

int ledPin = 4;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
	Serial.begin(9600);
	pinMode(ledPin, OUTPUT);
	Serial.println(F("hello"));
	Serial.println(F("DHTxx test!"));

	dht.begin();
}

// the loop function runs over and over again forever
void loop() {
	digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(1000);                       // wait for a second
	digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
	delay(1000);                       // wait for a second


	//temperature sensor
	// Wait a few seconds between measurements.
	delay(2000);

	// Reading temperature or humidity takes about 250 milliseconds!
	// Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
	float h = dht.readHumidity();
	// Read temperature as Celsius (the default)
	float t = dht.readTemperature();
	// Read temperature as Fahrenheit (isFahrenheit = true)
	float f = dht.readTemperature(true);

	// Check if any reads failed and exit early (to try again).
	if (isnan(h) || isnan(t) || isnan(f)) 
	{
		Serial.println(F("Failed to read from DHT sensor!"));
		return;
	}

	// Compute heat index in Fahrenheit (the default)
	float hif = dht.computeHeatIndex(f, h);
	// Compute heat index in Celsius (isFahreheit = false)
	float hic = dht.computeHeatIndex(t, h, false);

	Serial.print(F("Humidity\tTempurature(C)\tTemperature(F)\tHeat Index(C)\tHeat Index(F)\n"));

	Serial.print(F("  "));
	Serial.print(h);
	Serial.print(F("%\t\t"));
	Serial.print(t);
	Serial.print(F("\t\t"));
	Serial.print(f);
	Serial.print(F("\t\t"));
	Serial.print(hic);
	Serial.print(F("\t\t"));
	Serial.print(hif);
	Serial.println(F("\t\t"));
}
