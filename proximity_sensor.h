#ifndef PROXIMITY_SENSOR_H__
#define PROXIMITY_SENSOR_H__

#include <cstdlib>
#include <ctime>

/* */
#define PROXIMITY_BIT_INDEX (4)

namespace sensor {

class ProximitySensor {
 public:
  ProximitySensor(void) {
    srand(time(NULL));
  };
  ~ProximitySensor() {}

  bool GetProximityState(void) {
    auto r = rand();
    return static_cast<bool>((r & (1 << PROXIMITY_BIT_INDEX)) > 0);
  }
};

}  // namespace sensor

#endif  // PROXIMITY_SENSOR_H_
