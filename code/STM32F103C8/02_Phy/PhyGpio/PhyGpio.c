#include "PublicPhy.h"
#include "PhyGpio.h"



//==================================================
//Function name:		PhyGpio_PeriphInit
//Descriptions:			物理层输入处理
//input parameters:		
//Output parameters:
//Returned value:
//==================================================
void PhyGpio_PeriphInit (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);

//JTAG功能复用
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
//IO
//输入点部分
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
       GPIO_Init(GPIOA, &GPIO_InitStructure);  //电源输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);  //电池充电
	
//输出点部分 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

//指示灯
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //RUN led
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //BATTERY_INDICATOR
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

//==================================================
//Function name:		PhyGpio_ParamInit
//Descriptions:			物理层参数初始化
//input parameters:		
//Output parameters:
//Returned value:
//==================================================
void PhyGpio_ParamInit(void)
{

}

//==================================================
//Descriptions:			读DI
//input parameters:		
//Output parameters:
//Returned value:
//==================================================
unsigned long PhyGpio_ReadFromPeriph(void)
{
	return ul_phyIo_terminal;
}

/* ******************************************************************
* 功能：  输入处理
* 输入：  None
* 输出：  None
* 返回值: None
* ******************************************************************** */
void PhyIo_DiDeal(void)
{
    unsigned short i;
    unsigned long ul_ioComax;
    unsigned long ul_ioInputTemp = 0;

    ul_ioInputTemp |=((GPIOB->IDR&bit11)>>11);	
    ul_ioInputTemp |=((GPIOA->IDR&bit11)>>10);
    ul_ioInputTemp ^= 0x00000003;

    for(i = 0; i < PHYIO_DI_NUM; i++)
    {
        ul_ioComax = bit0<<i;
        if((ul_phyIo_terminal&ul_ioComax) != (ul_ioInputTemp&ul_ioComax))
        {
            uc_phyIo_diFilter[i] += TIME_2MS;
            if(uc_phyIo_diFilter[i] >= PHYIO_FILTER_TIME)
            {
                ul_phyIo_terminal = (ul_phyIo_terminal&(~ul_ioComax))+(ul_ioInputTemp&ul_ioComax);
                uc_phyIo_diFilter[i] = 0;
            }
        }
        else
        {			
            uc_phyIo_diFilter[i] = 0;
        }
    } 
}


//==================================================
//Descriptions:		
//input parameters:		
//Output parameters:
//Returned value:
//==================================================
void PhyGpio_WriteToPeriph(union GPIO_OUTPUT *pOutput)
{
	if(pOutput->bit.powerHold)//PC13  hold 	
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
	}
	else		
	{		
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);  	
	}
	
	if(pOutput->bit.runLed)//PA8  RUN LED
	{		
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	}
	else 		
	{		
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
	}		
	
	if(pOutput->bit.batLed)//PB5  BAT LED
	{  	
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	}
	else	
	{		
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
	}
}

