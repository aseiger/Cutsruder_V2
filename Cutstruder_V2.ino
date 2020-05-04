#include <AccelStepper.h>
#include <Servo.h>

const double steps_per_in = -800 / 6;

const int footPin = 13;
const int feedButton = 8;

AccelStepper stepper(1, 2, 3); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
Servo myServo;

void setup()
{  
   pinMode(footPin, INPUT_PULLUP);
   pinMode(feedButton, INPUT_PULLUP);
   stepper.setMaxSpeed(2500); //<=============== edit the maximum feed rate here
   stepper.setAcceleration(15000); //<============== edit the maximum acceleration here
   myServo.attach(9);	
   myServo.write(0);
   delay(1000);
}

void loop()
{  
   
   if(digitalRead(footPin) == LOW)
   {
     cut();
     feed_length(13); //<=================== edit the length of the strips here
     delay(100);
   }
   
   if(digitalRead(feedButton) == LOW)
   {
     stepper.setSpeed(-100);
     while(digitalRead(feedButton) == LOW)
     {
        stepper.runSpeed();
     }
     delay(100);
   }
}

void cut()
{
  myServo.write(180);
  delay(800); //<=========================== edit the servo delay time here
  myServo.write(0);
  delay(800); //<========================== and here too. The bad programming practice velociraptor is coming for me.
}

void feed_length(double length_in)
{
  stepper.setCurrentPosition(0);
  stepper.runToNewPosition(length_in * steps_per_in);
}
