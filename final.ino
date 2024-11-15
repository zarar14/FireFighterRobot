

/*------ Arduino Fire Fighting Robot Code----- */

#include <Servo.h>
Servo myservo;

int pos = 0;
boolean fire = false;

/*-------defining Inputs------*/
#define Left_S 13      // left sensor
#define Right_S 12     // right sensor
#define Forward_S 7 //forward sensor


/*-------defining Outputs------*/
#define LM1 2       // left motor
#define LM2 3       // left motor
#define RM1 4       // right motor
#define RM2 5       // right motor
#define pump 0
#define EnA 10
#define EnB 11

void setup()
{
  pinMode(Left_S, INPUT);
  pinMode(Right_S, INPUT);
  pinMode(Forward_S, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);
  pinMode(pump, OUTPUT);

  myservo.attach(1);
  myservo.write(90);
}

void put_off_fire()
{
  delay (500);

  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, HIGH);

  digitalWrite(pump, HIGH); delay(1000);

  for (pos = 50; pos <= 130; pos += 1) {
    myservo.write(pos);
    delay(10);
  }
  for (pos = 130; pos >= 50; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }

  digitalWrite(pump, LOW);
  myservo.write(90);

  fire = false;
}

void loop()
{
  myservo.write(90); //Sweep_Servo();

  if (digitalRead(Left_S) == 1 && digitalRead(Right_S) == 1 && digitalRead(Forward_S) == 1) //If Fire not detected all sensors are zero
  {
    //Do not move the robot
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
  }

  else if (digitalRead(Forward_S) == 0) //If Fire is straight ahead
  {
    //Move the robot forward
    // turn on motor A and B
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    // set speed to 0 out 200
    digitalWrite(EnA, 1);
    digitalWrite(EnB, 1);
    fire = true;
  }

  else if (digitalRead(Left_S) == 0) //If Fire is to the left
  {
    //Move the robot left
    // turn on motor A and B
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    // set speed to 0 out 200
    digitalWrite(EnA, 1);
    digitalWrite(EnB, 1);
    fire = true;
  }

  else if (digitalRead(Right_S) == 0) //If Fire is to the right
  {
    //Move the robot right
    // turn on motor A and B
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    // set speed to 0 out 200
    digitalWrite(EnA, 1);
    digitalWrite(EnB, 1);
    fire = true;

  }

  delay(200); //Slow down the speed of robot

  while (fire == true)
  {
    put_off_fire();
  }
}
