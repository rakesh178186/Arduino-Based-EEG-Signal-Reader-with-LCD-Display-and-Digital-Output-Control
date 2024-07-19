// Include libraries
#include <OneWire.h>
#include <DallasTemperature.h>

// Constants
const int pResistor = A0;   // Photoresistor pin to Arduino analog A0 pin
const int buzzer = 7;       // Buzzer pin to Arduino pin 7
const int gasSensor = A1;   // Gas sensor MQ-5 signal pin to Arduino analog A1 pin
const int hLight = 8;       // Helmet light to Arduino pin 8
const int redLed = 9;       // Red led pin to Arduino pin 9

// Temp sensor DS18B20 to Arduino pin 2
#define ONE_WIRE_BUS 11
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Change values if you want
////////////////////
int dTemp = 20;   // Default temperature threshold
int dGas = 400;   // Default dangerous gas value (0-1023)
int bValue = 10;  // Brightness value (0-1023)
///////////////////

// Variables
int gasValue;
int lightValue;
int tempValue;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(buzzer, OUTPUT);
  pinMode(hLight, OUTPUT);
  pinMode(redLed, OUTPUT);
  sensors.begin();
  delay(60000); // MQ-5 warm-up delay (60sec)
}

void loop() {
  // Read and store values to additional variables 
  gasValue = analogRead(gasSensor);
  lightValue = analogRead(pResistor);
  sensors.requestTemperatures();  
  tempValue = sensors.getTempCByIndex(0); // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire

  // Debug statements to monitor light value and brightness threshold
  Serial.print("Light Value: ");
  Serial.println(lightValue);
  Serial.print("Brightness Threshold: ");
  Serial.println(bValue);

  // Room/area light - brightness
  if (lightValue > bValue) {
    digitalWrite(hLight, LOW); // Turning off helmet light
  } else {
    digitalWrite(hLight, HIGH); // Turning on helmet light
  }

  // Dangerous gas detection
  if (gasValue >= dGas + 100 && gasValue < dGas + 200) {
    // Add your code for gas detection here
  } 
  // Add other gas detection conditions as needed
  
  // High temperature detection
  if (tempValue >= dTemp + 15 && tempValue < 16) {
    // Add your code for high temperature detection here
  } 
  // Add other temperature detection conditions as needed
}
