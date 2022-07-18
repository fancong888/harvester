#include "Main.h"
#include "PublicPhy.h"
#include "PublicObj.h"
#include "Public_Function.h"


int main()
{
    SysClockInit();
    if(SysTick_Config(0x00FFFFFF))while (1);

    PeripheralInit();
    IwdgInit();
	
    uc_dealStep = 0;
    ul_baseTime = GetTime();
    for(;;)
    {
        if (ul_baseTime - GetTime() >= TIME_100US)
        {
            ul_baseTime -= TIME_100US;
            //user code
            us_timerTicker++;
            if((us_timerTicker%5) == 0)
            {
                ObjOLED_MainDeal();
            }
            if(us_timerTicker >= 20)
            {
                us_timerTicker = 0;

                PhyIo_DiDeal();
                ObjGpio_InputDeal();
                ObjSci_Uart1MainDeal();
                ObjSci_Uart2MainDeal();
                ObjAdc_MainDeal();
                
                IWDG_ReloadCounter();
                switch(uc_dealStep)
                {
                    case 0:
                    {			
                        ObjGpio_OutputDeal();
                        uc_dealStep++;
                        break;
                    }	
                    case 1:
                    {         
                        uc_dealStep++;
                        break;
                    }					
                    case 2:
                    {
                        uc_dealStep++;
                        break;
                    }				
                    case 3:
                    {
                        uc_dealStep++;
                        break;
                    }					
                    case 4:
                    {
                        uc_dealStep = 0;
                        break;					
                    }					
                    default:
                    {
                        uc_dealStep = 0;
                        break;
                    }				
                }
            }	
        }					
    }
}
