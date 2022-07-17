/************************************************************************************
*  Copyright (c), 2014, HelTec Automatic Technology co.,LTD.
*            All rights reserved.
*
* Http:    www.heltec.cn
* Email:   cn.heltec@gmail.com
* WebShop: heltec.taobao.com
*
* File name: OLED_I2C.c
* Project  : HelTec.uvprij
* Processor: STM32F103C8T6
* Compiler : MDK fo ARM
* 
* Author : С��
* Version: 1.00
* Date   : 2014.4.8
* Email  : hello14blog@gmail.com
* Modification: none
* 
* Description:128*64�����OLED��ʾ�������ļ����������ڻ����Զ���(heltec.taobao.com)��SD1306����IICͨ�ŷ�ʽ��ʾ��
*
* Others: none;
*
* Function List:
*	1. void I2C_Configuration(void) -- ����CPU��Ӳ��I2C
* 2. void I2C_WriteByte(uint8_t addr,uint8_t data) -- ��Ĵ�����ַдһ��byte������
* 3. void WriteCmd(unsigned char I2C_Command) -- д����
* 4. void WriteDat(unsigned char I2C_Data) -- д����
* 5. void OLED_Init(void) -- OLED����ʼ��
* 6. void OLED_SetPos(unsigned char x, unsigned char y) -- ������ʼ������
* 7. void OLED_Fill(unsigned char fill_Data) -- ȫ�����
* 8. void OLED_CLS(void) -- ����
* 9. void OLED_ON(void) -- ����
* 10. void OLED_OFF(void) -- ˯��
* 11. void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize) -- ��ʾ�ַ���(�����С��6*8��8*16����)
* 12. void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N) -- ��ʾ����(������Ҫ��ȡģ��Ȼ��ŵ�codetab.h��)
* 13. void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]) -- BMPͼƬ
*
* History: none;
*
*************************************************************************************/
#include	"PublicPhy.h"
#include "OLED_I2C.h"
#include "codetab.h"


//==================================================
//Descriptions:			
//input parameters:		
//Output parameters:
//Returned value:
//==================================================
void PhyIIC_OLEDInit (void)
{
    I2C_Configuration();
    OLED_Init();
    OLED_Fill(0x00);//ȫ����
}


void I2C_Configuration(void)
{
	I2C_InitTypeDef  I2C_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure; 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	/*STM32F103C8T6оƬ��Ӳ��I2C: PB6 -- SCL; PB7 -- SDA */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;//I2C���뿪©���
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	I2C_DeInit(I2C1);//ʹ��I2C1
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x30;//������I2C��ַ,���д��
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 400000;//400K

	I2C_Cmd(I2C1, ENABLE);
	I2C_Init(I2C1, &I2C_InitStructure);
}

void OLED_Init(void)
{
    unsigned short i = 0;
    for(i = 0; i < 100; i++)
        PhySys_UsDelay(1000); //�������ʱ����Ҫ
	
    while(!WriteCmd(0xAE)); //display off
    while(!WriteCmd(0x20));	//Set Memory Addressing Mode	
    while(!WriteCmd(0x10));	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
    while(!WriteCmd(0xb0));	//Set Page Start Address for Page Addressing Mode,0-7
    while(!WriteCmd(0xc8));	//Set COM Output Scan Direction
    while(!WriteCmd(0x00)); //---set low column address
    while(!WriteCmd(0x10)); //---set high column address
    while(!WriteCmd(0x40)); //--set start line address
    while(!WriteCmd(0x81)); //--set contrast control register
    while(!WriteCmd(0xff)); //���ȵ��� 0x00~0xff
    while(!WriteCmd(0xa1)); //--set segment re-map 0 to 127
    while(!WriteCmd(0xa6)); //--set normal display
    while(!WriteCmd(0xa8)); //--set multiplex ratio(1 to 64)
    while(!WriteCmd(0x3F)); //
    while(!WriteCmd(0xa4)); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
    while(!WriteCmd(0xd3)); //-set display offset
    while(!WriteCmd(0x00)); //-not offset
    while(!WriteCmd(0xd5)); //--set display clock divide ratio/oscillator frequency
    while(!WriteCmd(0xf0)); //--set divide ratio
    while(!WriteCmd(0xd9)); //--set pre-charge period
    while(!WriteCmd(0x22)); //
    while(!WriteCmd(0xda)); //--set com pins hardware configuration
    while(!WriteCmd(0x12));
    while(!WriteCmd(0xdb)); //--set vcomh
    while(!WriteCmd(0x20)); //0x20,0.77xVcc
    while(!WriteCmd(0x8d)); //--set DC-DC enable
    while(!WriteCmd(0x14)); //
    while(!WriteCmd(0xaf)); //--turn on oled panel
}

