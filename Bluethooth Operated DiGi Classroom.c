#include <AT89S52.h>
#define FOSC 11059200
#define TCLK FOSC/12
#define SCLK TCLK/32
#define FAN1 P0_0
#define FAN2 P0_1
#define LIGHT1 P0_2
#define LIGHT2 P0_3
#define DATA P2
#define RS P0_4
#define RW P0_5
#define EN P0_6
#define ODOOR P3_0
#define CDOOR P3_1
void BAUD_RATE(int);
void wait (char);
void lcd_init(void);
void lcd_data(char);
void lcd_cmd(char);
void lcd_busy(void);
void lcd_print(char*);
void main()
{
 int F1=0;
 int F2=0;
 int L1=0;
 int L2=0;
 int D1=0;
 BAUD_RATE(9600);
 ODOOR=0;
 CDOOR=0;
 LIGHT1=0;
 LIGHT2=0;
 FAN1=0;
 FAN2=0;
 EN=0;
 lcd_init();
 lcd_print("Welcome to");
 lcd_cmd(0xC0);
 lcd_print("TEAM DYNAMIC !");

 while(1)
 {  
   if(F1==1)
   {
    FAN1=1;
    lcd_cmd(0x01);
    lcd_print("  FAN-1  ");
    lcd_cmd(0xC0);
    lcd_print("***ON***");
   }
   else if (F1==2)
   {
    FAN1=0;
    F1=0;
    lcd_cmd(0x01);
    lcd_print("  FAN-1  ");
    lcd_cmd(0xC0);
    lcd_print("***OFF***");
   }
   if(F2==1)
   {
    FAN2=1;
    lcd_cmd(0x01);
    lcd_print("  FAN-2  ");
    lcd_cmd(0xC0);
    lcd_print("***ON***");
   }
   else if(F2==2)
   {
    FAN2=0;
    F2=0;
    lcd_cmd(0x01);
    lcd_print("  FAN-2  ");
    lcd_cmd(0xC0);
    lcd_print("***OFF***");
   }
   if(L1==1)
   {
    LIGHT1=1;
    lcd_cmd(0x01);
    lcd_print("  LIGHT-1  ");
    lcd_cmd(0xC0);
    lcd_print("***ON***");
   }
   else if(L1==2)
   {
    LIGHT1=0;
    L1=0;
    lcd_cmd(0x01);
    lcd_print("  LIGHT-1  ");
    lcd_cmd(0xC0);
    lcd_print("***ON***");
   }
   if(L2==1)
   {
    LIGHT2=1;
    lcd_cmd(0x01);
    lcd_print("  LIGHT-2  ");
    lcd_cmd(0xC0);
    lcd_print("***ON***");
   }
   else if(L2==2)
   {
    LIGHT2=0;
    L2=0;
    lcd_cmd(0x01);
    lcd_print("  LIGHT-1  ");
    lcd_cmd(0xC0);
    lcd_print("***ON***");
   }
   if(D1==1)
   {
    ODOOR=1;
    CDOOR=0;
    lcd_cmd(0x01);
    lcd_print("  DOOR  ");
    lcd_cmd(0xC0);
    lcd_print("***OPENING***");
    wait(150);
    ODOOR=0;
    lcd_cmd(0x01);
    lcd_print("  DOOR  ");
    lcd_cmd(0xC0);
    lcd_print("***OPENED***");
   }
   else if(D1==2)
   {
    D1=0;
    ODOOR=0;
    CDOOR=1;
    lcd_cmd(0x01);
    lcd_print("  DOOR  ");
    lcd_cmd(0xC0);
    lcd_print("***CLOSING***");
    wait(150);
    CDOOR=0;
    lcd_cmd(0x01);
    lcd_print("  DOOR  ");
    lcd_cmd(0xC0);
    lcd_print("***CLOSED***");
   }
  if(RI==1)
  {
   RI=0;
    if(SBUF=='B'&(F1==0|F2==1))
    {
    wait(50);
    F1++;
    }
    else if(SBUF=='S')
    {
    }
    if(SBUF == 'C'&(F2==0|F2==1))
    {
    wait(50);
    F2++;
    }
    else if(SBUF=='S')
    {
    }
    if (SBUF == 'D'& (L1==0|L1==1))
    {
    wait(50);
    L1++;
    }
    else if(SBUF=='S')
    {
    }
    if (SBUF == 'E'& (L2==0|L2==1))
    {
    wait(50);
    L2++;
    }
    else if(SBUF=='S')
    {
    }
    if (SBUF == 'F'& (D1==0|D1==1))
    {
    wait(50);
    D1++;
    }
    else if(SBUF=='S')
    {
    }
    if(SBUF=='A')
    {
    ODOOR=0;
    CDOOR=0;
    LIGHT1=0;
    LIGHT2=0;
    FAN1=0;
    FAN2=0;
    lcd_cmd(0x01);
    lcd_print("  RESET  ");
    lcd_cmd(0xC0);
    lcd_print("***ALL***");
    }
    else if(SBUF=='S')
    {
    }
}
}
}
void BAUD_RATE(int baud)
{
 char b;
 SCON=0X50;
 TMOD=0x20;
 b=(0xFF-(SCLK/baud))+1;
 TH1=b;
 TL1=b;
 TR1=1;
}
void lcd_init(void)
{
 lcd_busy();
 lcd_cmd(0x38);
 lcd_cmd(0x01);
 lcd_cmd(0x0C);
 lcd_cmd(0x06);
 lcd_cmd(0x80);
}

void lcd_cmd(char c)
{
 DATA=c;
 RS=0;
 RW=0;
 EN=1;
 EN=0;
 lcd_busy();
}

void lcd_data(char d)
{
 DATA=d;
 RS=1;
 RW=0;
 EN=1;
 EN=0;
 lcd_busy();
}

void lcd_busy()
{
 char s;
 RS=0;
 RW=1;
 DATA=0xFF;
 EN=1;
 s=DATA&0x80;
 EN=0;
 while(s!=0x00)
 {
  EN=1;
  s=DATA&0x80;
  EN=0;
 }
}

void lcd_print(char*msg)
{
 while(*msg!=0x00)
 {
  lcd_data(*msg);
  *msg++;
 }
}

void wait (char d)
{
 char i;
 int j;
 for(i=0;i<d;i++)
 {
  for(j=0;j<1275;j++)
  {
  
  }
 }
}



