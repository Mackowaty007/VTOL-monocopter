#include <Wire.h>
#include <Servo.h>

#define SERVO_INPUT_MIN 1070
#define SERVO_INPUT_MAX 2100

Servo myservo1;
Servo myservo2;
Servo myservo3;

//accelerometer / gyro setup
//int MPUaddress = 0x68;
//float accelX, accelY, accelZ;

void setup() {
  pinMode(9,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);

  myservo1.attach(3);
  myservo2.attach(5);
  myservo3.attach(6);
  /*
  Wire.begin(); //initiatise the wire library and join I2C bus as master device
  Wire.beginTransmission(MPUaddress); // transmit to device at MPUaddress
  Wire.write(0x6B); // access the power management register PWR_MGMT_1
  Wire.write(0); // set to zero to wake the MPU-6050
  Wire.endTransmission(true); // end the transmission
  */
  Serial.begin(115200);
}


void loop() {
  //read reciver signal
  int servoIn1 = pulseIn(9,HIGH);
  int servoIn2 = pulseIn(10,HIGH);
  int servoIn3 = pulseIn(11,HIGH);

  int yawValue   = (((float)servoIn1 - SERVO_INPUT_MIN) / (SERVO_INPUT_MAX-SERVO_INPUT_MIN) ) * 180 - 90;
  int pitchValue = (((float)servoIn2 - SERVO_INPUT_MIN) / (SERVO_INPUT_MAX-SERVO_INPUT_MIN) ) * 180 - 90;
  int rollValue  = (((float)servoIn3 - SERVO_INPUT_MIN) / (SERVO_INPUT_MAX-SERVO_INPUT_MIN) ) * 180 - 90;

  //set the value to be in between
  myservo1.write(90+rollValue/3-pitchValue*cos(60)/3 + yawValue*cos(60)/3 );
  myservo2.write(90+rollValue/3+pitchValue*cos(60)/3 - yawValue*cos(60)/3 );
  myservo3.write(90+rollValue/3                      + yawValue/3 );

  Serial.print("pitch: ");
  Serial.println(pitchValue);
  Serial.print("yaw: ");
  Serial.println(yawValue);
  Serial.print("roll: ");
  Serial.println(rollValue);

  //Gyro stuff
  /*
  Wire.beginTransmission(MPUaddress);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPUaddress, 6, true);
  //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  accelX = (Wire.read() << 8 | Wire.read()) / 16384.0; // X-axis value
  accelY = (Wire.read() << 8 | Wire.read()) / 16384.0; // Y-axis value
  accelZ = (Wire.read() << 8 | Wire.read()) / 16384.0; // Z-axis value
  Serial.println(accelX);
  Serial.println(accelY);
  Serial.println(accelZ);
/*deprint servo positions
  Serial.println("values");
  Serial.println((((float)servoIn1 - SERVO_INPUT_MIN) / (SERVO_INPUT_MAX-SERVO_INPUT_MIN) ) * 180);
  Serial.println((((float)servoIn2 - SERVO_INPUT_MIN) / (SERVO_INPUT_MAX-SERVO_INPUT_MIN) ) * 180);
  Serial.println((((float)servoIn3 - SERVO_INPUT_MIN) / (SERVO_INPUT_MAX-SERVO_INPUT_MIN) ) * 180);
  delay(1);
*/
}
