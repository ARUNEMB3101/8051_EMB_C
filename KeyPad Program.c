#include <AT89S52.h>
#define FOSC 11059200
#define TCLK FOSC/12
#define SCLK TCLK/32
#define LED P2_0
void baud_rate(int);
void send_msg(char*);
void send_byte(char);
void wait (char);
char readKey(void);
void read(void);
char buffer[50];
__bit b;
__bit verify(char *);
#define KEYPAD P0
const char array[]={0X76,0X7A,0X7C,0XB6,0XBA,0XBC,0XD6,0XDA,0XDC,0XE6,0XEA,0XEC};
const char key[]="123456789*0#";

void main()
{
 char ch;
 baud_rate(9600);
 LED=1;
 while(1)
 {
  send_byte(key[readKey()]);
  send_msg("\n\n");
  KEYPAD = 0XF0;
  ch = (KEYPAD&0XF0)|0X0F;
  ch = ~ch;
  while(ch!=0)
  {
   ch = (KEYPAD&0XF0)|0X0F;
   ch = ~ch;
  }
 }
}
void read(void)
  {
   char i=0;
   while(1)
   {
    while(RI==0)
    { 
    }
    RI=0;
    if(SBUF!='$')
    {
      buffer[i]=SBUF;
      i++;
    }
    else
    {
      break;
    }
   }
   }
__bit verify(char *buf)
{
   char i=0;
   while(*buf!=0)
  {
    if (*buf ==buffer[i])
    {
       b=1;
    }
    else 
    {
      b=0;
      return b;
    }
    i++;
    *buf++;
  }
  
  return b;
}


void baud_rate(int baud)
{
 char b;
 SCON=0X50;
 TMOD=0x20;
 b=(0xFF-(SCLK/baud))+1;
 TH1=b;
 TL1=b;
 TR1=1;
}

void send_msg(char *m)
{
 while(*m!=0)
 {
  SBUF=*m;
  *m++;
  while(TI==0)
  {}
  TI=0;
 }
}


void send_byte(char c)
{
 SBUF=c;
 while(TI==0)
  {}
  TI=0;
}

void wait (char d)
{
 char i;
 int j;
 for(i=0;i<d;i++)
 {
  for(j=0;j<1275;j++)
  {}
 }
}

char readKey()
{
 char row,col,position,i;
  KEYPAD = 0XF0;
  while((KEYPAD & 0XF0)==0xF0)
  {
  }
  row = KEYPAD & 0XF0;
  KEYPAD = 0X0F;
  col=KEYPAD & 0X0E;
  position = row|col;
  for(i=0;i<11;i++)
  {
   if(position ==array[i])
   {
     return i;
   }
   else
   {
   }
  }
  return i;
}

