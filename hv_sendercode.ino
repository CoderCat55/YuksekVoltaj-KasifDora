#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

// Define the struct outside of any functions
struct SensorData {
    int x4;
    int x5;
};

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  SensorData sensor;  // Create an instance of the struct
  
  // Read analog values
  sensor.x4 = map(analogRead(A4), 0, 1023, 0, 255);
  sensor.x5 = map(analogRead(A5), 0, 1023, 0, 255);
  
  // Send the struct data
  radio.write(&sensor, sizeof(sensor));
  
  Serial.println("meow");
  delay(200);
}