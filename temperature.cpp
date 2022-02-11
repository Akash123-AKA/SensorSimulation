#include "temperature_sensor.h"

namespace sensor {

double TemperatureSensor::GetCurrentReading() {
    int raw_reading = (rand() % (m_raw_max - m_raw_min)) + m_raw_min;
    return (((m_max - m_min)/(m_raw_max - m_raw_min)) * static_cast<double> (raw_reading));
}

}  // namespace sensor
