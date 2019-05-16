// Define pin connections & motor's steps per revolution
const int dirPin = 3;
const int stepPin = 2;
const int stepsPerRevolution = 200;

void setup()
{
  Serial.begin(9600);
  
  // Declare pins as Outputs
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}

void loop(){
  sin_move();
}



void sin_move(){
  // Set motor direction clockwise
  digitalWrite(dirPin, HIGH);

  unsigned long T = 3000;   //duration in ms
  float S = 2.5;
  int O = 0;

  sin_move(T, S, O);
}

void sin_move(int T, float S, int O){
  /*
   * Moves the stepper in a sinusoidal motion
   * S = number of revolutions to spin (then spin back)
   * T = duration for spin forwards then back to take (ms)
   * O = current offset of motor
   * 
   * Requires global variable stepsPerRevolution
   */
   
  int number_of_steps = S*stepsPerRevolution;
  float phi = PI + O;
  float omega = 2*PI/T;

  unsigned long ms = 0;
  int curr_pos = 0;
  int next_pos = 0;
  int no_steps_to_take = 0;
  int time_between_steps_us = 0;
  
  while(ms<T){
    //Calculate how many steps we need to take
    //during this millisecond
    next_pos = 0.5*number_of_steps*(cos(omega*ms + phi)+1);
    no_steps_to_take = next_pos - curr_pos;

    //Print serial for plotting
    Serial.println(curr_pos);

    //If we need to step backwards, flip the direction
    if(no_steps_to_take<0){
      digitalWrite(dirPin, LOW);
      no_steps_to_take = -no_steps_to_take;
    }
    else{
      digitalWrite(dirPin, HIGH);
    }

    //Take the steps
    time_between_steps_us = 1000/no_steps_to_take;  // 1000us / number of steps to take
    for(int i=0; i<no_steps_to_take; i++){
      step_motor(time_between_steps_us);
    }
    
    curr_pos = next_pos;
    ms++;
  }
}

void step_motor(int del){
  //Steps the motor once
  //del is the TOTAL duration for this action
  //del is in MICROseconds
  del /= 2;
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(del);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(del);
}
