#include <lpc214x.h>
#include <stdio.h> //visit http://www.ocfreaks.com/retarget-redirect-printf-scanf-uart-keil/ 
#include "lib_funcs.h" //OCFreaks LPC214x Tutorials Library Header
#include "StringUART0Trans.c"
#include "FloatToString.c"
#include "doubleToString.c"
#define TRIG (1<<2) //P0.2
#define ECHO (1<<3) //P0.3

int main(void)
{
	initUART0();  //Initialize UART0 for retargeted printf()
	UART0_String_Tx(" Serial Initialized : ");
	initClocks(); //Set PCLK = CCLK = 60Mhz - used by: UART, Timer and ADC
	initTimer0(); //Init Timer for delay functions
	int echoTime=0;
	float distance1;
	unsigned char dist1;
	unsigned char finalltrs;

	IO0DIR |= TRIG;    //Set P0.2(TRIG) as output
	IO0DIR &= ~(ECHO); //Set P0.3(ECHO) as input (explicitly)
	IO0CLR |= TRIG;    //Set P0.2 LOW initially

	while(1)
	{
		//Output 10us HIGH on TRIG pin
		IO0SET |= TRIG;
		delayUS(10);
		IO0CLR |= TRIG;
	
		while(!(IO0PIN & ECHO)); //Wait for a HIGH on ECHO pin
		startTimer0(); //Start counting
		while(IO0PIN & ECHO); //Wait for a LOW on ECHO pin
		echoTime = stopTimer0()/10000; //Stop counting and save value(us) in echoTime

		distance1 = (echoTime)/58.20; //Find the distance
		UART0_String_Tx("\n Distance (in cm) : ");
		//initial_level_inltrs = (0.00231564 * distance1) + 0.80702712;
		//UART0_String_Tx(" You have ");
		//UART0_String_Tx(initial_level_inltrs);
		delayMS(100);
		dist1= float_to_string(distance1);
			for( int i=0;i<7;i++)
			{
				uartWrite(r[i]);
			}
		float finalliters = (431.3674714 * distance1) - 345.134817;
		finalltrs = float_to_string(finalliters);
		UART0_String_Tx("\t Litres (in ml) : ");
		for( int i=0;i<7;i++)
		{
				uartWrite(r[i]);
		}
		//}
		
		delayMS(1000); //wait 1 second for next update
	}
}

// distance = distance2 - distance1;
// final_level_inltrs = (0.00231564 * distance) + 0.80702712;


