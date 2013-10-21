
int IR_sensor = 11;
int led = 10;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(IR_sensor, INPUT);
}

void loop()
{
  if(digitalRead(IR_sensor)==HIGH) {
    digitalWrite(led, HIGH);
    delay(10);
  }
  else {
    digitalWrite(led, LOW);
    delay(10);
  }
}


