#include <Servo.h>

Servo servo;

/* low and high positions for all 9 arduinos, labeled and corresponding to the array index */
int servo_low[] = {110};
int servo_high[] = {175, 180};

void setup()
{
  Serial.begin(9600);
  
  servo.attach(9);


}

void sweep_servo()
{
  Serial.println(servo.read());
  int height = servo.read();
  while(height > servo_low[0])
  {
    height--;
    servo.write(height);
    delay(20);
  }
  while(height < servo_high[0])
  {
    height++;
    servo.write(height);
    delay(20);
  }
}

void loop()
{
  sweep_servo();

}
