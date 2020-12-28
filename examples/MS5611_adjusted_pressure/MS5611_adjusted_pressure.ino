#include <Wire.h>
#include <MS5611.h>

MS5611 ms5611;

double lastRawPressure;
double lastRawTemp;

void setup() 
{
  Serial.begin(9600);

  // Initialize sensor
  Serial.println("Initializing MS5611 Sensor...");
  while(!ms5611.begin())
  {
    Serial.println("Could not find a valid MS5611 sensor, check wiring!");
    delay(500);
  }

  // Print oversampling setting
  Serial.print("Oversampling: ");
  Serial.println(ms5611.getOversampling());

  // Start the first temperature reading
  ms5611.readRawTemperature();
}

void loop()
{
  // Check if pressure reading ready
  if (ms5611.pressureReady()) {

    // Pressure reading ready, get pressure
    lastRawPressure = ms5611.readRawPressure();

    double adjustedPressure = ms5611.adjustPressure(lastRawPressure, lastRawTemp);
    double adjustedTemp = ms5611.adjustTemperature(lastRawTemp);

    // Print out reading
    Serial.println();
    Serial.print("Raw Pressure = ");
    Serial.print(lastRawPressure);
    Serial.println(" Pa");
    Serial.print("Adjusted Pressure = ");
    Serial.print(adjustedPressure);
    Serial.println(" Pa");
    Serial.print("Raw Temp = ");
    Serial.print(lastRawTemp);
    Serial.println(" Pa");
    Serial.print("Adjusted Temp = ");
    Serial.print(adjustedTemp);
    Serial.println(" Pa");

    // Delay to help with logging to Serial
    delay(500);
  
    // Start a temperature reading
    ms5611.requestTemperature();
  }

  // Check if temperature reading ready
  if (ms5611.temperatureReady()) {

    // Temperature reading ready, get temperature
    lastRawTemp = ms5611.readRawTemperature();
  
    // Start a pressure reading
    ms5611.requestPressure();
  }

  // More code...
}
