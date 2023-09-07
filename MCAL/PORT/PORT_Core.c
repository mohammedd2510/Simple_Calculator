 /**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  PORT_Core.c
 *        \brief  responsible for ports initialization
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "PORT_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
volatile static uint8* Direction_Registers[]={&GPIOA_DIRECTION_REGISTER,&GPIOB_DIRECTION_REGISTER,&GPIOC_DIRECTION_REGISTER,&GPIOD_DIRECTION_REGISTER};
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void PORT_Init(void)        
* \Description     : initializes all the pins directions                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : void                     
* \Parameters (out): void                                                      
* \Return value:   : void                                 
*******************************************************************************/
void PORT_Init(void)
{
	uint8 Cnt=0 , Port = 0 , Pin = 0 , Dir = 0;
	for(Cnt = 0; Cnt<DEFINED_PINS ; Cnt++){
		Port=PORT_Initialization[Cnt].PIN_NUM / NUMBER_OF_EACH_PORT_PINS;
		Pin=PORT_Initialization[Cnt].PIN_NUM % NUMBER_OF_EACH_PORT_PINS;
		Dir=PORT_Initialization[Cnt].PIN_DIR;
		
		switch (Dir)
		{
		case PIN_OUTPUT :
			SET_BIT(*Direction_Registers[Port],Pin);
			break;
		case  PIN_INPUT :
			CLR_BIT(*Direction_Registers[Port],Pin);
			break;
		default:
				break;
		}
	}
	
}

/**********************************************************************************************************************
 *  END OF FILE: PORT_Core.c
 *********************************************************************************************************************/