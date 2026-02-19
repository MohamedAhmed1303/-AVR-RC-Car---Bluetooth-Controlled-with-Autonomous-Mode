/*
 * LCD_interface.h
 *
 *  Created on: Sep 6, 2025
 *      Author: Mohamed
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


void LCD_SendData(u8 Data);
void LCD_SendCmd(u8 Cmd);
void LCD_Init();
void LCD_SendString(char *ptrstring);
void LCD_SetPosition(u8 x,u8 y);
void LCD_ClearDisplay();
void LCD_SendNumber(u16 Number);
void LCD_SendSpecialCharacter(u8 BlockNum,u8 *ptrpattern,u8 x,u8 y );


#endif /* LCD_INTERFACE_H_ */
