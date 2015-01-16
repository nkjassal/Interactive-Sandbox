#include <Servo.h>

Servo s0, s1, s2, s3, s4, s5, s6, s7, s8;
Servo servos[] = {s0, s1, s2, s3, s4, s5, s6, s7, s8};

/* for each servo (corresponding to the index), the arduino pin
 * at which it's attached */
int pins[] = {0};

/* high and low values platform corresponding to each servo */
int servo_low[] = {0};
int servo_high[] = {0};

void sweep_all();
void sweep_servo(int servo_num);


void setup()
{
  // begin serial communication and attach servos
  Serial.begin(9600);
  for(int i = 0; i < 9; i++)
    servos[i].attach(pins[i]);

}

void loop()
{
  
}

/* sweep_all - moves all servos up down to their low height 
 * and back up to the max height. Works regardless of start 
 * position of individual servos
 *
 * Works simultaneously - all servos will move one together,
 * one degree at a time
 */
void sweep_all()
{
  int heights[9];
  
  // get starting height for each
  for(int i = 0; i < 9; i++)
    heights[i] = servos[i].read();
    
  // move down
  while(1)
  {
    // if all low, exit down loop
    int all_low = 0;
    for(int k = 0; k < 9; k++)
    {
      if(heights[k] != servo_low[k])
      {
        all_low = 1;
        break;
      }
    }
    if(all_low == 0)  // all at lowest, stop
      break;
    
    // lower all heights by 1, set height
    for(int j = 0; j < 9; j++)
    {
      if(heights[j] != servo_low[j])
        heights[j]--;
    }  
  }
  
   // move back up
  while(1)
  {
    // if all high, exit down loop
    int all_low = 0;
    for(int k = 0; k < 9; k++)
    {
      if(heights[k] != servo_high[k])
      {
        all_low = 1;
        break;
      }
    }
    if(all_low == 0)  // all at highest, stop
      break;
    
    // raise all heights by 1, set height
    for(int j = 0; j < 9; j++)
    {
      if(heights[j] != servo_high[j])
        heights[j]++;
    }  
  }
  
  Serial.println("sweep of all servos complete");
}

/* sweep_servo - moves single servo down to lowest height
 * and back up to max height. works regardless of starting
 * position of the servo
 */
void sweep_servo(int servo_num)
{
  Servo servo = servos[servo_num];
  int height = servo.read();
  while(height > servo_low[servo_num])
  {
    height--;
    servo.write(height);
    delay(20);
  }
  while(height < servo_high[servo_num])
  {
    height++;
    servo.write(height);
    delay(20);
  }
  
  Serial.println("sweep individual servo complete");
}
