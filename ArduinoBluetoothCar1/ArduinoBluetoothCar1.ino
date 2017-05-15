// heavily borrowed from http://www.instructables.com/id/Android-controlled-car-for-beginners-MIT-app-inven/

const int trigPin = 2;
const int echoPin = 3;

int speedPin_M1 = 5;     //M1 Speed Control
int speedPin_M2 = 6;     //M2 Speed Control
int directionPin_M1 = 4;     //M1 Direction Control
int directionPin_M2 = 7;     //M1 Direction Control

const int speedMotor = 140;

int input = '0'; //input to be used
String input2; //variable for string input


void setup() {
  sensorSetup();
  motorSetup();
  Serial.begin(9600);
}

void loop() {

  if (Serial.available() > 0)
  {
    input = Serial.read();
  }

  // forward
  if (input == '1')
  {
    carAdvance( speedMotor, speedMotor);
  }

  //back
  else if (input == '2')
  {
    carBack(speedMotor, speedMotor);
  }

  //right
  else if (input == '3')
  {
    carTurnRight(speedMotor, speedMotor);
  }

  //left
  else if (input == '4')
  {
    carTurnLeft(speedMotor, speedMotor);
  }

  //default state
  else if (input == '0')
  {
    carStop();
  }

  //string to be displayed on lcd
  else if (input == '5')

  { Serial.flush();
    while (!Serial.available()) ;
    input2 = Serial.readString();
    //  strng = input2.length();
    //    lcd.clear();
    delay(10);
    //    lcd.setCursor(0, 0);
    //    lcd.print(input2.c_str());
    //    delay(1000);
    //    lcd.clear();
    input = '0';
  }


  //s
  else if (input == '6')

  {
    input = '0';
  }

  //ultrasound sensor
  else if (input = '7')
  {
    int distance = ultraSound();
    Serial.print("Distance= ");
    Serial.print(distance);
    Serial.print("cm  ");
    delay(800);
  }
}

void sensorSetup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

int ultraSound( void ) {
  long duration;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  int distance = (duration / 2) / 29.1;
  if (distance > 100) distance = 0;
  return (int) distance;
}

void motorSetup() {
   pinMode(speedPin_M1, OUTPUT);
  pinMode(speedPin_M2, OUTPUT);
  pinMode(directionPin_M1, OUTPUT);
  pinMode(directionPin_M2, OUTPUT);
}

void carStop() {                //  Motor Stop
  digitalWrite(speedPin_M2, 0);
  digitalWrite(directionPin_M1, LOW);
  digitalWrite(speedPin_M1, 0);
  digitalWrite(directionPin_M2, LOW);
}

void carAdvance(int leftSpeed, int rightSpeed) {       //Move forward
  analogWrite (speedPin_M2, leftSpeed);             //PWM Speed Control
  digitalWrite(directionPin_M1, HIGH);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, HIGH);
}

void carBack(int leftSpeed, int rightSpeed) {     //Move backward
  analogWrite (speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, LOW);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, LOW);
}

void carTurnRight(int leftSpeed, int rightSpeed) {           //Turn Left
  analogWrite (speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, LOW);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, HIGH);
}

void carTurnLeft(int leftSpeed, int rightSpeed) {         //Turn Right
  analogWrite (speedPin_M2, leftSpeed);
  digitalWrite(directionPin_M1, HIGH);
  analogWrite (speedPin_M1, rightSpeed);
  digitalWrite(directionPin_M2, LOW);
}


