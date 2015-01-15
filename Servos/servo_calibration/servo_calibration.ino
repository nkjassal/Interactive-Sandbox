#include <Servo.h>

Servo servo;

/***
/* servo  0  1  2  3  4  5  6  7  8
/* weight 12       12       6

/*5 volts, expect 5.75 for sand */
/* low and high positions for all 9 arduinos, labeled and corresponding to the array index */
int servo_low[] = {145, 145, 0, 85, 40, 0, 155, 0, 130};
int servo_high[] = {180, 180, 0, 115, 70, 0, 180, 0, 170};

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

void setup()
{
  Serial.begin(9600);
  
  servo.attach(9);
  servo.write(180);
  /*delay(1000);
  servo.write(140);
  delay(1000);
  servo.write(175);*/
  
 sweep_servo(6);


}



void loop()
{
  sweep_servo(6);
}
