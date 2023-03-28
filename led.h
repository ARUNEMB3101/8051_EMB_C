#ifndef LED_H
#define LED_H
void led_on(void)
{ LED=0;
}
void ledoff(void)
{ 
  LED=1;
}
void toggle(void)
{ LED =!LED;
}

#endif
