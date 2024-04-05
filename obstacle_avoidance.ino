#include <NewPing.h>
#include <Servo.h>
Servo myservo;

//Define constants for motor pins
#define PIN_Motor_PWMA 10 //Right speed control
#define PIN_Motor_PWMB 11 //Left speed control
#define PIN_Motor_A 12//Right side
#define PIN_Motor_B 13//Left side
#define Speed_num 105
float half_speed=(Speed_num/2);

//Define constants for ir pins
#define LIR 7 //pin 3
#define RIR 8 //pin 8

//Define constants for Servo
//#define SERVO_PIN 9
//int distanceRight = 0;
//int distanceLeft = 0;

//Define constants for ultrasonic sensor
#define L_ECHO_PIN 5
#define L_TRIG_PIN 6
#define R_ECHO_PIN 3
#define R_TRIG_PIN 9
#define maximum_distance 200
long t, cm;
int limit;
int right_dist, left_dist;
int duration, distance; // Add types 'duration' and 'distance'.
//NewPing sonar(TRIG_PIN, ECHO_PIN, maximum_distance); //sensor  

//Define constants for linetrack
void setup() {
  Serial.begin(9600);
  //Motors
  pinMode(PIN_Motor_PWMA, OUTPUT);
  pinMode(PIN_Motor_PWMB, OUTPUT);
  pinMode(PIN_Motor_A, OUTPUT);
  pinMode(PIN_Motor_B, OUTPUT);
  //IR sensors
  pinMode(LIR, INPUT);
  pinMode(RIR, INPUT);
  //Servo
  //pinMode(SERVO_PIN, INPUT);
  //myservo.attach(SERVO_PIN);
  //myservo.write(90); //Put servo in the middle to look forward
  
  //Ultrasonic Sensors
  pinMode(L_ECHO_PIN, INPUT);
  pinMode(L_TRIG_PIN, OUTPUT);
  pinMode(R_ECHO_PIN, INPUT);
  pinMode(R_TRIG_PIN, OUTPUT);
  
}

void forward() {
  digitalWrite(PIN_Motor_A, HIGH);
  analogWrite(PIN_Motor_PWMA, Speed_num);

  digitalWrite(PIN_Motor_B, LOW);
  analogWrite(PIN_Motor_PWMB, Speed_num);
}

void backward() {
  digitalWrite(PIN_Motor_A, LOW);
  analogWrite(PIN_Motor_PWMA, Speed_num);

  digitalWrite(PIN_Motor_B, HIGH);
  analogWrite(PIN_Motor_PWMB, Speed_num);
}

void left() {
  digitalWrite(PIN_Motor_A, HIGH);
  analogWrite(PIN_Motor_PWMA, Speed_num);

  digitalWrite(PIN_Motor_B, HIGH);
  analogWrite(PIN_Motor_PWMB, Speed_num);
}

void right() {
  digitalWrite(PIN_Motor_A, LOW);
  analogWrite(PIN_Motor_PWMA, Speed_num);

  digitalWrite(PIN_Motor_B, LOW);
  analogWrite(PIN_Motor_PWMB, Speed_num);
}

void stop_bot(){
  digitalWrite(PIN_Motor_A, LOW);
  analogWrite(PIN_Motor_PWMA, 0);

  digitalWrite(PIN_Motor_B, LOW);
  analogWrite(PIN_Motor_PWMB, 0);
}


int get_left_distance(){ 
  // Clears the trigPin condition
  digitalWrite(L_TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(L_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(L_TRIG_PIN, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  t = pulseIn(L_ECHO_PIN, HIGH);
  // Calculating the distance
  cm = t / 29 / 2;
  //Serial.print("left");
  //Serial.println(cm);
  return cm;
}

int get_right_distance(){ 
  // Clears the trigPin condition
  digitalWrite(R_TRIG_PIN, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(R_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(R_TRIG_PIN, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  t = pulseIn(R_ECHO_PIN, HIGH);
  // Calculating the distance
  cm = t / 29 / 2;
  //Serial.print("right");
  //Serial.println(cm);
  return cm;
}

void loop() { 
  //Edge avoidance code beginning **********************************************************EDGE AVOIDANCE BELOW
  int LIR_sensor = digitalRead(LIR);
  int RIR_sensor= digitalRead(RIR);
  if (!(LIR_sensor) && !(RIR_sensor)){
    // ground detected under both sensors
    // go straight
    forward();
  }
  if (LIR_sensor && !(RIR_sensor)) {
    // no ground on left side, ground under right side
    // go right
    stop_bot();
    delay(200);
    backward();
    delay(100);
    right();
    delay(500);
  }
  if (!(LIR_sensor) && RIR_sensor) {
    // no ground on right side, ground under left side
    // go left
    stop_bot();
    delay(200);
    backward();
    delay(100);
    left();
    delay(500);
  }
  if (LIR_sensor && RIR_sensor) {
    // no ground on either side detected
    // move back and turn either left(rand is 0) or right(rand is 1)
    stop_bot();
    delay(200);
    backward();
    delay(300);
    if ((rand() % 2)==0) {
      left();
      delay(1000);
    }
    else {
      right();
      delay(1000);
    }
  } //******************************************************************************************EDGE AVOIDANCE ENDS
  
  //********************************************************************************************OBSTACLE AVOIDANCE BEGINS
    right_dist=get_right_distance(); 
    left_dist=get_left_distance();
    limit=10;

    if ((right_dist >= limit) && (left_dist >= limit)){ //If nothing is within 10 cm of both sensors
      //Serial.println("go straight");
      //delay(300);
      forward();
    }
    if ((right_dist <= limit) && (left_dist >= limit)){ //If within 10 cm of right sensor turn left
      //Serial.println("go left");
      //delay(300);
      stop_bot();
      delay(200);
      backward();
      delay(100);
      left();
      delay(300);
    }
    if ((right_dist >= limit) && (left_dist <= limit)){ //If within 10 cm of left sensor turn right
      //Serial.println("go right");
      //delay(300);
      stop_bot();
      delay(200);
      backward();
      delay(100);
      right();
      delay(300);
    }
    if ((right_dist <= limit) && (left_dist <= limit)){ //If within 10 cm of both sensors reverse 
      //Serial.println("need to check left and right");
      //delay(300);
      stop_bot();
      delay(200);
      backward();
      delay(100);
      //Go in the direction in which the object is farther
      right_dist=get_right_distance(); 
      left_dist=get_left_distance();
      if (right_dist>left_dist) {
        stop_bot();
        delay(200);
        backward();
        delay(100);
        right();
        delay(300);
      }
      else {
        stop_bot();
        delay(200);
        backward();
        delay(100);
        left();
        delay(300);
      }
    } //********************************************************************************************OBSTACLE AVOIDANCE ENDS
}

  //Ultrasonic test
  /* 
  digitalWrite (TRIG_PIN, HIGH);
  delay(50);
  digitalWrite (TRIG_PIN, LOW);
  duration=pulseIn(ECHO_PIN,HIGH);
  distance=(duration/2)/29.1;
  if(distance <=30) // If the sensor detects an obstacle less than 30 cm in distance, the LED will start to blink.
  delay(50);
  if(distance >=30)// If no obstacle is there within 30 cm, the Led should turn off.
  delay(50);
  Serial.print("cm");
  Serial.println(distance); 
  */

  //Servo test
  /* myservo.write(0); //Right side
  delay(2000);
  myservo.write(90); //Middle
  delay(2000);
  myservo.write(180); //Left side
  delay(2000);
  */
