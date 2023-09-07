/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Calculator.c 
 *        \brief  contains the implementation of Calculator functions
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Calculator.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static uint8 button=0;
static float64 val1=0;
static float64 val2=0;
static float64 val3=0;
static Operations_t operation1=init;
static Operations_t operation2=init;
static Operations_t Last_operation=init;
static calc_states_t state =initial_state;
static float64 Result=0;
uint8 error_flag=0; // used to indicate there's an error to go to error state
uint8 float_result_flag=0; // used to indicate that there's result in float
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/******************************************************************************
* \Syntax          : static void calc_init_state(void);
* \Description     : start the calculator initial state where you insert first number or minus sign
*******************************************************************************/
static void calc_init_state(void);
/******************************************************************************
* \Syntax          : static void calc_1st_num_neg (void);
* \Description     : start calculator 1st_num_neg state where you insert negative number at first
*******************************************************************************/
static void calc_1st_num_neg (void);
/******************************************************************************
* \Syntax          : static void calc_After_init_state (void);
* \Description     : start the calculator 1st_number_After_init_state,
					 where you can insert operator or another digit for your first number
*******************************************************************************/
static void calc_After_init_state (void);
/******************************************************************************
* \Syntax          : static void calc_2nd_num_init_state(void);
* \Description     : start the calculator 2nd_num_init_state where you can
					 insert your 2nd number 1st digit or minus sign 
*******************************************************************************/
static void calc_2nd_num_init_state(void);
/******************************************************************************
* \Syntax          : static void calc_2nd_num_neg_State (void);
* \Description     : start the calculator 2nd_num_neg_state where you insert the first digit of your 2nd negative number 
*******************************************************************************/
static void calc_2nd_num_neg_State (void);
/******************************************************************************
* \Syntax          : static void calc_2nd_num_After_init_state (void);
* \Description     : start the calculator 2nd_num_after_init_state where you 
					 insert another digit for your second number , or operator , or equal sign to show result
*******************************************************************************/
static void calc_2nd_num_After_init_state (void);
/******************************************************************************
* \Syntax          : static void calc_3rd_num_init_state (void);
* \Description     : start the calculator 3rd_num_init_state where you 
					 insert your 3rd_num 1st digit or minus sign 
*******************************************************************************/
static void calc_3rd_num_init_state (void);
/******************************************************************************
* \Syntax          : static void calc_3rd_num_neg_state(void);
* \Description     : start the calculator 3rd_num_neg_state where you insert the first digit of your 2nd negative number 
*******************************************************************************/
static void calc_3rd_num_neg_state(void);
/******************************************************************************
* \Syntax          : static void calc_3rd_num_After_init_state(void);
* \Description     : start the calculator 3rd_num_after_init_state where you
					 insert another digit for your 3rd number , or operator , or equal sign to show result
*******************************************************************************/
static void calc_3rd_num_After_init_state(void);
 
 /******************************************************************************
 * \Syntax          : static void clear_calc(void);
 * \Description     : clear LCD screen and return to calc_init_state
 *******************************************************************************/
