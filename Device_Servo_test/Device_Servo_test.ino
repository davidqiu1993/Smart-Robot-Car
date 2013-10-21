#include <Servo.h>

int key_s6 = 2;
int sensor = 10;
Servo myservo;
int pos = 0;

void setup()
{
  myservo.attach(8);
  pinMode(key_s6,INPUT);
  pinMode(sensor,INPUT);
}

void loop()
{
  if(analogRead(sensor)>512) {
    for(pos=0;pos<180;pos+=1)
    {
      myservo.write(pos);
      delay(15);
    }
    delay(100);
    for(pos=180;pos>=1;pos-=1)
    {
      myservo.write(pos);
      delay(15);
    }
  }
}


