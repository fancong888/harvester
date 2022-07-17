#include "PublicPhy.h"
#include "PhyGpio.h"



//==================================================
//Function name:		PhyGpio_PeriphInit
//Descriptions:			ÎïÀí²ãÊäÈë´¦Àí
//input parameters:		
//Output parameters:
//Returned value:
//==================================================
void PhyGpio_PeriphInit (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);

//JTAG¹¦ÄÜ¸´ÓÃ
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
//IO
//ÊäÈëµã²¿·Ö
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//GPIO_Init(GPIOC, &GPIO_InitStructure);
	
//Êä³öµã²¿·Ö 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

//Ö¸Ê¾µÆß
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
//Descriptions:			ÎïÀí²ã²ÎÊý³õÊ¼»¯
//input parameters:		
//Output parameters:
//Returned value:
//==================================================
void PhyGpio_ParamInit(void)
{

}

//==================================================
//Function name:		PhyGpio_ReadFromPeriph
//Descriptions:			¶ÁDI
//input parameters:		
//Output parameters:
//Returned value:
//==================================================
void PhyGpio_ReadFromPeriph(unsigned long *gpioInputValue)
{
	//*gpioInputValue = (ul_phyGpio_terminal&0xFFEFFF00)+ (ul_phyGpio_termDiFlag&0x1000FF);
}

#if 0
//==================================================
//Function name:		PhyGpio_InputTerm
//Descriptions:			¶ÁDI
//input parameters:		
//Output parameters:
//Returned value:
//==================================================
void PhyGpio_InputTerm (void)
{
	unsigned short i;
	unsigned long temp;
	unsigned long gpioComax;
	unsigned long gpioInputTemp = 0;

	gpioInputTemp = 0;
	gpioInputTemp |= ((GPIOC->IDR&0xE000)>>13);
	gpioInputTemp |= ((GPIOB->IDR&0x00E0)>>2);
	gpioInputTemp |= ((GPIOA->IDR&0x8000)>>9);
	gpioInputTemp |= ((GPIOB->IDR&0x0008)<<4);

	temp = 0;
	temp = (GPIOA->IDR&0x00F0);
	gpioInputTemp |= (temp<<4);
	
	temp = 0;
	temp = (GPIOB->IDR&0x0003);
	gpioInputTemp |= (temp<<12);

	temp = 0;
	temp = (GPIOB->IDR&0x0C00);
	gpioInputTemp |= (temp<<4);
	
	temp = 0;
	temp = (GPIOB->IDR&0xE000);
	gpioInputTemp |= (temp<<3);

	temp = 0;
	temp = (GPIOB->IDR&0x0010);
	gpioInputTemp |= (temp<<15);

	temp = 0;
	temp = (GPIOB->IDR&0x1000);
	gpioInputTemp |= (temp<<8);

	gpioInputTemp = (~gpioInputTemp)&0x001FFFFF; //È¡·´

//ÂË²¨	
	for(i=0;i<GPIO_DI_NUM;i++)
	{
		gpioComax = 0x00000001 << i;
		if((ul_phyGpio_terminal & gpioComax) != (gpioInputTemp & gpioComax))//
		{
			uc_phyGpio_diFilter[i]++;
			if(uc_phyGpio_diFilter[i] >= GPIO_FILTER_COUNTS_5)
			{
				ul_phyGpio_terminal = (ul_phyGpio_terminal & (~gpioComax))+(gpioInputTemp & gpioComax);
				uc_phyGpio_diFilter[i] = 0;
			}
		}
		else
		{			
			uc_phyGpio_diFilter[i] = 0;//±ØÐëµÄ
		}
	}
}
#endif

//==================================================
//Descriptions:		
//input parameters:		
//Output parameters:
//Returned value:
//==================================================
void PhyGpio_WriteToPeriph(union GPIO_OUTPUT *pOutput)
{
	if(pOutput->bit.powerHold)//PB10  hold 	
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_10);
	}
	else		
	{		
		GPIO_ResetBits(GPIOB, GPIO_Pin_10);  	
	}
	
	if(pOutput->bit.runLed)//PA8  RUN LED
	{		
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
	}
	else 		
	{		
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	}		
	
	if(pOutput->bit.batLed)//PB5  BAT LED
	{  	
		GPIO_SetBits(GPIOB, GPIO_Pin_5);
	}
	else	
	{		
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);
	}
}

