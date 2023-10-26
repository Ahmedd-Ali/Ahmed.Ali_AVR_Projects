/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : APP                  **********************/
/****************    SWC       : LOGIN_SYSTEM         *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#include "STD_TYPES.h"
#include "MEM_MAP.h"
#include "DIO_interface.h"
#include "TIMER0_interface.h"
#include "UART_interface.h"
#include "I2C_Interface.h"
#include "FingerPrint_interface.h"
#include "RTC_interface.h"
#include "DC_MOTOR_interface.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include "EXT_EEPROM_Interface.h"
#include "LOGIN_SYSTEM_config.h"
#include "LOGIN_SYSTEM_private.h"
#include "LOGIN_SYSTEM_interface.h"

static uint8 FingerPS_BootState= 0x55;
static uint8 FingerPS_Count= 0;
static LOGIN_SYSTEM_State_t System_State= SYSTEM_LOCKED;
volatile static LOGIN_SYSTEM_TimeState_t Time_State= TIME_OUT;

uint8 Authentication_Trials= 0;


static time_t time_now={
		.hour= 06,
		.minute= 30,
		.second= 30,
		.time_format= time_format_12,
		.time_mode= PM,
};

/********************* Password **************************/

static uint8 Saved_Password[4];
static uint8 Entered_Password[4];


static ErrorState_t LOGIN_SYSTEM_AuthenticatePassword(void)
{
	ErrorState_t ret= E_OK;
	uint8 Pass_Iterator= 0;

	for(Pass_Iterator= 0; Pass_Iterator < 4; Pass_Iterator++)
	{
		if(Saved_Password[Pass_Iterator] == Entered_Password[Pass_Iterator])
		{
			/* Do Nothing */
		}
		else
		{
			ret= E_NOT_OK;
			break;
		}
	}

	return ret;
}

static ErrorState_t LOGIN_SYSTEM_ScanPassword(void)
{
	ErrorState_t ret= E_OK;
	uint8 Pass_Iterator= 0;
	uint8 Key= 'B';

	while(Pass_Iterator < 4)
	{
		ret|= KEYPAD_GetKey(&Key);
		ret|= RTC_Runnable();
		if(Key != 'B')
		{
			ret|= LCD_SetCursor(2, (Pass_Iterator + 11));
			ret|= LCD_WriteChar(Key);
			_delay_ms(200);
			ret|= LCD_SetCursor(2, (Pass_Iterator + 11));
			ret|= LCD_WriteChar('*');
			Entered_Password[Pass_Iterator]= Key;
			Pass_Iterator++;
		}
		else
		{
			/* Do Nothing */
		}
	}

	return ret;
}

static ErrorState_t LOGIN_SYSTEM_GetSavedPassword(void)
{
	ErrorState_t ret= E_OK;

	ret|= EEPROM_ReadDataByte(0x30, &Saved_Password[0]);
	ret|= EEPROM_ReadDataByte(0x31, &Saved_Password[1]);
	ret|= EEPROM_ReadDataByte(0x32, &Saved_Password[2]);
	ret|= EEPROM_ReadDataByte(0x33, &Saved_Password[3]);

	return ret;
}

static ErrorState_t LOGIN_SYSTEM_ChangePassword(void)
{
	ErrorState_t ret= E_OK;

	ret|= EEPROM_SendDataByte(0x30, Entered_Password[0]);
	Saved_Password[0]= Entered_Password[0];
	ret|= EEPROM_SendDataByte(0x31, Entered_Password[1]);
	Saved_Password[1]= Entered_Password[1];
	ret|= EEPROM_SendDataByte(0x32, Entered_Password[2]);
	Saved_Password[2]= Entered_Password[2];
	ret|= EEPROM_SendDataByte(0x33, Entered_Password[3]);
	Saved_Password[3]= Entered_Password[3];

	ret|= LCD_SetCursor(1, 1);
	ret|= LCD_WriteString((uint8 *)"       Success      ");
	ret|= LCD_SetCursor(2, 1);
	ret|= LCD_WriteString((uint8 *)" New Password Saved ");
	_delay_ms(2000);

	return ret;
}

/************************************************************/


