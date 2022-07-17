#ifndef _PHYUART_H_
#define _PHYUART_H_

/*******************************Definition***************************************/
struct USART_IN_PARA st_uart1,st_uart2,st_uart3,st_uart4,st_uart5;
struct USART_PARA phy_st_uart1,phy_st_uart2,phy_st_uart3,phy_st_uart4,phy_st_uart5;
unsigned char uc_uartNoUse;


/*******************************Function***************************************/
void PhyUart_GpioInit(USART_TypeDef* USARTx);
void PhyUart_IrqInit(USART_TypeDef* USARTx);



#endif









