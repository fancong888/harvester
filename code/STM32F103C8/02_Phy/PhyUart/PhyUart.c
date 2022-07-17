#include	"PublicPhy.h"
#include	"PhyUart.h"


//==================================================
//Function name:		UartPeripheralInit
//Descriptions:		 初始化
//input parameters:		波特率选择
//Output parameters:
//Returned value:
//==================================================
void PhyUart_PeripheralInit(USART_TypeDef* USARTx,unsigned long uartBaud,unsigned short uartMasterSlave)
{
    USART_InitTypeDef USART_InitStructure;

    USART_Cmd(USARTx, DISABLE) ;
    PhyUart_GpioInit(USARTx);
    PhyUart_IrqInit(USARTx);
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;		
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	
    USART_InitStructure.USART_BaudRate = uartBaud;	
    USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
    USART_Init(USARTx, &USART_InitStructure);	

    if(uartMasterSlave == 0)
    {
        USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);
    }
    USART_Cmd(USARTx, ENABLE);		

    if(USARTx == USART1)
    {			
        st_uart1.us_rxDelay = (USART_InitStructure.USART_BaudRate>19200)?2:5;
    }
    else if(USARTx == USART2)	
    {
        st_uart2.us_rxDelay = (USART_InitStructure.USART_BaudRate > 19200)?2:5;	
    }
    else if(USARTx == USART3)	
    {
        st_uart3.us_rxDelay = (USART_InitStructure.USART_BaudRate > 19200)?2:5;	
    }
    else if(USARTx == UART4)	
    {
        st_uart4.us_rxDelay = (USART_InitStructure.USART_BaudRate > 19200)?2:5;		
    }
    else if(USARTx == UART5)	
    {
        st_uart5.us_rxDelay = (USART_InitStructure.USART_BaudRate > 19200)?2:5;		
    }
}
//==================================================
//Descriptions:			
//input parameters:		
//Output parameters:
//Returned value:
//==================================================
void PhyUart_GpioInit(USART_TypeDef* USARTx)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	if(USARTx == USART1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);			
	}
	if(USARTx == USART2)		
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);			
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOA, &GPIO_InitStructure);		
	}
	if(USARTx == USART3)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
					
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOB, &GPIO_InitStructure);	
	}
	if(USARTx == UART4)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
				
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_10;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	}	
	if(USARTx == UART5)		
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
									
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOD, &GPIO_InitStructure);			
	}										
}

//==================================================
//Descriptions:			usart中断初始化
//input parameters:		
//Output parameters:
//Returned value:
//==================================================
void PhyUart_IrqInit(USART_TypeDef* USARTx)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	if(USARTx == USART1)
	{	
		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
	else if(USARTx == USART2)
	{
		NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);			
	}
	else if(USARTx == USART3)
	{
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn; 
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);					
	}	
}


//==================================================
//Descriptions:			接收数据
//input parameters:		串口选择；数据长度；数据 ；发送类型
//Output parameters:
//Returned value:
//==================================================
bool PhyUart_RxDeal(USART_TypeDef* USARTx ,struct UART_DATA *pSt_uartRxBuff)
{
    unsigned short i = 0;
    struct USART_PARA *st_pUart = &phy_st_uart1;

    if(USARTx == USART1)
    {
        st_pUart = &phy_st_uart1;
    }
    else if(USARTx == USART2)
    {
        st_pUart = &phy_st_uart2;
    }
    else if(USARTx == USART3)
    {
        st_pUart = &phy_st_uart3;
    }
	
    if(st_pUart->uc_rxOver)
    {
        for(i = 0; i < st_pUart->uc_rxLen; i++)
        {
            pSt_uartRxBuff->uc_data[i] = st_pUart->uc_rxData[i];			
        }
        pSt_uartRxBuff->us_length = st_pUart->uc_rxLen;
        st_pUart->uc_rxOver = 0;			
        return TRUE;
    }
    
    return FALSE;	
}



