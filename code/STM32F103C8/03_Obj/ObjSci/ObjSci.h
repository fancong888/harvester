#ifndef _OBJSCI_H_
#define _OBJSCI_H_

/*******************************Definition***************************************/
#define REG_READ        0x03
#define REG_WRITE      0x06
#define COMN_BYTE_NUM   8


struct UART_DATA st_objSci_rxMsg1,st_objSci_rxMsg2;
struct UART_DATA st_objSci_txMsg1,st_objSci_txMsg2;
unsigned short us_objSci_sendEnable1;

unsigned short us_objSci_sleepTime = 5;



/*******************************Function***************************************/
void ObjSci_Uart1RxDeal(void);
void ObjSci_Uart1TxMasterDeal(void);
void ObjSci_Uart1TxSlaveDeal(void);
bool ObjSci_DataDeal(unsigned char *pRecv,unsigned short us_recLen,unsigned char *pSend,unsigned short *pSendLen);
unsigned int ObjSci_CrcCalculate(unsigned char *pBuffer, unsigned short len);

#endif
