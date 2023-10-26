/******************************************************************************/
/*****************************************************************************/
/****************    Author    : Ahmed Ali            ***********************/
/****************    Layer     : MCAL                 **********************/
/****************    SWC       : TIMER0               *********************/
/****************    version   : 1.0                  ********************/
/************************************************************************/
/***********************************************************************/

#ifndef TIMER0_TIMER0_PRIVATE_H_
#define TIMER0_TIMER0_PRIVATE_H_

/**********************************************************************************************************/
/*                                           TIMER0 MASKS                                                 */
/**********************************************************************************************************/

/* Prescaler (Reg: TCCR0), (Bits: [2]CS02, [1]CS01, [0]CS00) */
#define TIMER0_RESET_PRESCALER_MASK		0xF8

/* Timer Mode (Reg: TCCR0), (Bits: [6]WGM00, [3]WGM01) */
#define TIMER0_RESET_MODE_MASK          0xB7

#define TIMER0_NORMAL_MODE_MASK			0x00
#define TIMER0_PHASECORRECT_MODE_MASK	0x40
#define TIMER0_CTC_MODE_MASK			0x08
#define TIMER0_FASTPWM_MODE_MASK		0x48


/* OC Mode (Reg: TCCR0), (Bits: [5]COM01, [4]COM00) */
#define OC0_RESET_MODE_MASK				0xCF

#define OC0_DISCONNECTED_MASK			0x00
#define OC0_TOGGLE_MASK					0x10
#define OC0_NON_INVERTING_MASK          0x20
#define OC0_INVERTING_MASK              0x30

#endif /* TIMER0_TIMER0_PRIVATE_H_ */
