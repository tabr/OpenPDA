/*
  *  debugInMain.h
  *
  *  Created:  2015-07-19  23:17:30
  *    Author:  tabr
  */  


#ifndef  DEBUGINMAIN_H_
#define  DEBUGINMAIN_H_

/*
//  while(1){};
UsableItem.testWrite();
//UsableItem.twi_write_byte(0,100);
//  uint8_t  testData1[8]  =  {16,17,18,19,20,21,22,23};
//  UsableItem.twi_write_page(2,testData1);
//  uint8_t  testData2[8]  =  {24,25,26,27,28,29,30,31};
//  UsableItem.twi_write_page(3,testData2);
  while(1)
    {
    sprintf  (lcd_buf,  "6:  ___");
    LcdString(1,LCD_LINE_6);
    LcdUpdate();
    UsableItem.testRead();
    sprintf  (lcd_buf,  "7:  ___");
    LcdString(1,LCD_LINE_6);
    LcdUpdate();
//    delay_ms(100);
//    LcdUpdate();
    delay_ms(1000);
    sprintf  (lcd_buf,  "8:  ___");
    LcdString(1,LCD_LINE_6);
    LcdUpdate();
    }
*/
  //rtcSetDateTime(rtc,14,8,5,19,29,00);
/*
  M25P05_Init();

  M25P05_Write_enable();
  M25P05_BulkErase();//нужно  разр  запись  сначала!
    sprintf  (lcd_buf,  "123");
    LcdString(1,LCD_LINE_1);
    LcdUpdate();
  M25P05_Write_disable();
  while((M25P05_Read_Status_Register()  &  1)  !=  0)
    {
    sprintf  (lcd_buf,  "%03d",++randomPseudo);
    LcdString(1,LCD_LINE_1);
    LcdUpdate();
    }
  M25P05_Write_enable();
  M25P05_ByteProgram(0,0,0,ArtefactPorts.ITEM_TYPE_MEDICAMENTS);
  while((M25P05_Read_Status_Register()  &  1)  !=  0);
*/
/*
  M25P05_Write_enable();
  M25P05_ByteProgram(0,0,1,0);//subtype
  while((M25P05_Read_Status_Register()  &  1)  !=  0);
  M25P05_Write_enable();
  M25P05_ByteProgram(0,0,2,PlayerInventoryClass::ITEM_FIRST_AID);
  while((M25P05_Read_Status_Register()  &  1)  !=  0);
  M25P05_Write_enable();
  M25P05_ByteProgram(0,0,3,ArtefactPortsClass::DEVICE_STATUS_OK);
  while((M25P05_Read_Status_Register()  &  1)  !=  0);
  M25P05_Write_enable();
  M25P05_ByteProgram(0,0,4,0b11111111);//заряды
  while((M25P05_Read_Status_Register()  &  1)  !=  0);
  M25P05_Write_enable();
  M25P05_ByteProgram(0,0,5,10);//к-во  ХП
  while((M25P05_Read_Status_Register()  &  1)  !=  0);
  M25P05_Write_enable();
  M25P05_ByteProgram(0,0,6,50);//задержка  (x10ms)
  M25P05_Write_disable();
*/
/*
M25P05_Init();
while(1)
  {
  sprintf  (lcd_buf,  "%03d%03d  %03d%03d",  M25P05_Read_DataByte(0,0,0),  M25P05_Read_DataByte(0,0,1),  M25P05_Read_DataByte(0,0,2),  M25P05_Read_DataByte(0,0,3));
  LcdString(1,LCD_LINE_1);
  sprintf  (lcd_buf,  "%03d%03d  %03d%03d",  M25P05_Read_DataByte(0,0,4),  M25P05_Read_DataByte(0,0,5),  M25P05_Read_DataByte(0,0,6),  M25P05_Read_DataByte(0,0,7));
  LcdString(1,LCD_LINE_2);
  sprintf  (lcd_buf,  "%03d",++randomPseudo);
  LcdString(1,LCD_LINE_3);
  LcdUpdate();
  }
*/
/*
    while(1)
    {


  cbi(M25P05_SS_PORT,    M25P05_SS_PIN);
  cbi(M25P05_SS_DDR,    M25P05_SS_PIN);//вход
  _delay_us(1);
  if  ((M25P05_SS_IN  &  1<<M25P05_SS_PIN)  ==  0)
    {
    sprintf  (lcd_buf,  "not  presents");
    }
  else
    {
    sprintf  (lcd_buf,  "  presents");
    }
  LcdString(1,LCD_LINE_3);
  sprintf  (lcd_buf,  "%03d",(M25P05_SS_IN  &  M25P05_SS_PIN));
  LcdString(1,LCD_LINE_4);
  sbi(M25P05_SS_DDR,    M25P05_SS_PIN);//выход
  _delay_us(1);


uint8_t  tmp=0;
PORTF.DIR=255;
PORTK.DIR=255;
delay_ms(100);
PORTF.OUT=255;
PORTK.OUT=0;
//PORTK.PIN0CTRL  =  PORT_OPC_PULLDOWN_gc;
while  (1)
{
  PORTK.OUTTGL  =  1<<0;
  PORTF.OUTTGL  =  1<<0;
  sprintf  (lcd_buf,  "%03d",++tmp);
  LcdString(1,LCD_LINE_1);
  LcdUpdate();
  delay_ms(1000);
}
while(1)
    {
    sprintf  (lcd_buf,  "[%03d/%03d/%03d]",  M25P05_Read_DataByte(0,0,0),  M25P05_Read_DataByte(0,0,1),  ++tmp);
    LcdString(1,LCD_LINE_1);
    sprintf  (lcd_buf,  "status:[%03d]",  M25P05_Read_Status_Register());
    LcdString(1,LCD_LINE_2);
//    sprintf  (lcd_buf,  "connected[%01d]",  ((M25P05_SS_IN  &  1<<M25P05_SS_PIN)  !=  0));
    //LcdString(1,LCD_LINE_3);
    LcdUpdate();
    if  (M25P05_SS_IN  &  1<<M25P05_SS_PIN)
      {
      //_delay_ms(100);
      PORTE.OUTTGL  =  1<<M25P05_LED_PIN;
      }
    }
*/
  
  
//  PDASound.stopSouns();
/*
  AES_Class  AESobj;
//  bool  result  =  AESobj.Lastsubkey_generate();
  uint8_t  encryptedData[16]  =  {0x9F,  0xC3,  0x85,  0x0E,  0x99,  0x19,  0x81,  0x26,  0x35,  0x52,  0x03,  0xB3,  0x5F,  0xA3,  0x0F,  0x2B};
  uint8_t  resultText[16]    =  {0x73,  0x75,  0x6b,  0x61,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00};//suka
    
  
  //AESobj.SoftwareReset();
  bool  result  =  false;
//  result  =  AESobj.AES_CBC_encrypt(resultText,  encryptedData,  AESobj.key,  AESobj.init,  1);
  //result  =  AESobj.AES_CBC_decrypt(encryptedData,  resultText,  AESobj.lastSubkey,  AESobj.init,  1);
  //result  =  AESobj.CBC_Decrypt(encryptedData);
  //result    =  AESobj.AES_decrypt(uint8_t  *  ciphertext,  uint8_t  *  plaintext,  uint8_t  *  key)
  //bool  AES_CBC_encrypt(uint8_t  *  plaintext,  uint8_t  *  ciphertext,uint8_t  *  key,  uint8_t  *  init,  uint16_t  block_count)
//    uint8_t*  printObj  =  dynamic_cast<const  uint8_t>(AESobj.lastSubkey);



    result  =  AESobj.AES_CBC_encrypt(resultText,  encryptedData,  1);
    result  =  AESobj.CBC_Decrypt(encryptedData);
    uint8_t*  printObj  =  encryptedData;
    LcdClearCache();
    sprintf  (lcd_buf,"%01d",result);
    LcdString(1,LCD_LINE_1);
    sprintf  (lcd_buf,"%02x  %02x  %02x  %02x",  printObj[0],  printObj[1],  printObj[2],  printObj[3]);
    LcdString(1,LCD_LINE_2);
    sprintf  (lcd_buf,"%02x  %02x  %02x  %02x",  printObj[4],  printObj[5],  printObj[6],  printObj[7]);
    LcdString(1,LCD_LINE_3);
    sprintf  (lcd_buf,"%02x  %02x  %02x  %02x",  printObj[8],  printObj[9],  printObj[10],  printObj[11]);
    LcdString(1,LCD_LINE_4);
    sprintf  (lcd_buf,"%02x  %02x  %02x  %02x",  printObj[12],  printObj[13],  printObj[14],  printObj[15]);
    LcdString(1,LCD_LINE_5);
    LcdUpdate();
    while(1)
      {
      
      }
*/



#endif  /*  DEBUGINMAIN_H_  */
