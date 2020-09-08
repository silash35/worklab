#include <Servo.h>
#include <SoftwareSerial.h>

#define MAX_PWM_VALUE 255

#define RIGHT_WHEEL_PIN_SPEED 6
#define LEFT_WHEEL_PIN_SPEED 5

#define RIGHT_WHEEL_PIN_CLOCKWISE 13
#define RIGHT_WHEEL_PIN_ANTICLOCKWISE 12

#define LEFT_WHEEL_PIN_CLOCKWISE 11
#define LEFT_WHEEL_PIN_ANTICLOCKWISE 10

#define SERVO_PIN 7

#define BLUETOOTH_RX A0
#define BLUETOOTH_TX A1

SoftwareSerial bluetooth(BLUETOOTH_RX, BLUETOOTH_TX); //Bluetooth Artificial Serial

class Robot{
  public:
    Servo ultraServo;

    Robot();
    void begin();
    void stopAll();
    void goForward(int rightSpeed = MAX_PWM_VALUE, int leftSpeed = MAX_PWM_VALUE);
    void goBack(int rightSpeed = MAX_PWM_VALUE, int leftSpeed = MAX_PWM_VALUE);
    void brake();
    void turnLeft();
    void turnRight();
}robot;

Robot::Robot(){};

void Robot::begin(){

  pinMode(RIGHT_WHEEL_PIN_SPEED, OUTPUT);
  pinMode(LEFT_WHEEL_PIN_SPEED, OUTPUT);

  pinMode(RIGHT_WHEEL_PIN_CLOCKWISE, OUTPUT);
  pinMode(RIGHT_WHEEL_PIN_ANTICLOCKWISE, OUTPUT);

  pinMode(LEFT_WHEEL_PIN_CLOCKWISE, OUTPUT);
  pinMode(LEFT_WHEEL_PIN_ANTICLOCKWISE, OUTPUT);

  pinMode(ULTRASONIC_PIN_TRIGGER, OUTPUT);
  pinMode(ULTRASONIC_PIN_ECHO, INPUT);

  pinMode(RIGHT_INFRARED_PIN, INPUT);
  pinMode(LEFT_INFRARED_PIN, INPUT);

  pinMode(SERVO_PIN, INPUT);

  bluetooth.begin(9600);

  ultraServo.attach(SERVO_PIN);
  ultraServo.write(90);
}

void Robot::stopAll(){
  digitalWrite(LEFT_WHEEL_PIN_CLOCKWISE, LOW);
  digitalWrite(LEFT_WHEEL_PIN_ANTICLOCKWISE, LOW);

  digitalWrite(RIGHT_WHEEL_PIN_CLOCKWISE, LOW);
  digitalWrite(RIGHT_WHEEL_PIN_ANTICLOCKWISE, LOW);

  analogWrite(RIGHT_WHEEL_PIN_SPEED, 0);
  analogWrite(LEFT_WHEEL_PIN_SPEED, 0);
}

void Robot::goForward(int rightSpeed, int leftSpeed){
  stopAll();

  analogWrite(RIGHT_WHEEL_PIN_SPEED, rightSpeed);
  analogWrite(LEFT_WHEEL_PIN_SPEED, leftSpeed);

  digitalWrite(RIGHT_WHEEL_PIN_CLOCKWISE, HIGH);
  digitalWrite(LEFT_WHEEL_PIN_CLOCKWISE, HIGH);
}

void Robot::goBack(int rightSpeed, int leftSpeed){
  stopAll();

  analogWrite(RIGHT_WHEEL_PIN_SPEED, rightSpeed);
  analogWrite(LEFT_WHEEL_PIN_SPEED, leftSpeed);

  digitalWrite(RIGHT_WHEEL_PIN_ANTICLOCKWISE, HIGH);
  digitalWrite(LEFT_WHEEL_PIN_ANTICLOCKWISE, HIGH);
}

void Robot::brake(){
  digitalWrite(RIGHT_WHEEL_PIN_ANTICLOCKWISE, HIGH);
  digitalWrite(LEFT_WHEEL_PIN_ANTICLOCKWISE, HIGH);

  digitalWrite(RIGHT_WHEEL_PIN_CLOCKWISE, HIGH);
  digitalWrite(LEFT_WHEEL_PIN_CLOCKWISE, HIGH);

  analogWrite(RIGHT_WHEEL_PIN_SPEED, MAX_PWM_VALUE);
  analogWrite(LEFT_WHEEL_PIN_SPEED, MAX_PWM_VALUE);
}

void Robot::turnLeft(){
  stopAll();
  digitalWrite(RIGHT_WHEEL_PIN_CLOCKWISE, HIGH);
  digitalWrite(LEFT_WHEEL_PIN_ANTICLOCKWISE, HIGH);

  analogWrite(RIGHT_WHEEL_PIN_SPEED, MAX_PWM_VALUE);
  analogWrite(LEFT_WHEEL_PIN_SPEED, MAX_PWM_VALUE);
}
void Robot::turnRight(){
  stopAll();
  digitalWrite(RIGHT_WHEEL_PIN_ANTICLOCKWISE, HIGH);
  digitalWrite(LEFT_WHEEL_PIN_CLOCKWISE, HIGH);

  analogWrite(RIGHT_WHEEL_PIN_SPEED, MAX_PWM_VALUE);
  analogWrite(LEFT_WHEEL_PIN_SPEED, MAX_PWM_VALUE);
}
