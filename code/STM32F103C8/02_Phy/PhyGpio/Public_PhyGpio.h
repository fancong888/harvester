#ifndef	_PUBLIC_PHYGPIO_H_
#define _PUBLIC_PHYGPIO_H_

/*******************************Definition***************************************/
union GPIO_OUTPUT
{
    unsigned short all; 	
    struct 
    {
        unsigned short powerHold: 1;                
        unsigned short runLed: 1;                        
        unsigned short batLed: 1;                        
        unsigned short rsvd1: 13;                       
    }bit;
};




/*******************************Function***************************************/
void PhyGpio_ParamInit(void);
void PhyGpio_PeriphInit(void);
void PhyGpio_ReadFromPeriph(unsigned long *gpioInputValue);
void PhyGpio_WriteToPeriph(union GPIO_OUTPUT *pOutput);



#endif

