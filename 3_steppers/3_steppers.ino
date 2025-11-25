#include <Stepper.h>
#include <math.h>

const int stepsPerRevolution = 2048; 

int ls1 = 3;
int suck = 6;
int release = 7;

Stepper motor1(stepsPerRevolution, 22, 24, 23, 25);
Stepper motor2(stepsPerRevolution, 26, 28, 27, 29);
Stepper motor3(stepsPerRevolution, 30, 32, 31, 33); 

float theta1 = 0;
float theta2 = -20;
float theta3 = 0;
float tarTheta1 = 0;
float tarTheta2 = 0;
float tarTheta3 = 0;

void setup() {
  motor1.setSpeed(10);
  motor2.setSpeed(10);
  motor3.setSpeed(10);

  pinMode(ls1, INPUT);

  pinMode(suck, OUTPUT);
  pinMode(release, OUTPUT);

  digitalWrite(suck, LOW);
  digitalWrite(release, HIGH);

  homePosition();

  moveMotors(-179, -560, 0);
  moveMotors(0, 0, 1124);
  digitalWrite(suck, HIGH);
  digitalWrite(release, LOW);
  delay(500);
  moveMotors(0, 0, -1024);

  moveMotors(240, 0, 0);
  moveMotors(0, 1000, 0);
  moveMotors(0, 0, 1024);
  digitalWrite(suck, LOW);
  digitalWrite(release, HIGH);
  delay(500);
  moveMotors(0, 0, -1024);

  moveMotors(-560, 0, 0);
  moveMotors(0, -390, 0);
  moveMotors(0, 0, 1124);
  digitalWrite(suck, HIGH);
  digitalWrite(release, LOW);
  delay(500);
  moveMotors(0, 0, -1024);

  moveMotors(500, 0, 0);
  moveMotors(0, 210, 0);
  moveMotors(0, 0, 1024);
  digitalWrite(suck, LOW);
  digitalWrite(release, HIGH);
  delay(500);
  moveMotors(0, 0, -1024);
}

void loop() {

}

void moveMotors(long s1, long s2, long s3) {
  long steps1 = abs(s1); 
  long steps2 = abs(s2);
  long steps3 = abs(s3);

  int dir1;
  int dir2;
  int dir3;

  if (s1 >= 0) {
    dir1 = 1;
  } else {
    dir1 = -1;
  }
  if (s2 >= 0) {
    dir2 = 1;
  } else {
    dir2 = -1;
  }
  if (s3 >= 0) {
    dir3 = 1;
  } else {
    dir3 = -1;
  }

  long maxSteps = max(steps1, max(steps2, steps3));

  long stepCounter1=0;
  long stepCounter2=0;
  long stepCounter3=0;
  for (int i = 0; i < maxSteps; i++) {
    if ((i * steps1) / maxSteps > stepCounter1) {
      motor1.step(dir1);
    stepCounter1++;
    }
    if ((i * steps2) / maxSteps > stepCounter2) {
      motor2.step(dir2);
      stepCounter2++;
    }
    if ((i * steps3) / maxSteps > stepCounter3) {
      motor3.step(dir3);
      stepCounter3++;
    }
    delay(2); 
  }
}

void homePosition() {
  while(digitalRead(ls1) != HIGH){
    motor1.step(-1);
  }
  moveMotors(-750, 0, 0);
  moveMotors(400, 0, 0);
  moveMotors(0, -1524, 0);
  moveMotors(0, 820, 0);
}