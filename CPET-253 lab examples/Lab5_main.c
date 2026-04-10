/****************************************************************************************
         CPET253 Lab5 - Servos and Ultrasonic Sensing

 Jeanne Christman
 original version 1/19/2025

 This program uses an ultrasonic sensor to determine when there is an object in front of a
 forward moving robot. Once it is determined that the robot is approaching an object, it backs up,
 stops and then controls a servo motor to sweep the sensor 90 degrees right then 90 degrees left.
 A distance measurement is taken on each sweep. The robot then turns in the direction that is "more
 clear" and continues forward again.

 The servo motor is controlled by a PWM signal from TimerA3. The period of the PWM signal is 20ms
 and the pulse width ranges from 1 ms to 2 ms to control the sweep. The PWM signal is output on
 pin P9.2

 The ultrasonic sensor trigger is connected to pin P6.2 and the echo is connected to pin P6.3. The
 distance measurement is calculated using the width of the pulse returned from the sensor. TimerA2
 is used to determine the duration of the pulse from the sensor.

 Functions in this code:
     -Clock_Init48MHz() - function provided by TI to set system clock
     -Clock_Delay1ms(time) - built in function that delays time ms
     -Clock_Delay1us(time) - built in function that delays time us
     -Port2_Init();
     -Port3_Init();
     -Port5_Init();
     -Port6_Init();
     -Port9_Init();
     -TimerA0_Init();
     -TimerA2_Init();
     -TimerA3_Init();
     -Motor_Forward(volatile uint16_t rightDuty, volatile uint16_t leftDuty );
     -Motor_Backward(volatile uint16_t rightDuty, volatile uint16_t leftDuty );
     -Motor_Right(volatile uint16_t rightDuty, volatile uint16_t leftDuty );
     -Motor_Left(volatile uint16_t rightDuty, volatile uint16_t leftDuty );
     -Motor_Stop();

The state machine has 6 states; forward, turn right, turn left, backward, sweep right, sweep left
*******************************************************************************************/


#include "msp.h"
#include <msp432.h>
#include <stdint.h>
#include <stdbool.h>
#include "../inc/Clock.h"
#include "../inc/CortexM.h"
#include "../inc/motor.h"
#include "../inc/Init_Ports.h"
#include "../inc/Init_Timers.h"

#define TRIGGER 0x04
#define ECHO 0x08

#define microsecondsToClockCycles(a) ( (a) * 1.5 )       //assume 12Mhz clock divided by 8
#define clockCyclesToMicroseconds(a) ( (a) /  1.5 )       // 1.5 clock cycles = 1us

void Servo(uint16_t angle);
uint32_t pulseIn (void);


void ServoInit(void)  //This function initializes the servo to be centered (0 degrees)
{
    Servo(4499);//call Servo() function to center servo
    Clock_Delay1ms(100);//delay here to give servo time to move - can use built in timer function
    TA3CTL &= ~0x0030;//stop the timer
    return;
}
void Servo(uint16_t angle_count) // this function moves the servo.
//input: angle_count should be in terms of clock counts to create the 
//desired pulse width in the PWM signal
{
    TA3CCR0 = 59999;//set period for 20ms
    TA3CCR3 = angle_count;//set high time for the input angle using angle_count
    Clock_Delay1ms(100);//delay here to give servo time to move - can use built in timer function
    TA3CTL |= 0x0010;//set timer for up mode
    return;
}
uint16_t distanceInCm(void) {  //this function measures and returns the distance to the nearest object
    uint16_t distance;

    P6OUT |= BIT2;//drive trigger pin high
    Clock_Delay1ms(0.1);//wait 10 us - can use built-in timer function
    P6OUT &= ~BIT2;//drive trigger pin low
    distance = pulseIn() * (0.034 / 2);//calculate distance using s=t * 0.034/2. t comes from pulseIn() function
    if(distance == 0)
    {
        distance = 0;// if no echo (distance = 0), assume object is at farthest distance
    }
    else
    {
        distance = distance;
    }
    return distance;//return the distance
}
uint32_t pulseIn (void)  //this function returns the width of the return pulse
//from the ultrasonic sensor in terms of microseconds
{
    uint16_t width = 0;   //will be in clock counts
    uint16_t time = 0;    //the result of converting clock counts to microseconds
    uint16_t maxcount = 56999;  //max count for 38 ms (timeout)

    TA2CTL |= 0x0220;//set timer for continuous mode

    TA2R = 0;//reset the count register
    while((P6IN & BIT3) == 0b00000000)
    {
        //wait for the pulse to start (while Echo is low)

        if (TA2R > maxcount)
        {
            return 0;//if count is greater than maxcount return 0
        }
    }
    TA2R = 0;//reset the count register
    while((P6IN & BIT3) != 0b00000000)
    {
        //wait for the pulse to finish (while Echo is high)

        if(TA2R > maxcount)
        {
            return 0;//if count is greater than maxcount return 0
        }
    }

    width = TA2R;//read the count (width of the return pulse)
    TA2CTL &= ~0x0030;//stop the timer
    time = clockCyclesToMicroseconds(width);//convert the reading to microseconds.
    return time;//return the microsecond reading
}

