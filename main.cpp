#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <chrono>
#include <thread>

#include "json/json.h"
#include "json/value.h"
#include "json/reader.h"

#include "proximity_sensor.h"
#include "temperature_sensor.h"
#include "humidity_sensor.h"

using namespace std;
using namespace sensor;

class AppConfig {
  public:
    AppConfig() {
      ifstream configFile("C:/Users/user/Downloads/joyofenergy_cpp-devel (1)/joyofenergy_cpp-devel/src/app_config.json");
      Json::Reader reader;
      m_isValid = reader.parse(configFile, configJson);
    }

    ~AppConfig() {}

    bool doesValidConfigExists() {
      return m_isValid;
    }

    int getSensorIntervalInMs(string sensorId) {
      Json::String sensorIntervalString = configJson[sensorId]["timeInterval"].toStyledString();
      int sensorInterval = stoi(sensorIntervalString.substr(1, sensorIntervalString.find_first_of(" ms")));
      return sensorInterval;
    }

  private:
    Json::Value configJson;
    bool m_isValid = false;
};

class SensorDataCollector {
  public:
    SensorDataCollector() {}
    ~SensorDataCollector() {}

    /** 
     * This function initializes Data collector module by getting sensor data fetch intervals for all 3 sensors
     * Returns true if all 3 sensors interval fetch is successful otherwise false
    */
    bool Initialize(AppConfig appConfig) {
      if (appConfig.doesValidConfigExists()) {
        temperatureSensorInterval = appConfig.getSensorIntervalInMs("TemperatureSensor");
        humiditySensorInterval = appConfig.getSensorIntervalInMs("HumiditySensor");
        proximitySensorInterval = appConfig.getSensorIntervalInMs("ProximitySensor");
      }
      return temperatureSensorInterval > 0 && humiditySensorInterval > 0 && proximitySensorInterval > 0; 
    }

    /** 
     * This function starts collection of sensor data
     * Note: Before starting initialize data collector to have positive fetch intervals
     *       If intervals are negative, data collector will ignore fetching data from the sensor
    */
    void Start() {
      TemperatureSensor t;
      ProximitySensor p;
      HumiditySensor h;

      int temperatureCounter = -1, humidityCounter = -1, proximityCounter = -1;
      while (true) {
        temperatureCounter++;
        humidityCounter++;
        proximityCounter++;

        if (temperatureCounter == temperatureSensorInterval) {
          cout << "Temperature Value at " << GetCurrentTimeStampString() << " : " << t.GetCurrentReading() << endl;
          temperatureCounter = 0;
        }

        if (humidityCounter == humiditySensorInterval) {
          cout << "Humidity Value at " << GetCurrentTimeStampString() << " : " << h.GetCurrentReading() << endl;
          humidityCounter = 0;
        }

        if (proximityCounter == proximitySensorInterval) {
          cout << "Proximity Value at " << GetCurrentTimeStampString() << " : " << p.GetProximityState() << endl;
          proximityCounter = 0;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
    }

    string GetCurrentTimeStampString() {
      auto t = std::time(nullptr);
      auto tm = *std::localtime(&t);
      std::ostringstream oss;
      oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
      return oss.str();
    }

    /** 
     * This function stops collection of sensor data from all 3 sensors
    */
    void Stop() {}

  private:
    int temperatureSensorInterval = -1;
    int humiditySensorInterval = -1;
    int proximitySensorInterval = -1;
};

int main(int argc, const char *argv[]) {
  // 1. Collect configuration data from config file (intervals for each sensor)  - SensorDataCollector::GetConfigurationData() 
  // 2. Start data collector - SensorDataCollector::Start() (Optional - SensorDataCollector::Stop())

  SensorDataCollector dataCollector;
  AppConfig appConfig;
  if (dataCollector.Initialize(appConfig)) {
    dataCollector.Start();
  }
}
