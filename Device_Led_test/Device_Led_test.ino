
int led = 10;
int IR_sensor = 11;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(IR_sensor, INPUT);
}

void loop()
{
  int i;
  //if(digitalRead(IR_sensor)==1) {
    for(i=0;i<20;++i) {
      digitalWrite(led, HIGH);
      delay(i);
      digitalWrite(led, LOW);
      delay(20-i);
    }
    for(i=20;i>0;--i) {
      digitalWrite(led, HIGH);
      delay(i);
      digitalWrite(led, LOW);
      delay(20-i);
    }
  //}
}

