#ifndef	_PUBLIC_PHYSYS_H_
#define _PUBLIC_PHYSYS_H_

/*******************************Definition***************************************/
#define GetTime()       ((SysTick->VAL) << 8)
#define TIME_1US	(72UL<<8)
#define TIME_100US	(TIME_1US * 100)
#define TIME_1MS	(TIME_1US * 1000)


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

