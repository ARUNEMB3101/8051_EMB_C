#include <AT89S52.h> 

#define LCD_DATA P2 
#define LCD_RS P3_4 
#define LCD_RW P3_5 
#define LCD_EN P3_6 

void lcd_init(); 
void lcd_command(unsigned char cmd); 
void lcd_data(unsigned char dat); 
void lcd_string(unsigned char str[]); 
void delay_ms(); 

void main()
{
  lcd_init();
  lcd_string("EMBEDDED"); 
  
  while(1)
  {
     }
}

void lcd_init()
{
  delay_ms(); 
  
  lcd_command(0x38); 
  lcd_command(0x0C); 
  lcd_command(0x01); 
  lcd_command(0x06); 
}

void lcd_command(unsigned char cmd)
{
  LCD_RS = 0; 
  LCD_RW = 0; 
  LCD_DATA = cmd; 
  LCD_EN = 1; 
   delay_ms(); 
  LCD_EN = 0; 
}

void lcd_data(unsigned char dat)
{
  LCD_RS = 1; 
  LCD_RW = 0; 
  LCD_DATA = dat; 
  LCD_EN = 1; 
  delay_ms(); 
  LCD_EN = 0; 
}

void lcd_string(unsigned char str[])
{
  int i; 
  for(i=0; str[i]!='\0'; i++) 
  {
    lcd_data(str[i]); 
  }
}

void delay_ms()
{
  unsigned int i, j;
  for(i=0; i<10000; i++)
  {
 
  }
}

