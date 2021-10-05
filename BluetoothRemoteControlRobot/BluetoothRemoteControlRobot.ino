/*
 * Epignosis Center 
 * @joan.mouba@gmail.com
 * lesson 1.14
 * Bluetooth Remote Control    
 * http://les10doigtsdelareussitescolaire.org
 */

#define ML_Ctrl_A_pin 2 // define direction control pin of A motor 
#define ML_Ctrl_B_pin 4 // define direction control pin of B motor 
#define ML_PWM_A_pin 9 // define the PWM control pin of A motor 
#define ML_PWM_B_pin 5 // define the PWM control pin of B motor

char BLE_val;  
int car_slow = 100;
int car_speed = 200; 
 
void go_forward(int car_speed_in);
void go_backward(int car_speed_in);
void go_left(int car_speed_in);
void go_right(int car_speed_in);
void go_stop(int car_speed_in);
void move(); 

void setup() { 
  Serial.begin(9600);
  pinMode(ML_Ctrl_A_pin, OUTPUT);
  pinMode(ML_Ctrl_B_pin, OUTPUT);
  pinMode(ML_PWM_A_pin, OUTPUT);
  pinMode(ML_PWM_A_pin, OUTPUT); 
  delay(300);
}

void loop() {
   move();
} 

void move(){
  if (Serial.available()>0) 
  {
    BLE_val = Serial.read(); 
    Serial.println(BLE_val);
  }  
  switch(BLE_val)
  {
    case 'F' : go_forward(car_slow); break;
    case 'B' : go_backward(car_slow); break;
    case 'L' : go_left(car_speed); break;
    case 'R' : go_right(car_speed); break;
    case 'S' : go_stop(car_speed); break;
  }
}  

void go_forward(int car_speed_in){
  digitalWrite(ML_Ctrl_A_pin, HIGH);
  analogWrite(ML_PWM_A_pin, car_speed_in);
  digitalWrite(ML_Ctrl_B_pin, LOW);
  analogWrite(ML_PWM_B_pin, car_speed_in);
  return true;
}

void go_backward(int car_speed_in){
  digitalWrite(ML_Ctrl_A_pin, LOW);
  analogWrite(ML_PWM_A_pin, car_speed_in);
  digitalWrite(ML_Ctrl_B_pin, HIGH);
  analogWrite(ML_PWM_B_pin, car_speed_in);
  return true;
}

void go_left(int car_speed_in){
  digitalWrite(ML_Ctrl_A_pin, HIGH);
  analogWrite(ML_PWM_A_pin, car_speed_in);
  digitalWrite(ML_Ctrl_B_pin, LOW);
  analogWrite(ML_PWM_B_pin, 0);
  return true;
}

void go_right(int car_speed_in){
  digitalWrite(ML_Ctrl_A_pin, HIGH);
  analogWrite(ML_PWM_A_pin, 0);
  digitalWrite(ML_Ctrl_B_pin, LOW);
  analogWrite(ML_PWM_B_pin, car_speed_in);
  return true;
}

void go_stop(int car_speed_in=100){
  digitalWrite(ML_Ctrl_A_pin, LOW);
  digitalWrite(ML_Ctrl_B_pin, HIGH);
  analogWrite(ML_PWM_A_pin, car_speed_in/2);
  analogWrite(ML_PWM_B_pin, car_speed_in/2);
  analogWrite(ML_PWM_A_pin, 0);
  analogWrite(ML_PWM_B_pin, 0);
  return true;
}

//******************************************************
