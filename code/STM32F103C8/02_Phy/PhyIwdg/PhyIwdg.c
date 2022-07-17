#include	"PublicPhy.h"
#include	"PhyIwdg.h"

//==================================================
//Descriptions:			管脚初始化，时钟初始化，IIC初始化，是否采用DMA			
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
void IwdgInit(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//允许访问看门狗
	IWDG_SetPrescaler(IWDG_Prescaler_32);//40K分频
	IWDG_SetReload(1250);//约为1S
	IWDG_ReloadCounter();
	IWDG_Enable();
}
