
//******************************************************************************

#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= (BIT0 + BIT6);                   // Set P1.0 and P1.6 to output direction
  P1OUT |= ~(BIT0 + BIT6);                  // Clear the LEDs

  P1IE |=  BIT3;                            // P1.3 interrupt enabled
  P1IES |= BIT3;                            // P1.3 Hi/lo edge
  P1REN |= BIT3;                            // Enable Pull Up on SW2 (P1.3)
  P1IFG &= ~BIT3;                           // P1.3 IFG cleared
                                            //BIT3 on Port 1 can be used as Switch2

  __enable_interrupt();

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
   P1OUT ^= BIT0;                           // toggle LED 1.0
   P1OUT ^= BIT6;                           // toggle LED 1.6
   P1IFG &= ~BIT3;                          // Clear the Button IFG

}

