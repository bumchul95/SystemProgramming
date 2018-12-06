#include <stdio.h>
#include <wiringPi.h>

#define MOTOR1A 1
#define MOTOR1B 2

int main (void){
  if(wiringPiSetup()==-1)
  {
    return 1;
   }
  pinMode(MOTOR1A,OUTPUT);
  pinMode(MOTOR1B,OUTPUT);

  for(;;){
    digitalWrite(MOTOR1A,1);
    digitalWrite(MOTOR1B,0);
    
    delay(1000);

    digitalWrite(MOTOR1A,0);
    digitalWrite(MOTOR1B,0);
     
    delay(1000);
  }
  return 0;
}
