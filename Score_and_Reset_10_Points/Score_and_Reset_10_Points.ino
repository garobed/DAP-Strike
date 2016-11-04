#include <elapsedMillis.h>
#include <Arduino.h>
#include <Suli.h>
#include <Four_Digit_Display_Arduino.h> //libraries for controlling 4 digit displays

/**********************************/
const int reset = 1; //when activated, resets scoresg 
const int winner1 = 4;
const int winner2 = 5;
const int keyPin2 = 11;
const int keyPin = 12;
const int ledPin = 13;
int score1 = 0;
int score2 = 0;
int score3 = 0;
int score4 = 0; //reset conditions
Four_Digit_Display_Arduino    disp;
unsigned long score1timer;
unsigned long score2timer;
boolean leda = false;
boolean ledb = false;
/**********************************/
void setup()
{
  disp.begin(2,3);
  disp.display(0, score1); 
  disp.display(1, score2);
  disp.display(2, score3);
  disp.display(3, score4); //write initial score digit values on displays
  pinMode(reset, INPUT);
  pinMode(keyPin2,INPUT);
  pinMode(keyPin,INPUT);
  pinMode(ledPin,OUTPUT);
  pinMode(winner1,OUTPUT);
  pinMode(winner2,OUTPUT); //indicate winner once score is reached

}
/**********************************/
void loop()
{
  if(leda == false && digitalRead(keyPin) ==HIGH) //if photocell allows current to pass (laser hits it), start delay timer for more scoring, raise score by 1, and rewrite display
  {
    digitalWrite(ledPin,HIGH);//indicator for testing
    score1timer = millis();
    leda = !leda;
    score1 = score1 + 1;
    if(score1 == 10) //carry over to next digit
    {
      score1 = 0;
      score2 = score2 + 1;
    }
    disp.display(3, score1);
    disp.display(2, score2);

  }
  if(ledb == false && digitalRead(keyPin2) ==HIGH) //same for player 2
  {
    digitalWrite(ledPin,HIGH);//turn on the led
    score2timer= millis(); 
    ledb = !ledb;
    score3 = score3 + 1;
    if(score3 == 10)
    {
      score3 = 0;
      score4 = score4 + 1;
    }
    disp.display(1, score3);
    disp.display(0, score4); 
  }
  else
  {
    digitalWrite(ledPin,LOW);//turn off the led
  }
if (leda == true && millis()-score1timer >= 500UL ) //once score delay timer is up, allow player to score again
  {
    leda = !leda;
    digitalWrite(ledPin, LOW);
  }
if (ledb == true && millis()-score2timer >= 500UL) //same for player 2
  {
    ledb = !ledb;
    digitalWrite(ledPin, LOW);
  }
if (digitalRead(reset) == HIGH) //if resets are pressed, set digits to 0 and rewrite display
  {
    score1 = 0;
    score2 = 0;
    score3 = 0;
    score4 = 0;
    disp.display(0, score4);
    disp.display(1, score3);
    disp.display(2, score2);
    disp.display(3, score1);
    digitalWrite(winner1,LOW);
    digitalWrite(winner2,LOW);
  }
while (score4 >= 1) //when score reaches limit, prevent players from scoring again
  {
    digitalWrite(winner1,HIGH);
    digitalWrite(keyPin,LOW);
    digitalWrite(keyPin2,LOW);
    if (digitalRead(reset) == HIGH) //reset to escape while loop and restart game
    {
      score1 = 0;
      score2 = 0;
      score3 = 0;
      score4 = 0;
      disp.display(0, score4);
      disp.display(1, score3);
      disp.display(2, score2);
      disp.display(3, score1);
      digitalWrite(winner1,LOW);
      digitalWrite(winner2,LOW);
    }
  }
while (score2 >= 1)
  {
    digitalWrite(winner2,HIGH);
    digitalWrite(keyPin,LOW);
    digitalWrite(keyPin2,LOW);
    if (digitalRead(reset) == HIGH)
    {
      score1 = 0;
      score2 = 0;
      score3 = 0;
      score4 = 0;
      disp.display(0, score4);
      disp.display(1, score3);
      disp.display(2, score2);
      disp.display(3, score1);
      digitalWrite(winner1,LOW);
      digitalWrite(winner2,LOW);
    }
  }  
}
/************************************/
