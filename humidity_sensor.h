#ifndef HUMIDITY_SENSOR_H_
#define HUMIDITY_SENSOR_H_

#include <cstdlib>
#include <ctime>

#define HUMIDITY_RAW_MIN (0)
#define HUMIDITY_RAW_MAX (1024)
#define HIMIDITY_MIN (0)
#define HIMIDITY_MAX (100)

namespace sensor {

class HumiditySensor {
 public:
  HumiditySensor(void) {
    srand(time(NULL));
  }
  ~HumiditySensor() {}

  double GetCurrentReading() {
    int raw_reading = (rand() % (m_raw_max - m_raw_min)) + m_raw_min;
    return (((m_max - m_min) / (m_raw_max - m_raw_min)) * static_cast<double>(raw_reading));
  }
  
  double GetHumidityMin() { return m_min; }
  double GetHumidityTempMax() { return m_max; }

 private:
  const int m_raw_min {HUMIDITY_RAW_MIN};
  const int m_raw_max {HUMIDITY_RAW_MAX};
  const double m_min {HIMIDITY_MIN};
  const double m_max {HIMIDITY_MAX};
};

}  // namespace sensor

#endif  // HUMIDITY_SENSOR_H_
