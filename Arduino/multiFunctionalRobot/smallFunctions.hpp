#define ULTRASONIC_PIN_TRIGGER 8
#define ULTRASONIC_PIN_ECHO 9

#define RIGHT_INFRARED_PIN 5
#define LEFT_INFRARED_PIN 4

int getselectedMode(int buttonPin){
  int mode = 0;
  int timer = 0;

  while(mode == 0 || timer < 8000){
    delay(1);
    if(digitalRead(buttonPin) == HIGH){
      delay(100);
      ++mode;
    }
    timer++;
    if(mode == 0){timer = 0;}
  }
  return mode;
}

long readUltrasonicDistance(int trigger, int echo){
  pinMode(trigger, OUTPUT);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigger, LOW);
  pinMode(echo, INPUT);
  return pulseIn(echo,HIGH);
}