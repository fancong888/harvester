#ifndef	_PUBLIC_PHYSYS_H_
#define _PUBLIC_PHYSYS_H_

/*******************************Definition***************************************/
#define GetTime()       ((SysTick->VAL) << 8)
#define TIME_1US	(72UL<<8)
#define TIME_100US	(TIME_1US * 100)
#define TIME_1MS	(TIME_1US * 1000)

#define bit0  0x0001
#define bit1  0x0002
#define bit2  0x0004
#define bit3  0x0008
#define bit4  0x0010
#define bit5  0x0020
#define bit6  0x0040
#define bit7  0x0080
#define bit8  0x0100
#define bit9  0x0200
#define bit10 0x0400
#define bit11 0x0800
#define bit12 0x1000
#define bit13 0x2000
#define bit14 0x4000
#define bit15 0x8000


#define TIME_2MS       2
#define TIME_10MS     10
#define TIME_100MS   100
#define TIME_200MS   200
#define TIME_500MS   500
#define TIME_1S         1000
#define TIME_3S         3000
#define TIME_1MIN     60000


/*******************************Function***************************************/
void SysClockInit(void);
void PeripheralInit(void);
void PhySys_UsDelay(unsigned short us_delay);
bool PhySys_IsOffset(unsigned long ul_a, unsigned long ul_b, unsigned short us_offset);


#endif

