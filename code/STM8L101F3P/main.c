/* Includes ------------------------------------------------------------------*/
#include "stm8l10x.h"
#include "nrf2401.h"

u8 buf[5] = {0x11,0x22,0x3,0x44,0x55};

void Delay(__IO uint16_t nCount)
{
    /* Decrement nCount value */
    while (nCount != 0)
    {
        nCount--;
    }
}

void Gpio_Init(void)
{
     //����IOȫ������͵�ƽ
    GPIO_Init(GPIOA, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOB, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOC, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(GPIOD, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7, GPIO_Mode_Out_PP_Low_Slow);
    
    GPIO_Init(GPIOC, GPIO_Pin_4, GPIO_Mode_Out_PP_Low_Slow);//��ʼ��LED
}


void Usart_Init(void)
{
    CLK_PeripheralClockConfig (CLK_Peripheral_USART,ENABLE); //ʹ������ʱ��
    
    //��ʼ��USART��2����--TXD-RXD
    GPIO_Init(GPIOC,GPIO_Pin_3,GPIO_Mode_Out_PP_High_Fast);//TXD
    GPIO_Init(GPIOC,GPIO_Pin_2,GPIO_Mode_In_PU_No_IT);//RXD
    
    USART_Init(9600,USART_WordLength_8D,USART_StopBits_1,USART_Parity_No,USART_Mode_Tx|USART_Mode_Rx);//USART��ʼ����9600��8N1
    
    USART_ITConfig (USART_IT_RXNE,ENABLE);//ʹ�ܽ����жϣ��ж�������28
    USART_Cmd (ENABLE);//ʹ��USART
}

void main(void)
{
    Gpio_Init();
    Usart_Init();  
    enableInterrupts();

    NRF24L01_Init();    		//��ʼ��NRF24L01 
    while(NRF24L01_Check());						    
    NRF24L01_TX_Mode();
  
    while(1)
    {
        Delay(0X1FFF);
        GPIO_ResetBits(GPIOC, GPIO_Pin_4);
        Delay(0X1FFF);
        GPIO_SetBits(GPIOC, GPIO_Pin_4);
        NRF24L01_TxPacket(buf);

        wfi();//�ȴ�WFI
    }
}
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/