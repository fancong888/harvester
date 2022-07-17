#ifndef	_PUBLIC_PHYUART_H_
#define _PUBLIC_PHYUART_H_

/*******************************Definition***************************************/
#define UARTLEN 50

struct USART_IN_PARA
{
	unsigned char us_txMsg[UARTLEN];			//发送数据	
	unsigned short us_txLenth;	//发送数据长度	
	unsigned char uc_rxMsg[UARTLEN];			//接收数据	
	unsigned short us_rxLenth;						//接收数据长度			
	unsigned short us_txTime;			//UART发送时间
	unsigned short us_rxTime;			//UART接收时间
	unsigned short us_txLenCount;		//UART发送长度计数
	unsigned short us_rxDelay;			//UART波特率标志位
	unsigned short us_status;				//UART的状态 0:空闲；1：正在发送；2：发送完成;3:正在接收；4：接收完成；							
};
struct USART_PARA
{
	unsigned char uc_rxData[UARTLEN]; 
	unsigned char uc_rxOver;
	unsigned char uc_rxLen;			
};
struct UART_DATA
{
	unsigned char uc_data[UARTLEN];
	unsigned short us_length;
};




/*******************************Function***************************************/
void PhyUart_InitTim2(void);
void PhyUart_PeripheralInit(USART_TypeDef* USARTx,unsigned long uartBaud,unsigned short uartMasterSlave);
bool PhyUart_RxDeal(USART_TypeDef* USARTx ,struct UART_DATA *pSt_uartRxBuff);
void PhyUart_TxDeal(USART_TypeDef* USARTx ,struct UART_DATA *pSt_uartTxBuff);




#endif

