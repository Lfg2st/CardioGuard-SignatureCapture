#include <OneWire.h>
#include <DallasTemperature.h>


#define REPORTING_PERIOD_MS 1000
#define DS18B20 5


OneWire oneWire(DS18B20);
DallasTemperature sensors(&oneWire);

float bodytemperature;
unsigned long tsLastReport = 0;  

void setup() {
    Serial.begin(115200);
    sensors.begin();
}

void loop() {
    sensors.requestTemperatures();  
    bodytemperature = sensors.getTempCByIndex(0);

    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Body Temperature: ");
        Serial.print(bodytemperature);
        Serial.println("°C");
        tsLastReport = millis();  
    }
}
