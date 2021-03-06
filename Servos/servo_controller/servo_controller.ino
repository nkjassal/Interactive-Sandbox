#include <Servo.h>

Servo s0, s1, s2, s3, s4, s5, s6, s7, s8;
Servo servos[] = {s0, s1, s2, s3, s4, s5, s6, s7, s8};

/* for each servo (corresponding to the index), the arduino pin
 * at which it's attached */
int pins[] = {2,3,4,5,6,7,8,9,10};

/* high and low values platform corresponding to each servo */
int servo_low[] = {130, 140, 150, 4, 60, 143, 8, 154, 150};
int servo_high[] = {165, 175, 177, 25, 95, 170, 25, 177, 177};
int servo_pos[9];
int servo_vel[] = {5,1,2,6,3,7,2,3,4};

//void sweep_all();
//void sweep_servo(int servo_num);


void setup()
{
  // begin serial communication and attach servos
  Serial.begin(9600);
  for(int i = 0; i < 9; i++) {
    servos[i].attach(pins[i]);
    servos[i].write(servo_high[i]);
  // servo_pos[9] = (int)random(0,360);
  }
  
  //s0.attach(pins[0]);

  
  
}

void loop()
{
  sweep_servo(random(8));
  delay(500);
  /*for(int i = 0; i < 9; i++) {
    float servo_pos_rads = servo_pos[9]/180*3.1415926535;
    
    double nextpos = (sin(servo_pos_rads) + 1)/2;
    int lo = servo_low[i];
    int hi = servo_high[i];
    
    int actualpos = lo + (int)(nextpos*(hi-lo));
    servos[i].write(actualpos);
    
    servo_pos[i] = (servo_pos[i] + servo_vel[i]) % 360;
  }*/
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
      {
        heights[j]--;
        servos[j].write(heights[j]);
        delay(100);
      }
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
      {
        heights[j]++;
        servos[j].write(heights[j]);
        delay(100);
      }

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
