#include	"PublicPhy.h"
#include	"PhyIwdg.h"

//==================================================
//Descriptions:			�ܽų�ʼ����ʱ�ӳ�ʼ����IIC��ʼ�����Ƿ����DMA			
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
void IwdgInit(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//������ʿ��Ź�
	IWDG_SetPrescaler(IWDG_Prescaler_32);//40K��Ƶ
	IWDG_SetReload(1250);//ԼΪ1S
	IWDG_ReloadCounter();
	IWDG_Enable();
}
