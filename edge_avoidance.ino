//Define constants for motor pins
#define PIN_Motor_PWMA 5
#define PIN_Motor_PWMB 6
#define PIN_Motor_BIN_1 8
#define PIN_Motor_AIN_1 7
#define PIN_Motor_STBY 3
//Define constants for ir pins
#define LIR 10 //Servo1 pin 10
#define RIR 11 //Servo2 pin 11
#define LED 13

#define Speed_num 100
float half_speed=(Speed_num/2);

//Set the pinmode with the constants
void setup() {
  Serial.begin(9600);
  pinMode(PIN_Motor_PWMA, OUTPUT);
  pinMode(PIN_Motor_PWMB, OUTPUT);
  pinMode(PIN_Motor_AIN_1, OUTPUT);
  pinMode(PIN_Motor_BIN_1, OUTPUT);
  pinMode(PIN_Motor_STBY, OUTPUT);
  
  pinMode(LIR, INPUT);
  pinMode(RIR, INPUT);
  pinMode(LED, OUTPUT);
}

void forward() {
  digitalWrite(PIN_Motor_STBY, HIGH);
  
  digitalWrite(PIN_Motor_AIN_1, HIGH);
  analogWrite(PIN_Motor_PWMA, Speed_num);

  digitalWrite(PIN_Motor_BIN_1, HIGH);
  analogWrite(PIN_Motor_PWMB, Speed_num);
}

void backward() {
  digitalWrite(PIN_Motor_STBY, HIGH);
  
  digitalWrite(PIN_Motor_AIN_1, LOW);
  analogWrite(PIN_Motor_PWMA, Speed_num);

  digitalWrite(PIN_Motor_BIN_1, LOW);
  analogWrite(PIN_Motor_PWMB, Speed_num);
}

void left() {
  digitalWrite(PIN_Motor_STBY, HIGH);
  
  digitalWrite(PIN_Motor_AIN_1, HIGH);
  analogWrite(PIN_Motor_PWMA, Speed_num);

  digitalWrite(PIN_Motor_BIN_1, LOW);
  analogWrite(PIN_Motor_PWMB, Speed_num);
}

void right() {
  digitalWrite(PIN_Motor_STBY, HIGH);
  
  digitalWrite(PIN_Motor_AIN_1, LOW);
  analogWrite(PIN_Motor_PWMA, Speed_num);

  digitalWrite(PIN_Motor_BIN_1, HIGH);
  analogWrite(PIN_Motor_PWMB, Speed_num);
}

void stop_bot(){
  digitalWrite(PIN_Motor_STBY, HIGH);
  
  digitalWrite(PIN_Motor_AIN_1, LOW);
  analogWrite(PIN_Motor_PWMA, 0);

  digitalWrite(PIN_Motor_BIN_1, LOW);
  analogWrite(PIN_Motor_PWMB, 0);
}

void leftForward() {
  digitalWrite(PIN_Motor_STBY, HIGH);
  
  digitalWrite(PIN_Motor_AIN_1, HIGH);
  analogWrite(PIN_Motor_PWMA, Speed_num);

  digitalWrite(PIN_Motor_BIN_1, HIGH);
  analogWrite(PIN_Motor_PWMB, half_speed);
}

void leftBackward() {
  digitalWrite(PIN_Motor_STBY, HIGH);
  
  digitalWrite(PIN_Motor_AIN_1, HIGH);
  analogWrite(PIN_Motor_PWMA, Speed_num);

  digitalWrite(PIN_Motor_BIN_1, HIGH);
  analogWrite(PIN_Motor_PWMB, half_speed);
}

void rightForward() {
  digitalWrite(PIN_Motor_STBY, HIGH);
  
  digitalWrite(PIN_Motor_AIN_1, HIGH);
  analogWrite(PIN_Motor_PWMA, half_speed);

  digitalWrite(PIN_Motor_BIN_1, HIGH);
  analogWrite(PIN_Motor_PWMB, Speed_num);
}

void rightBackward() {
  digitalWrite(PIN_Motor_STBY, HIGH);
  
  digitalWrite(PIN_Motor_AIN_1, LOW);
  analogWrite(PIN_Motor_PWMA, half_speed);

  digitalWrite(PIN_Motor_BIN_1, LOW);
  analogWrite(PIN_Motor_PWMB, Speed_num);
}

void loop(){
  int LIR_sensor = digitalRead(LIR);
  int RIR_sensor= digitalRead(RIR);
  if (!(LIR_sensor) && !(RIR_sensor)){
    // ground detected under both sensors
    // go straight
    //Serial.println("");
    forward();
  }
  if (LIR_sensor && !(RIR_sensor)) {
    // no ground on left side, ground under right side
    // go right
    stop_bot();
    delay(200);
    right();
    delay(200);
  }
  if (!(LIR_sensor) && RIR_sensor) {
    // no ground on right side, ground under left side
    // go left
    stop_bot();
    delay(200);
    left(); 
    delay(200);
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
      delay(200);
      left();
    }
    else {
      right();
      delay(200);
      right();
    }
    delay(200);
  }
}
