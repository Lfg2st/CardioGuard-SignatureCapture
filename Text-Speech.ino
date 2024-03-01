#include <DFRobotDFPlayerMini.h>

#include <SoftwareSerial.h>

#include <Wire.h>

DFRobotDFPlayerMini Player;
void printDetail(uint8_t type, int value);
SoftwareSerial mySerial(9, 10);

int flexRead, flexRead2, flexRead3, flexRead4, flexRead5;

void setup() {
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  Serial.begin(115200);
  mySerial.begin(9600);
  Serial.println();
  Serial.println("Initializing DFPlayer..");

  if (!Player.begin(mySerial)) {
    Serial.println("Unable to begin; please recheck the connection.");
    while (true);
  }
  Serial.println("DFPlayer Mini online.");
  Player.begin(mySerial);
  Player.outputDevice(DFPLAYER_DEVICE_SD);
  Player.volume(30);
  Serial.print("Amount of files installed: ");
  Serial.println(Player.readCurrentFileNumber());
  delay(1000);
}

void loop() {
  flexRead = analogRead(A1);
  flexRead2 = analogRead(A2);
  flexRead3 = analogRead(A3);
  flexRead4 = analogRead(A4);
  flexRead5 = analogRead(A5);

  Serial.print("flex1: ");
  Serial.println(flexRead);
  Serial.print("flex2: ");
  Serial.println(flexRead2);
  Serial.print("flex3: ");
  Serial.println(flexRead3);
  Serial.print("flex4: ");
  Serial.println(flexRead4);
  Serial.print("flex5: ");
  Serial.println(flexRead5);
  Serial.println();

  if (flexRead < 987) {
    Serial.println("Yes");
    Serial.print("Amount of files installed: ");
    Serial.println(Player.readCurrentFileNumber());
    Player.play(1);
    delay(5000);
  }

  else if (flexRead2 < 982) {
    Serial.println("No");
    Serial.print("Amount of files installed: ");
    Serial.println(Player.readCurrentFileNumber());
    Player.play(3);
    delay(5000);
  }

  else if (flexRead3 < 989) {
    Serial.println("Please give me water");
    Serial.print("Amount of files installed: ");
    Serial.println(Player.readCurrentFileNumber());
    Player.play(5);
    delay(8000);
    
  }

  else if (flexRead4 < 991) {
    Serial.println("Please give me food");
    Serial.print("Amount of files installed: ");
    Serial.println(Player.readCurrentFileNumber());
    Player.play(7);
    delay(8000);
  }

  else if (flexRead5 < 983) {
    Serial.println("I feel sick");
    Serial.print("Amount of files installed: ");
    Serial.println(Player.readCurrentFileNumber());
    Player.play(9);
    delay(9000);
  }
  delay(1000);
}