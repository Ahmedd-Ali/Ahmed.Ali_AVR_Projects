
#ifndef STDTYPES_H_
#define STDTYPES_H_

typedef unsigned char       uint8;
typedef signed char         sint8;

typedef unsigned int        uint16;
typedef signed int          sint16;

typedef unsigned long       uint32;
typedef signed long         sint32;

typedef unsigned long long  uint64;
typedef signed long long    sint64;

typedef enum{
	E_OK          = 0,
	E_NOT_OK         = 1,
	E_NULL_PTR    = 2,
	E_OUT_OF_RANGE= 3
}ErrorState_t;

typedef enum{
	FALSE= 0,
	TRUE = 1
}Bool_t;

#define NULL_PTR    ((void*)0)
#define NULL       	(0)

#define MAX_UINT8      ((u8)0xff)
#define MAX_SINT8      ((s8)0x7f)
#define MIN_SINT8      ((s8)0x80)

#define MAX_UINT16     ((u16)0xffff)
#define MAX_SINT16     ((s16)0x7fff)
#define MIN_SINT16     ((s16)0x8000)

#define MAX_UINT32     ((u32)0xffffffff)
#define MAX_SINT32     ((s32)0x7fffffff)
#define MIN_SINT32     ((s32)0x80000000)

#define MAX_UINT64     ((u64)0xffffffffffffffff)
#define MAX_SINT64     ((s64)0x7fffffffffffffff)
#define MIN_SINT64     ((s64)0x8000000000000000)

#endif /* STDTYPES_H_ */
