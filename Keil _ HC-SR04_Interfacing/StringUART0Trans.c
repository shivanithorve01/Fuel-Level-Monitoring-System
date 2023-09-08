#include "lib_funcs.h"
void UART0_String_Tx(unsigned char *serial_ptr)
{
	unsigned int i;
	for(i=0; serial_ptr[i] != '\0'; i++)
	{
		uartWrite(serial_ptr[i]);
	}
}