static ErrorState_t LOGIN_SYSTEM_LockOpen(void)
{
	ErrorState_t ret= E_OK;

	ret|= LCD_SetCursor(4, 5);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(2);
	ret|= LCD_WriteChar(2);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_SetCursor(4, 14);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);

	ret|= LCD_SetCursor(3, 5);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_SetCursor(3, 14);
	ret|= LCD_WriteChar(' ');
	ret|= LCD_WriteChar(4);
	ret|= LCD_WriteChar(5);

	_delay_ms(200);

	ret|= LCD_SetCursor(3, 5);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_SetCursor(3, 15);
	ret|= LCD_WriteChar(' ');
	ret|= LCD_WriteChar(1);
	ret|= SERVO_MOTOR_Set_Angle(179);

	_delay_ms(200);

	ret|= LCD_SetCursor(3, 5);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_SetCursor(3, 16);
	ret|= LCD_WriteChar(4);
	ret|= LCD_WriteChar(5);

	_delay_ms(200);

	ret|= LCD_SetCursor(3, 5);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_SetCursor(3, 16);
	ret|= LCD_WriteChar(4);
	ret|= LCD_WriteChar(2);
	ret|= LCD_WriteChar(5);

	_delay_ms(200);
	ret|= TIMER0_Start();
	System_State= SYSTEM_UNLOCKED;
	Time_State= TIME_IN;

	return ret;
}


static ErrorState_t LOGIN_SYSTEM_LockClose(void)
{
	ErrorState_t ret= E_OK;

	ret|= LCD_SetCursor(4, 5);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(2);
	ret|= LCD_WriteChar(2);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_SetCursor(4, 14);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);

	ret|= LCD_SetCursor(3, 5);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_SetCursor(3, 16);
	ret|= LCD_WriteChar(4);
	ret|= LCD_WriteChar(5);
	ret|= LCD_WriteChar(' ');

	_delay_ms(200);

	ret|= LCD_SetCursor(3, 5);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_SetCursor(3, 16);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(' ');
	ret|= SERVO_MOTOR_Set_Angle(0);
	_delay_ms(200);

	ret|= LCD_SetCursor(3, 5);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_SetCursor(3, 15);
	ret|= LCD_WriteChar(4);
	ret|= LCD_WriteChar(5);
	ret|= LCD_WriteChar(' ');

	_delay_ms(200);

	ret|= LCD_SetCursor(3, 5);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_SetCursor(3, 14);
	ret|= LCD_WriteChar(4);
	ret|= LCD_WriteChar(2);
	ret|= LCD_WriteChar(5);

	_delay_ms(200);
	ret|= TIMER0_Stop();
	System_State= SYSTEM_LOCKED;
	Time_State= TIME_OUT;

	return ret;
}

static void TIMER0_Func(void)
{
	Time_State= TIME_OUT;
}

ErrorState_t LOGIN_SYSTEM_Init(void)
{
	ErrorState_t ret= E_OK;

	ret|= DIO_Init();
	ret|= TIMER0_Init(TIMER0_CTC_MODE, TIMER0_SCALER_64);
	ret|= TIMER0_SetInterruptTime_ms((SIGNED_IN_TIME * 1000UL), &TIMER0_Func);
	ret|= TIMER0_OC0Mode(OC0_TOGGLE);
	ret|= RTC_voidInit();
	ret|= LCD_Init();
	ret|= KEYPAD_Init();
	ret|= SERVO_MOTOR_Init();
	ret|= SERVO_MOTOR_Set_Angle(0);
	ret|= UART_Init(BAUD_57600);
	//ret|= I2C_MasterInit(SCL_400KHZ);
	ret|= FingerPS_Init();

	//ret|= LOGIN_SYSTEM_Reset();
	uint8 Char_Black[]= {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F};
	uint8 Char_UpperHalf_Black[]= {0x1F, 0x1F, 0x1F, 0x00, 0x00,0x00, 0x00,0x00};
	uint8 Char_LowerHalf_Black[]= {0x00,0x00, 0x00,0x00, 0x1F, 0x1F, 0x1F,0x00};
	uint8 Char_LeftHalf_Black[]= {0x1F, 0x1F, 0x1F, 0x1C, 0x1C, 0x1C, 0x1C, 0x00};
	uint8 Char_RighttHalf_Black[]={ 0x1F,  0x1F, 0x1F, 0x07, 0x07, 0x07, 0x07,  0x00};

	ret|= LCD_SetCursor(1, 1);
	ret|= LCD_WriteString((uint8 *)"       WELCOME      ");
	ret|= LCD_SetCursor(2, 1);
	ret|= LCD_WriteString((uint8 *)" SMART LOGIN SYSTEM ");

	ret|= LCD_Create_Character(Char_Black, 1);
	ret|= LCD_Create_Character(Char_UpperHalf_Black, 2);
	ret|= LCD_Create_Character(Char_LowerHalf_Black, 3);
	ret|= LCD_Create_Character(Char_LeftHalf_Black, 4);
	ret|= LCD_Create_Character(Char_RighttHalf_Black, 5);

	ret|= LCD_SetCursor(3, 5);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_WriteChar(3);
	ret|= LCD_SetCursor(3, 14);
	ret|= LCD_WriteChar(4);
	ret|= LCD_WriteChar(2);
	ret|= LCD_WriteChar(5);

	ret|= LCD_SetCursor(4, 5);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(2);
	ret|= LCD_WriteChar(2);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_SetCursor(4, 14);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	ret|= LCD_WriteChar(1);
	sei();

	ret|= EEPROM_ReadDataByte(0x10, &FingerPS_BootState);
	ret|= EEPROM_ReadDataByte(0x20, &FingerPS_Count);
	ret|= LOGIN_SYSTEM_GetSavedPassword();
	RTC_voidSetTime(&time_now);
	FingerPS_AuraLedControl(BREATHING_LIGHT, 0xA0, PURPLE_COLOR, 0xFF);

	_delay_ms(1500);
	ret|= LOGIN_SYSTEM_LockOpen();
	_delay_ms(1500);
	ret|= LOGIN_SYSTEM_LockClose();
	_delay_ms(1500);

	return ret;
}

