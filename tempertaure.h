#ifndef TEMPERATURE_SENSOR_H_
#define TEMPERATURE_SENSOR_H_

#include <cstdlib>
#include <ctime>

#define TEMP_SENSOR_RAW_MIN (0)     // RAW minimum value of the sensor.
#define TEMP_SENSOR_RAW_MAX (1024)  // RAW maximum value of the sensor.
#define TEMP_SENSOR_MIN (0)         // Minimum range value in physical units (celcius)
#define TEMP_SENSOR_MAX (100)       // Maximum range value in physical units (celcius)

namespace sensor {

class TemperatureSensor {
 public:
  TemperatureSensor(void) { srand(time(NULL)); }
  ~TemperatureSensor() {};
  double GetCurrentReading();
  double GetTempMin() { return m_min; }
  double GetTempMax() { return m_max; }

 private:
  const int m_raw_min {TEMP_SENSOR_RAW_MIN};
  const int m_raw_max {TEMP_SENSOR_RAW_MAX};
  const double m_min {TEMP_SENSOR_MIN};
  const double m_max {TEMP_SENSOR_MAX};
};

}  // namespace sensor

#endif  // TEMPERATURE_SENSOR_H_
