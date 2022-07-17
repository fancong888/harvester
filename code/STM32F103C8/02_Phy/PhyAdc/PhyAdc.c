#include	"PublicPhy.h"
#include	"PhyAdc.h"

//==================================================
//Descriptions:			�ܽų�ʼ����ʱ�ӳ�ʼ����ADC,����16·ADC�����Ƕ���ת��ģʽ			
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
void PhyAdc_Init(void)
{
    PhyAdc_GpioInit();
    PhyAdc_ADC1Init();
    PhyAdc_DmaInit();
}


//==================================================
//Descriptions:				
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
void PhyAdc_GpioInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);	   

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_4|GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//==================================================
//Descriptions:				
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
void PhyAdc_ADC1Init(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);		
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);	   

    ADC_DeInit(ADC1); //������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ
    
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = ADC_NUM;
    ADC_Init(ADC1, &ADC_InitStructure);	
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 2, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 3, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 4, ADC_SampleTime_239Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 5, ADC_SampleTime_239Cycles5);

    // ����ADC��DMA֧�֣�Ҫʵ��DMA���ܣ������������DMAͨ���Ȳ�����
    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    //У׼
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));	

    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

//==================================================
//Descriptions:				
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
void PhyAdc_DmaInit(void)
{
	DMA_InitTypeDef DMA_InitStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //ʹ��DMA����    
    
    DMA_DeInit(DMA1_Channel1); //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; //DMA����ADC����ַ
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&us_PhyAdc_dmaValue; //DMA�ڴ����ַ
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //�ڴ���Ϊ���ݴ����Ŀ�ĵ�
    DMA_InitStructure.DMA_BufferSize = ADC_FILTER_NUM*ADC_NUM; //DMAͨ����DMA����Ĵ�С
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ�Ĵ�������
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ�Ĵ�������
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //���ݿ��Ϊ16λ
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //���ݿ��Ϊ16λ
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //������ѭ������ģʽ
    DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMAͨ�� xӵ�и����ȼ�
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
    DMA_Init(DMA1_Channel1, &DMA_InitStructure); //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��

    DMA_Cmd(DMA1_Channel1, ENABLE); //����DMAͨ��
}


//==================================================
//Descriptions:				
//input parameters:	us_num   0-4
//Output parameters:
//Returned value:    ����ƽ����ѹֵ0.01v
//==================================================
unsigned short PhyAdc_GetValue(unsigned short us_num)
{
    unsigned short i = 0;
    unsigned long ul_sum = 0;

    if(us_num >= ADC_NUM)
    {
        return 0;
    }

    for(i = 0; i < ADC_FILTER_NUM; i++)
    {
        ul_sum += us_PhyAdc_dmaValue[i][us_num];
    }
    us_PhyAdc_value[us_num] = ul_sum/ADC_FILTER_NUM;
    return us_PhyAdc_value[us_num] *330/4096;
}


