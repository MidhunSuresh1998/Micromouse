#include <StackArray.h>

boolean last = false;
boolean trial = false;
boolean turnback = false;
int motor1A = 12;
int motor1E = 3;
int motor2A = 13;
int motor2E = 11;
int THRESHOLD = 40;
const int echoPin2 = 9;
const int trigPin2 = 8;
const int echoPin3 = 7;
const int trigPin3 = 6;
const int echoPin4 = 10;
const int trigPin4 = 2;
int right_old = 0;
int left_old = 0;
int front_old = 0;
boolean turn_right = true;
boolean turn_left = true;

boolean turn_back = false;
boolean turn = false;
int parent = 0;
int a = 0;

StackArray <int> righthandstack;
StackArray <int> lefthandstack;
StackArray <int> truestack;
StackArray <int> PARENTSTACK;

boolean turnbacktime = false;
boolean righthandrule = false;
boolean lefthandrule = true;

void setup() 
{
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  pinMode(motor1E, OUTPUT);
  pinMode(motor2E, OUTPUT);
  pinMode(motor1A, OUTPUT);
  pinMode(motor2A, OUTPUT);
  Serial.begin(9600);
  forward(70);
  delay(50);
  forward(0);
}


void loop() 
{
  long duration2, right;
  long duration3, left;
  long duration4, front;

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  right = duration2 / 10;
  Serial.print(right);
  Serial.print("\t");

  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  left = duration3 / 10;
  Serial.print(left);
  Serial.print("\t");
  
  digitalWrite(trigPin4, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin4, LOW);
  duration4 = pulseIn(echoPin4, HIGH);
  front = duration4 / 10;
  Serial.print(front);
  Serial.println("\t");
  
  if (right < THRESHOLD) 
  {
    turn_right = true;
  }
  if (left < THRESHOLD) 
  {
    turn_left = true;
  }
  if (turn_right && turn_left) 
  {
    parent = false;
  }
  if (righthandrule) 
  {
    if (left > 500 && front > 500 && right > 500) 
    {
      rightf(90);
      delay(230);
      rightf(0);
      delay(150);
      rightf(90);
      delay(230);
      rightf(0);
      righthandrule = false;
      lefthandrule = true;
      delay(10000);
    }
    else if (right > THRESHOLD + 40 && left > THRESHOLD + 40 && turn_right && front > THRESHOLD - 15) 
    {
      for (int i = 0; i < 2; i++) 
      {
        forward(50);
        delay(125);
        forward(0);
      }
      rightf(90);
      delay(230);
      rightf(0);
      turn_right = false;
      turn_left = false;
      righthandstack.push(4);
    }
    else if (front > THRESHOLD + 40 && right > THRESHOLD + 40 && turn_right) 
    {
      for (int i = 0; i < 4; i++) 
      {
        forward(50);
        delay(125);
        forward(0);
      }
      rightf(90);
      delay(230);
      rightf(0);
      turn_right = false;
      turn_left = false;
      righthandstack.push(4);
    }
    else if (left > THRESHOLD + 40 && front > THRESHOLD + 40 && turn_left) 
    {
      forward(50);
      delay(125);
      forward(0);
      righthandstack.push(1);
      turn_left = false;
    }
    else if (front > THRESHOLD - 15) 
    {
      if (right > left) 
      {
        digitalWrite(motor1A, LOW);
        digitalWrite(motor2A, LOW);
        analogWrite(motor1E, 175);
        analogWrite(motor2E, 120);
        delay(60);
        forward(0);
      }
      else if (left > right) 
      {
        digitalWrite(motor1A, LOW);
        digitalWrite(motor2A, LOW);
        analogWrite(motor1E, 120);
        analogWrite(motor2E, 175);
        delay(60);
        forward(0);
      }
      else
      {
        forward(50);
        delay(125);
        forward(0);
      }
    }
    else if (right > THRESHOLD && turn_right) 
    {
      rightf(90);
      delay(230);
      rightf(0);
      turn_right = false;
      for (int i = 0; i < 2; i++) 
      {
        forward(50);
        delay(125);
        forward(0);
      }
      righthandstack.push(4);
    }
    else if (left > THRESHOLD && turn_left) 
    {
      leftf(90);
      delay(230);
      leftf(0);
      turn_left = false;
      for (int i = 0; i < 2; i++) 
      {
        forward(50);
        delay(125);
        forward(0);
      }
      righthandstack.push(5);
    }
    else if (turn_right && turn_left) 
    {
      rightf(90);
      delay(230);
      rightf(0);
      delay(150);
      rightf(90);
      delay(230);
      rightf(0);
      delay(150);
    }
    else 
    {
      turn_right = true;
      turn_left = true;
    }
  }
  else if (lefthandrule) 
  {
    if (left > 500 && front > 500 && right > 500) 
    {
        rightf(90);
        delay(230);
        rightf(0);
        delay(150);
        rightf(90);
        delay(230);
        rightf(0);
        lefthandrule = false;
        trial = true;
        delay(10000);
      }
      else if (right > THRESHOLD+40 && left > THRESHOLD+40 && turn_left && front > THRESHOLD - 15) 
      {
        for (int i = 0; i < 2; i++) 
        {
          forward(50);
          delay(125);
          forward(0);
        }
        leftf(90);
        delay(230);
        leftf(0);
        turn_right = false;
        turn_left = false;
        lefthandstack.push(4);
      }
      else if (front > THRESHOLD+40 && left > THRESHOLD+40 && turn_left) 
      {
        for (int i = 0; i < 4; i++) 
        {
          forward(50);
          delay(125);
          forward(0);
        }
        leftf(90);
        delay(230);
        leftf(0);
        turn_right = false;
        turn_left = false;
        lefthandstack.push(4);
      }
      else if (right > THRESHOLD+40 && front > THRESHOLD+40 && turn_right) 
      {
        forward(50);
        delay(125);
        forward(0);
        lefthandstack.push(1);
        turn_right = false;
      }
      else if (front > THRESHOLD - 15) 
      {
        if (right > left) 
        {
          digitalWrite(motor1A, LOW);
          digitalWrite(motor2A, LOW);
          analogWrite(motor1E, 175);
          analogWrite(motor2E, 120);
          delay(60);
          forward(0);
        }
        else if (left > right) 
        {
          digitalWrite(motor1A, LOW);
          digitalWrite(motor2A, LOW);
          analogWrite(motor1E, 120);
          analogWrite(motor2E, 175);
          delay(60);
          forward(0);
        }
        else 
        {
          forward(50);
          delay(125);
          forward(0);
        }
      }
      else if (left > THRESHOLD && turn_left) 
      {
        leftf(90);
        delay(230);
        leftf(0);
        turn_left = false;
        for (int i = 0; i < 2; i++) 
        {
          forward(50);
          delay(125);
          forward(0);
        }
        lefthandstack.push(4);
      }
      else if (right > THRESHOLD && turn_right) 
      {
        rightf(90);
        delay(230);
        rightf(0);
        turn_right = false;
        for (int i = 0; i < 2; i++) 
        {
          forward(50);
          delay(125);
          forward(0);
        }
        lefthandstack.push(5);
      }
      else if (turn_right && turn_left) 
      {
        rightf(90);
        delay(230);
        rightf(0);
        delay(150);
        rightf(90);
        delay(230);
        rightf(0);
        delay(150);
      }
      else 
      {
        turn_right = true;
        turn_left = true;
      }
  }

 //Shorter
  else if (trial) 
  {
    if (righthandstack.count() <= lefthandstack.count()) 
    {
      if (!(turnbacktime)) 
      {
        if (left > 500 && front > 500 && right > 500) 
        {
          rightf(90);
          delay(230);
          rightf(0);
          delay(150);
          rightf(90);
          delay(230);
          rightf(0);
          trial = false;
          last = true;
          int yeah = truestack.count();
          for (int i = 0; i < yeah; i++) 
          {
            PARENTSTACK.push(truestack.pop());
          }
          a = PARENTSTACK.pop();
          delay(10000);
        }
        else if (right > THRESHOLD + 40 && left > THRESHOLD + 40 && turn_right && front > THRESHOLD - 15) 
        {
          for (int i = 0; i < 2; i++) 
          {
            forward(50);
            delay(125);
            forward(0);
          }
          rightf(90);
          delay(230);
          rightf(0);
          turn_right = false;
          turn_left = false;
          truestack.push(4);
        }
        else if (front > THRESHOLD + 40 && right > THRESHOLD + 40 && turn_right) 
        {
          for (int i = 0; i < 4; i++) 
          {
            forward(50);
            delay(125);
            forward(0);
          }
          rightf(90);
          delay(230);
          rightf(0);
          turn_right = false;
          turn_left = false;
          truestack.push(4);
        }
        else if (left > THRESHOLD + 40 && front > THRESHOLD + 40 && turn_left) 
        {
          forward(50);
          delay(125);
          forward(0);
          truestack.push(1);
          turn_left = false;
        }
        else if (front > THRESHOLD - 15) 
        {
          if (right > left) 
          {
            digitalWrite(motor1A, LOW);
            digitalWrite(motor2A, LOW);
            analogWrite(motor1E, 175);
            analogWrite(motor2E, 120);
            delay(60);
            forward(0);
          }
          else if (left > right) 
          {
            digitalWrite(motor1A, LOW);
            digitalWrite(motor2A, LOW);
            analogWrite(motor1E, 120);
            analogWrite(motor2E, 175);
            delay(60);
            forward(0);
          }
          else 
          {
            forward(50);
            delay(125);
            forward(0);
          }
        }
        else if (right > THRESHOLD && turn_right) 
        {
          rightf(90);
          delay(230);
          rightf(0);
          turn_right = false;
          for (int i = 0; i < 2; i++) 
          {
            forward(50);
            delay(125);
            forward(0);
          }
          truestack.push(4);
        }
        else if (left > THRESHOLD && turn_left) 
        {
          leftf(90);
          delay(230);
          leftf(0);
          turn_left = false;
          for (int i = 0; i < 2; i++) 
          {
            forward(50);
            delay(125);
            forward(0);
          }
          truestack.push(5);
        }
        else if (turn_right && turn_left) 
        {
          rightf(90);
          delay(230);
          rightf(0);
          delay(150);
          rightf(90);
          delay(230);
          rightf(0);
          delay(150);
          turnbacktime = true;
          delay(2000);
        }
        else 
        {
          turn_right = true;
          turn_left = true;
        }
      }
      else if (turnbacktime) 
      {
        if (right > THRESHOLD && left > THRESHOLD && turn_right && front > THRESHOLD - 15) 
        {
          for (int i = 0; i < 2; i++) 
          {
            forward(50);
            delay(125);
            forward(0);
          }
          rightf(90);
          delay(230);
          rightf(0);
          turn_right = false;
          turnbacktime = false;
          truestack.pop();
          truestack.push(1);
          delay(2000);
        }
        else if (front > THRESHOLD + 40 && right > THRESHOLD + 40 && turn_right) 
        {
          for (int i = 0; i < 4; i++) 
          {
            forward(50);
            delay(125);
            forward(0);
          }
          rightf(90);
          delay(230);
          rightf(0);
          turn_right = false;
          turnbacktime = false;
          truestack.pop();
          truestack.push(5);
          delay(2000);
        }
        else if (left > THRESHOLD + 40 && front > THRESHOLD + 40 && turn_left) 
        {
          forward(50);
          delay(125);
          forward(0);
          turnbacktime = false;
          truestack.pop();
          truestack.push(5);
          turn_left = false;
          delay(2000);
        }
        else if (front > THRESHOLD - 10) 
        {
          if (right > left) 
          {
            digitalWrite(motor1A, LOW);
            digitalWrite(motor2A, LOW);
            analogWrite(motor1E, 175);
            analogWrite(motor2E, 120);
            delay(60);
            forward(0);
          }
          else if (left > right) 
          {
            digitalWrite(motor1A, LOW);
            digitalWrite(motor2A, LOW);
            analogWrite(motor1E, 120);
            analogWrite(motor2E, 175);
            delay(60);
            forward(0);
          }
          else 
          {
            forward(50);
            delay(125);
            forward(0);
          }
        }
        else if (right > THRESHOLD && turn_right) 
        {
          rightf(90);
          delay(230);
          rightf(0);
          turn_right = false;
          for (int i = 0; i < 2; i++) 
          {
            forward(50);
            delay(125);
            forward(0);
          }
          truestack.pop();
        }
        else if (left > THRESHOLD && turn_left) 
        {
          leftf(90);
          delay(230);
          leftf(0);
          turn_left = false;
          for (int i = 0; i < 2; i++) 
          {
            forward(50);
            delay(125);
            forward(0);
          }
          truestack.pop();
        }
        else 
        {
          turn_right = true;
          turn_left = true;
        }
      }
    }
    else if (lefthandstack.count() < righthandstack.count()) 
    {
      if (!(turnbacktime)) 
      {
        if (left > 500 && front > 500 && right > 500) 
        {
          rightf(90);
          delay(230);
          rightf(0);
          delay(150);
          rightf(90);
          delay(230);
          rightf(0);
          trial = false;
          last = true;
          int yeah = truestack.count();
          for (int i = 0; i < yeah; i++) 
          {
            PARENTSTACK.push(truestack.pop());
          }
          a = PARENTSTACK.pop();
          delay(10000);
        }
        else if (right > THRESHOLD + 40 && left > THRESHOLD + 40 && turn_left && front > THRESHOLD - 15) 
        {
          for (int i = 0; i < 2; i++) 
          {
            forward(50);
            delay(125);
            forward(0);
          }
          leftf(90);
          delay(230);
          leftf(0);
          turn_right = false;
          turn_left = false;
          truestack.push(5);
        }
        else if (front > THRESHOLD + 40 && left > THRESHOLD + 40 && turn_left) 
        {
          for (int i = 0; i < 4; i++) 
          {
            forward(50);
            delay(125);
            forward(0);
          }
          rightf(90);
          delay(230);
          rightf(0);
          turn_right = false;
          turn_left = false;
          truestack.push(5);
        }
        else if (right > THRESHOLD + 40 && front > THRESHOLD + 40 && turn_right) 
        {
          forward(50);
          delay(125);
          forward(0);
          truestack.push(1);
          turn_right = false;
        }
        else if (front > THRESHOLD - 15) 
        {
          if (right > left) 
          {
            digitalWrite(motor1A, LOW);
            digitalWrite(motor2A, LOW);
            analogWrite(motor1E, 175);
            analogWrite(motor2E, 120);
            delay(60);
            forward(0);
          }
          else if (left > right) 
          {
            digitalWrite(motor1A, LOW);
            digitalWrite(motor2A, LOW);
            analogWrite(motor1E, 120);
            analogWrite(motor2E, 175);
            delay(60);
            forward(0);
          }
          else 
          {
            forward(50);
            delay(125);
            forward(0);
          }
        }
        else if (left > THRESHOLD && turn_left) 
        {
          leftf(90);
          delay(230);
          leftf(0);
          turn_left = false;
          for (int i = 0; i < 2; i++) 
          {
            forward(50);
            delay(125);
            forward(0);
          }
          truestack.push(5);
        }
        else if (right > THRESHOLD && turn_right) 
        {
          rightf(90);
          delay(230);
          rightf(0);
          turn_right = false;
          for (int i = 0; i < 2; i++) 
          {
            forward(50);
            delay(125);
            forward(0);
          }
          truestack.push(4);
        }
        else if (turn_right && turn_left) 
        {
          rightf(90);
          delay(230);
          rightf(0);
          delay(150);
          rightf(90);
          delay(230);
          rightf(0);
          delay(150);
          turnbacktime = true;
          delay(2000);
        }
        else 
        {
          turn_right = true;
          turn_left = true;
        }
      }
      else if (turnbacktime) 
      {
        if (right > THRESHOLD && left > THRESHOLD && turn_left && front > THRESHOLD - 15) 
        {
          for (int i = 0; i < 2; i++) 
          {
            forward(50);
            delay(125);
            forward(0);
          }
          leftf(90);
          delay(230);
          leftf(0);
          turn_left = false;
          turnbacktime = false;
          truestack.pop();
          truestack.push(1);
          delay(2000);
        }
        else if (front > THRESHOLD + 40 && left > THRESHOLD + 40 && turn_left) 
        {
          for (int i = 0; i < 4; i++) 
          {
            forward(50);
            delay(125);
            forward(0);
          }
          leftf(90);
          delay(230);
          leftf(0);
          turn_left = false;
          turnbacktime = false;
          truestack.pop();
          truestack.push(5);
          delay(2000);
        }
        else if (right > THRESHOLD + 40 && front > THRESHOLD + 40 && turn_right) 
        {
          forward(50);
          delay(125);
          forward(0);
          turnbacktime = false;
          truestack.pop();
          truestack.push(5);
          turn_right = false;
          delay(2000);
        }
        else if (front > THRESHOLD - 10) 
        {
          if (right > left) 
          {
            digitalWrite(motor1A, LOW);
            digitalWrite(motor2A, LOW);
            analogWrite(motor1E, 175);
            analogWrite(motor2E, 120);
            delay(60);
            forward(0);
          }
          else if (left > right) 
          {
            digitalWrite(motor1A, LOW);
            digitalWrite(motor2A, LOW);
            analogWrite(motor1E, 120);
            analogWrite(motor2E, 175);
            delay(60);
            forward(0);
          }
          else 
          {
            forward(50);
            delay(125);
            forward(0);
          }
        }
        else if (left > THRESHOLD && turn_left) 
        {
          leftf(90);
          delay(230);
          leftf(0);
          turn_left = false;
          for (int i = 0; i < 2; i++) 
          {
            forward(50);
            delay(125);
            forward(0);
          }
          truestack.pop();
        }
        else if (right > THRESHOLD && turn_right) 
        {
          rightf(90);
          delay(230);
          rightf(0);
          turn_right = false;
          for (int i = 0; i < 2; i++) 
          {
            forward(50);
            delay(125);
            forward(0);
          }
          truestack.pop();
        }
        else 
        {
          turn_right = true;
          turn_left = true;
        }
      }
    }

    // last trip
    else if (last) 
    {
      if (righthandstack.count() <= lefthandstack.count()) 
      {
        if (a == 31) 
        {
          forward(50);
          delay(125);
          forward(0);
        }
        else if (parent) 
        {
          forward(50);
          delay(125);
          forward(0);
        }
        else if (a == 4) 
        {
          if (right > THRESHOLD + 40 && left > THRESHOLD + 40 && turn_right) 
          {
            for (int i = 0; i < 2; i++) 
            {
              forward(50);
              delay(125);
              forward(0);
            }
            parent = true;
            rightf(90);
            delay(230);
            rightf(0);
            turn_right = false;
            if (PARENTSTACK.count() > 0) 
            {
              a = PARENTSTACK.pop();
            }
            else 
            {
              a = 31;
            }
          }
          else if (front > THRESHOLD + 40 && right > THRESHOLD + 40 && turn_right) 
          {
            for (int i = 0; i < 4; i++) 
            {
              forward(50);
              delay(125);
              forward(0);
            }
            parent = true;
            rightf(90);
            delay(230);
            rightf(0);
            turn_right = false;
            if (PARENTSTACK.count() > 0) 
            {
              a = PARENTSTACK.pop();
            }
            else 
            {
              a = 31;
            }
          }
          else if (front > THRESHOLD - 10) 
          {
            if (right > left) 
            {
              digitalWrite(motor1A, LOW);
              digitalWrite(motor2A, LOW);
              analogWrite(motor1E, 175);
              analogWrite(motor2E, 120);
              delay(60);
              forward(0);
            }
            else if (left > right) 
            {
              digitalWrite(motor1A, LOW);
              digitalWrite(motor2A, LOW);
              analogWrite(motor1E, 120);
              analogWrite(motor2E, 175);
              delay(60);
              forward(0);
            }
            else 
            {
              forward(50);
              delay(125);
              forward(0);
            }
          }
          else if (right > THRESHOLD && turn_right) 
          {
            rightf(90);
            delay(230);
            rightf(0);
            turn_right = false;
            parent = true;
            for (int i = 0; i < 2; i++) 
            {
              forward(50);
              delay(125);
              forward(0);
            }
            if (PARENTSTACK.count() > 0) 
            {
              a = PARENTSTACK.pop();
            }
            else 
            {
              a = 31;
            }
          }
        }
        else if (a == 5) 
        {
          if (right > THRESHOLD + 40 && left > THRESHOLD + 40 && turn_left) 
          {
            for (int i = 0; i < 2; i++) 
            {
              forward(50);
              delay(125);
              forward(0);
            }
            leftf(90);
            delay(230);
            leftf(0);
            turn_left = false;
            parent = true;
            if (PARENTSTACK.count() > 0) 
            {
              a = PARENTSTACK.pop();
            }
            else 
            {
              a = 31;
            }
          }
          else if (left > THRESHOLD + 40 && front > THRESHOLD + 40 && turn_left) 
          {
            for (int i = 0; i < 4; i++) 
            {
              forward(50);
              delay(125);
              forward(0);
            }
            parent = true;
            leftf(90);
            delay(230);
            leftf(0);
            turn_left = false;
            if (PARENTSTACK.count() > 0) 
            {
              a = PARENTSTACK.pop();
            }
            else 
            {
              a = 31;
            }
          }
          else if (front > THRESHOLD - 10) 
          {
            if (right > left) 
            {
              digitalWrite(motor1A, LOW);
              digitalWrite(motor2A, LOW);
              analogWrite(motor1E, 175);
              analogWrite(motor2E, 120);
              delay(60);
              forward(0);
            }
            else if (left > right) 
            {
              digitalWrite(motor1A, LOW);
              digitalWrite(motor2A, LOW);
              analogWrite(motor1E, 120);
              analogWrite(motor2E, 175);
              delay(60);
              forward(0);
            }
            else 
            {
              forward(50);
              delay(125);
              forward(0);
            }
          }
          else if (left > THRESHOLD && turn_left) 
          {
            parent = true;
            leftf(90);
            delay(230);
            leftf(0);
            turn_left = false;
            for (int i = 0; i < 2; i++) 
            {
              forward(50);
              delay(125);
              forward(0);
            }
            if (PARENTSTACK.count() > 0) 
            {
              a = PARENTSTACK.pop();
            }
            else 
            {
              a = 31;
            }
          }
        }
        else if (a == 1) 
        {
          if (front > THRESHOLD && right > THRESHOLD && turn_right) 
          {
            turn_right = false;
            for (int i = 0; i < 4; i++) 
            {
              forward(50);
              delay(125);
              forward(0);
            }
            if (PARENTSTACK.count() > 0) 
            {
              a = PARENTSTACK.pop();
            }
            else 
            {
              a = 31;
            }
            parent = true;
          }
          else 
          {
            forward(50);
            delay(125);
            forward(0);
          }
        }
      }
      else if (lefthandstack.count() <= righthandstack.count()) 
      {
        if (a == 31) 
        {
          forward(50);
          delay(125);
          forward(0);
        }
        else if (parent) 
        {
          forward(50);
          delay(125);
          forward(0);
        }
        else if (a == 5) 
        {
          if (left > THRESHOLD + 40 && right > THRESHOLD + 40 && turn_left) 
          {
            for (int i = 0; i < 2; i++) 
            {
              forward(50);
              delay(125);
              forward(0);
            }
            parent = true;
            leftf(90);
            delay(230);
            leftf(0);
            turn_left = false;
            if (PARENTSTACK.count() > 0) 
            {
              a = PARENTSTACK.pop();
            }
            else 
            {
              a = 31;
            }
          }
          else if (front > THRESHOLD + 40 && left > THRESHOLD + 40 && turn_left) 
          {
            for (int i = 0; i < 4; i++) 
            {
              forward(50);
              delay(125);
              forward(0);
            }
            parent = true;
            leftf(90);
            delay(230);
            leftf(0);
            turn_left = false;
            if (PARENTSTACK.count() > 0) 
            {
              a = PARENTSTACK.pop();
            }
            else 
            {
              a = 31;
            }
          }
          else if (front > THRESHOLD - 10) 
          {
            if (right > left) 
            {
              digitalWrite(motor1A, LOW);
              digitalWrite(motor2A, LOW);
              analogWrite(motor1E, 175);
              analogWrite(motor2E, 120);
              delay(60);
              forward(0);
            }
            else if (left > right) 
            {
              digitalWrite(motor1A, LOW);
              digitalWrite(motor2A, LOW);
              analogWrite(motor1E, 120);
              analogWrite(motor2E, 175);
              delay(60);
              forward(0);
            }
            else 
            {
              forward(50);
              delay(125);
              forward(0);
            }
          }
          else if (left > THRESHOLD && turn_left) 
          {
            leftf(90);
            delay(230);
            leftf(0);
            turn_left = false;
            parent = true;
            for (int i = 0; i < 2; i++) 
            {
              forward(50);
              delay(125);
              forward(0);
            }
            if (PARENTSTACK.count() > 0) 
            {
              a = PARENTSTACK.pop();
            }
            else 
            {
              a = 31;
            }
          }
        }
        else if (a == 4) 
        {
          if (right > THRESHOLD + 40 && left > THRESHOLD + 40 && turn_right) 
          {
            for (int i = 0; i < 2; i++) 
            {
              forward(50);
              delay(125);
              forward(0);
            }
            rightf(90);
            delay(230);
            rightf(0);
            turn_right = false;
            parent = true;
            if (PARENTSTACK.count() > 0) 
            {
              a = PARENTSTACK.pop();
            }
            else 
            {
              a = 31;
            }
          }
          else if (right > THRESHOLD + 40 && front > THRESHOLD + 40 && turn_right) 
          {
            for (int i = 0; i < 4; i++) 
            {
              forward(50);
              delay(125);
              forward(0);
            }
            parent = true;
            rightf(90);
            delay(230);
            rightf(0);
            turn_right = false;
            if (PARENTSTACK.count() > 0) 
            {
              a = PARENTSTACK.pop();
            }
            else 
            {
              a = 31;
            }
          }
          else if (front > THRESHOLD - 10) 
          {
            if (right > left) 
            {
              digitalWrite(motor1A, LOW);
              digitalWrite(motor2A, LOW);
              analogWrite(motor1E, 175);
              analogWrite(motor2E, 120);
              delay(60);
              forward(0);
            }
            else if (left > right) 
            {
              digitalWrite(motor1A, LOW);
              digitalWrite(motor2A, LOW);
              analogWrite(motor1E, 120);
              analogWrite(motor2E, 175);
              delay(60);
              forward(0);
            }
            else 
            {
              forward(50);
              delay(125);
              forward(0);
            }
          }
          else if (right > THRESHOLD && turn_right) 
          {
            parent = true;
            rightf(90);
            delay(230);
            rightf(0);
            turn_right = false;
            for (int i = 0; i < 2; i++) 
            {
              forward(50);
              delay(125);
              forward(0);
            }
            if (PARENTSTACK.count() > 0) 
            {
              a = PARENTSTACK.pop();
            }
            else 
            {
              a = 31;
            }
          }
        }
        else if (a == 1) 
        {
          if (front > THRESHOLD && right > THRESHOLD && turn_left) 
          {
            turn_left = false;
            for (int i = 0; i < 4; i++) 
            {
              forward(50);
              delay(125);
              forward(0);
            }
            if (PARENTSTACK.count() > 0) 
            {
              a = PARENTSTACK.pop();
            }
            else 
            {
              a = 31;
            }
            parent = true;
          }
          else 
          {
            forward(50);
            delay(125);
            forward(0);
          }
        }
      }
    }
  }
}

void forward(int powa) 
{
  digitalWrite(motor1A, LOW);
  digitalWrite(motor2A, LOW);
  analogWrite(motor1E, powa+2);
  analogWrite(motor2E, powa);
}

void backward(int powa) 
{
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor2A, HIGH);
  analogWrite(motor1E, powa);
  analogWrite(motor2E, powa);
}

void leftf(int powa) 
{
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor2A, LOW);
  analogWrite(motor1E, powa);
  analogWrite(motor2E, powa);
}

void rightf(int powa) 
{
  digitalWrite(motor1A, LOW);
  digitalWrite(motor2A, HIGH);
  analogWrite(motor1E, powa);
  analogWrite(motor2E, powa);
}
