#define BLYNK_TEMPLATE_ID "TMPL3BMj8371W"
#define BLYNK_TEMPLATE_NAME "Oakridge Codefest"
#define BLYNK_AUTH_TOKEN "ioBRI8I7FtCdrxMIEJfgdPrcSZMvEW_Y"

#include <Wire.h>
#include <SoftwareSerial.h>
#include <BlynkSimpleEsp8266.h>
#include <Blynk.h>

char auth[] = "ioBRI8I7FtCdrxMIEJfgdPrcSZMvEW_Y";
char ssid[] = "Epik wifi";
char pass[] = "stonkstonks";

const int ecgPin = A0;

long instance1=0, timer;

double hrv =0, hr = 72, interval = 0;

int value = 0, count = 0;  

bool flag = 0;

#define threshold 100 // to identify R peak

#define timer_value 10000 // 10 seconds timer to calculate hr

void setup() {
  // initialize the serial communication:
  Serial.begin(115200);
  pinMode(D0, INPUT); // Setup for leads off detection LO +
  pinMode(D1, INPUT); // Setup for leads off detection LO -
  Blynk.begin(auth, ssid, pass);
  pinMode(ecgPin, INPUT);
  Serial.println("ECG sensor connected to Blynk!");
}

void loop() {
  Blynk.run();
  
    value = analogRead(ecgPin);

    value = map(value, 250, 400, 0, 100); //to flatten the ecg values a bit

    if((value > threshold) && (!flag)) {

      count++;  

      Serial.println("in");

      flag = 1;

      interval = micros() - instance1; //RR interval

      instance1 = micros(); 

    }

  else if((value < threshold)) {

      flag = 0;

    }

   if ((millis() - timer) > 10000) {

      hr = count*2;

      timer = millis();

      count = 0; 

    }

    hrv = hr/60 - interval/1000000;

    Serial.print(hr);

    Serial.print(",");

    Serial.print(hrv);

    Serial.print(",");

    Serial.println(value);

    delay(10);

    Blynk.virtualWrite(V0, hr);

  }
