//desnecessario quando for rodar no arduino
#include<control.hpp>
//desnecessario quando for rodar no arduino

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
