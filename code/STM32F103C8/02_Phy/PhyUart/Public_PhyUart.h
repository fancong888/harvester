#ifndef	_PUBLIC_PHYUART_H_
#define _PUBLIC_PHYUART_H_

/*******************************Definition***************************************/
#define UARTLEN 50

struct USART_IN_PARA
{
	unsigned char us_txMsg[UARTLEN];			//��������	
	unsigned short us_txLenth;	//�������ݳ���	
	unsigned char uc_rxMsg[UARTLEN];			//��������	
	unsigned short us_rxLenth;						//�������ݳ���			
	unsigned short us_txTime;			//UART����ʱ��
	unsigned short us_rxTime;			//UART����ʱ��
	unsigned short us_txLenCount;		//UART���ͳ��ȼ���
	unsigned short us_rxDelay;			//UART�����ʱ�־λ
	unsigned short us_status;				//UART��״̬ 0:���У�1�����ڷ��ͣ�2���������;3:���ڽ��գ�4��������ɣ�							
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