//==================================================
//Descriptions:			UART发送数据
//input parameters:		串口选择；数据长度；数据 ；发送类型
//Output parameters:
//Returned value:
//==================================================
void PhyUart_TxDeal(USART_TypeDef* USARTx ,struct UART_DATA *pSt_uartTxBuff)
{
	unsigned char i;

	if(USARTx == USART1)
	{
		//USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
		st_uart1.us_txLenth = pSt_uartTxBuff->us_length;
		st_uart1.us_txLenCount = 0;	
		for(i = 0; i < st_uart1.us_txLenth; i++)
		{
			st_uart1.us_txMsg[i] = pSt_uartTxBuff->uc_data[i];			
		}	
		USART_GetFlagStatus(USART1, USART_FLAG_TXE);
		USART_SendData(USART1, st_uart1.us_txMsg[0]); 	
		USART_ITConfig(USART1, USART_IT_TC, ENABLE);					
	}
	else if(USARTx == USART2)
	{
		USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);		
		st_uart2.us_txLenth = pSt_uartTxBuff->us_length;
		st_uart2.us_txLenCount = 0;	
		for(i = 0; i < st_uart2.us_txLenth; i++)
		{
			st_uart2.us_txMsg[i] = pSt_uartTxBuff->uc_data[i];			
		}
		USART_GetFlagStatus(USART2, USART_FLAG_TXE);
		USART_SendData(USART2, st_uart2.us_txMsg[0]); 	
		USART_ITConfig(USART2, USART_IT_TC, ENABLE);			
	}
	else if(USARTx == USART3)
	{
		USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);	
		st_uart3.us_txLenth = pSt_uartTxBuff->us_length;
		st_uart3.us_txLenCount = 0;	
		for(i = 0; i < st_uart3.us_txLenth; i++)
		{
			st_uart3.us_txMsg[i] = pSt_uartTxBuff->uc_data[i];			
		}
		USART_GetFlagStatus(USART3, USART_FLAG_TXE);
		USART_SendData(USART3, st_uart3.us_txMsg[0]); 	
		USART_ITConfig(USART3, USART_IT_TC, ENABLE);		
	}	
}

//==================================================
//Function name:		USART1_IRQHandler
//Descriptions:			UART1接收和发送完成中断
//input parameters:		串口选择；数据长度；数据 ；发送类型
//Output parameters:
//Returned value:
//==================================================
void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  
	{
		st_uart1.uc_rxMsg[st_uart1.us_rxLenth] = USART_ReceiveData(USART1);		
		st_uart1.us_rxLenth++;
		st_uart1.us_rxTime = 0;																					
		st_uart1.us_status = 3;
		if(st_uart1.us_rxLenth >= UARTLEN)					
		{ 
			USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
		}	          															
	}
	else if(USART_GetITStatus(USART1, USART_IT_TC) != RESET)
	{
		st_uart1.us_txLenCount++;  	
		st_uart1.us_txTime = 0;
		st_uart1.us_status = 1;	
		if(st_uart1.us_txLenCount >= st_uart1.us_txLenth)
		{
			USART_ITConfig(USART1, USART_IT_TC, DISABLE);		  
			st_uart1.us_status = 2;									  
			st_uart1.us_txLenCount = 0;		
			st_uart1.us_txLenth = 0;				
		}
		else
		{
			USART_SendData(USART1,st_uart1.us_txMsg[st_uart1.us_txLenCount]); 						  
		}
	}	
	else
	{
		uc_uartNoUse = USART1->SR;
		uc_uartNoUse = USART_ReceiveData(USART1);
		uc_uartNoUse = USART_ReceiveData(USART1);
		USART_ClearFlag(USART1,USART_FLAG_ORE|USART_FLAG_NE|USART_FLAG_FE|USART_FLAG_PE|USART_FLAG_IDLE);					
	}
}
//==================================================
//Function name:		USART2_IRQHandler
//Descriptions:			UART2接收和发送完成中断
//input parameters:		串口选择；数据长度；数据 ；发送类型
//Output parameters:
//Returned value:
//==================================================
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  
	{
		st_uart2.uc_rxMsg[st_uart2.us_rxLenth] = USART_ReceiveData(USART2);		
		st_uart2.us_rxLenth++;
		st_uart2.us_rxTime = 0;																					
		st_uart2.us_status = 3;
		if(st_uart2.us_rxLenth >= UARTLEN)					
		{ 
			USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
		}	          															
	}
	else if(USART_GetITStatus(USART2, USART_IT_TC) != RESET)
	{
		st_uart2.us_txLenCount++;  	
		st_uart2.us_txTime = 0;
		st_uart2.us_status = 1;	
		if(st_uart2.us_txLenCount >= st_uart2.us_txLenth)
		{
			st_uart2.us_status = 2;									  
			st_uart2.us_txLenCount = 0;		
			st_uart2.us_txLenth = 0;
			USART_ITConfig(USART2, USART_IT_TC, DISABLE);		  				
		}
		else
		{
			USART_SendData(USART2,st_uart2.us_txMsg[st_uart2.us_txLenCount]); 						  
		}
	}
	else
	{
		uc_uartNoUse = USART2->SR;
		uc_uartNoUse = USART_ReceiveData(USART2);
		uc_uartNoUse = USART_ReceiveData(USART2);
		USART_ClearFlag(USART2,USART_FLAG_ORE|USART_FLAG_NE|USART_FLAG_FE|USART_FLAG_PE|USART_FLAG_IDLE);			
	}
	
}

