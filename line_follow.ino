#include <NewPing.h>

//Define constants for motor pins
#define PIN_Motor_PWMA 10 //Right speed control
#define PIN_Motor_PWMB 11 //Left speed control
#define PIN_Motor_A 12//Right side
#define PIN_Motor_B 13//Left side
#define Speed_num 120 //135
float half_speed=(Speed_num/2)+10;

//Define constants for ir pins
#define LIR 7 //pin 3
#define RIR 8 //pin 8

//Define constants for ultrasonic sensor
#define L_ECHO_PIN 5
#define L_TRIG_PIN 6
#define R_ECHO_PIN 3
#define R_TRIG_PIN 9
#define maximum_distance 200
long t, cm;
boolean timestamp = true;
boolean blind = true;
int limit;
int right_dist, left_dist;
int duration, distance; // Add types 'duration' and 'distance'.
int num=0;

//Define constants for linetrack
#define L_LINETRACK_PIN A2
#define M_LINETRACK_PIN A1
#define R_LINETRACK_PIN A0

#define R_BACKUP_LINE_PIN A3
#define L_BACKUP_LINE_PIN A4

float left_line, middle_line, right_line, r_backup_line, l_backup_line;


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
  //Ultrasonic Sensors
  pinMode(L_ECHO_PIN, INPUT);
  pinMode(L_TRIG_PIN, OUTPUT);
  pinMode(R_ECHO_PIN, INPUT);
  pinMode(R_TRIG_PIN, OUTPUT);
  //Linetrack sensors
  pinMode(L_LINETRACK_PIN, INPUT);
  pinMode(M_LINETRACK_PIN, INPUT);
  pinMode(R_LINETRACK_PIN, INPUT);

  pinMode(R_BACKUP_LINE_PIN, INPUT);
  pinMode(L_BACKUP_LINE_PIN, INPUT);
  //forward(80);
}

void forward() {
  digitalWrite(PIN_Motor_A, HIGH);
  analogWrite(PIN_Motor_PWMA, Speed_num);

  digitalWrite(PIN_Motor_B, LOW);
  analogWrite(PIN_Motor_PWMB, Speed_num);
}

