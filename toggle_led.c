#include<AT89S52.h>
void wait(char val)
{
int i;
for(i=0;i<val;i++)
{
}
}
void main()
{
while(1)
{
P2_0=!P2_0;
wait(10);
}
}



