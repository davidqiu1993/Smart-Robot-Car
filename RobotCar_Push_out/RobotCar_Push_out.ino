int count = 0;
int mid_count = 0;

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
  
  // serial ..
  //Serial.begin(19200);
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

int GSensor_back_seen()
{
  return 1-digitalRead(GSensor_middle);
}

int GSensor_right_seen()
{
  return 1-digitalRead(GSensor_right);
}

int detect_left()
{
  return 1-digitalRead(IRSensor_left);
}

int detect_middle()
{
  return 1-digitalRead(IRSensor_middle);
}

int detect_right()
{
  return 1-digitalRead(IRSensor_right);
}

void search_left()
{
  int alpha = 0;
  // turning to find ..
  while(alpha==0)
  {
    count = 0;
    while(count<=300)
    {
      if(detect_left() || detect_middle() || detect_right())
      {
        alpha = 1;
        break;
      }
      turn_left(200,200);
      delay(5);
      ++count;
    }
    turn_right(500,500);
    delay(5);
    
    if(alpha==1) break;
    count = 0;
    while(count<200)
    {
      if(GSensor_left_seen() || GSensor_right_seen() || detect_left() || detect_middle() || detect_right()) 
      {
        alpha = 1;
        break;
      }
      advance(500,500);
      delay(5);
      ++count;
    }
  }
  car_stop();
}

void searchmid_left()
{
  mid_count = 0;
  while((!detect_middle()) && mid_count<100)
  {
    turn_left(200,200);
    delay(5);
    ++mid_count;
  }
  turn_right(500,500);
  delay(5);
  car_stop();
}

void searchmid_right()
{
  mid_count = 0;
  while((!detect_middle()) && mid_count<100)
  {
    turn_right(200,200);
    delay(5);
    ++mid_count;
  }
  turn_left(500,500);
  delay(5);
  car_stop();
}

void push_out()
{
  if(GSensor_left_seen())
  {
    back(500,500);
    delay(200);
    turn_right(500,500);
    delay(100);
  }
  else if(GSensor_right_seen())
  {
    back(500,500);
    delay(200);
    turn_left(500,500);
    delay(100);
  }
  else if(GSensor_back_seen())
  {
    advance(500,500);
    delay(200);
  }
  else
  {
    if(detect_middle())
    {
      advance(500,500);
      delay(5);
    }
    else
    {
      if(detect_right())
      {
        searchmid_right();
      }
      else if(detect_left())
      {
        searchmid_left();
      }
      else
      {
        search_left();
      }
    }
  }
}

void loop()
{
  push_out();
  //Serial.print(digitalRead(IRSensor_right));
  //delay(100);
}