ErrorState_t RTC_Runnable(void)
{
	ErrorState_t ret= E_OK;

	RTC_GetTime(&time_now);
	ret|= LCD_SetCursor(1, 17);
	ret|= LCD_WriteNumber(time_now.hour);
	ret|= LCD_WriteChar(':');
	ret|= LCD_WriteNumber(time_now.minute);
	ret|= LCD_SetCursor(2, 18);
	ret|= LCD_WriteNumber(time_now.second);
	ret|= LCD_WriteChar(' ');

	return ret;
}

ErrorState_t LOGIN_SYSTEM_CheckLogging(void)
{
	ErrorState_t ret= E_OK;

	if((Time_State == TIME_OUT)  &&  (System_State == SYSTEM_UNLOCKED))
	{
		ret|= TIMER0_Stop();
		ret|= LCD_SetCursor(1, 1);
		ret|= LCD_WriteString((uint8 *)"     Time Out       ");
		ret|= LCD_SetCursor(2, 1);
		ret|= LCD_WriteString((uint8 *)"    Logging Out     ");
		ret|= LCD_SetCursor(3, 1);
		ret|= LCD_WriteString((uint8 *)"                    ");
		ret|= LCD_SetCursor(4, 1);
		ret|= LCD_WriteString((uint8 *)"                    ");
		_delay_ms(500);

		ret|= LOGIN_SYSTEM_LockClose();
		ret|= E_NOT_OK;
	}
	else
	{
		ret= E_OK;
		/* Do Nothing */
	}

	return ret;
}

ErrorState_t LOGIN_SYSTEM_Reset(void)
{
	ErrorState_t ret= E_OK;

	FingerPS_BootState= 0x55;
	ret|= EEPROM_SendDataByte(0x10, FingerPS_BootState);
	FingerPS_Count= 0x00;
	ret|= EEPROM_SendDataByte(0x20, FingerPS_Count);
	ret|= FingerPS_EmptyLibrary();

	ret|= EEPROM_SendDataByte(0x30, '1');
	ret|= EEPROM_SendDataByte(0x31, '2');
	ret|= EEPROM_SendDataByte(0x32, '3');
	ret|= EEPROM_SendDataByte(0x33, '4');

	return ret;
}

