//******************************************************************************
// LAB 3: Timers and Interrupts
//
// MSP430G2553 Button-Based Delay
//
// Kyle Limbaga
// Rowan University
// Date Created: October 5, 2019
// Date Updated: October 5, 2019
//******************************************************************************

#include <msp430.h>

unsigned int buttonPressed;
unsigned int en = 0x00;
unsigned int count = 0;
unsigned int i = 0;

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer

  P1DIR |= BIT0;                            // Set P1.0 to output direction
  P1OUT &= ~BIT0;                           // Clear the LED

  P1IE |=  BIT3;                            // P1.3 interrupt enabled
  P1IES |= BIT3;                            // P1.3 Hi/lo edge
  P1REN |= BIT3;                            // Enable Pull Up on SW2 (P1.3)
  P1IFG &= ~BIT3;                           // P1.3 IFG cleared
                                            //BIT3 on Port 1 can be used as Switch2

  int n;
  TA0CCTL0 = CCIE; // Enable interrupt in compare mode
  TA0CTL = TASSEL_2 + MC_1 + ID_2; // SMCLK/4, Up
  n = 250000 / 10; //250000 / 10 = 25000
  TA0CCR0 = n; // ( 10^6 [Hz] / 4) / (25000) = 10Hz

  __enable_interrupt();

  __bis_SR_register(LPM0 + GIE); // enable interrupts in LPM0

}


#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
    if (en != 0x00)
    {
        if (P1IN & BIT3) // Reset count and enabled when button is up
        {
            buttonPressed = 0;
            en = 0;
            count = 0;
        }

        else    // Increment i while the button is pressed on each timer interrupt
        {
            P1OUT |= BIT0;
            i++;
        }


    }

    else // Increment until count == i
    {
        if (count == i) // Toggle every i interrupts (i * 0.1 = 5 s)
        {
            P1OUT ^= BIT0; //Toggle LED
            count = 0;  // reset count
        }

        else
            count++;    // increment count each interrupt until count = i
    }
}

// Port 1 interrupt routine
#pragma vector = PORT1_VECTOR
__interrupt void PORT_1(void)
{
    en = 1;
    i = 0; // Reset timing counter
    buttonPressed = 1;
    P1IFG &= ~BIT3; // Clear interrupt flag
}