static void clear_calc(void);
/******************************************************************************
* \Syntax          : static void calc_2nums_Show_Result(void);
* \Description     : Shows the result when you insert only 2 numbers
*******************************************************************************/
static void calc_2nums_Show_Result(void);
/******************************************************************************
* \Syntax          : static void calc_operator_precedence_Show_Result(void);
* \Description     : Shows the result depending on the operators precedence rules
*******************************************************************************/
static void calc_operator_precedence_Show_Result(void);
/******************************************************************************
* \Syntax          : static void calc_operator_precedence_in_the_middle(void);
* \Description     : apply the operator precedence rules for the 3 numbers before inserting another number
*******************************************************************************/
static void calc_operator_precedence_in_the_middle(void);
/******************************************************************************
* \Syntax          : static uint8 is_integer(float64 value);
* \Description     : return 1 if value is integer value or 0 if it's float value
*******************************************************************************/
static uint8 is_integer(float64 value);
/******************************************************************************
* \Syntax          : static void Calc_LCD_Write_Float(float64 value)
* \Description     : writes float numbers on LCD
*******************************************************************************/
static void Calc_LCD_Write_Float(float64 value);
/******************************************************************************
* \Syntax          : static void calc_After_error_state(void);
* \Description     : it's the state where the error appears on Lcd when you divide by zero 
					you must press clear to pass this state 
*******************************************************************************/
static void calc_After_error_state(void);
/******************************************************************************
* \Syntax          : static void calc_Show_error(void);
* \Description     : Shows the error message on LCD when you try to divide by zero
*******************************************************************************/
static void calc_Show_error(void);
/******************************************************************************
* \Syntax          : static void LCD_Write_Decimal_num(sint32 num);
* \Description     : this function is used in lcd_write_float function it's responsible for showing decimal numbers
*******************************************************************************/
static void LCD_Write_Decimal_num(sint32 num);
/**********************************************************************************************************************

 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
static void calc_init_state(void){
	if ((button>='0') && (button<='9'))
	{
		LCD_WriteChar(button);
		val1=(button-48);
		state=After_init_state;
	}
	else if (button ==MINUS_SIGN)
	{
		LCD_WriteChar(button);
		state=_1st_num_neg_state;
	}
	else {/*nothing*/}
}
static void calc_1st_num_neg (void){
	if ((button>='0') && (button<='9'))
	{
		LCD_WriteChar(button);
		val1=(button-48)*(-1);
		state=After_init_state;
	}
	else if (button == clear)
	{
		clear_calc();
	}
	else {/*nothing*/}
}
static void calc_After_init_state (void){
	if ((button>='0') && (button<='9') && (float_result_flag ==0))
	{
		LCD_WriteChar(button);
		if(val1<0){
			val1=(val1*10) - (button-48);
		}
		else val1=(val1*10)+(button-48);
		state=After_init_state;
	}
	else if ((button ==ADD) || (button==SUB) || (button ==MUL) || (button == DIV))
	{
		LCD_WriteChar(button);
		operation1=button;
		state=_2nd_num_init_state;
		
	}
	else if (button == clear)
	{
		clear_calc();
	}
	else {/*nothing*/}
}
static void calc_2nd_num_init_state(void){
	if ((button>='0') && (button<='9'))
	{
		LCD_WriteChar(button);
		val2=(button-48);
		state=_2nd_num_After_init_state;
	}
	else if (button ==MINUS_SIGN)
	{
		LCD_WriteChar(button);
		state=_2nd_num_neg_state;
	}
	else if (button == clear)
	{
		clear_calc();
	}
	else {/*nothing*/}
}
static void calc_2nd_num_neg_State (void){
	if ((button>='0') && (button<='9'))
	{
		LCD_WriteChar(button);
		val2=(button-48)*(-1);
		state=_2nd_num_After_init_state;
	}
	else if (button == clear)
	{
		clear_calc();
	}
	else {/*nothing*/}
}
static void calc_2nd_num_After_init_state (void){
	if ((button>='0') && (button<='9'))
	{
		LCD_WriteChar(button);
		if(val2<0){
			val2=(val2*10) - (button-48);
		}
		else val2=(val2*10)+(button-48);
		state=_2nd_num_After_init_state;
	}
	else if ((button ==ADD) || (button==SUB) || (button ==MUL) || (button == DIV))
	{
		LCD_WriteChar(button);
		operation2=button;
		state=_3rd_num_init_state;
	}
	else if (button ==EQUAL_SIGN)
	{
	calc_2nums_Show_Result();	
	}
	else if (button == clear)
	{
		clear_calc();
	}
	else {/*nothing*/}
}
static void calc_3rd_num_init_state (void){
	if ((button>='0') && (button<='9'))
	{
		LCD_WriteChar(button);
		val3=(button-48);
		state=_3rd_num_After_init_state;
	}
	else if (button ==MINUS_SIGN)
	{
		LCD_WriteChar(button);
		state=_3rd_num_neg_state;
	}
	else if (button == clear)
	{
		clear_calc();
	}
	else {/*nothing*/}
}
static void calc_3rd_num_neg_state(void){
	if ((button>='0') && (button<='9'))
	{
		LCD_WriteChar(button);
		val3=(button-48)*(-1);
		state=_3rd_num_After_init_state;
	}
	else if (button == clear)
	{
		clear_calc();
	}
	else {/*nothing*/}
}
static void calc_3rd_num_After_init_state(void){
	if ((button>='0') && (button<='9'))
	{
		LCD_WriteChar(button);
		if(val3<0){
			val3=(val3*10) - (button-48);
		}
		else val3=(val3*10)+(button-48);
		state=_3rd_num_After_init_state;
	}
	else if ((button ==ADD) || (button==SUB) || (button ==MUL) || (button == DIV))
	{
		calc_operator_precedence_in_the_middle();
	}
	else if (button == EQUAL_SIGN)
	{
		calc_operator_precedence_Show_Result();
	}
	else if (button ==clear)
	{
		clear_calc();
	}
	else {/*nothing*/}
}

