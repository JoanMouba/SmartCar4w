/*
 * Epignosis Center 
 * @joan.mouba@gmail.com
 * lesson 1.10
 * Line Tracking follow up  
 * http://les10doigtsdelareussitescolaire.org
 */


#define ML_Ctrl_A_pin 2 // define direction control pin of A motor 
#define ML_Ctrl_B_pin 4 // define direction control pin of B motor 
#define ML_PWM_A_pin 9 // define the PWM control pin of A motor 
#define ML_PWM_B_pin 5 // define the PWM control pin of B motor 

const int car_speed = 150; 
const int curve_car_speed = 2530; 
const int led_pin = 3;
const int L_pin = 6; // pin of left line tracking sensor 
const int M_pin = 7;  // pin of middle line tracking sensor
const int R_pin = 8;  // pin of right line tracking sensor
const int wait_time = 100; 

int val_L, val_M, val_R;

 
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

void servopulse(int servopin,int myangle)//the running angle of servo
{
  for(int i=0; i<30; i++)
  {
    int pulsewidth = (myangle*11)+500;
    digitalWrite(servopin,HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(servopin,LOW);
    delay(20-pulsewidth/1000);
  }  
}

void setup() { 
  Serial.begin(9600);
  pinMode(ML_Ctrl_A_pin, OUTPUT);
  pinMode(ML_Ctrl_B_pin, OUTPUT);
  pinMode(ML_PWM_A_pin, OUTPUT);
  pinMode(ML_PWM_A_pin, OUTPUT);
  // Set the pins of the tracking sensors to INPUT 
  pinMode(L_pin, INPUT); 
  pinMode(M_pin, INPUT); 
  pinMode(R_pin, INPUT); 
  delay(300);
}

void tracking()
{
  val_L = digitalRead(L_pin);
  val_M = digitalRead(M_pin);
  val_R = digitalRead(R_pin);

  if (val_M == 1){
    go_forward(car_speed);
    delay(300);
  }
  else // 2nd condition
  {
    if( (val_L==1) && (val_R==0) )
    {
      //go_backward(car_speed);
      //delay(wait_time);
      go_left(curve_car_speed);
      //delay(wait_time);
    }
    else if ( (val_L==0) && (val_R==1) )
    {
      //go_backward(car_speed);
      //delay(wait_time);
      go_right(curve_car_speed);
      //delay(wait_time);
    }
    else
    {
      go_backward(car_speed);
      delay(100);
      go_stop(car_speed);
    }
  } // end of 2nd condition
  
}

void loop() {
   tracking();
}//******************************************************
