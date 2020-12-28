#include <Wire.h>
#include <MS5611.h>

MS5611 ms5611;

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

  // Start the first pressure reading
  ms5611.requestPressure();
}

void loop()
{
  // Check if pressure reading ready
  if (ms5611.pressureReady()) {

    // Pressure reading ready, get pressure
    long pressure = ms5611.readRawPressure();

    // Print out reading
    Serial.print("Pressure = ");
    Serial.print(pressure);
    Serial.println(" Pa");
  
    // Delay to help with logging to Serial
    delay(500);

    // Start another reading
    ms5611.requestPressure();
  }

  // More code...
}
