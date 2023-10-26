/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : TIMER1               *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#ifndef TIMER1_TIMER1_PRIVATE_H_
#define TIMER1_TIMER1_PRIVATE_H_

/**********************************************************************/
/*                      TIMER1 MASKS                                  */
/**********************************************************************/

/* ========================== TIMER1 Masks ================== */
#define TIMER1_STOP_MASK				0xF8

/* non-PWM Compare Output Mode for Compare Unit A */
#define OC1A_DISCONNECTED_MASK			0x00
#define OC1A_TOGGLE_MASK				0x40
#define OC1A_CLEAR_MASK                 0x80
#define OC1A_SET_MASK                   0xC0

/* non-PWM Compare Output Mode for Compare Unit B */
#define OC1B_DISCONNECTED_MASK			0x00
#define OC1B_TOGGLE_MASK				0x10
#define OC1B_CLEAR_MASK                 0x20
#define OC1B_SET_MASK                   0x30

/* Phase Correct and Phase and Frequency Coreect-PWM Compare Output Mode for Compare Unit A */
#define OC1A_CLEAR_UP_SET_DOWN_MASK     0x80
#define OC1A_CLEAR_DOWN_SET_UP_MASK     0xC0

/* Phase Correct and Phase and Frequency Coreect-PWM Compare Output Mode for Compare Unit B */
#define OC1B_CLEAR_UP_SET_DOWN_MASK     0x20
#define OC1B_CLEAR_DOWN_SET_UP_MASK     0x30



#endif /* TIMER1_TIMER1_PRIVATE_H_ */
