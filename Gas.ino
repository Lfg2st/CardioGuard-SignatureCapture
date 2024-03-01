#include <SoftwareSerial.h>
SoftwareSerial mySerial(3,2);
char msg;
char call;
int AlcoholPin=8; 
int Threshold = 600;
int AlcoholLevel;


void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);// Setting the baud rate of Serial Monitor (Arduino)
  Serial.println("SOS");
  mySerial.println("ATD+918951241114;");
}

void loop()
{
  AlcoholLevel=digitalRead(8);
  Serial.print("MQ-3:");
  Serial.println(AlcoholLevel);
  delay(1000);
  if(AlcoholLevel==0)
  {
    Serial.println("SOSS");
    delay(1000);
    mySerial.println("ATD+918951241114;");
    SendMessage(); 
    Serial.println("Calling  ");
    delay(10000); // wait for 50 seconds...
    mySerial.println("ATH"); //hang up
    Serial.println("Hangup Call"); 
  }
}

void SendMessage()
{
  
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second

  mySerial.println("AT+CMGS=\"+918951241114\"\r"); // Replace x with mobile number
  delay(1000);

  mySerial.println("Attender is Drunk");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}