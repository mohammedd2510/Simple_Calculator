/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  MCU.h
 *       Module: MCU Register Definitions
 *
 *  Description: has the definition of all the registers in the MCU  
 *  
 *********************************************************************************************************************/

#ifndef MCU_H_
#define MCU_H_
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "std_types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*************************************** GPIO Registers ************************************************/
#define PHYSICAL_GPIO_ACCESS(addr)      (*(volatile uint8*)(addr))
#define GPIOA_BASE_ADDRRESS             (0X39)
#define GPIOB_BASE_ADDRRESS             (0X36)
#define GPIOC_BASE_ADDRRESS             (0X33)
#define GPIOD_BASE_ADDRRESS             (0X30)

#define GPIO_INPUT_REGISTER_PIN         (0X00)
#define GPIO_DIRCETION_REGISTER_DDR     (0X01)
#define GPIO_OUTPUT_REGISTER_PORT       (0X02)

/*Direction Registers*/
#define GPIOA_DIRECTION_REGISTER PHYSICAL_GPIO_ACCESS(GPIOA_BASE_ADDRRESS+GPIO_DIRCETION_REGISTER_DDR)
#define GPIOB_DIRECTION_REGISTER PHYSICAL_GPIO_ACCESS(GPIOB_BASE_ADDRRESS+GPIO_DIRCETION_REGISTER_DDR)
#define GPIOC_DIRECTION_REGISTER PHYSICAL_GPIO_ACCESS(GPIOC_BASE_ADDRRESS+GPIO_DIRCETION_REGISTER_DDR)
#define GPIOD_DIRECTION_REGISTER PHYSICAL_GPIO_ACCESS(GPIOD_BASE_ADDRRESS+GPIO_DIRCETION_REGISTER_DDR)

/*Output Registers*/
#define GPIOA_OUTPUT_REGISTER PHYSICAL_GPIO_ACCESS(GPIOA_BASE_ADDRRESS+GPIO_OUTPUT_REGISTER_PORT)
#define GPIOB_OUTPUT_REGISTER PHYSICAL_GPIO_ACCESS(GPIOB_BASE_ADDRRESS+GPIO_OUTPUT_REGISTER_PORT)
#define GPIOC_OUTPUT_REGISTER PHYSICAL_GPIO_ACCESS(GPIOC_BASE_ADDRRESS+GPIO_OUTPUT_REGISTER_PORT)
#define GPIOD_OUTPUT_REGISTER PHYSICAL_GPIO_ACCESS(GPIOD_BASE_ADDRRESS+GPIO_OUTPUT_REGISTER_PORT)

/*Input Registers*/
#define GPIOA_INPUT_REGISTER PHYSICAL_GPIO_ACCESS(GPIOA_BASE_ADDRRESS+GPIO_INPUT_REGISTER_PIN)
#define GPIOB_INPUT_REGISTER PHYSICAL_GPIO_ACCESS(GPIOB_BASE_ADDRRESS+GPIO_INPUT_REGISTER_PIN)
#define GPIOC_INPUT_REGISTER PHYSICAL_GPIO_ACCESS(GPIOC_BASE_ADDRRESS+GPIO_INPUT_REGISTER_PIN)
#define GPIOD_INPUT_REGISTER PHYSICAL_GPIO_ACCESS(GPIOD_BASE_ADDRRESS+GPIO_INPUT_REGISTER_PIN)
/*******************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif /* MCU_H_ */

/**********************************************************************************************************************
 *  END OF FILE: 
 *********************************************************************************************************************/


