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

void loop()
{
  // Set motor direction clockwise
  digitalWrite(dirPin, HIGH);

  unsigned long T = 2000000;   //duration in us
  int S = 1;
  int O = 0;

  int number_of_steps = S*stepsPerRevolution;
  unsigned long time_between_steps = T/number_of_steps;

  Serial.println(number_of_steps);
  Serial.println(time_between_steps);

  for(int x = 0; x < number_of_steps; x++){
    step_motor(time_between_steps);
    Serial.println(x);
  }

  delay(1000); // Wait a second
  
  // Set motor direction counterclockwise
  digitalWrite(dirPin, LOW);

  // Spin motor quickly
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    step_motor(1000);
  }
  delay(1000); // Wait a second
}

void step_motor(int del){
  //Steps the motor once
  //del is the TOTAL duration for this action
  //del is in MICROseconds
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(del/2);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(del/2);
}
