#ifndef _PHYADC_H_
#define _PHYADC_H_

/*******************************Definition***************************************/
#define ADC_FILTER_NUM   50   //每通道采50次
#define ADC_NUM 5                   //通道个数
 
unsigned short us_PhyAdc_dmaValue[ADC_FILTER_NUM][ADC_NUM]; //用来存放ADC转换结果，也是DMA的目标地址
unsigned short us_PhyAdc_value[ADC_NUM]; //用来存放求平均值之后的结果




/*******************************Function***************************************/
void PhyAdc_GpioInit(void);
void PhyAdc_ADC1Init(void);
void PhyAdc_DmaInit(void);



#endif
