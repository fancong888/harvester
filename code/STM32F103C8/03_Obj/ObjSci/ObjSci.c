#include "PublicPhy.h"
#include "PublicObj.h"
#include "ObjSci.h"



//==================================================
//Descriptions:			485从机处理主函数	
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
void ObjSci_Uart1MainDeal(void)
{	
    static unsigned short us_sendTimer1 = 0;
    
    if(TRUE == PhyUart_RxDeal(USART1,&st_objSci_rxMsg1))
    {
        ObjSci_Uart1RxDeal();
    }

    us_sendTimer1 += TIME_2MS;
    if(us_sendTimer1 >= TIME_1S)
    {
        us_sendTimer1 = 0;
        ObjSci_Uart1TxMasterDeal();
    }
    else if(us_objSci_sendEnable1)
    {
        us_objSci_sendEnable1 = 0;
        ObjSci_Uart1TxSlaveDeal();
    } 
}


//==================================================
//Descriptions:			485从机处理主函数	
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
void ObjSci_Uart2MainDeal(void)
{	
    static unsigned short us_sendTimer2 = 0;
    static unsigned short us_sendTimer3 = 0;
    
    us_sendTimer2 += TIME_2MS;
    if(us_sendTimer2 >= TIME_1S)
    {
        us_sendTimer2 = 0;
        us_sendTimer3++;
    }
    
    if(us_sendTimer3 >= us_objSci_sleepTime)
    {
        us_sendTimer3 = 0;
        st_objSci_txMsg2.uc_data[0] = (unsigned char)us_objSci_sleepTime;
        st_objSci_txMsg2.us_length = 1;
        PhyUart_TxDeal(USART2, &st_objSci_txMsg2);
    }
}


//==================================================
//Descriptions:			发送处理	
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
void ObjSci_Uart1TxMasterDeal(void)
{
    static unsigned short us_step = 0;
    switch(us_step)
    {
        case 0:
        {
            st_objSci_txMsg1.uc_data[0] = us_step+1;
            st_objSci_txMsg1.uc_data[2] = (ul_objAdc_vBat>>0)&0xff;
            st_objSci_txMsg1.uc_data[3] = (ul_objAdc_vBat>>8)&0xff;
            st_objSci_txMsg1.uc_data[4] = (ul_objAdc_vBat>>16)&0xff;
            st_objSci_txMsg1.uc_data[5] = (ul_objAdc_vBat>>24)&0xff;
            us_step = 1;
            break;
        }
        case 1:
        {
            st_objSci_txMsg1.uc_data[0] = us_step+1;
            st_objSci_txMsg1.uc_data[2] = (ul_objAdc_vin>>0)&0xff;
            st_objSci_txMsg1.uc_data[3] = (ul_objAdc_vin>>8)&0xff;
            st_objSci_txMsg1.uc_data[4] = (ul_objAdc_vin>>16)&0xff;
            st_objSci_txMsg1.uc_data[5] = (ul_objAdc_vin>>24)&0xff;
            us_step = 2;
            break;
        }
        case 2:
        {
            st_objSci_txMsg1.uc_data[0] = us_step+1;
            st_objSci_txMsg1.uc_data[2] = (ul_objAdc_outputLtc>>0)&0xff;
            st_objSci_txMsg1.uc_data[3] = (ul_objAdc_outputLtc>>8)&0xff;
            st_objSci_txMsg1.uc_data[4] = (ul_objAdc_outputLtc>>16)&0xff;
            st_objSci_txMsg1.uc_data[5] = (ul_objAdc_outputLtc>>24)&0xff;
            us_step = 3;
            break;
        }
        case 3:
        {
            st_objSci_txMsg1.uc_data[0] = us_step+1;
            st_objSci_txMsg1.uc_data[2] = (ul_objAdc_pGood>>0)&0xff;
            st_objSci_txMsg1.uc_data[3] = (ul_objAdc_pGood>>8)&0xff;
            st_objSci_txMsg1.uc_data[4] = (ul_objAdc_pGood>>16)&0xff;
            st_objSci_txMsg1.uc_data[5] = (ul_objAdc_pGood>>24)&0xff;
            us_step = 4;
            break;
        }
        case 4:
        {
            st_objSci_txMsg1.uc_data[0] = us_step+1;
            st_objSci_txMsg1.uc_data[2] = (ul_objAdc_current>>0)&0xff;
            st_objSci_txMsg1.uc_data[3] = (ul_objAdc_current>>8)&0xff;
            st_objSci_txMsg1.uc_data[4] = (ul_objAdc_current>>16)&0xff;
            st_objSci_txMsg1.uc_data[5] = (ul_objAdc_current>>24)&0xff;
            us_step = 0;
            break;
        }
    }

    st_objSci_txMsg1.us_length = 8;
    PhyUart_TxDeal(USART1, &st_objSci_txMsg1);
}