//==================================================
//Function name:		USART3_IRQHandler
//Descriptions:			UART3接收和发送完成中断
//input parameters:		串口选择；数据长度；数据 ；发送类型
//Output parameters:
//Returned value:
//==================================================
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  
	{
		st_uart3.uc_rxMsg[st_uart3.us_rxLenth] = USART_ReceiveData(USART3);		
		st_uart3.us_rxLenth++;
		st_uart3.us_rxTime = 0;																					
		st_uart3.us_status = 3;
		if(st_uart3.us_rxLenth >= UARTLEN)					
		{ 
			USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
		}	          															
	}
	else if(USART_GetITStatus(USART3, USART_IT_TC) != RESET)
	{
		st_uart3.us_txLenCount++;  	
		st_uart3.us_txTime = 0;
		st_uart3.us_status = 1;	
		if(st_uart3.us_txLenCount >= st_uart3.us_txLenth)
		{
			USART_ITConfig(USART3, USART_IT_TC, DISABLE);		  
			st_uart3.us_status = 2;									  
			st_uart3.us_txLenCount = 0;		
			st_uart3.us_txLenth = 0;				
		}
		else
		{
			USART_SendData(USART3,st_uart3.us_txMsg[st_uart3.us_txLenCount]); 						  
		}
	}
	else
	{
		uc_uartNoUse = USART3->SR;
		uc_uartNoUse = USART_ReceiveData(USART3);
		uc_uartNoUse = USART_ReceiveData(USART3);
		USART_ClearFlag(USART3,USART_FLAG_ORE|USART_FLAG_NE|USART_FLAG_FE|USART_FLAG_PE|USART_FLAG_IDLE);		
	}	
}

//==================================================
//Function name:		UART4_IRQHandler
//Descriptions:			UART4接收和发送完成中断
//input parameters:		串口选择；数据长度；数据 ；发送类型
//Output parameters:
//Returned value:
//==================================================
void UART4_IRQHandler(void)
{
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  
	{
		st_uart4.uc_rxMsg[st_uart4.us_rxLenth] = USART_ReceiveData(UART4);		
		st_uart4.us_rxLenth++;
		st_uart4.us_rxTime = 0;																					
		st_uart4.us_status = 3;
		if(st_uart4.us_rxLenth >= UARTLEN)					
		{ 
			USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);
		}	          															
	}
	else if(USART_GetITStatus(UART4, USART_IT_TC) != RESET)
	{
		st_uart4.us_txLenCount++;  	
		st_uart4.us_txTime = 0;
		st_uart4.us_status = 1;	
		if(st_uart4.us_txLenCount >= st_uart4.us_txLenth)
		{
			USART_ITConfig(UART4, USART_IT_TC, DISABLE);		  
			st_uart4.us_status = 2;									  
			st_uart4.us_txLenCount = 0;		
			st_uart4.us_txLenth = 0;				
		}
		else
		{
			USART_SendData(UART4,st_uart4.us_txMsg[st_uart4.us_txLenCount]); 						  
		}
	}
	else
	{
		uc_uartNoUse = UART4->SR;
		uc_uartNoUse = USART_ReceiveData(UART4);
		uc_uartNoUse = USART_ReceiveData(UART4);
		USART_ClearFlag(UART4,USART_FLAG_ORE|USART_FLAG_NE|USART_FLAG_FE|USART_FLAG_PE|USART_FLAG_IDLE);	
	}
}

