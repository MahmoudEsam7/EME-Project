#define __STM32F1__
#include <PRDC_ServoHT.h>

ServoHT servoLifter;   // create servo object to control a servo
ServoHT servoGripper;  // create another servo object for gripper
ServoHT servoRotor;    // create another servo object for rotor joint
// Macros Section 
#define ENA               PB1
#define ENB               PB0
#define IN1               PA7
#define IN2               PA6
#define IN3               PA5
#define IN4               PA4
#define TRIGGER_PIN       23
#define ECHO_PIN          24
#define SERVO_LIFTER_PIN  PB9
#define SERVO_GRIPPER_PIN PB8
#define SERVO_ROTOR_PIN   PB7   
#define OPEN_ANGLE        0
#define CLOSE_ANGLE       180
#define UP_ANGLE          130
#define MID_ANGLE         60
#define DOWN_ANGLE        20
#define GREEN_ANGLE       20
#define BLUE_ANGLE        0
#define HOME_ANGLE        180
#define COLOR_BLUE        1
#define COLOR_GREEN       2
#define COLOR_NULL        0
/******************************************************************* Macros Section Ends *******************************************************************/
/******************************************************************* Function Declaration*******************************************************************/
void Forward();
void Backward();
void Right();
void Left();
void Stop();
void servoUp(void);
void servoDown(void);
void servoMid(void);
void gripperOpen(void);
void gripperClose(void);
int calculateDistance(void);
void servoRotate(uint8_t color);
/***************************************************************** Function Declaration Ends*****************************************************************/

// Global Variabels
long duration = 0;
int distance = 0;
uint8_t color = 0;

void setup() {
  // Init Pin Modes
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  // pinMode(TRIGGER_PIN, OUTPUT); 
  // pinMode(ECHO_PIN, INPUT); 
  
  // // Init Servos
  servoLifter.attach(SERVO_LIFTER_PIN);
  servoGripper.attach(SERVO_GRIPPER_PIN);
  servoLifter.write(MID_ANGLE);
  servoGripper.write(OPEN_ANGLE);
  servoRotor.attach(SERVO_ROTOR_PIN);
  servoRotor.write(HOME_ANGLE);
  Serial.begin(115200);
  Serial1.begin(115200);

}

void loop() {

  // int distan = calculateDistance();
  // if (distan < 9){
    // servoDown();
    // delay(10);
    // gripperClose();
    // delay(10);
    // servoUp();
    // servoRotate(color);
    // delay(1000);
    // gripperOpen();
    // delay(5);
    // servoRotate(COLOR_NULL);
  // }
  while (Serial1.available() > 0) {
    char s = Serial1.read();
    Serial.print(s);

    switch (s) {
      case 'F':
        Forward();
        break;
      case 'B':
        Backward();
        break;
      case 'L':
        Left();
        break;
      case 'R':
        Right();
        break;
      case 'S':
        Stop();
        break;
      case 'G':
        color = COLOR_GREEN;
        break;
      case 'P':
        color = COLOR_BLUE;
        break;
      case 'O':
        gripperOpen();
        break;
      case 'C':
        gripperClose();
        break;
      case 'U':
        servoUp();
        break;
      case 'D':
        servoDown();
        break; 
      case 'M':
        servoMid();
        break;  
      case '0':
        servoRotate(COLOR_NULL);
        break;
      case '1':
        servoRotate(COLOR_GREEN);
        break;       
      case '2':
        servoRotate(COLOR_BLUE);
        break;
    }
  }
}

void Forward() {
  analogWrite(ENA, 250);
  analogWrite(ENB, 250);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void Backward() {
  analogWrite(ENA, 250);
  analogWrite(ENB, 250);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void Right() {
  analogWrite(ENA, 250);
  analogWrite(ENB, 250);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
void Left() {
  analogWrite(ENA, 250);
  analogWrite(ENB, 250);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void Stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

void servoUp(void){
  servoLifter.write(UP_ANGLE);
}

void servoDown(void){
  servoLifter.write(DOWN_ANGLE);
}

void servoMid(void){
  servoLifter.write(MID_ANGLE);
}
void gripperOpen(void){
  servoGripper.write(OPEN_ANGLE);
}

void gripperClose(void){
  servoGripper.write(CLOSE_ANGLE);
}

void servoRotate(uint8_t color){
  if (color == COLOR_GREEN){
    servoRotor.write(GREEN_ANGLE);
  }else if(color == COLOR_BLUE){
    servoRotor.write(BLUE_ANGLE);
  }else{
    servoRotor.write(HOME_ANGLE);
  }
}

int calculateDistance(void){
    // Clears the trigPin
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  return distance;
}