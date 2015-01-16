#include <Servo.h>

Servo servo;

/***
/* servo  0  1  2  3  4  5  6  7  8
/* weight 

/*5 volts, expect 5.75 for sand */
/* low and high positions for all 9 arduinos, labeled and corresponding to the array index */
int servo_low[] = {0, 0, 150, 4, 0, 143, 8, 154, 150};
int servo_high[] = {0, 0, 177, 25, 0, 170, 25, 177, 177};


void setup()
{
  Serial.begin(9600);
  
  servo.attach(9);
  servo.write(8);
  /*delay(3000);
  servo.write(10);*/
  //delay(1000);
  //servo.write(175);
  
 //sweep_servo(8);


}


void loop()
{
  sweep_servo(3);
}


void sweep_servo(int num)
{
  Serial.println(servo.read());
  int height = servo.read();
  while(height > servo_low[num])
  {
    height--;
    servo.write(height);
    delay(20);
  }
  while(height < servo_high[num])
  {
    height++;
    servo.write(height);
    delay(20);
  }
}
