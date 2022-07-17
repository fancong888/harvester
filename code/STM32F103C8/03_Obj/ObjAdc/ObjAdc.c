#include "PublicPhy.h"
#include "PublicObj.h"
#include "ObjAdc.h"



//==================================================
//Descriptions:			
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
void ObjAdc_MainDeal(void)
{	
    ul_objAdc_vBat = PhyAdc_GetValue(0)*1410ul/100;
    ul_objAdc_current = PhyAdc_GetValue(1)*1000ul/100;
    ul_objAdc_pGood = PhyAdc_GetValue(2)*1000ul/100;
    ul_objAdc_outputLtc = PhyAdc_GetValue(3)*1110ul/100;
    ul_objAdc_vin = PhyAdc_GetValue(4)*5590ul/100; 

    ObjAdc_CurrentDeal();
}


//==================================================
//Descriptions:			
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
void ObjAdc_CurrentDeal(void)
{
    if(ul_objAdc_current < 15)
    {
        ul_objAdc_current = 0;
    }
    else if(ul_objAdc_current <= 110)
    {
        ul_objAdc_current = 200*(ul_objAdc_current-15)/95;
    }
    else if(ul_objAdc_current <= 124)
    {
        ul_objAdc_current = 200+200*(ul_objAdc_current-110)/14;
    }
    else if(ul_objAdc_current <= 137)
    {
        ul_objAdc_current = 400+200*(ul_objAdc_current-124)/13;
    }
    else if(ul_objAdc_current <= 151)
    {
        ul_objAdc_current = 600+200*(ul_objAdc_current-137)/14;
    }
    else if(ul_objAdc_current <= 164)
    {
        ul_objAdc_current = 800+200*(ul_objAdc_current-151)/13;
    }
    else if(ul_objAdc_current <= 427)
    {
        ul_objAdc_current = 1000+200*(ul_objAdc_current-164)/263;
    }
    else if(ul_objAdc_current <= 758)
    {
        ul_objAdc_current = 5000+4000*(ul_objAdc_current-427)/331;
    }
    else if(ul_objAdc_current <= 1089)
    {
        ul_objAdc_current = 10000+5000*(ul_objAdc_current-758)/331;
    }
    else if(ul_objAdc_current <= 1420)
    {
        ul_objAdc_current = 15000+5000*(ul_objAdc_current-1089)/331;
    }
    else if(ul_objAdc_current <= 1750)
    {
        ul_objAdc_current = 20000+5000*(ul_objAdc_current-1420)/330;
    }
    else if(ul_objAdc_current <= 2081)
    {
        ul_objAdc_current = 25000+5000*(ul_objAdc_current-1750)/331;
    }
    else if(ul_objAdc_current <= 2412)
    {
        ul_objAdc_current = 30000+5000*(ul_objAdc_current-2081)/331;
    }
    else if(ul_objAdc_current <= 2742)
    {
        ul_objAdc_current = 35000+5000*(ul_objAdc_current-2412)/330;
    }
    else if(ul_objAdc_current <= 3073)
    {
        ul_objAdc_current = 40000+5000*(ul_objAdc_current-2742)/331;
    }
    else if(ul_objAdc_current <= 3403)
    {
        ul_objAdc_current = 45000+5000*(ul_objAdc_current-3073)/330;
    }
    else
    {
        ul_objAdc_current = 50000;
    }
}


