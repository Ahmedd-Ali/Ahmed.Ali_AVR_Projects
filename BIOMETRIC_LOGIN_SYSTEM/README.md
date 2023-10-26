/*******************************************************************************/
/******************************************************************************/
/****************    Author    : Ahmed Ali              **********************/
/****************    SWC       : BIOMETRIC LOGIN SYSTEM *********************/
/****************    version   : 1.0.0                  ********************/
/**************************************************************************/
/*************************************************************************/


 > BIOMETRIC LOGIN SYSTEM PROJECT : System that investigates sign-in security.
	=========================================================================
 - Features included: 
		> Two Authentication Modes Fingerprint sensor & Password.
		> Store multiple Fingerprints in sensor flash library.
		> Store Password and System States using Ext-EEPROM.
		> Display Real Time on LCD using RTC Module.
		> Keypad for interfacing ( Select system options & Enter password ).
		> Max Three wrong trials before system block for certain time.
		> Time Out Count down before Automatic Sign-out.
		> Support Add Fingerprint, Change password, Lock system & Reset system.
		
 - Implemented Drivers:
		> GPIO
		> Timers
		> UART
		> I2C
		> R503 Fingerprint sensor
		> Keypad
		> LCD
		> EXT-EEPROM
		> RTC
		> Servo motor
 