static ErrorState_t LOGIN_SYSTEM_ScanFingerPrint(void)
{
	ErrorState_t ret= E_OK;
	Error_FingerPS_t confirm_code;

	do{
		confirm_code= FingerPS_AuraLedControl(BREATHING_LIGHT, 0xA0, PURPLE_COLOR, 0xFF);

		ret|= LCD_SetCursor(1, 1);
		ret|= LCD_WriteString((uint8 *)" Put Your Finger To ");
		ret|= LCD_SetCursor(2, 1);
		ret|= LCD_WriteString((uint8 *)" Scan & Store Print ");
		_delay_ms(2000);

		confirm_code= FingerPS_AuraLedControl(BREATHING_LIGHT, 0x20, PURPLE_COLOR, 0xFF);

		//Generate 2 images
		confirm_code|= FingerPS_GenImage();
		_delay_ms(200);

		if(confirm_code == NO_FINGER_ON_SENSOR)
		{
			ret|= LCD_SetCursor(1, 1);
			ret|= LCD_WriteString((uint8 *)"    No Finger       ");
			ret|= LCD_SetCursor(2, 1);
			ret|= LCD_WriteString((uint8 *)"        Try Again   ");

			confirm_code|= FingerPS_AuraLedControl(LIGHT_ALWAYS_ON, 0x20, RED_COLOR, 0x05);
			_delay_ms(2000);
		}
		else
		{
			confirm_code|= FingerPS_ConvertImageToCharFile(T_BUFFER_1);
			_delay_ms(200);
			confirm_code|= FingerPS_GenImage();
			_delay_ms(200);
			confirm_code|= FingerPS_ConvertImageToCharFile(T_BUFFER_2);
			_delay_ms(200);
			confirm_code|= FingerPS_GenTemplate();
			_delay_ms(200);
			confirm_code|= FingerPS_StrTemplate(T_BUFFER_1, FingerPS_Count);
			_delay_ms(200);


			if(confirm_code == 0)
			{
				FingerPS_Count++;
				ret|= EEPROM_SendDataByte(0x20, FingerPS_Count);

				ret|= LCD_SetCursor(1, 1);
				ret|= LCD_WriteString((uint8 *)"       Success      ");
				ret|= LCD_SetCursor(2, 1);
				ret|= LCD_WriteString((uint8 *)" Finger Print Saved ");

				confirm_code|= FingerPS_AuraLedControl(LIGHT_ALWAYS_ON, 0x20, BLUE_COLOR, 0x05);
				_delay_ms(2000);
				confirm_code= FingerPS_AuraLedControl(BREATHING_LIGHT, 0xA0, PURPLE_COLOR, 0xFF);
			}
			else
			{
				ret|= LCD_SetCursor(1, 1);
				ret|= LCD_WriteString((uint8 *)"       Failed       ");
				ret|= LCD_SetCursor(2, 1);
				ret|= LCD_WriteString((uint8 *)"     Try Again      ");

				confirm_code|= FingerPS_AuraLedControl(LIGHT_ALWAYS_ON, 0x20, RED_COLOR, 0x05);
				_delay_ms(2000);
			}
		}
	}while(confirm_code != 0);

	return ret;
}

static ErrorState_t LOGIN_SYSTEM_SearchFingerPrint(void)
{
	ErrorState_t ret= E_OK;
	Error_FingerPS_t confirm_code;

	do{
		confirm_code= FingerPS_AuraLedControl(BREATHING_LIGHT, 0xA0, PURPLE_COLOR, 0xFF);

		ret|= LCD_SetCursor(1, 1);
		ret|= LCD_WriteString((uint8 *)" Put Your Finger To ");
		ret|= LCD_SetCursor(2, 1);
		ret|= LCD_WriteString((uint8 *)" Scan & Search Print");
		_delay_ms(2000);

		confirm_code= FingerPS_AuraLedControl(BREATHING_LIGHT, 0x20, PURPLE_COLOR, 0xFF);

		// Generate 2 images
		confirm_code|= FingerPS_GenImage();
		_delay_ms(200);

		if(confirm_code == NO_FINGER_ON_SENSOR)
		{
			ret|= LCD_SetCursor(1, 1);
			ret|= LCD_WriteString((uint8 *)"    No Finger       ");
			ret|= LCD_SetCursor(2, 1);
			ret|= LCD_WriteString((uint8 *)"        Try Again   ");
			confirm_code|= FingerPS_AuraLedControl(LIGHT_ALWAYS_ON, 0x20, RED_COLOR, 0x05);
			_delay_ms(1000);
		}
		else
		{
			confirm_code|= FingerPS_ConvertImageToCharFile(T_BUFFER_1);
			_delay_ms(200);
			confirm_code|= FingerPS_GenImage();
			_delay_ms(200);
			confirm_code|= FingerPS_ConvertImageToCharFile(T_BUFFER_2);
			_delay_ms(200);
			confirm_code|= FingerPS_GenTemplate();
			_delay_ms(200);
			confirm_code|= FingerPS_SearchFinger(T_BUFFER_1, 0x00, 0x05);
			_delay_ms(200);

			if(confirm_code == COMMAND_EXECUTION_COMPLETE)
			{
				ret|= LCD_SetCursor(1, 1);
				ret|= LCD_WriteString((uint8 *)"   Congratulations  ");
				ret|= LCD_SetCursor(2, 1);
				ret|= LCD_WriteString((uint8 *)"  Signed Successful ");

				confirm_code|= FingerPS_AuraLedControl(LIGHT_ALWAYS_ON, 0x20, BLUE_COLOR, 0x05);
				ret|= LOGIN_SYSTEM_LockOpen();
				_delay_ms(2000);
				confirm_code= FingerPS_AuraLedControl(BREATHING_LIGHT, 0xA0, PURPLE_COLOR, 0xFF);
			}
			else
			{
				ret|= LCD_SetCursor(1, 1);
				ret|= LCD_WriteString((uint8 *)" Finger Not Found   ");
				ret|= LCD_SetCursor(2, 1);
				ret|= LCD_WriteString((uint8 *)"      Try Again     ");

				confirm_code|= FingerPS_AuraLedControl(LIGHT_ALWAYS_ON, 0x20, RED_COLOR, 0x05);

				_delay_ms(1000);
				Authentication_Trials++;
				confirm_code= COMMAND_EXECUTION_COMPLETE;

				_delay_ms(2000);
			}
		}
	} while(confirm_code != COMMAND_EXECUTION_COMPLETE);

	return ret;
}


