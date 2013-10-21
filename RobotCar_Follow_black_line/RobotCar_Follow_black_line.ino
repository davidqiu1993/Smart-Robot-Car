
// Define: Ground Sensors
int GSensor_left = 10;
int GSensor_middle = 11;
int GSensor_right = 12;

// Define: IR Sensors 
int IRSensor_left = 1;
int IRSensor_middle = 2;
int IRSensor_right = 3;

// Define: Motor 
int E1 = 5;
int E2 = 6;
int M1 = 4;
int M2 = 7;

void setup()
{
  pinMode(GSensor_left, INPUT);
  pinMode(GSensor_middle, INPUT);
  pinMode(GSensor_right, INPUT);
  pinMode(IRSensor_left, INPUT);
  pinMode(IRSensor_middle, INPUT);
  pinMode(IRSensor_right, INPUT);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}

void car_stop(void)
{
  digitalWrite(E1,LOW);
  digitalWrite(E2,LOW);
}

void advance(char a, char b)
{
  analogWrite(E1, a);
  digitalWrite(M1, HIGH);
  analogWrite(E2, b);
  digitalWrite(M2, HIGH);
}

void back(char a, char b)
{
  analogWrite(E1, a);
  digitalWrite(M1, LOW);
  analogWrite(E2, b);
  digitalWrite(M2, LOW);
}

void turn_left(char a, char b)
{
  analogWrite(E1, a);
  digitalWrite(M1, HIGH);
  analogWrite(E2, b);
  digitalWrite(M2, LOW);
}

void turn_right(char a, char b)
{
  analogWrite(E1, a);
  digitalWrite(M1, LOW);
  analogWrite(E2, b);
  digitalWrite(M2, HIGH);
}

int GSensor_left_seen()
{
  return 1-digitalRead(GSensor_left);
}

int GSensor_middle_seen()
{
  return 1-digitalRead(GSensor_middle);
}

int GSensor_right_seen()
{
  return 1-digitalRead(GSensor_right);
}


/* Smooth Turning */
void smooth_turning()
{
  if(GSensor_left_seen()) {
    while(GSensor_right==0) {
      advance(50,160);
      delay(2);
    }
    turn_right(40,100);
    delay(10);
  }
  else if(GSensor_right_seen()) {
    while(GSensor_left==0) {
      advance(100,100);
      delay(2);
    }
    turn_left(40,100);
    delay(10);
  }
  else {
    advance(100,250);
    delay(5);
  }
}


/* Normal Running */
void normal_running()
{
  if(GSensor_left_seen()) {
    turn_left(100,100);
    delay(10);
  }
  else if(GSensor_right_seen()) {
    turn_right(100,100);
    delay(10);
  }
  else {
    advance(500,500);
    delay(5);
  }
}


void loop()
{
  normal_running();
}

