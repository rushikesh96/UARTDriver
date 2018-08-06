/*
 * uart.h
 *
 *  Created on: 24-Jul-2018
 *      Author: Hrishikesh-Derive
 */
#define DECIMAL_COUNT 5
#define BAUD_RATE 9600
unsigned int adc_data=0,uart_data=0;



void uart_init(unsigned int b_rate)
{
    P3SEL = BIT3+BIT4;                        // P3.4,5 = USCI_A0 TXD/RXD
     UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
     UCA0CTL1 |= UCSSEL_2;

switch(b_rate)
{
case 9600:
    UCA0BR0 = 6;
     UCA0BR1 = 0;
     UCA0MCTL = UCBRS_0 + UCBRF_13 + UCOS16;
break;
case 14400:
    UCA0BR0 = 4;
     UCA0BR1 = 0;
     UCA0MCTL = UCBRS_0 + UCBRF_13 + UCOS16;
    break;
case 19200:
    UCA0BR0 = 52;
     UCA0BR1 = 0;
     UCA0MCTL |= UCBRS_1 + UCBRF_0 ;
    break;
case 38400:
    UCA0BR0 = 26;
     UCA0BR1 = 0;
     UCA0MCTL |= UCBRS_1 + UCBRF_0 ;
    break;
case 57600:
    UCA0BR0 = 17;
     UCA0BR1 = 0;
     UCA0MCTL |= UCBRS_1 + UCBRF_0 ;
    break;
default:
    UCA0BR0 = 9;
     UCA0BR1 = 0;
     UCA0MCTL |= UCBRS_1 + UCBRF_0 ;






}
UCA0CTL1 &= ~UCSWRST;
__no_operation();

}
void uart_tx(unsigned char data)
{
    while (!(UCA0IFG&UCTXIFG));

    UCA0TXBUF = data;



}


unsigned char uart_rx()
{

    while (!(UCA0IFG&UCRXIFG));
return UCA0RXBUF ;
}




void reverse(unsigned int data)
{
  unsigned int temp_data=0;
  uart_data=0;
  while(data)
  {
      temp_data=data%10;
      uart_data=uart_data*10+temp_data;
   data=data/10;

  }


}

void uart_data_send(unsigned int data)
{

reverse(data);
while(uart_data)
{
uart_tx((uart_data%10)+48);
uart_data=uart_data/10;

}
}


void uart_string(unsigned char *str)
{
    while(*str)
    {

        uart_tx(*str);
        str++;

    }



}
void uart_float_send(float data)
{
   unsigned int temp_data,count=DECIMAL_COUNT;
temp_data=data;
reverse(temp_data);
while(uart_data)
{
uart_tx((uart_data%10)+48);
uart_data=uart_data/10;

}
uart_tx('.');
data=data-(int)data;
while(data && count)
{
    uart_tx((int)(data*10)+48);
    data=data*10;
    data=data-(int)data;
    count--;
}

}



