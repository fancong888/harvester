#ifndef _PHYADC_H_
#define _PHYADC_H_

/*******************************Definition***************************************/
#define ADC_FILTER_NUM   50   //ÿͨ����50��
#define ADC_NUM 5                   //ͨ������
 
unsigned short us_PhyAdc_dmaValue[ADC_FILTER_NUM][ADC_NUM]; //�������ADCת�������Ҳ��DMA��Ŀ���ַ
unsigned short us_PhyAdc_value[ADC_NUM]; //���������ƽ��ֵ֮��Ľ��




/*******************************Function***************************************/
void PhyAdc_GpioInit(void);
void PhyAdc_ADC1Init(void);
void PhyAdc_DmaInit(void);



#endif
