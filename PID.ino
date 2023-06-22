
#include "max6675.h"

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;

int time = 200;
int Ku = 6;
int Tu = 35;
int Kp = .2*Ku;
int Ti = .5*Tu;
int Td = .33*Tu; 
int proportional = 0;
int integral = 0;
int derivative = 0;
float u = 0;
int ERROR = 0;
int target = 99;
int out = 3;
int a = 0;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setup() {
  Serial.begin(9600);
  pinMode(out, OUTPUT);

  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);
  a = thermocouple.readCelsius();
}

void loop() {
  // basic readout test, just print the current temp

  //proportional
    proportional = (target - thermocouple.readCelsius());

  //integral
    ERROR += (target - thermocouple.readCelsius());
    integral = (1/Ti)*ERROR;

  //derivative
  int b = thermocouple.readCelsius();

  derivative = Td*(b-a)/time;

  a = b;

  u = Kp*(proportional + integral + derivative);


  if (u > 0){
    digitalWrite(3, HIGH);
  }else{
    digitalWrite(3, LOW);

  
  }
  Serial.print("C = "); 
  Serial.println(thermocouple.readCelsius());
  Serial.println(u);

  u = 0;
  
 
  // For the MAX6675 to update, you must delay AT LEAST 250ms between reads!
  delay(time);
}