//==================================================
//Function name:		UART5_IRQHandler
//Descriptions:			UART5接收和发送完成中断
//input parameters:		串口选择；数据长度；数据 ；发送类型
//Output parameters:
//Returned value:
//==================================================
void UART5_IRQHandler(void)
{
	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  
	{
		st_uart5.uc_rxMsg[st_uart5.us_rxLenth] = USART_ReceiveData(UART5);		
		st_uart5.us_rxLenth++;
		st_uart5.us_rxTime = 0;																					
		st_uart5.us_status = 3;
		if(st_uart5.us_rxLenth >= UARTLEN)					
		{ 
			USART_ITConfig(UART5, USART_IT_RXNE, DISABLE);
		}	          															
	}
	else if(USART_GetITStatus(UART5, USART_IT_TC) != RESET)
	{
		st_uart5.us_txLenCount++;  	
		st_uart5.us_txTime = 0;
		st_uart5.us_status = 1;	
		if(st_uart5.us_txLenCount >= st_uart5.us_txLenth)
		{
			USART_ITConfig(UART5, USART_IT_TC, DISABLE);		  
			st_uart5.us_status = 2;									  
			st_uart5.us_txLenCount = 0;		
			st_uart5.us_txLenth = 0;				
		}
		else
		{
			USART_SendData(UART5,st_uart5.us_txMsg[st_uart5.us_txLenCount]); 						  
		}
	}
	else
	{
		uc_uartNoUse = UART5->SR;
		uc_uartNoUse = USART_ReceiveData(UART5);
		uc_uartNoUse = USART_ReceiveData(UART5);
		USART_ClearFlag(UART5,USART_FLAG_ORE|USART_FLAG_NE|USART_FLAG_FE|USART_FLAG_PE|USART_FLAG_IDLE);	
	}	
}


