# Arduino-Async-MS5611

Asynchronous MS5611 Barometric Pressure & Temperature Sensor Arduino Library

This library use I2C to communicate, so only 2 pins are required to interface with the sensor. Unlike most other MS5611 libraries, this library does not use `delay()` to wait until a measurement is received by the sensor. Rather, it initiates the measurement and lets the user check back at a later time to read it.

Based on the [Arduino-MS5611](https://github.com/jarzebski/Arduino-MS5611) library by [jarzebski](https://github.com/jarzebski).

## Examples
`MS5611_pressure.ino` - gets the pressure in Pascals asynchronously

`MS5611_adjusted_pressure.ino` - gets the pressure in Pascals asynchronously, adjusted for temperature and using the factory calibration data

## Usage

### First, initialize the sensor 

Use `begin()` to initialize the sensor. It will return `false` if no sensor is detected.

### Secondly, initiate a measurement

Use `requestTemperature()` or `requestPressure()` to request a temperature or pressure measurement, respectfully. 

These functions will return `false` if a measurement is already in progress. Not more than one measurement may be in progress at a time, regardless of the type.

### Next, check if the measurement is ready yet

Use `temperatureReady()` or `pressureReady()` to check whether the temperature or pressure measurement is ready. 

These functions return a `true` or `false` value.

### Lastly, read the measurement

Use `readRawTemperature()` or `readRawPressure()` to read the temperature, in Celsius, or pressure, in Pascals, after the measurement is ready. 

These measurements aren't adjusted using calibration data from the factory, and the temperature is not compensated for in the pressure reading. This was done to make the library as preformant as possible for users who do not need this feature.

If you do want to adjust the temperature value using the calibration data, which is recommended, pass the output of `readRawTemperature()` to `adjustTemperature()`.

If you want to adjust the pressure value using the calibration data and temperature, pass the output of `readRawPressure()` to `adjustPressure()`. YOU MUST also pass the output of `readRawTemperature()` as a second argument.

### Helper functions

You can calculate the altitude from a given pressure by passing the pressure, in Pascals, to `getAltitude()`. You can optionally specify the sea level pressure as a second argument.

You can calculate the sea level pressure by passing a pressure, in Pascals and the corresponding altitude, in Meters, to `getSeaLevel()`.

### Other

You can get and set the sensor's oversampling setting with `getOversampling()` and `setOversampling()`, respectfully.
