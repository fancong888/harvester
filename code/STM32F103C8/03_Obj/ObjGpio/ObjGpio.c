#include "PublicPhy.h"
#include "PublicObj.h"
#include "ObjGpio.h"


//==================================================
//Function name:		ObjGpio_ParaInit
//Descriptions:			变量初始化
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
void ObjGpio_ParaInit(void)
{
	
}


//==================================================
//Descriptions:			
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
void ObjGpio_AdcDeal(void)
{
	
}

//==================================================
//Descriptions:			
//input parameters:		
//Output parameters:
//Returned value:
//==================================================
void ObjGpio_BatHold(void)
{
    static unsigned long ul_holdTimer = 0;
    
    un_objGpio_output.bit.powerHold = 1;
    
    if(un_objGpio_output.bit.powerHold)
    {
        ul_holdTimer += TIME_10MS;
    }
    if(ul_holdTimer >= TIME_1MIN*30)
    {
        ul_holdTimer = TIME_1MIN*30;
        un_objGpio_output.bit.powerHold = 0;
    }
}


//==================================================
//Descriptions:			对象层灯处理
//input parameters:		
//Output parameters:
//Returned value:
//==================================================
void ObjGpio_LedDeal(void)
{
    static unsigned short us_runTimer = 0;

    //run指示灯
    us_runTimer += TIME_10MS;
    if(us_runTimer <= 100)
    {
        un_objGpio_output.bit.runLed = 1;
    }
    else if(us_runTimer < 200)
    {
        un_objGpio_output.bit.runLed = 0;
    }
    else
    {
        us_runTimer = 0;
    }
}

//==================================================
//Descriptions:			
//input parameters:		
//Output parameters:
//Returned value:
//==================================================
void ObjGpio_OutputDeal(void)
{
    ObjGpio_BatHold();
    ObjGpio_LedDeal();
    PhyGpio_WriteToPeriph(&un_objGpio_output);
}



