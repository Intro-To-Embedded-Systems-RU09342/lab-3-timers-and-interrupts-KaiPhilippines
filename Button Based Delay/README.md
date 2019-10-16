# Button Based Delay
In this repository includes two button based delay code for FR6989 and G2553. In this program, an LED is set at a rate of 10Hz. Then pressing one of the buttons on board, the time the button is held is counted by the TIMERA module, where SMCLK is selected, Up-Count selected, and clock divider of 4 selected. The program uses two interrupt service routine: TIMERA and PORT1. In TIMERA, nested if statement is used to find how long the button is pressed and getting a new value to use for the rate of the blink. In PORT1 is where the code initiates since when button is pressed the interrupt is activated. THe only difference between the boards are that in FR6989, the default high impedence is dispabled and the ports and button layouts are different from G2553. 