ErrorState_t LOGIN_SYSTEM_Handler(void)
{
	ErrorState_t ret= E_OK;
	uint8 key= 'B';

	if(Authentication_Trials == MAX_TRIALS)
	{
		ret|= LCD_SetCursor(1, 1);
		ret|= LCD_WriteString((uint8 *)"  Reach Max Trials  ");
		ret|= LCD_SetCursor(2, 1);
		ret|= LCD_WriteString((uint8 *)"   System Blocked   ");
		_delay_ms(10000);
		Authentication_Trials= 0;
	}
	else
	{
		/* Do Nothing */
	}


	ret|= LCD_SetCursor(1, 1);
	ret|= LCD_WriteString((uint8 *)"Authentication:     ");
	ret|= LCD_SetCursor(2, 1);
	ret|= LCD_WriteString((uint8 *)"1) FPS  2) PASS     ");

	if(System_State == SYSTEM_UNLOCKED)
	{
		ret|= LOGIN_SYSTEM_LockClose();
	}
	else
	{
		/* Do Nothing */
	}

	ret|= KEYPAD_GetKey(&key);
	while(key == 'B')
	{
		ret|= KEYPAD_GetKey(&key);
		ret|= RTC_Runnable();
	}

	switch(key)
	{
	case '1':
		ret|= LOGIN_SYSTEM_FingerPrintState();
		break;

	case '2':
		ret|= LOGIN_SYSTEM_PasswordState();
		break;

	default:
		ret|= E_OUT_OF_RANGE;
		break;
	}

	if(System_State == SYSTEM_UNLOCKED)
	{
		ret|= LCD_SetCursor(1, 1);
		ret|= LCD_WriteString((uint8 *)" CHOOSE :           ");
		ret|= LCD_SetCursor(2, 1);
		ret|= LCD_WriteString((uint8 *)"1) Add New Print    ");
		ret|= LCD_SetCursor(3, 1);
		ret|= LCD_WriteString((uint8 *)"2) Change Password  ");
		ret|= LCD_SetCursor(4, 1);
		ret|= LCD_WriteString((uint8 *)"3) LOCK   4) RESET  ");

		ret|= KEYPAD_GetKey(&key);
		while(key == 'B')
		{
			ret|= RTC_Runnable();
			ret|= LOGIN_SYSTEM_CheckLogging();
			if(ret == E_NOT_OK)
			{
				break;
			}
			else
			{
				ret|= KEYPAD_GetKey(&key);
			}
		}



		switch(key)
		{
		case '1':
			ret|= LCD_SetCursor(3, 1);
			ret|= LCD_WriteString((uint8 *)"                    ");
			ret|= LCD_SetCursor(4, 1);
			ret|= LCD_WriteString((uint8 *)"                    ");
			ret|= LOGIN_SYSTEM_ScanFingerPrint();
			break;

		case '2':
			ret|= LCD_SetCursor(1, 1);
			ret|= LCD_WriteString((uint8 *)" Enter New          ");
			ret|= LCD_SetCursor(2, 1);
			ret|= LCD_WriteString((uint8 *)" Password           ");
			ret|= LCD_SetCursor(3, 1);
			ret|= LCD_WriteString((uint8 *)"                    ");
			ret|= LCD_SetCursor(4, 1);
			ret|= LCD_WriteString((uint8 *)"                    ");

			ret|= LOGIN_SYSTEM_ScanPassword();
			ret|= LOGIN_SYSTEM_ChangePassword();

			break;

		case '3':

			ret|= LCD_SetCursor(1, 1);
			ret|= LCD_WriteString((uint8 *)"   System Locked    ");
			ret|= LCD_SetCursor(2, 1);
			ret|= LCD_WriteString((uint8 *)"                    ");
			ret|= LCD_SetCursor(3, 1);
			ret|= LCD_WriteString((uint8 *)"                    ");
			ret|= LCD_SetCursor(4, 1);
			ret|= LCD_WriteString((uint8 *)"                    ");
			ret|= LOGIN_SYSTEM_LockClose();
			_delay_ms(1000);

			break;

		case '4':
			ret|= LCD_SetCursor(3, 1);
			ret|= LCD_WriteString((uint8 *)"                    ");
			ret|= LCD_SetCursor(4, 1);
			ret|= LCD_WriteString((uint8 *)"                    ");
			ret|= LOGIN_SYSTEM_Reset();
			break;

		default:
			ret|= E_OUT_OF_RANGE;
			break;
		}
	}
	else
	{
		/* Do Nothing */
	}

	return ret;
}


