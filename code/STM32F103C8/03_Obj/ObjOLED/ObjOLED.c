#include "PublicPhy.h"
#include "PublicObj.h"
#include "ObjOLED.h"



//==================================================
//Descriptions:				
//input parameters:	
//Output parameters:
//Returned value:
//==================================================
void ObjOLED_MainDeal(void)
{	
    char uc_strDis[20];
    char uc_str[5];
    static unsigned short us_step = 0;
    
    memset(uc_strDis, 0, sizeof(uc_strDis));
    
    switch(us_step)
    {
        case 0:
        {            
            uc_strDis[0] = 'V';
            uc_strDis[1] = 'B';
            uc_strDis[2] = 'A';
            uc_strDis[3] = 'T';
            uc_strDis[4] = ' ';
            uc_strDis[5] = ' ';
            uc_strDis[6] = ' ';
            uc_strDis[7] = ':';
            if(TRUE == PhySys_IsOffset(ul_objOLED_vBat, ul_objAdc_vBat, 5))
            {
                ul_objOLED_vBat = ul_objAdc_vBat;
            }
            sprintf(uc_str, " %d" , ul_objOLED_vBat);
            strcat(uc_strDis,uc_str);
            strcat(uc_strDis, " mV");
            if(TRUE == OLED_ShowStr1(0,us_step,uc_strDis))
            {
                us_step = 1;
            }
            break;
        }
        case 1:
        {            
            uc_strDis[0] = 'V';
            uc_strDis[1] = 'I';
            uc_strDis[2] = 'N';
            uc_strDis[3] = ' ';
            uc_strDis[4] = ' ';
            uc_strDis[5] = ' ';
            uc_strDis[6] = ' ';
            uc_strDis[7] = ':';
            if(TRUE == PhySys_IsOffset(ul_objOLED_vin, ul_objAdc_vin, 5))
            {
                ul_objOLED_vin = ul_objAdc_vin;
            }
            sprintf(uc_str, " %d" , ul_objOLED_vin);
            strcat(uc_strDis,uc_str);
            strcat(uc_strDis, " mV");
            if(TRUE == OLED_ShowStr1(0,us_step,uc_strDis))
            {
                us_step = 2;
            }
            break;
        }
        case 2:
        {            
            uc_strDis[0] = 'V';
            uc_strDis[1] = 'O';
            uc_strDis[2] = 'U';
            uc_strDis[3] = 'T';
            uc_strDis[4] = ' ';
            uc_strDis[5] = ' ';
            uc_strDis[6] = ' ';
            uc_strDis[7] = ':';
            if(TRUE == PhySys_IsOffset(ul_objOLED_outputLtc, ul_objAdc_outputLtc, 5))
            {
                ul_objOLED_outputLtc = ul_objAdc_outputLtc;
            }
            sprintf(uc_str, " %d" , ul_objOLED_outputLtc);
            strcat(uc_strDis,uc_str);
            strcat(uc_strDis, " mV");
            if(TRUE == OLED_ShowStr1(0,us_step,uc_strDis))
            {
                us_step = 3;
            }
            break;
        }
        case 3:
        {            
            uc_strDis[0] = 'P';
            uc_strDis[1] = 'G';
            uc_strDis[2] = 'O';
            uc_strDis[3] = 'O';
            uc_strDis[4] = 'D';
            uc_strDis[5] = ' ';
            uc_strDis[6] = ' ';
            uc_strDis[7] = ':';
            if(TRUE == PhySys_IsOffset(ul_objOLED_pGood, ul_objAdc_pGood, 5))
            {
                ul_objOLED_pGood = ul_objAdc_pGood;
            }
            sprintf(uc_str, " %d" , ul_objOLED_pGood);
            strcat(uc_strDis,uc_str);
            strcat(uc_strDis, " mV");
            if(TRUE == OLED_ShowStr1(0,us_step,uc_strDis))
            {
                us_step = 4;
            }
            break;
        }
        case 4:
        {            
            uc_strDis[0] = 'C';
            uc_strDis[1] = 'U';
            uc_strDis[2] = 'R';
            uc_strDis[3] = 'R';
            uc_strDis[4] = 'E';
            uc_strDis[5] = 'N';
            uc_strDis[6] = 'T';
            uc_strDis[7] = ':';
            if(TRUE == PhySys_IsOffset(ul_objOLED_current, ul_objAdc_current, 10))
            {
                ul_objOLED_current = ul_objAdc_current;
            }
            sprintf(uc_str, " %d" , ul_objOLED_current);
            strcat(uc_strDis,uc_str);
            strcat(uc_strDis, " uA");
            if(TRUE == OLED_ShowStr1(0,us_step,uc_strDis))
            {
                us_step = 0;
            }
            break;
        }
    }
}





