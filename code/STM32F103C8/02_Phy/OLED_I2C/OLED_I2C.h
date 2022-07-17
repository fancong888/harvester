#ifndef __OLED_I2C_H
#define	__OLED_I2C_H

/*******************************Definition***************************************/
#define OLED_ADDRESS	0x78 //ͨ������0R����,������0x78��0x7A������ַ -- Ĭ��0x78




/*******************************Function***************************************/
void I2C_Configuration(void);
void OLED_Init(void);
bool OLED_WriteChar(unsigned char ch);
bool OLED_SetPos(unsigned char x, unsigned char y) ;
void OLED_Fill(unsigned char fill_Data);
bool WriteCmd(unsigned char I2C_Command);
bool WriteDat(unsigned char I2C_Data);
bool I2C_WriteByte(uint8_t addr,uint8_t data);




#endif
