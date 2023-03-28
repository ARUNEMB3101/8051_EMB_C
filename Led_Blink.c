#include<AT89S52.h>
void wait(void)       //DEFINING DELAY PROGRAM
{
int i;
for(i=0;i<100;i++)
{
}
}
void main()
{
while(1)    //THE LOOP RUNS INFINITE TIMES
{
P2_0=0; //INTIALLY LED IS ON
wait();  //CALLING DELAY FUNCTION
P2_0=1;   //LED IS OFF
wait();   //CALLING DELAY FUNCTION
}
}


