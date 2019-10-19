//******************************************************************************
//  Lab 3: Timers and Interrupt
//
//  MSP430FR6989 - Button Interrupt with P1.0 and P9.7
//
//
//   Kyle Limbaga
//   Rowan University
//   Date Started: October 14, 2019
//   Date Updated: September 14, 2019
//******************************************************************************

#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  PM5CTL0 &= ~LOCKLPM5;                     // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings

  P1DIR |= (BIT0);                          // Set P1.0 to output direction
  P1OUT &= ~(BIT0);                         // Clear the LED

  P9DIR |= BIT7;                            // Set P9.7 to output direction
  P9OUT &= ~BIT7;                            // Turn on LED

  P1IE |=  BIT1;                            // P1.1 interrupt enabled
  P1IES |= BIT1;                            // P1.1 Hi/lo edge
  P1REN |= BIT1;                            // Enable Pull Up on (P1.1)
  P1IFG &= ~BIT1;                           // P1.1 IFG cleared
                                            //BIT3 on Port 1 can be used as Switch2

  __enable_interrupt();


}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR;
__interrupt void Port_1(void)
{
   P1OUT ^= BIT0;                           // toggle LED 1.0
   P9OUT ^= BIT7;                           // toggle LED 9.7
   P1IFG &= ~BIT1;                          // Clear the Button IFG
}


