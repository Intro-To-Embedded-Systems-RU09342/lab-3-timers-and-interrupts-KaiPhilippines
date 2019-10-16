# Button Interrupt
In this lab instead of inefficently "Polling" and waiting around until something changes within a specific register, we are now using interrupts to toggle an LED. This is done with the use of P1IE and PIES registers on both the G2553 and FR6989. This code acts similar to Lab 2 for Button Blink. Using a button, it will toggle LED on and off. It has the same LED setup and button setup as the Button Blink. The only difference are the P1IE and P1IES as well as:
```c
__enable_interrupt();
```

```c
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
}
```