//==================================================
//Descriptions:			定时器2的设置，采用中断模式
//input parameters:		timerNum 定时0.5MS的倍数
//Output parameters:
//Returned value:
//==================================================
void PhyUart_InitTim2(void)
{	
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);			
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM2->CR1=0x0000;
	TIM2->CR2=0x0000;
	TIM2->SMCR=0x0000;
	TIM2->DIER=0x0001;				//允许更新中断
	TIM2->CNT=0;
	TIM2->PSC=0xe0f;				//72M/3600=20K
	TIM2->ARR=10;					//延时0.5MS
	TIM2->EGR=TIM2->EGR|0x0001;
	TIM2->CR1=TIM2->CR1|0x0001;		//定时器开始计数
	
}
//==================================================
//Function name:		TIM2_IRQHandler
//Descriptions:			定时器2中断，用来对UART的接收完成和发送完成的处理
//input parameters:		
//Output parameters:
//Returned value:
//==================================================
void TIM2_IRQHandler(void)
{
	unsigned char i;	
	if(TIM_GetFlagStatus(TIM2, TIM_FLAG_Update) == SET)
	{
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);
		TIM2->CNT=0;

		//USART1
		if(st_uart1.us_status==2) 
		{//发送完成且定时<1ms后,可接收 	
			st_uart1.us_txTime++;
			if(st_uart1.us_txTime >= 2)
			{
				st_uart1.us_status = 5;					
				st_uart1.us_txTime = 0;
				st_uart1.us_rxLenth = 0; 
				if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE))				
				{
					uc_uartNoUse = USART_ReceiveData(USART1);  
				}				        										
				USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
			}
		}
		if(st_uart1.us_status == 3)  //从开启接收中断开始计时
		{
			st_uart1.us_rxTime++;
			if(st_uart1.us_rxTime > st_uart1.us_rxDelay) 
			{
				st_uart1.us_rxTime = 0;
				st_uart1.us_status = 4;
				phy_st_uart1.uc_rxLen = st_uart1.us_rxLenth;
				for(i=0;i<phy_st_uart1.uc_rxLen;i++)
				{
					phy_st_uart1.uc_rxData[i] = st_uart1.uc_rxMsg[i];
				}
				st_uart1.us_rxLenth = 0;
				phy_st_uart1.uc_rxOver = 1;
				USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
			}
		}	
		//USART2
		if(st_uart2.us_status==2) 
		{//发送完成且定时1ms后,可接收 	
			st_uart2.us_txTime++;
			if(st_uart2.us_txTime >= 2)
			{
				st_uart2.us_status = 5;					
				st_uart2.us_txTime = 0;
				st_uart2.us_rxLenth = 0;  
				if(USART_GetFlagStatus(USART2,USART_FLAG_RXNE))				
				{
					uc_uartNoUse = USART_ReceiveData(USART2);  
				}
				USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
			}
		}
		if(st_uart2.us_status == 3)  //从开启接收中断开始计时
		{
			st_uart2.us_rxTime++;
			if(st_uart2.us_rxTime > st_uart2.us_rxDelay) 
			{
				st_uart2.us_rxTime = 0;			
				st_uart2.us_status = 4;
				phy_st_uart2.uc_rxLen = st_uart2.us_rxLenth;
				for(i=0;i<phy_st_uart2.uc_rxLen;i++)
				{
					phy_st_uart2.uc_rxData[i] = st_uart2.uc_rxMsg[i];
				}
				phy_st_uart2.uc_rxOver = 1;
				st_uart2.us_rxLenth = 0;
			}	
		}		
					
		//USART3
		if(st_uart3.us_status==2) 
		{//发送完成且定时<1ms后,可接收 	
			st_uart3.us_txTime++;
			if(st_uart3.us_txTime >= 2)
			{
				st_uart3.us_status = 5;					
				st_uart3.us_txTime = 0;
				st_uart3.us_rxLenth = 0; 
				if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE))				
				{
					uc_uartNoUse = USART_ReceiveData(USART3);  
				}				        										
				USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
			}
		}
		if(st_uart3.us_status == 3)  //从开启接收中断开始计时
		{
			st_uart3.us_rxTime++;
			if(st_uart3.us_rxTime > st_uart3.us_rxDelay) 
			{
				st_uart3.us_rxTime = 0;
				st_uart3.us_status = 4;
				phy_st_uart3.uc_rxLen = st_uart3.us_rxLenth;
				for(i=0;i<phy_st_uart3.uc_rxLen;i++)
				{
					phy_st_uart3.uc_rxData[i] = st_uart3.uc_rxMsg[i];
				}
				phy_st_uart3.uc_rxOver = 1;
			}	
		}		
		//UART4
		if(st_uart4.us_status==2) 
		{//发送完成且定时<1ms后,可接收 	
			st_uart4.us_txTime++;
			if(st_uart4.us_txTime >= 2)
			{
				st_uart4.us_status = 5;					
				st_uart4.us_txTime = 0;
				st_uart4.us_rxLenth = 0; 
				if(USART_GetFlagStatus(UART4,USART_FLAG_RXNE))				
				{
					uc_uartNoUse = USART_ReceiveData(UART4);  
				}				        										
				USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
			}
		}
		if(st_uart4.us_status == 3)  //从开启接收中断开始计时
		{
			st_uart4.us_rxTime++;
			if(st_uart4.us_rxTime > st_uart4.us_rxDelay) 
			{
				st_uart4.us_rxTime = 0;
				st_uart4.us_status = 4;
				phy_st_uart4.uc_rxLen = st_uart4.us_rxLenth;
				for(i=0;i<phy_st_uart4.uc_rxLen;i++)
				{
					phy_st_uart4.uc_rxData[i] = st_uart4.uc_rxMsg[i];
				}
				phy_st_uart4.uc_rxOver = 1;
			}	
		}	
		//UART5
		if(st_uart5.us_status==2) 
		{//发送完成且定时<1ms后,可接收 	
			st_uart5.us_txTime++;
			if(st_uart5.us_txTime >= 2)
			{
				st_uart5.us_status = 5;					
				st_uart5.us_txTime = 0;
				st_uart5.us_rxLenth = 0;
				if(USART_GetFlagStatus(UART5,USART_FLAG_RXNE))				
				{
					uc_uartNoUse = USART_ReceiveData(UART5);  
				}					        										
				USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
			}
		}
		if(st_uart5.us_status == 3)  //从开启接收中断开始计时
		{
			st_uart5.us_rxTime++;
			if(st_uart5.us_rxTime > st_uart5.us_rxDelay) 
			{
				st_uart5.us_rxTime = 0;
				st_uart5.us_status = 4;
				phy_st_uart5.uc_rxLen = st_uart5.us_rxLenth;
				for(i=0;i<phy_st_uart5.uc_rxLen;i++)
				{
					phy_st_uart5.uc_rxData[i] = st_uart5.uc_rxMsg[i];
				}
				phy_st_uart5.uc_rxOver = 1;				
			}	
		}
	}
}

