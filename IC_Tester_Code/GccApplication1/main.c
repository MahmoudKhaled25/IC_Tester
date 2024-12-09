/*
 * GccApplication1.c
 *
 * Created: 11/4/2024 6:11:43 PM
 * Author : Blu-Ray
 */ 

#include "main.h"

const c8 *s;

int main(void)
{
    /* Replace with your application code */
	DIO_INIT();
	LCD_INIT();
	
	LCD_CLR();
	s = test_ic_74xx();
	LCD_WRITE_STRING(s);
	
    while (1) 
    {
		
    }
	
	return 0; 
}
 
