#include <elapsedMillis.h>
#include <Arduino.h>

/**********************************/
const int laserPin1 = 3;
const int laserPin2 = 4;
const int firePin = 5;
const int firePin2= 6; //initialize pins on board
unsigned long laser1timer1;
unsigned long laser2timer1;
unsigned long laser1timer2;
unsigned long laser2timer2;
boolean lasera = false;
boolean laserb = false;
boolean laseradelay = false;
boolean laserbdelay = false;
/**********************************/
void setup()
{
  pinMode(laserPin1,INPUT);
  pinMode(laserPin2,INPUT);
  pinMode(firePin,OUTPUT);
  pinMode(firePin2,OUTPUT); //initialize input and output pins
}
/**********************************/
void loop()
{ 
if(lasera == false && digitalRead(laserPin1) ==HIGH ) //check timer when laser is fired
  {
    digitalWrite(firePin,HIGH); 
    laser1timer1 = millis();
    laser1timer2 = millis();
    lasera = true;
    laseradelay = false; //fire laser and start cooldowns
  }
if(laserb == false && digitalRead(laserPin2) ==HIGH)
  {
    digitalWrite(firePin2,HIGH);
    laser2timer1 = millis();
    laser2timer2 = millis();
    laserb = true;
    laserbdelay = false;
  }
if (lasera == true && laseradelay == false && millis()-laser1timer1 >= 500UL)
  {
    digitalWrite(firePin, LOW);
    laser1timer2 = millis();
    laseradelay = true; //force laser delay before next fire
  }
if (laserb == true && laserbdelay == false && millis()-laser2timer1 >= 500UL )
  {
    digitalWrite(firePin2, LOW);
    laser2timer2 = millis();
    laserbdelay = true;
  }
if (lasera == true && millis()-laser1timer2 >= 600UL ) //set time for cooldown
  {
    lasera = false;
  }
if (laserb == true && millis()-laser2timer2 >= 600UL )
  {
    laserb = false;
  }
}
/************************************/