ErrorState_t LOGIN_SYSTEM_FingerPrintState(void)
{
	ErrorState_t ret= E_OK;
	Error_FingerPS_t confirm_code;

	confirm_code= FingerPS_HandShake();
	confirm_code= FingerPS_AuraLedControl(BREATHING_LIGHT, 0xA0, PURPLE_COLOR, 0xFF);

	if(FingerPS_BootState == 0x55) // First time
	{
		ret|= LOGIN_SYSTEM_ScanFingerPrint();
		FingerPS_BootState= 0xAA;
		ret|= EEPROM_SendDataByte(0x10, FingerPS_BootState);
	}
	else
	{
		ret|= LOGIN_SYSTEM_SearchFingerPrint();
	}

	return ret;
}


/****************** Password ***********************/

ErrorState_t LOGIN_SYSTEM_PasswordState(void)
{
	ErrorState_t ret= E_OK;

	if(FingerPS_BootState == 0x55) // First time
	{
		ret|= LCD_SetCursor(1, 1);
		ret|= LCD_WriteString((uint8 *)" Enter New          ");
		ret|= LCD_SetCursor(2, 1);
		ret|= LCD_WriteString((uint8 *)" Password           ");

		ret|= LOGIN_SYSTEM_ScanPassword();
		ret|= LOGIN_SYSTEM_ChangePassword();

		FingerPS_BootState= 0xAA;
		ret|= EEPROM_SendDataByte(0x10, FingerPS_BootState);
	}
	else
	{
		ret|= LCD_SetCursor(1, 1);
		ret|= LCD_WriteString((uint8 *)" Enter Password     ");
		ret|= LCD_SetCursor(2, 1);
		ret|= LCD_WriteString((uint8 *)"                    ");
		ret|= LOGIN_SYSTEM_ScanPassword();
		ret|= LOGIN_SYSTEM_AuthenticatePassword();

		if(ret == E_OK)
		{
			ret|= LCD_SetCursor(1, 1);
			ret|= LCD_WriteString((uint8 *)"   Congratulations  ");
			ret|= LCD_SetCursor(2, 1);
			ret|= LCD_WriteString((uint8 *)"  Signed Successful ");

			ret|= LOGIN_SYSTEM_LockOpen();
			_delay_ms(2000);
		}
		else
		{
			ret|= LCD_SetCursor(1, 1);
			ret|= LCD_WriteString((uint8 *)"   Wrong Password   ");
			ret|= LCD_SetCursor(2, 1);
			ret|= LCD_WriteString((uint8 *)"      Try Again     ");

			Authentication_Trials++;

			_delay_ms(2000);
		}

	}

	return ret;
}



