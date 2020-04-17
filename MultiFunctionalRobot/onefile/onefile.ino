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

//#include <Arduino/Servo/src/Servo.h>
#include <Servo.h> // use this on real arduino

//#include <Arduino/SoftwareSerial/src/SoftwareSerial.h>
#include <SoftwareSerial.h> //Use this on real Arduino

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


void setup(){
  pinMode(righSpeed, OUTPUT);
  pinMode(leftSpeed, OUTPUT);

  pinMode(righClockWise, OUTPUT);
  pinMode(righAntiClockWise, OUTPUT);

  pinMode(leftClockWise, OUTPUT);
  pinMode(leftAntiClockWise, OUTPUT);

  pinMode(righInfraSensor,INPUT);
  pinMode(leftInfraSensor,INPUT);
  pinMode(floorInfraSensor,INPUT);

  pinMode(button,INPUT);
  Serial.begin(9600);
  bluetoothAS.begin(9600);

  ultraServo.attach(servopin);
  ultraServo.write(90);

}

void loop(){

  if(digitalRead(button) == HIGH){
    robo.botao++;
    delay(1000);
  }

  int aux{0}; //Variavel axuliar para o modo Sumô

  switch (robo.botao){
    case 0: //Sumô

      if( digitalRead(righInfraSensor) == LOW || digitalRead(leftInfraSensor) == LOW){
        robo.goBack();
        aux++;
      }

      if( digitalRead(floorInfraSensor) == LOW ){
        robo.goForward();
        aux++;
      }

      if( robo.readUDistance(8,9) < 19000 ){
        robo.goForward();
        aux++;
      }

      if(aux == 0){
        robo.goForward(100,150);
      }else{
        aux = 0;
      }

    break;
    case 1: //Seguidor de Linha

      if( digitalRead(righInfraSensor) == LOW && digitalRead(leftInfraSensor) == LOW ){
        robo.goForward();
      }

      if( digitalRead(righInfraSensor) == HIGH && digitalRead(leftInfraSensor) == HIGH){
        robo.goForward();
      }

      if( digitalRead(righInfraSensor) == HIGH && digitalRead(leftInfraSensor) == LOW){
        robo.goForward(200,255);
      }

      if( digitalRead(righInfraSensor) == LOW && digitalRead(leftInfraSensor) == HIGH){
        robo.goForward(255,200);
      }

    break;
    case 2: //Carro autonomo

      while(robo.readUDistance(8,9) < 5000){

        int f = robo.readUDistance(8,9);
        ultraServo.write(180);
        delay(1000);
        int l = robo.readUDistance(8,9);
        ultraServo.write(0);
        delay(1000);
        int r = robo.readUDistance(8,9);
        ultraServo.write(90);
        delay(1000);

        if(f > l && f > r){
          robo.goForward();
        }
        if(r > f && r > l){
          robo.turnRigh();
        }
        if(l > f && l > r){
          robo.turnLeft();
        }

        delay(1000);

      }

      robo.goForward();

    break;
    case 3: //Controle Remoto

      while(bluetoothAS.available()){

        if(bluetoothAS.read() == 'F'){
          robo.goForward();
        }

        if(bluetoothAS.read() == 'B'){
          robo.goBack();
        }

        if(bluetoothAS.read() == 'R'){
          robo.turnRigh();
        }

        if(bluetoothAS.read() == 'L'){
          robo.turnLeft();
        }

        if( bluetoothAS.read() == 'S' || bluetoothAS.read() == 'S' ){
          robo.stopAll();
        }

      }

    break;
    default:

    robo.botao = 0;

    break;
  }

  Serial.print("Mode:");
  Serial.print(robo.botao);
  Serial.print("\n");
  delay(1000);

}




Robo::Robo(){

}

void Robo::stopAll(){
  digitalWrite(righClockWise, LOW);
  digitalWrite(leftClockWise, LOW);

  digitalWrite(righAntiClockWise, LOW);
  digitalWrite(leftAntiClockWise, LOW);

  analogWrite(leftSpeed, 0);
  analogWrite(righSpeed, 0);

  delay(100);
}

void Robo::goForward(int Rspeed, int Lspeed){

  digitalWrite(righAntiClockWise, LOW);
  digitalWrite(leftAntiClockWise, LOW);

  delay(100);

  analogWrite(leftSpeed, Lspeed);
  analogWrite(righSpeed, Rspeed);

  digitalWrite(righClockWise, HIGH);
  digitalWrite(leftClockWise, HIGH);
}

void Robo::goBack(int Rspeed, int Lspeed){

  digitalWrite(righClockWise, LOW);
  digitalWrite(leftClockWise, LOW);

  delay(100);

  analogWrite(leftSpeed, Lspeed);
  analogWrite(righSpeed, Rspeed);


  digitalWrite(righAntiClockWise, HIGH);
  digitalWrite(leftAntiClockWise, HIGH);
}

void Robo::brake(){

  digitalWrite(righAntiClockWise, HIGH);
  digitalWrite(leftAntiClockWise, HIGH);

  digitalWrite(righClockWise, HIGH);
  digitalWrite(leftClockWise, HIGH);

  analogWrite(leftSpeed, 255);
  analogWrite(righSpeed, 255);
}

void Robo::turnLeft(){

  digitalWrite(leftClockWise, LOW);
  digitalWrite(righAntiClockWise, LOW);

  delay(100);

  digitalWrite(leftAntiClockWise,HIGH);
  digitalWrite(righClockWise,HIGH);

  analogWrite(leftSpeed, 100);
  analogWrite(righSpeed, 100);

}
void Robo::turnRigh(){
  digitalWrite(righClockWise, LOW);
  digitalWrite(righAntiClockWise, LOW);

  delay(100);

  digitalWrite(leftClockWise,HIGH);
  digitalWrite(righAntiClockWise,HIGH);

  analogWrite(leftSpeed, 100);
  analogWrite(righSpeed, 100);

  //delay(50);
}

long Robo::readUDistance(int trigger, int echo){
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echo,HIGH);
}
