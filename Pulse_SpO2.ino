#define BLYNK_TEMPLATE_ID "TMPL3BMj8371W"
#define BLYNK_TEMPLATE_NAME "Oakridge Codefest"

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <BlynkSimpleEsp8266.h>

#define REPORTING_PERIOD_MS     1000

PulseOximeter pox;


float BPM, SpO2;
uint32_t tsLastReport = 0;

char auth[] = "ioBRI8I7FtCdrxMIEJfgdPrcSZMvEW_Y";
char ssid[] = "Epik wifi";
char pass[] = "stonkstonks";

BlynkTimer timer;

void onBeatDetected() {
    Serial.println("Beat!");
}

void setup() {
    Serial.begin(9600);
    Blynk.begin(auth, ssid, pass);

    Serial.print("Initializing pulse oximeter..");

    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }


  // Configure sensor to use 7.6mA for LED drive
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

    // Register a callback routine
    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {

  Blynk.run();
  timer.run();
  
    // Read from the sensor
    pox.update();

    // Grab the updated heart rate and SpO2 levels
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");

        tsLastReport = millis();

        Blynk.virtualWrite(V3, pox.getHeartRate());
        Blynk.virtualWrite(V2, pox.getSpO2());
    }
}