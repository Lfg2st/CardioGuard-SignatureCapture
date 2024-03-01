

#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
    Serial.begin(9600);
    while (!Serial);

    if (!mlx.begin()) {
        Serial.println("Error connecting to MLX sensor. Check wiring.");
        while (1);
    };
}

void sendSensorData()
{
    float ambientTempC = mlx.readAmbientTempC();
    float objectTempC = mlx.readObjectTempC();
    float ambientTempF = mlx.readAmbientTempF();
    float objectTempF = mlx.readObjectTempF();

    Serial.println(objectTempF);
}

void loop() {


    sendSensorData();
    delay(500); 
}