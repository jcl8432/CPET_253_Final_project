/**************************************************************/
/*** Developer: Jacob Loretz                                ***/
/*** Title: lab8_main.cpp								    ***/
/*** Description: This program will follow a black line		***/
/*** by using infared sensors on the bottom of the board    ***/
/**************************************************************/


#include "msp.h"
#include <msp432.h>
#include <stdint.h>
#include <stdbool.h>
#include "../inc/Clock.h"
#include "../inc/CortexM.h"
#include "../inc/motor.h"
#include "../inc/Init_Ports.h"
#include "../inc/Init_Timers.h"
#include "../inc/Reflectance.h"


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


    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    Clock_Init48MHz();  // makes bus clock 48 MHz

    //call all the port initialization functions
    Port2_Init(); // Debugging leds for making sure it goes through states
    Port3_Init();
    Port4_Init();
    Port5_Init(); // motors Port and the IR led
    Port9_Init(); // Odd IR LED


    //call all the timer initialization functions
    TimerA0_Init();


    //These are the states of the state machine
    enum robotState {FORWARD_MOVE,CORRECT_LEFT,CORRECT_RIGHT} state, prevState;//These are the states of the state machine
    state = FORWARD_MOVE;          //start in FORWARD state
    prevState = !FORWARD_MOVE;   //used to know when the state has changed
    uint16_t stateTimer = 0;           //used to stay in a state
    bool isNewState;              //true when the state has switched

    int32_t reflectance_value;
    uint32_t time = 1500;
    uint8_t data;




    while(1) {

            isNewState = (state != prevState);
            prevState = state;
            data = Reflectance_Read(time);
            reflectance_value = Reflectance_Position(data);
            // printf(" reflectance value: %d\n",reflectance_value);

            switch (state) {
            case FORWARD_MOVE:
               if(isNewState)
               {

                  // stateTimer = 0; //Sets state timer to 0
                  Motor_Forward(5999,5999); // motor movement moving forward
                  LED_Color(RED); // debugging purposes



               }
               // stateTimer++;
               if(reflectance_value <= -50)
               {
                   state = CORRECT_LEFT;

               }
               if(reflectance_value >= 50)
               {
            	   state = CORRECT_RIGHT;
               }
               break;
            case CORRECT_LEFT:
            	if(isNewState)
            	{

            		// stateTimer = 0; // sets state timer to 0
            		Motor_Left(2999,6999); // motor movement turning left
            		LED_Color(PURPLE); // debugging purposes
            	}
            	// stateTimer++; // incrementing state timer
            	if(reflectance_value >= -50)
            	{
            		state = FORWARD_MOVE;
            	}
            	break;
            case CORRECT_RIGHT:
            	if(isNewState)
            	{
            	    // stateTimer = 0; // sets state timer to 0
            		Motor_Right(6999,2999); // motor movement turning right
            		LED_Color(BLUE); // debugging purposes
            	}
            	// stateTimer++; // incrementing state timer
            	if(reflectance_value <= 50)
            	{
            		state = FORWARD_MOVE;
            	}
            	break;



            } //switch
            Clock_Delay1ms(20);
        }  //while
}
