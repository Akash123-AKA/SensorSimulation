#include <iostream>

#include "proximity_sensor.h"
#include "temperature_sensor.h"
#include "humidity_sensor.h"

using namespace std;
using namespace sensor;

int main(int argc, const char *argv[]) {
  TemperatureSensor t;
  ProximitySensor p;
  HumiditySensor h;

  for (auto i = 0; i < 10; ++i) {
    cout << i << "-> "
         << "Temperature: " << t.GetCurrentReading()
         << ", Proximity: " << p.GetProximityState()
         << ", Humidity: " << h.GetCurrentReading()
         << endl;
  }
}
