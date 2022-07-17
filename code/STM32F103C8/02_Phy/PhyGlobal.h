#include "stm32f10x.h"

	


//=========================Uart============================//
#define UART2RTS 1
#ifdef UART2RTS
	#define UART2TX 1
	#define UART2RX 2
#endif 
void UartRts(unsigned char control,USART_TypeDef* USARTx,unsigned char dir);

#define UARTLEN 50//30
void PhyUartGpioClockInit(USART_TypeDef* USARTx);
void PhyUartPeripheralInit(USART_TypeDef* USARTx,unsigned long uartBaud,unsigned short uartMasterSlave);
void PhyUartTx(USART_TypeDef* USARTx ,unsigned short uartLenth,unsigned char *uartData);
void PhyUart_RxErrDeal(void);

struct USART_PARA
{
	unsigned char uc_rxData[UARTLEN]; 
	unsigned char uc_rxOver;
	unsigned char uc_rxLen;			
};
extern struct USART_PARA phy_st_uart1,phy_st_uart2,phy_st_uart3,phy_st_uart4,phy_st_uart5;

//=========================Timer============================//
#define T3_REAL_VALUE TIM3->CNT		//提供实时的TIME3的值，可以用作延时等函数
void Init_Tim2(void);

//=========================ADCInit============================//
void ADCInit(unsigned long PortNub,unsigned short PinNub);
void PhyAdcDeal(unsigned long PortNub,unsigned short PinNub);
//PortNub:RCC_APB2Periph_GPIOA或RCC_APB2Periph_GPIOB;RCC_APB2Periph_GPIOC
//PinNub:GPIO_Pin_1;GPIO_Pin_2;GPIO_Pin_3.......
extern unsigned short us_phy_adcValue[16];//每个通道对应的转换值


//=========================GPIO============================//
void PhyGpio_PeriphInit(void);
void PhyGpio_ParamInit(void);

void PhyGpio_ReadFromPeriph (unsigned long*);
void PhyGpio_WriteToPeriph (unsigned short);


//=========================IWDG============================//
void IwdgInit(void);

//=========================SysInit============================//
void SysClockInit(void);
void PeripheralInit(void);
