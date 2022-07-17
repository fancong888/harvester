#ifndef _OBJGPIO_H_
#define _OBJGPIO_H_

/*******************************Definition***************************************/
union GPIO_INPUT un_objGpio_input;
union GPIO_OUTPUT un_objGpio_output;
unsigned short us_objGpio_powerOnTimer;




/*******************************Function***************************************/
void ObjGpio_BatHold(void);
void ObjGpio_LedDeal(void);



#endif
