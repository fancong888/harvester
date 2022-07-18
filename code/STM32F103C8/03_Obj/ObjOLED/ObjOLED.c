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
    unsigned char i = 0;
    unsigned char len = 0;
    char uc_strDis[20];
    char uc_str[5];
    static unsigned short us_step = 0, us_stepBak = 0;
    
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
            sprintf(uc_str, " %d" , ul_objOLED_vBat);
            strcat(uc_strDis,uc_str);
            strcat(uc_strDis, " mV");
            len = OLED_X_MAX-strlen(uc_strDis);
            for(i = 0; i < len; i++)
            {
                strcat(uc_strDis, " ");
            }
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
            sprintf(uc_str, " %d" , ul_objOLED_vin);
            strcat(uc_strDis,uc_str);
            strcat(uc_strDis, " mV");
            len = OLED_X_MAX-strlen(uc_strDis);
            for(i = 0; i < len; i++)
            {
                strcat(uc_strDis, " ");
            }
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
            sprintf(uc_str, " %d" , ul_objOLED_outputLtc);
            strcat(uc_strDis,uc_str);
            strcat(uc_strDis, " mV");
            len = OLED_X_MAX-strlen(uc_strDis);
            for(i = 0; i < len; i++)
            {
                strcat(uc_strDis, " ");
            }
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
            sprintf(uc_str, " %d" , ul_objOLED_pGood);
            strcat(uc_strDis,uc_str);
            strcat(uc_strDis, " mV");
            len = OLED_X_MAX-strlen(uc_strDis);
            for(i = 0; i < len; i++)
            {
                strcat(uc_strDis, " ");
            }
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
            sprintf(uc_str, " %d" , ul_objOLED_current);
            strcat(uc_strDis,uc_str);
            strcat(uc_strDis, " uA");
            len = OLED_X_MAX-strlen(uc_strDis);
            for(i = 0; i < len; i++)
            {
                strcat(uc_strDis, " ");
            }
            if(TRUE == OLED_ShowStr1(0,us_step,uc_strDis))
            {
                us_step = 5;
            }
            break;
        }
        case 5:
        {            
            uc_strDis[0] = 'C';
            uc_strDis[1] = 'H';
            uc_strDis[2] = 'A';
            uc_strDis[3] = 'R';
            uc_strDis[4] = 'G';
            uc_strDis[5] = 'E';
            uc_strDis[6] = ' ';
            uc_strDis[7] = ':';
            if(un_objGpio_input.bit.charge)
            {
                strcat(uc_strDis," YES");
            }
            else
            {
                strcat(uc_strDis, " NO ");
            }         
            len = OLED_X_MAX-strlen(uc_strDis);
            for(i = 0; i < len; i++)
            {
                strcat(uc_strDis, " ");
            }
            if(TRUE == OLED_ShowStr1(0,us_step,uc_strDis))
            {
                us_step = 0;
            }
            break;
        }
    }

    if(us_step != us_stepBak)
    {
        ul_objOLED_vBat = ul_objAdc_vBat;
        ul_objOLED_vin = ul_objAdc_vin;
        ul_objOLED_outputLtc = ul_objAdc_outputLtc;
        ul_objOLED_pGood = ul_objAdc_pGood;
        ul_objOLED_current = ul_objAdc_current;
    }
    us_stepBak = us_step;
}




