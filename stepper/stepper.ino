

class stepper {
  /*
   * Class for a stepper motor driven by the
   * Pololu DRV8825 stepper motor driver
   */
  public:   // Make all variables public
  
  int dirPin;
  int stepPin;
  int sleepPin;
  int modePin0;
  int modePin1;
  int modePin2;
  int stepsPerRevolution;

  int currentPosition;      // Position of the motor, in full steps
  boolean currentDirection; // True=clockwise
  boolean powerStatus;      // True=not sleeping
  byte mode;                // Step mode
  float stepSize;           // Number of steps per full step

  stepper(int dir, int stp, int slp, int spr, int mp0=-1, int mp1=-1, int mp2=-1) {
    /*
     * Constructor for the stepper class
     * dir - direction pin                (driver)
     * stp - stepper pin                  (driver)
     * slp - sleep pin                    (driver)
     * spr - steps per revolution         (motor)
     * mp0 - mode pin 0 (negative=none)   (driver)
     * mp1 - mode pin 1
     * mp2 - mode pin 2
     */
     
     dirPin = dir;
     stepPin = stp;
     sleepPin = slp;
     modePin0 = mp0;
     modePin1 = mp1;
     modePin2 = mp2;
     stepsPerRevolution = spr;

     currentPosition = 0;
     currentDirection = true;
     powerStatus = false;
     mode = 0;
     stepSize = 1;

     pinMode(dirPin, OUTPUT);
     pinMode(stepPin, OUTPUT);
     pinMode(sleepPin, OUTPUT);
     if(modePin0>=0){
      pinMode(modePin0, OUTPUT);
     }
     if(modePin1>=0){
      pinMode(modePin1, OUTPUT);
     }
     if(modePin2>=0){
      pinMode(modePin2, OUTPUT);
     }

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


  void change_mode(byte new_mode){
    /*
     * Changes the step mode of the motor to
     * new_mode. This is achieved by writing
     * to the stepper driver pins
     * If a stepper driver mode pin is not
     * connected (i.e. modePinX is negative),
     * modePinX is not written to
     * This allows for mode selection when only
     * some of the mode pins are connected
     * 
     *        Step modes:
     * Bin     Dec   Resolution   
     * 0b000   0d0   Full step (200)
     * 0b001   0d1   Half step (400)
     * 0b010   0d2   1/4 step  (800)
     * 0b011   0d3   1/8 step  (1600)
     * 0b100   0d4   1/16 step (3200)
     * 0b101   0d5   1/32 step (6400)
     * 0b110   0d6   1/32 step (6400)
     * 0b111   0d7   1/32 step (6400)
     */

    // Change mode variable and set pins
    bool tmp;
    if(modePin0>=0){
      tmp = bitRead(new_mode, 0);
      bitWrite(mode, 0, tmp);
      digitalWrite(modePin0, tmp);
    }
    if(modePin1>=0){
      tmp = bitRead(new_mode, 1);
      bitWrite(mode, 1, tmp);
      digitalWrite(modePin1, tmp);
    }
    if(modePin2>=0){
      tmp = bitRead(new_mode, 2);
      bitWrite(mode, 2, tmp);
      digitalWrite(modePin2, tmp);
    }
    
    // Calculate the new step size (using above table)
    if(mode>=5){
      stepSize = 32 * stepsPerRevolution;
    }
    else{
      stepSize = (2^mode) * stepsPerRevolution;
    }

    Serial.print("Stepper mode set to ");
    Serial.print(mode);
    
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
    currentPosition += stepSize;
  }
};



stepper stepper1(3, 2, 4, 200, -1, -1, 5);

void setup()
{
  Serial.begin(9600);

  stepper1.turn_on();

  unsigned long T = 3000;             //duration in ms
  float S = 2.5;                      //revolutions to spin
  sin_move(stepper1, T, S);

  stepper1.turn_off();
  
  delay(2000);
  stepper1.turn_on();
  stepper1.change_mode(4);
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