bool OLED_ShowStr1(unsigned char x, unsigned char y, char ch[])
{
    unsigned char uc_char = 0;
    static unsigned short us_num = 0;
    static unsigned us_step = 0;

    if(ch[us_num]  ==  '\0')
    {
        us_num = 0;
        return TRUE;
    }

    uc_char = ch[us_num]-32; 
    switch(us_step)
    {
        case 0:
        {
            if(TRUE == OLED_SetPos(x+us_num*6,y))
            {
                us_step = 1;
            }
            break;
        }
        case 1:
        {
            if(TRUE == OLED_WriteChar(uc_char))
            {
                us_num++;
                us_step = 0;
            }
            break;
        }
        default:
        {
            us_step = 0;
            break;
        }
    }

    if(ch[us_num]  ==  '\0')
    {
        us_num = 0;
        return TRUE;
    }

    return FALSE;
}

//==================================================
//Descriptions:			дһ���ַ�6*8
//input parameters:		
//Output parameters:
//Returned value:
//==================================================

bool OLED_WriteChar(unsigned char ch)
{
    static unsigned us_num = 0;

    if(TRUE == WriteDat(F6x8[ch][us_num]))
    {
        us_num++;
    }
    if(us_num >= 6)
    {
        us_num = 0;
        return TRUE;
    }

    return FALSE;
}


bool OLED_SetPos(unsigned char x, unsigned char y) //������ʼ������
{ 
    static unsigned us_step = 0;

    switch(us_step)
    {
        case 0:
        {
            if(TRUE == WriteCmd(0xb0+y))
            {
                us_step = 1;
            }
            break;
        }
        case 1:
        {
            if(TRUE == WriteCmd(((x&0xf0)>>4)|0x10))
            {
                us_step = 2;
            }
            break;
        }
        case 2:
        {
            if(TRUE == WriteCmd((x&0x0f)|0x01))
            {
                us_step = 0;
                return TRUE;
            }
            break;
        }
        default:
        {
            us_step = 0;
            break;
        }
    }

    return FALSE;
}

void OLED_Fill(unsigned char fill_Data)//ȫ�����
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		while(!WriteCmd(0xb0+m));		//page0-page1
		while(!WriteCmd(0x00));		//low column start address
		while(!WriteCmd(0x10));		//high column start address
		for(n=0;n<128;n++)
		{
			while(!WriteDat(fill_Data));
		}
	}
}

bool WriteCmd(unsigned char I2C_Command)//д����
{
	return I2C_WriteByte(0x00, I2C_Command);
}

bool WriteDat(unsigned char I2C_Data)//д����
{
	return I2C_WriteByte(0x40, I2C_Data);
}


bool I2C_WriteByte(uint8_t addr,uint8_t data)
{
    static unsigned us_step = 0;

    switch(us_step)
    {
        case 0:
        {
            if(RESET == I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY))
            {
                I2C_GenerateSTART(I2C1, ENABLE);//����I2C1
                us_step = 1;
            }
            break;
        }
        case 1:
        {
            if(SET == I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) /*EV5,��ģʽ*/
            {
                I2C_Send7bitAddress(I2C1, OLED_ADDRESS, I2C_Direction_Transmitter);//������ַ -- Ĭ��0x78
                us_step = 2;
            }
            break;
        }
        case 2:
        {
            if(SET == I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
            {
                I2C_SendData(I2C1, addr);//�Ĵ�����ַ
                us_step = 3;
            }
            break;
        }
        case 3:
        {
            if(SET == I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
            {
                I2C_SendData(I2C1, data);//��������
                us_step = 4;
            }
            break;
        }
        case 4:
        {
            if(SET == I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
            {
                I2C_GenerateSTOP(I2C1, ENABLE);//�ر�I2C1����
                us_step = 0;
                return TRUE;
            }
            break;
        }
        default:
        {
            us_step = 0;
            break;
        }
    }

    return FALSE;
}






