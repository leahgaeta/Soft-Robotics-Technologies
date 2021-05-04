/*****
  ME 568 Final Project Prototype: Capacitive sensor sock with laminar jamming stiffening mechanism.
  Leah T. Gaeta
  2021 - 04 - 25
*****/

// Libraries
#include <Capacitor.h>
#include <CapacitorLite.h>
#include <MeanFilterLib.h>

MeanFilter<float> meanFilter(10); // Moving average with window = 10

int CAP_TERMINAL_A = 7;
int CAP_TERMINAL_B = A2; 
//int solenoidPin = 9; // Solenoid output pin
int pumpPin = 2;

CapacitorLite cap1(CAP_TERMINAL_A, CAP_TERMINAL_B);

float rawCapacitance;
float meanCapacitance; 

void setup() {
  //pinMode(solenoidPin, OUTPUT); // Sets solenoid pin as output here
  pinMode(pumpPin, OUTPUT);
  Serial.begin(9600); // Serial transmission rate
}

void loop() {
  rawCapacitance = cap1.Measure(); 
  meanCapacitance = meanFilter.AddValue(rawCapacitance); // calculates moving average, removes *some* noise
  Serial.println(meanCapacitance); 
  
  // Test for threshold capacitance to activate LJ stiffening
  if (meanCapacitance > 1100){
    //digitalWrite(solenoidPin, HIGH); // Solenoid on
    //digitalWrite(solenoidPin, HIGH);      //Switch Solenoid ON
    digitalWrite(pumpPin, HIGH);
    //delay(2000);  //Wait 2 Seconds
  }
  else{
    //digitalWrite(solenoidPin, LOW);       //Switch Solenoid OFF
    digitalWrite(pumpPin, LOW);
    //delay(2000);                          //Wait 2 Seconds
  }
}
