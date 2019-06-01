

class stepper {
  /*
   * Class for a stepper motor driven by the
   * Pololu DRV8825 stepper motor driver
   */
  public:   // Make all variables public
  
  int dirPin;
  int stepPin;
  int sleepPin;
  int stepsPerRevolution;

  int currentPosition;      // Position of the motor, in full steps
  boolean currentDirection; // True=clockwise
  boolean powerStatus;      // True=not sleeping

  stepper(int dir, int stp, int slp, int spr) {
    /*
     * Constructor for the stepper class
     * dir - direction pin          (driver)
     * stp - stepper pin            (driver)
     * slp - sleep pin              (driver)
     * spr - steps per revolution   (motor)
     */
     
     dirPin = dir;
     stepPin = stp;
     sleepPin = slp;
     stepsPerRevolution = spr;

     currentPosition = 0;
     currentDirection = true;
     powerStatus = false;

     pinMode(dirPin, OUTPUT);
     pinMode(stepPin, OUTPUT);
     pinMode(sleepPin, OUTPUT);

     digitalWrite(dirPin, currentDirection);
     digitalWrite(sleepPin, powerStatus);

  }


  void turn_on(){
    powerStatus = true;
    digitalWrite(sleepPin, powerStatus);
  }

  void turn_off(){
    powerStatus = false;
    digitalWrite(sleepPin, powerStatus);
  }

  void clockwise(){
    currentDirection = true;
    digitalWrite(dirPin, currentDirection);
  }

  void anticlockwise(){
    currentDirection = false;
    digitalWrite(dirPin, currentDirection);
  }

  void change_direction(){
    currentDirection = ~currentDirection;
    digitalWrite(dirPin, currentDirection);
  }

  void take_step(int del){
    /*
     * Steps the motor once
     * del is the total duration for this
     * action, in MICROseconds
     */
    del /= 2;
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(del);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(del);
    //currentPosition++;
  }
};



stepper stepper1(3, 2, 4, 200);

void setup()
{
  Serial.begin(9600);

  stepper1.turn_on();

  unsigned long T = 3000;             //duration in ms
  float S = 2.5;                      //revolutions to spin
  sin_move(stepper1, T, S);

  stepper1.turn_off();
}

void loop(){
}

void sin_move(stepper motor, int T, float S){
  /*
   * Moves a stepper in a sinusoidal motion
   * 
   * motor = stepper object
   * T = duration for spin forwards then back to take (ms)
   * S = number of revolutions to spin (then spin back)
   * 
   * Requires global variable stepsPerRevolution
   */

  int O = motor.currentPosition;
   
  int number_of_steps = S*motor.stepsPerRevolution;
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
      motor.anticlockwise();
      no_steps_to_take = -no_steps_to_take;
    }
    else{
      motor.clockwise();
    }

    //Take the steps
    time_between_steps_us = 1000/no_steps_to_take;  // 1000us / number of steps to take
    for(int i=0; i<no_steps_to_take; i++){
      motor.take_step(time_between_steps_us);
    }
    
    curr_pos = next_pos;
    ms++;
  }
}
