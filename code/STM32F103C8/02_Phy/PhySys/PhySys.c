#include "PublicPhy.h"
#include "PhySys.h"

//======================================================
//Descriptions:			
//input parameters:
//Output parameters:
//Returned value:
//======================================================
void SysClockInit(void)
{ 
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON); 
	HSEStartUpStatus = RCC_WaitForHSEStartUp(); 

	if(HSEStartUpStatus == SUCCESS)
	{
		RCC_HCLKConfig(RCC_SYSCLK_Div1);  
		RCC_PCLK2Config(RCC_HCLK_Div1);  
		RCC_PCLK1Config(RCC_HCLK_Div2);
		FLASH_SetLatency(FLASH_Latency_2);  
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);  
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		RCC_PLLCmd(ENABLE);	
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) 
		{
		}
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  
		while(RCC_GetSYSCLKSource() != 0x08)   
		{
		}
	}
}


//======================================================
//Function name:		PeripheralInit
//Descriptions:			ST103所有常用外设初始化
//input parameters:
//Output parameters:	bTimerHalfMs;bTimer1ms;bTimer2ms
//Returned value:
//======================================================
void PeripheralInit(void)
{
    //GPIO
    PhyGpio_PeriphInit();
    PhyGpio_ParamInit();
    //232&485
    PhyUart_InitTim2();
    PhyUart_PeripheralInit(USART1,38400,0);
    PhyUart_PeripheralInit(USART2,9600,0);
    //AD
    PhyAdc_Init();

    PhyIIC_OLEDInit();
}


/* ******************************************************************
* 功能：  微秒延时
* 输入：  延时时间  
* 输出：  None
* 返回值: None
* ******************************************************************** */
void PhySys_UsDelay(unsigned short us_delay)
{
	unsigned long ul_base;
	unsigned long ul_delayTime;
	unsigned long ul_wait;
	ul_base = GetTime();
	ul_delayTime = TIME_1US*us_delay;
	do
	{
		if(ul_base >= GetTime())
			ul_wait = ul_base-GetTime();
		else
			ul_wait = (SysTick_LOAD_RELOAD_Msk<<8)-GetTime()+ul_base;
	}
	while(ul_wait < ul_delayTime);
}



/* ******************************************************************
* 功能：  计算两者偏差是否大于给定值
* 输入：  us_offset  0-100
* 输出：  
* 返回值: 
* ******************************************************************** */
bool PhySys_IsOffset(unsigned long ul_a, unsigned long ul_b, unsigned short us_offset)
{
    unsigned long ul_temp = 0;
    
    if(ul_a > ul_b)
    {
        ul_temp = ul_a-ul_b;
        if(ul_temp*100/ul_a >= us_offset)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else if(ul_a < ul_b)
    {
        ul_temp = ul_b-ul_a;
        if(ul_temp*100/ul_b >= us_offset)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        if(us_offset == 0)
        {
            return TRUE;
        }
        else
            {
            return FALSE;
        }
    }     
}