//==================================================
//Descriptions:			485接收处理	
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
void ObjSci_Uart1RxDeal(void)
{
    if(TRUE == ObjSci_DataDeal(st_objSci_rxMsg1.uc_data,st_objSci_rxMsg1.us_length,st_objSci_txMsg1.uc_data,&st_objSci_txMsg1.us_length))
    {
        us_objSci_sendEnable1 = 1; 
    }  
}
//==================================================
//Descriptions:			485发送处理
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
void ObjSci_Uart1TxSlaveDeal(void)
{
	PhyUart_TxDeal(USART1, &st_objSci_txMsg1);
}

//==================================================
//Descriptions:			485发送处理
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
bool ObjSci_DataDeal(unsigned char *pRecv,unsigned short us_recLen,unsigned char *pSend,unsigned short *pSendLen)
{
    unsigned short i;
    unsigned short us_addr = 0;
    unsigned short us_commmand = 0;
    unsigned short us_data = 0;
    unsigned short us_readData = 0;
    unsigned short us_crcRec = 0,us_crcCheck = 0;
    unsigned char uc_errNum = 0;
    // 1: crc错误
    // 2: 命令错误
    // 3: 无效地址
    // 4: 读取数据超限
    // 5: 写入数据超限
    // 6: 写入数据繁忙
    // 7: 从机地址错误

    if((us_recLen > COMN_BYTE_NUM)||(us_recLen < 4))
    {
        return FALSE;
    }

    if((pRecv[0] != 0x01))
    {
        uc_errNum = 0x07;
    }
    
    us_commmand = pRecv[1];
    us_addr = (pRecv[2]<<8)+pRecv[3];
    us_data = (pRecv[4]<<8)+pRecv[5];

    us_crcRec = (pRecv[us_recLen-1]<<8)+pRecv[us_recLen-2];
    us_crcCheck = ObjSci_CrcCalculate(pRecv,us_recLen-2);
    if(us_crcRec != us_crcCheck)
    {
        uc_errNum = 0x01;
    }

    if(us_commmand == REG_READ)
    {
        if(us_data != 1)
        {
            uc_errNum = 0x04;
        }
    } 

    for(i = 0; i < COMN_BYTE_NUM; i++)
    {
        pSend[i] = 0;
    }

    switch(us_addr)
    {
        case 0x01:
        {
            if(us_commmand == REG_READ)
            {
                us_readData = us_objSci_sleepTime;
            }
            else if(us_commmand == REG_WRITE)
            {
                us_objSci_sleepTime = us_data;
            }
            else
            {
                uc_errNum = 0x02;
            }
            break;
        }
        default:
        {
            uc_errNum = 0x03;
            break;
        }            
    }

    if(uc_errNum == 0)
    {
        if(us_commmand == REG_WRITE)
        {
            for(i = 0; i < COMN_BYTE_NUM; i++)
            {
                pSend[i] = pRecv[i];                
            }         
            *pSendLen = us_recLen;
        }
        else if(us_commmand == REG_READ)
        {
            pSend[0] = pRecv[0];   
            pSend[1] = pRecv[1];
            pSend[2] = us_data*2;
            pSend[3] = (us_readData>>8)&0xff;
            pSend[4] = us_readData&0xff;
            *pSendLen = 7;
        }
    }
    else
    {
        pSend[0] = pRecv[0];   
        pSend[1] = pRecv[1];
        pSend[2] = uc_errNum;
        *pSendLen = 5;
    }

    us_crcCheck = ObjSci_CrcCalculate(pSend,(*pSendLen)-2);
    pSend[*pSendLen-2] = us_crcCheck&0xff;
    pSend[*pSendLen-1] = (us_crcCheck>>8)&0xff;
    return TRUE;;
}



//==================================================
//Descriptions:			crc16标准校验值计算		
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
unsigned int ObjSci_CrcCalculate(unsigned char *pBuffer, unsigned short len)
{
	unsigned int crc_value=0xFFFF;
	unsigned int i;
	while(len--)
	{
		crc_value^=*pBuffer++;
		for(i=0;i<8;i++)
		{
			if(crc_value&0x0001)
			{
				crc_value=(crc_value>>1)^0xa001;
			}
			else
			{
				crc_value=crc_value>>1;
			}
		}
	}
	return(crc_value);
}

