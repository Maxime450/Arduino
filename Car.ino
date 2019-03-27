#include <NewPing.h>
#include <Servo.h> 

int commande;
int distance = 100;
NewPing sonar(A4, A5, 200)
Servo myservo;

void setup() {
  myservo.attach(9);
  myservo.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  Serial.begin(9600);
}


void loop() {
  if (Serial.available() > 0) {
    commande = Serial.read();
    Stop();
    switch (commande) {
      case 'X':
        Pilot = 1;
        while(Pilot==1) {
          AutoPilot();
          if(Serial.read()=='x') {
            Pilot = 0;
          }
        }
        break;
    } 
  }
}

void AutoPilot () {
  int distanceR = 0;
  int distanceL =  0;
  delay(40);
  if(distance<=20) {
    Stop();
    delay(100);
    back();
    delay(300);
    Stop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);
    if(distanceR>=distanceL) {
      right();
      delay(300);
      forward();
      Stop();
    }
    else {
      left();
      delay(300);
      forward();
      Stop();
    }
  }
  else  {
    forward();
  }
  distance = readPing();
  break;
  }
}
