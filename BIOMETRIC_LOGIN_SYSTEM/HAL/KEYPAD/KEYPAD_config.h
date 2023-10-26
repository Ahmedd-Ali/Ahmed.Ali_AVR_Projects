/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : HAL                  **********************/
/****************    SWC       : KEYPAD               *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#ifndef KEYPAD_KEYPAD_CONFIG_H_
#define KEYPAD_KEYPAD_CONFIG_H_

#define  ROWS  4
#define  COLS  4

#define  NOT_KEY  'B'

#ifdef   KeyPad

uint8 keypad_rows[ROWS] = {PINC5, PINC4, PINC3, PINC2};
uint8 keypad_cols[COLS] = {PIND7, PIND6, PIND5, PIND3};

static const uint8 KeysArray[ROWS][COLS]={
	{ '7' ,  '8' ,  '9' , '/'},
	{ '4' ,  '5' ,  '6' , '*'},
	{ '1' ,  '2' ,  '3' , '-'},
	{'c',  '0' , '=', '+'}
};

#endif

#endif /* KEYPAD_KEYPAD_CONFIG_H_ */