static void clear_calc(void){
	LCD_Clear();
	state=initial_state;
	float_result_flag=0;
	error_flag=0;
}
static void calc_2nums_Show_Result(void){
	LCD_Clear();
	switch(operation1){
		case ADD: Result =val1+val2;break;
		case SUB: Result =val1-val2;break;
		case MUL:Result =val1*val2;break;
		case DIV:{
			if (val2==0)
			{
				error_flag=1;
				break;
			}
			 Result =val1/val2;
			 break;
		}
		case init:break;
		default: break;
	}
	if (!error_flag)
	{
		if (is_integer(Result))
		{
			LCD_WriteInteger((sint32)Result);
			float_result_flag=0;	
		}
		else 
		{
			Calc_LCD_Write_Float(Result);
			float_result_flag=1;
		}
			state=After_init_state;
			val1=Result;
	}
	else{
		state=After_error_state;
		calc_Show_error();
		};
}
static void calc_operator_precedence_in_the_middle(void){
	LCD_WriteChar(button);
	if(((operation1==ADD)||(operation1==SUB))&&((operation2==MUL)||(operation2==DIV))){
		switch (operation2){
			case MUL : val2 =val2*val3;break;
			case DIV : {
				
				val2 =val2/val3;
				break;
			}
			case ADD: break;
			case SUB: break;
			case init:break;
			default:break;
		}
		state=_3rd_num_init_state;
		operation2=button;
	}
	else if (((operation1==MUL)||(operation1==DIV))&&((operation2==ADD)||(operation2==SUB)))
	{
		switch (operation1){
			case MUL : val1 =val1*val2;break;
			case DIV :{
				if (val2==0)
				{
					error_flag=1;
				}
				val1 =val1/val2;
				break;
			}
				 
			case ADD: break;
			case SUB: break;
			case init:break;
			default:break;
		}
		val2=val3;
		operation1=operation2;
		state=_3rd_num_init_state;
		operation2=button;
	}
	else {
		switch(operation1){
			case ADD : val1=val1+val2;break;
			case SUB : val1=val1-val2;break;
			case MUL:  val1=val1*val2;break;
			case DIV: {
				if (val2==0)
				{
					error_flag=1;
				}
				val1=val1/val2;
				break;
			}
			case init:break;
			default:break;
		}
		val2=val3;
		operation1=operation2;
		state=_3rd_num_init_state;
		operation2=button;
	}
}
static void calc_operator_precedence_Show_Result(void){
	if (!error_flag)
	{
		LCD_Clear();
		if(((operation1==ADD)||(operation1==SUB))&&((operation2==MUL)||(operation2==DIV))){
			switch (operation2){
				case MUL : val2 =val2*val3;break;
				case DIV : {
					if (val3==0)
					{
						error_flag=1;
					}
					val2 =val2/val3;
					break;
				}
				case ADD: break;
				case SUB: break;
				case init:break;
				default:break;
			}
			Last_operation=operation1;
		}
		else if (((operation1==MUL)||(operation1==DIV))&&((operation2==ADD)||(operation2==SUB)))
		{
			switch (operation1){
				case MUL : val1 =val1*val2;break;
				case DIV :{
					if (val2==0)
					{
						error_flag=1;
					}
					 val1 =val1/val2;
					 break;
				}
				case ADD: break;
				case SUB: break;
				case init:break;
				default: break;
			}
			val2=val3;
			Last_operation=operation2;
		}
		else {
			switch(operation1){
				case ADD : val1=val1+val2;break;
				case SUB : val1=val1-val2;break;
				case MUL:  val1=val1*val2;break;
				case DIV: {
					if (val2==0)
					{
						error_flag=1;
					}
					 val1=val1/val2;
					 break;
				}
				case init:break;
				default:break;
			}
			val2=val3;
			Last_operation =operation2;
		}
		switch(Last_operation){
			case ADD: Result =val1+val2;break;
			case SUB: Result =val1-val2;break;
			case MUL: Result =val1*val2;break;
			case DIV: {
				if (val2==0)
				{
					error_flag=1;
				}
				Result = val1/val2;
				break;
			}
			case init:break;
		}
		if (!error_flag)
		{
			if (is_integer(Result))
			{
				LCD_WriteInteger((sint32)Result);
				float_result_flag=0;
			}
			else
			{
				Calc_LCD_Write_Float(Result);
				float_result_flag=1;
			}
			state=After_init_state;
			val1=Result;
		}
		else {
			state=After_error_state;
			calc_Show_error();
		}
	}
	else {
		state =After_error_state;
		calc_Show_error();
	}
}
static uint8 is_integer(double value){
	sint32 trunc_val=(sint32)value;
	return (trunc_val==value);
}
static void Calc_LCD_Write_Float(float64 value){
	sint32 trunc_val=(sint32)value;
	if (value<0)
	{
		if (trunc_val==0)
		{
			LCD_WriteChar('-');
		}
		LCD_WriteInteger(trunc_val);
		trunc_val*=-1;
		value*=-1;
	}
	else {
		LCD_WriteInteger(trunc_val);
	}
	uint32 decimal_value =(uint32)(((value -trunc_val)+1.0)*percision_5_points);
	while ((decimal_value%10)==0)
	{
		decimal_value/=10;
	}
	if (decimal_value==out_of_percision_level)
	{
		LCD_Clear();
		LCD_WriteChar('0');
		float_result_flag=0;
	}
	else
	{
		LCD_WriteChar('.');
		LCD_Write_Decimal_num(decimal_value);
	}
}
static void calc_After_error_state(void){
	if (button==clear)
	{
		clear_calc();
	}
}
static void calc_Show_error(void){
	LCD_Clear();
	LCD_WriteString("    Error !!    ");
	LCD_GoTo(1,0);
	LCD_WriteString("Division By Zero");
}
void LCD_Write_Decimal_num(sint32 num){
	uint32 temp=1;
	if(num==0){
		LCD_WriteChar('0');
	}
	else if(num<0){
		LCD_WriteChar('-');
		num*=-1;
	}
	while(num){
		temp=(temp*10)+(num%10);
		num/=10;
	}
	temp/=10;
	while(temp!=1){
		LCD_WriteChar((temp%10)+48);
		temp/=10;
	}
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
* \Syntax          : void calc_app(void)       
* \Description     : Start the Calculator application                                                                    
*******************************************************************************/
void calc_app(void){
	button=KEYPAD_GetValue();
	if (button!=KEY_NOT_PRESSED)
	{
		if(state==initial_state){
			calc_init_state();
		}
		else if (state==_1st_num_neg_state)
		{
			calc_1st_num_neg();
		}
		else if (state==After_init_state)
		{
			calc_After_init_state();
		}
		else if (state==_2nd_num_init_state)
		{
			calc_2nd_num_init_state();
		}
		else if (state==_2nd_num_neg_state)
		{
			calc_2nd_num_neg_State();
		}
		else if (state==_2nd_num_After_init_state)
		{
			calc_2nd_num_After_init_state();
		}
		else if (state==_3rd_num_init_state)
		{
			calc_3rd_num_init_state();
		}
		else if (state==_3rd_num_neg_state)
		{
			calc_3rd_num_neg_state();
		}
		else if (state==_3rd_num_After_init_state)
		{
			calc_3rd_num_After_init_state();
		}
		else if (state==After_error_state)
		{
			calc_After_error_state();
		}
		else {/*Nothing*/}	
	}
	else {/*Nothing*/}
}
/**********************************************************************************************************************
 *  END OF FILE: Calculator.c 
 *********************************************************************************************************************/
