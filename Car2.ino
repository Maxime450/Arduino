#include <NewPing.h>
#include <Servo.h> 

#define VitG 3
#define VitD 11
#define SensG 12
#define SensD 13
int commande;
int distance = 100;
int Speed = 150; // 0 - 255
NewPing sonar(A4, A5, 200); // sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE)
Servo myservo;

void setup() {
  myservo.attach(9);
  myservo.write(115);
  pinMode(VitG, OUTPUT);
  pinMode(VitD, OUTPUT);
  pinMode(SensG, OUTPUT);
  pinMode(SensD, OUTPUT);
  
  myservo.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  
  Serial.begin(9600);
}


void loop() {
  if (Serial.available() > 0) {
    commande = Serial.read();
    Stop();
    switch (commande) {
      case 'F':
        forward();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'G':
        forwardleft();
        break;
      case 'I':
        forwardright();
        break;
      case 'H':
        backleft();
        break;
      case 'J':
        backright();
        break;
      case '0':
        Speed = 100;
        break;
      case '1':
        Speed = 114;
        break;
      case '2':
        Speed = 128;
        break;
      case '3':
        Speed = 142;
        break;
      case '4':
        Speed = 157;
        break;
      case '5':
        Speed = 170;
        break;
      case '6':
        Speed = 184;
        break;
      case '7':
        Speed = 198;
        break;
      case '8':
        Speed = 212;
        break;
      case '9':
        Speed = 226;
        break;
      case 'q':
        Speed = 255;
        break;
      case 'X':
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
}


int lookRight() {
  myservo.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115);
  return distance;
}

int lookLeft() {
  myservo.write(170); 
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115); 
  return distance;
  delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0) {
    cm = 250;
  }
  return cm;
}

void forward() {
  digitalWrite(SensG, HIGH);
  digitalWrite(SensD, LOW);
  analogWrite(VitG, Speed);
  analogWrite(VitD, Speed);
}

void back() {
  digitalWrite(SensG, LOW);
  digitalWrite(SensD, HIGH);
  analogWrite(VitG, Speed);
  analogWrite(VitD, Speed);
}

void left() {
  digitalWrite(SensG, LOW);
  digitalWrite(SensD, LOW);
  analogWrite(VitG, Speed);
  analogWrite(VitD, Speed);
}

void right() {
  digitalWrite(SensG, HIGH);
  digitalWrite(SensD, HIGH);
  analogWrite(VitG, Speed);
  analogWrite(VitD, Speed);
}

void forwardleft() {
  digitalWrite(SensD, LOW);
  analogWrite(VitG, 0);
  analogWrite(VitD, Speed);
}

void forwardright() {
  digitalWrite(SensG, HIGH);
  analogWrite(VitG, Speed);
  analogWrite(VitD, 0);
}

void backright() {
  digitalWrite(SensG, LOW);
  analogWrite(VitG, Speed);
  analogWrite(VitD, 0);
}

void backleft() {
  digitalWrite(SensD, HIGH);
  analogWrite(VitG, 0);
  analogWrite(VitD, Speed);
}

void Stop() {
  analogWrite(VitG, 0);
  analogWrite(VitD, 0);
}
