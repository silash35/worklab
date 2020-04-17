//desnecessario quando for rodar no arduino
#include <control.hpp>
//desnecessario quando for rodar no arduino

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
