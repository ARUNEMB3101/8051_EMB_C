#include <AT89S52.h>
#define FOSC 11059200
#define TCLK FOSC/12
#define SCLK TCLK/32
#define M1_FRONT P1_0
#define M1_BACK P1_1
#define M2_FRONT P1_2
#define M2_BACK P1_3
#define INDICATOR P0_0
#define BUZZER P0_1
#define DATA P2
#define RS P0_6
#define RW P0_5
#define EN P0_4
#define LAWN P0_2
#define VACUUM P0_3
#define TRIG P1_4
#define ECHO P1_5
void VACCUM_CLEANER(void);
void LAWN_MOWER(void);
void STOP_FUNCTION(void);
void MOVE_FRONT(void);
void MOVE_BACK(void);
void MOVE_RIGHT(void);
void MOVE_LEFT(void);
void BAUD_RATE(int);
int  get_distance(void);
void wait (char);
void lcd_init(void);
void lcd_data(char);
void lcd_cmd(char);
void lcd_busy(void);
void lcd_print(char*);
void ALERT(void);

void main()
{
 int AA=0;
 int BB=0;
 int CC=0;
 BAUD_RATE(9600);
 M1_FRONT=0;/*MOTOR_1 (P1_0) OFF*/
 M1_BACK =0;/*MOTOR_1 (P1_1)OFF*/
 M2_FRONT=0;/*MOTOR_2 (P1_2)OFF*/
 M2_BACK =0;/*MOTOR_2 (P1_3)OFF*/
 INDICATOR =0;
 BUZZER =0;
 LAWN =0;
 VACUUM =0;
 EN=0;
 lcd_init();
 lcd_print("Welcome to");
 lcd_cmd(0xC0);
 lcd_print("EMBEDED BUILDERS !");

 while(1)
 {  
   unsigned int dist=get_distance();
   if(CC==1)
   {
    MOVE_FRONT();
   }
   else if (CC==2)
   {
    CC=0;
    INDICATOR =0;
    M1_FRONT=0;/*MOTOR_1 (P1_0) OFF*/
    M2_FRONT=0;/*MOTOR_2 (P1_2)OFF*/
   }
   if(AA==1)
   {
    LAWN = 1;
    VACUUM =0;
    lcd_cmd(0x01);
    lcd_print("-------AS-------");
    lcd_cmd(0xC0);
    lcd_print("**Lawn Cutter**");
   }
   else if(AA==2)
   {
    AA=0;
    LAWN =0;
    lcd_cmd(0x01);
    lcd_print("---FUNCTION---");
    lcd_cmd(0xC0);
    lcd_print("***Stopped***");
   }
   if(BB==1)
   {
    VACUUM = 1;
    LAWN =0;
    lcd_cmd(0x01);
    lcd_print("-------AS-------");
    lcd_cmd(0xC0);
    lcd_print("*Vacuum Cleaner*");
   }
   else if(BB==2)
   {
    BB=0;
    VACUUM = 0;
    lcd_cmd(0x01);
    lcd_print("---FUNCTION---");
    lcd_cmd(0xC0);
    lcd_print("***Stopped***");
   }
  if(RI==1)
  {
   RI=0;
   if(SBUF=='F')
   {
    MOVE_FRONT();
   }
   else if(SBUF=='B')
   {
     MOVE_BACK();
   }
   else if(SBUF=='L')
   {
    MOVE_LEFT();
   }
   else if(SBUF=='R')
   {
    MOVE_RIGHT();
   }
    else if(SBUF=='S')
    {
    INDICATOR =0;
    M1_FRONT=0;/*MOTOR_1 (P1_0) OFF*/
    M1_BACK =0;/*MOTOR_1 (P1_1)OFF*/
    M2_FRONT=0;/*MOTOR_2 (P1_2)OFF*/
    M2_BACK =0;/*MOTOR_2 (P1_2)OFF*/
    }
    if(SBUF=='D'&(CC==0|CC==1))
    {
    wait(50);
    CC++;
    }
    else if(SBUF=='T')
    {
    }
    if(SBUF == 'M'&(AA==0|AA==1))
    {
    wait(50);
    AA++;
    }
    else if(SBUF=='T')
    {
    }
    if (SBUF == 'C'& (BB==0|BB==1))
    {
    wait(50);
    BB++;
    }
    else if(SBUF=='T')
    {
    }
}
}
}
int get_distance(void)
{
 int ultra_dist;
 char ultra_q;
 TRIG=0;
 ECHO=1;
 TR0=0;
 TMOD=(TMOD&0xF0)|(0x01);
 TH0=0x00;
 TL0=0x00;

 TRIG=1;
 for(ultra_q=0;ultra_q<10;ultra_q++)
 {}
 TRIG=0;
 while(ECHO==0)
 {
 }
 TR0=1;
 while(ECHO==1)
 {
 }
 TR0=0;
 ultra_dist=((TH0*256)+TL0)/54;
 return ultra_dist;
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
void MOVE_FRONT()
{
  M1_FRONT=1;
  M2_FRONT=1;
  INDICATOR =1;
}
void MOVE_BACK()
{
  M1_BACK=1;
  M2_BACK=1; 
  INDICATOR=1;
}
void MOVE_RIGHT()
{
  M1_FRONT=1;
  M2_BACK =1;
  INDICATOR =1;
}
void MOVE_LEFT()
{
  M1_BACK=1;
  M2_FRONT=1;
  INDICATOR =1;
}
void ALERT()
{
    M1_FRONT=0;/*MOTOR_1 (P1_0) OFF*/
    M1_BACK =0;/*MOTOR_1 (P1_1)OFF*/
    M2_FRONT=0;/*MOTOR_2 (P1_2)OFF*/
    M2_BACK =0;/*MOTOR_2 (P1_3)OFF*/
    INDICATOR = 0; /*RED LIGHT ON*/
    BUZZER = 1;
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