//debugging purposes
#define RED 0x01
#define GREEN 0x02
#define BLUE 0X04
#define PURPLE (BIT0 | BIT2)

void LED_Color (uint8_t color) {
//This is a simple function to turn on the multi-colored LED on the MSP432 Launchpad
//board according to the argument passed into the function
//The LED is controlled by bits 0, 1 and 2 on PORT2
   P2OUT &= ~0X07;                   //first turn off all colors
   P2OUT |= color;                   //second turn on the input color
}
//********************//

void main(void)
{

    uint16_t distance, right_wall, left_wall;

	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
	Clock_Init48MHz();  // makes bus clock 48 MHz
	//call all the port initialization functions
	Port2_Init();
    Port3_Init();
	Port5_Init();
	Port6_Init();
	Port9_Init();

	//call all the timer initialization functions
    TimerA0_Init();
    TimerA2_Init();
	TimerA3_Init();

	//center the servo using the ServoInit()
	ServoInit();

	

	//These are the states of the state machine
	enum robotState {FORWARD_MOVE,BACKWARDS_MOVE,RIGHT_SWEEP,LEFT_SWEEP,RIGHT_TURN,LEFT_TURN} state, prevState;//These are the states of the state machine
	state = FORWARD_MOVE;          //start in FORWARD state
	prevState = !FORWARD_MOVE;   //used to know when the state has changed
	uint16_t stateTimer = 0;           //used to stay in a state
	bool isNewState;              //true when the state has switched


   // Servo(1999);

	while(1) {

	    isNewState = (state != prevState);
        prevState = state;
	    distance = distanceInCm();  //this needs to be moved to the states in which it is used

	    switch (state) {
	    case FORWARD_MOVE:
	       if(isNewState)
	       {
	          ServoInit();
	          stateTimer = 0; //Sets state timer to 0
	          Motor_Forward(14999,14999);//motor movement moving forward
	          LED_Color(RED);//debugging purposes
	          distance = distanceInCm();

	          //stateTimer = 0; //Sets state timer to 0
	       }
	       stateTimer++;
	       if(distance < 12)
	       {
	           state = BACKWARDS_MOVE;

	       }
	       break;
	    case RIGHT_TURN:
	       if(isNewState)
	       {
	          stateTimer = 0; // sets state timer to 0
              Motor_Right(0,14999);//motor movement turning right
              LED_Color(BLUE);//debugging purposes


           }
           stateTimer++;
           if(stateTimer >= 30)
           {
              state = FORWARD_MOVE;

           }
           break;

        case BACKWARDS_MOVE:
          if(isNewState)
          {
              stateTimer = 0; // sets state timer to 0
              Motor_Backward(14999,14999);// Motor moving backwards
              LED_Color(GREEN);//debugging purposes


          }
          stateTimer++;
          if(stateTimer >= 25)
          {
              state = RIGHT_SWEEP;
           //   ServoInit();
              Motor_Stop();

          }
          break;
        case RIGHT_SWEEP:
          if(isNewState)
          {
              stateTimer = 0;
              Servo(1999);
              LED_Color(PURPLE);//debugging purposes
              stateTimer = 0;

          }

          stateTimer++;
          if(stateTimer >= 50)
          {
              state = LEFT_SWEEP;
              right_wall = distanceInCm();
             // ServoInit();
          }


          break;
        case LEFT_SWEEP:
          if(isNewState)
             {
              stateTimer = 0;
              Servo(7999);
              LED_Color(PURPLE);//debugging purposes

              }
              stateTimer++;
              if(stateTimer >= 50)
              {
                  left_wall = distanceInCm();
                  if(left_wall < right_wall)
                  {
                      state = RIGHT_TURN;
                  }
                  else
                  {
                      state = LEFT_TURN;
                  }
              }

              break;
            case LEFT_TURN:
            if(isNewState)
            {
                stateTimer = 0;
                Motor_Left(14999,0);
                LED_Color(RED);

            }
            stateTimer++;
            if(stateTimer >= 30)
            {
                state = FORWARD_MOVE;
                ServoInit();
            }
            break;



	    } //switch
        Clock_Delay1ms(20);
	}  //while
}