void forward(int speed_choose) {
  digitalWrite(PIN_Motor_A, HIGH);
  analogWrite(PIN_Motor_PWMA, speed_choose);

  digitalWrite(PIN_Motor_B, LOW);
  analogWrite(PIN_Motor_PWMB, speed_choose);
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

void left(int speed_choose) {
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

void right(int speed_choose) {
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

void stop_right(){
  digitalWrite(PIN_Motor_A, LOW);
  analogWrite(PIN_Motor_PWMA, 0);

  digitalWrite(PIN_Motor_B, LOW);
  analogWrite(PIN_Motor_PWMB, Speed_num); 
}

void stop_left(){
  digitalWrite(PIN_Motor_A, HIGH);
  analogWrite(PIN_Motor_PWMA, Speed_num);

  digitalWrite(PIN_Motor_B, LOW);
  analogWrite(PIN_Motor_PWMB, 0); 
}

void stop_back_right(){
  digitalWrite(PIN_Motor_A, LOW);
  analogWrite(PIN_Motor_PWMA, 0);

  digitalWrite(PIN_Motor_B, HIGH);
  analogWrite(PIN_Motor_PWMB, Speed_num); 
}

void stop_back_left(){
  digitalWrite(PIN_Motor_A, LOW);
  analogWrite(PIN_Motor_PWMA, Speed_num);

  digitalWrite(PIN_Motor_B, LOW);
  analogWrite(PIN_Motor_PWMB, 0); 
}

void forward_right() {
  digitalWrite(PIN_Motor_A, HIGH);
  analogWrite(PIN_Motor_PWMA, half_speed);

  digitalWrite(PIN_Motor_B, LOW);
  analogWrite(PIN_Motor_PWMB, Speed_num);
}

void forward_right(int speed_choose) {
  digitalWrite(PIN_Motor_A, HIGH);
  analogWrite(PIN_Motor_PWMA, half_speed);

  digitalWrite(PIN_Motor_B, LOW);
  analogWrite(PIN_Motor_PWMB, Speed_num);
}

void forward_left() {
  digitalWrite(PIN_Motor_A, HIGH);
  analogWrite(PIN_Motor_PWMA, Speed_num);

  digitalWrite(PIN_Motor_B, LOW);
  analogWrite(PIN_Motor_PWMB, half_speed);
}

void forward_left(int speed_choose) {
  digitalWrite(PIN_Motor_A, HIGH);
  analogWrite(PIN_Motor_PWMA, Speed_num);

  digitalWrite(PIN_Motor_B, LOW);
  analogWrite(PIN_Motor_PWMB, half_speed);
}

void back_left(){
  digitalWrite(PIN_Motor_A, LOW);
  analogWrite(PIN_Motor_PWMA, Speed_num);

  digitalWrite(PIN_Motor_B, HIGH);
  analogWrite(PIN_Motor_PWMB, half_speed);
}

void back_right(){
  digitalWrite(PIN_Motor_A, LOW);
  analogWrite(PIN_Motor_PWMA, half_speed);

  digitalWrite(PIN_Motor_B, HIGH);
  analogWrite(PIN_Motor_PWMB, Speed_num);
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
  return cm;
}

float left_linetrack(){
  return analogRead(L_LINETRACK_PIN);
}
float middle_linetrack(){
  return analogRead(M_LINETRACK_PIN);
}
float right_linetrack(){
  return analogRead(R_LINETRACK_PIN);
}
float r_backup_linetrack(){
  return analogRead(R_BACKUP_LINE_PIN);
}
float l_backup_linetrack(){
  return analogRead(L_BACKUP_LINE_PIN);
}

void loop() { 
  //Start blind detection
  int LIR_sensor = digitalRead(LIR);
  int RIR_sensor= digitalRead(RIR);
  
  right_dist=get_right_distance(); 
  left_dist=get_left_distance();
  limit=14;
  //Edge avoidance code beginning ****************************************************************EDGE AVOIDANCE BELOW
  //if (!(LIR_sensor) && !(RIR_sensor)){
    // ground detected under both sensors
    // go straight
    //forward();
  //}
  if (LIR_sensor && !(RIR_sensor)) {
    // no ground on left side, ground under right side
    // go right
    stop_bot();
    delay(100);
    backward();
    delay(200);
    right();
    delay(400);
  }
  if (!(LIR_sensor) && RIR_sensor) {
    // no ground on right side, ground under left side
    // go left
    stop_bot();
    delay(100);
    backward();
    delay(200);
    left();
    delay(400);
  }
  if (LIR_sensor && RIR_sensor) {
    // no ground on either side detected
    // move back and turn either left(rand is 0) or right(rand is 1)
    stop_bot();
    delay(50);
    backward();
    delay(300);
    if ((rand() % 2)==0) {
      left();
      delay(800);
    }
    else {
      right();
      delay(800);
    }
  } //************************************************************************************************EDGE AVOIDANCE ENDS 
  
  //********************************************************************************************OBSTACLE AVOIDANCE BEGINS
    //if ((right_dist >= limit) && (left_dist >= limit)){ //If nothing is within 12 cm of both sensors
      //forward();
    //}
    if ((right_dist <= limit) && (left_dist >= limit)){ //If within 10 cm of right sensor turn left
      stop_bot();
      delay(50);
      backward();
      delay(100);
      left();
      delay(300);
    }
    if ((right_dist >= limit) && (left_dist <= limit)){ //If within 10 cm of left sensor turn right
      stop_bot();
      delay(50);
      backward();
      delay(100);
      right();
      delay(300);
    }
    if ((right_dist <= limit) && (left_dist <= limit)){ //If within 10 cm of both sensors reverse 
      stop_bot();
      delay(50);
      backward();
      delay(100);
      //Go in the direction in which the object is farther
      right_dist=get_right_distance(); 
      left_dist=get_left_distance();
      if (right_dist>left_dist) {
        stop_bot();
        delay(50);
        backward();
        delay(100);
        right();
        delay(300);
      }
      else {
        stop_bot();
        delay(50);
        backward();
        delay(100);
        left();
        delay(300);
      }
    } //********************************************************************************************OBSTACLE AVOIDANCE ENDS 
    
   //****************************************************************************************************LINE FOLLOW BEGINS
    left_line=left_linetrack();
    middle_line=middle_linetrack();
    right_line=right_linetrack();
    l_backup_line=l_backup_linetrack();
    r_backup_line=r_backup_linetrack();

    if ((left_line>=100) && (middle_line>=100) && (right_line>=100)){ //Case C
      num=0;
      forward();
    }
    if ((left_line>=100) && (middle_line>=100) && (right_line<100)){ //Case A
      num=0;
      forward_left(); //110
    }
    if ((left_line<100) && (middle_line>=100) && (right_line>=100)){ //Case B
      num=0;
      forward_right(); //110
    }
    if ((left_line<100) && (middle_line<100) && (right_line>=100)){ //Case D
      num=0;
      right(190);
    }
    if ((left_line>=100) && (middle_line<100) && (right_line<100)){ //Case E
      num=0;
      left(190);
    }
    if ((left_line<100) && (middle_line<100) && (right_line<100)){ //Case F,G,H Blind detection
      if(r_backup_line>=100){
        while(l_backup_line>=100){
          num=num+1;
          left();
          stop_bot();
          delay(100);
        }
      }
      else if(l_backup_line>=100){
        while(r_backup_line>=100){
          num=num+1;
          left();
          stop_bot();
          delay(100);
        }
      }
      if(num>=10){
        num=0;
        forward(100);
      }
    }
    //****************************************************************************************************LINE FOLLOW ENDS 
}

//Test linetracking
  /*Serial.print("Left linetrack=");
  Serial.println(left_linetrack());
  Serial.print("Middle linetrack=");
  Serial.println(middle_linetrack());
  Serial.print("Right linetrack=");
  Serial.println(right_linetrack());
  delay(1500);
  
     //********************************************************************************************LINE FOLLOW BEGINS
    if ((left_line>=250) && (middle_line>=250) && (right_line>=250)){ //Case C
      forward();
    }
    if ((left_line>=250) && (middle_line>=250) && (right_line<250)){ //Case A
      left();
      delay(4);
    }
    if ((left_line<250) && (middle_line>=250) && (right_line>=250)){ //Case B
      right();
      delay(4);
    }
    if ((left_line<250) && (middle_line<250) && (right_line>=250)){ //Case 
      right();
      delay(5);
    }
    if ((left_line>=250) && (middle_line<250) && (right_line<250)){ //Case 
      left();
      delay(5);
    }
    if ((left_line<250) && (middle_line<250) && (right_line<250)){ //Case 
      forward();
    } //********************************************************************************************LINE FOLLOW ENDS 
  */

      /*//if ( (left_line<100) && (middle_line<100) && (right_line<100)){ //Case F,G,H
      //Serial.println("straight****");
      //forward();
      //prev_time = time_now;
      

      /*if( (time_now - prev_time >= 300) && (time_now - prev_time < 3000) ){
        // save the last time 
        prev_time = time_now;   
        right();
        //Serial.println("turn right*****************************");
      } 

      
    } */ 
