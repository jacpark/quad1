#include <Servo.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

int value = 0; // set values you need to zero
int StAngleX = 0;
int StAngleY = 0;
int LFspeed = 0;
int RFspeed = 0;
int LRspeed = 0;
int RRspeed = 0;

//create servo-object
Servo firstESC, secondESC, thirdESC, fourthESC; 
  int pos = 0; //Sets position variable

void arm(){

setSpeed(0); //Sets speed variable delay(1000);

}

void setSpeed(int speed){
int angle = map(speed, 0, 100, 0, 180); //Sets servo positions to different speeds 
firstESC.write(angle);
}
void setSpeed2(int speed){
  int angle = map(speed, 0, 100, 0, 180);
  secondESC.write(angle);
}
void setSpeed3(int speed){
  int angle = map(speed, 0, 100, 0, 180);
  thirdESC.write(angle);
}
void setSpeed4(int speed){
  int angle = map(speed, 0, 100, 0, 180);
  fourthESC.write(angle);
}
void tiltForward(speed){
  LRspeed = speed;
  RRspeed = speed;
  while (mpu6050.getAngleX() > StAngleX){
    LRspeed = LRspeed - 5;
    RRspeed = RRspeed - 5;
    setSpeed2(LRspeed);
    setSpeed3(RRspeed);
    if (LFspeed < 70) 
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  firstESC.attach(11);    // attached to pin 11
  secondESC.attach(10);
  thirdESC.attach(9);
  fourthESC.attach(6);
  arm();
}

void loop() {
mpu6050.update();
bool flying = false;

if (flying == false){
  StAngleX = mpu6050.getAngleX();
  StAngleY = mpu6050.getAngleY();
  flying = true;
}

int speed = 0; //Implements speed variable
for(speed = 0; speed <= 70; speed += 5 ) { //Cycles speed up to 70% power for 1 second
setSpeed(speed); //Creates variable for speed to be used in in for loop
setSpeed2(speed);
setSpeed3(speed);
setSpeed4(speed);
delay(1000);
}
while (flying == true){
if (mpu6050.getAngleX() > StAngleX){
  speed = speed - 5;
  setSpeed(speed);
  setSpeed4(speed);
  delay(1000);
}
if (mpu6050.getAngleX() < StAngleX){
  speed = speed - 5;
  setSpeed2(speed);
  setSpeed3(speed);
  delay(1000);
}
  mpu6050.update();
}
delay(4000); //Stays on for 4 seconds
for(speed = 70; speed > 0; speed -= 5) { // Cycles speed down to 0% power for 1 second
setSpeed(speed);
setSpeed2(speed);
setSpeed3(speed);
setSpeed4(speed);
delay(1000);
}

setSpeed(0); //Sets speed variable to zero no matter what
setSpeed2(0);
setSpeed3(0);
setSpeed4(0);
delay(1000); //Turns off for 1 second
}
