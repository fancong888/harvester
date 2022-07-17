#include	"PublicPhy.h"
#include	"PhyAdc.h"

//==================================================
//Descriptions:			管脚初始化，时钟初始化，ADC,包括16路ADC，都是独立转换模式			
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

    ADC_DeInit(ADC1); //将外设 ADC1 的全部寄存器重设为缺省值
    
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

    // 开启ADC的DMA支持（要实现DMA功能，还需独立配置DMA通道等参数）
    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    //校准
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
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //使能DMA传输    
    
    DMA_DeInit(DMA1_Channel1); //将DMA的通道1寄存器重设为缺省值
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR; //DMA外设ADC基地址
    DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&us_PhyAdc_dmaValue; //DMA内存基地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //内存作为数据传输的目的地
    DMA_InitStructure.DMA_BufferSize = ADC_FILTER_NUM*ADC_NUM; //DMA通道的DMA缓存的大小
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址寄存器不变
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址寄存器递增
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //数据宽度为16位
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //数据宽度为16位
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //工作在循环缓存模式
    DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA通道 x拥有高优先级
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; //DMA通道x没有设置为内存到内存传输
    DMA_Init(DMA1_Channel1, &DMA_InitStructure); //根据DMA_InitStruct中指定的参数初始化DMA的通道

    DMA_Cmd(DMA1_Channel1, ENABLE); //启动DMA通道
}


//==================================================
//Descriptions:				
//input parameters:	us_num   0-4
//Output parameters:
//Returned value:    返回平均电压值0.01v
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


