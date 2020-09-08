//desnecessario quando for rodar no arduino
#define A0 14
#define A1 15
#define A2 16
#define A3 17
#define A4 18
#define A5 19

#include<Arduino/Arduino.h>

class SSrial{
public:
  SSrial();
  void begin(int num){
    num=0;
  }
  void print(auto qualquercoisa){

  }
}Serial;
//descessario quando for rodar no arduino


#define righSpeed 6
#define leftSpeed 5

#define righClockWise 13
#define righAntiClockWise 12

#define leftClockWise 11
#define leftAntiClockWise 10

#define triggerPin 8
#define echoPin 9

#define righInfraSensor 5
#define leftInfraSensor 4
#define floorInfraSensor A5

#define button 2

#define servopin 7

//frontUltraSensor echo = 9 and trigger = 8

#define RX A0
#define TX A1

#include <Arduino/Servo/src/Servo.h>
//#include <Servo.h> // use this on real arduino

#include <Arduino/SoftwareSerial/src/SoftwareSerial.h>
//#include <SoftwareSerial.h> //Use this on real Arduino

SoftwareSerial bluetoothAS(RX, TX); //Bluetooth Artificial Serial
Servo ultraServo;

class Robo{
public:

  int botao{0};

  Robo();

  void stopAll();
  void goForward(int Rspeed = 255, int Lspeed = 255);
  void goBack(int Rspeed = 255, int Lspeed = 255);
  void brake();
  void turnLeft();
  void turnRigh();
  long readUDistance(int trigger, int echo); //Read Ultrasonic Distance

}robo;
