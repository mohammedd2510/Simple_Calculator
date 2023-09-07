/*
 * App.c
 *
 * Created: 8/12/2023 3:34:43 PM
 * Author : Mohamed Osama
 */ 

#include "App.h"	

int main(void)
{
	Application_initialize();	
    while (1) 
    {
		calc_app();
	}
}

void Application_initialize(void){
	PORT_Init();
	LCD_Init();
	KEYPAD_Init();
}