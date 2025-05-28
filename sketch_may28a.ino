#include <DHT.h>

#define DHTPIN 2       // Digital pin connected to DHT11
#define DHTTYPE DHT11  // DHT11 sensor type

DHT dht(DHTPIN, DHTTYPE);

int soilPin = A2;
int lightPin = A0;

int lastSoil = 0;
int lastLight = 0;
float lastTemp = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  int rawSoil = analogRead(soilPin);
  int rawLight = analogRead(lightPin);

  float temp = dht.readTemperature();  // read temp from DHT11
  if (isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    temp = lastTemp;  // keep last valid temp if fail
  }

  int soil = map(rawSoil, 0, 1023, 0, 1000);
  int light = map(rawLight, 100, 1123, 0, 1000);

  // Send only if values changed more than 5 (for temp use 0.5 for float)
  if (abs(soil - lastSoil) > 5 || abs(light - lastLight) > 5 || abs(temp - lastTemp) > 0.5) {
    Serial.print("*");
    Serial.print(soil);
    Serial.print(" ");
    Serial.print(light);
    Serial.print(" ");
    Serial.print(temp);
    Serial.println("#");

    lastSoil = soil;
    lastLight = light;
    lastTemp = temp;
  }

  delay(100); // DHT needs ~2 sec between reads
}
