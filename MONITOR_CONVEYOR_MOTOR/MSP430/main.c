
//----------------------------------------------------------------------------//
//--------------   MONITORING AND AIR CONDITIONING SYSTEMS  ------------------//
//-------------   FOR INDUSTRIAL MOTORS IN PRODUCTION LINES  -----------------//
//----------------------------------------------------------------------------//


// include library
#include "io430g2553.h"
#include "uart.h"
#include "stdio.h"
#include "string.h"
//#include "lcd.h"

#define variableresistor 0
#define temperature 5
#define amperage 7
#define VZERO 1.25                                                              // gia tri dien ap toi dong khong cua cam bien ACS712
#define MVPERA 100                                                              // he so quy ðoi giua dong dien va ðien ap dau ra cua cam bien ACS712, don vi mV/A
#define BAUDRATE 9600                                                           // Toc do truyen
#define BRCLK_FREQ 1000000                                                      // Tan so cua bo dem

unsigned int ReadADC10(int chanel);
unsigned int ReadADC10_ACS712(int channel);
unsigned int value_variableresistor, value_temperature, value_amperage;
unsigned int timer = 0, counter = 0, speed, encoder;
long map(long x, long in_min, long in_max, long out_min, long out_max);
float temp, amper, current, voutReal;
void control_fan();
void control_buzzer();
volatile unsigned int currentTemp = 40;
volatile unsigned int newTemp = 40;
volatile unsigned char buttonPressed = 0;

void uart_write_char(unsigned char data);
//----------------------   Subroutine declaration   --------------------------//
void init_uart()
{
  P1SEL |= BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
  P1SEL2 |= BIT1 + BIT2;
  UCA0CTL0 =0x00;
  UCA0CTL1 |= UCSSEL_2;
  UCA0BR0 = 104;
  UCA0BR1 = 0;
  UCA0CTL1 &= ~UCSWRST;
}

void init_encoder(){
    //set P1.3 INPUT Pulse
  P1REN  |=  BIT3;                                                              // dien tro keo len
  P1IE   |=  BIT3;                                                              //interrupt enable
  P1IES  &= ~BIT3;                                                              // interrupt low-high
  P1IFG  &= ~BIT3;                                                              // set interrupt flag to 0 in the beginning
  __bis_SR_register(GIE);                                                       // cho phep ngat   
}

void init_pwm(){
  // cau hinh PWM
  P1DIR  |=  BIT6;                                                              // cau hinh pwm
  P1SEL  |=  BIT6;                                                              // ngo ra pwm P1.6
  TACCTL1 =  OUTMOD_7;
  TACCR0  =  1050;
  TACTL   =  TASSEL_2 + MC_1;                                                   //SMCLK    
}

void init_button(){
  P2DIR  &= ~(BIT4 | BIT5 | BIT3);                                               // Cai ðt các chân P2.4, P2.5 và P2.3 là ð?u vào
  P2REN  |=  (BIT4 | BIT5 | BIT3);                                               // B?t ði?n tr? kéo lên cho các chân P2.4, P2.5 và P2.3
  P2OUT  |=  (BIT4 | BIT5 | BIT3);                                               // Cài ð?t ði?n tr? kéo lên là active-high
  P2IE   |=  (BIT4 | BIT5 | BIT3);                                               // Cho phép ng?t trên các chân P2.4, P2.5 và P2.3
  P2IES  |=  (BIT4 | BIT5 | BIT3);                                               // Cài ð?t ng?t theo c?nh xu?ng (falling edge)
  P2IFG  &= ~(BIT4 | BIT5 | BIT3);                                               // Xóa c? ng?t trên các chân P2.4, P2.5 và P2.3

  __bis_SR_register(GIE);
  //__enable_interrupt();                                                       // Cho phép ng?t toàn c?c
}
void init_control(){
  P2DIR |= BIT0 + BIT1;
  P2OUT &=~ (BIT0 + BIT1);
}

//funtion read ADC
unsigned int ReadADC10(int chanel){

  ADC10CTL0 &=~ ENC;
  ADC10CTL0 = SREF_1 + ADC10SHT_2 + ADC10ON + REF2_5V + REFON;
  ADC10AE0 |= (BIT0<<chanel);
  ADC10CTL1 |= (chanel*0x1000u);
  //__delay_cycles(1000);
  ADC10CTL0 |= ENC + ADC10SC;
  while(!(ADC10CTL0 & ADC10IFG));
  ADC10CTL0 = 0;// ADC10CTL0 &=~ ADC10ON;
  return ADC10MEM;

}

/*unsigned int ReadADC10(int channel){
  ADC10CTL0 &=~ ENC;
  ADC10CTL0 = SREF_1 + ADC10SHT_2 + ADC10ON + REFON; // tham chi?u ngoài 1.5V, t?c ð? l?y m?u 16 chu k?
  ADC10CTL1 |= (channel << 12); // ch?n kênh ð?c ADC
  ADC10AE0 |= (1 << channel); // cho phép ð?c t? chân kênh
  __delay_cycles(1000); // ch? cho ADC ?n ð?nh
  ADC10CTL0 |= ENC + ADC10SC; // b?t ð?u chuy?n ð?i ADC
  while(!(ADC10CTL0 & ADC10IFG)); // ch? chuy?n ð?i hoàn thành
  ADC10CTL0 &=~ ENC; // t?t chuy?n ð?i ADC
  ADC10AE0 &=~ (1 << channel); // ng?t cho phép ð?c t? chân kênh
  return ADC10MEM;
}*/

//funtion map value temperature
long map(long x, long in_min, long in_max, long out_min, long out_max){
  return(x - in_min)*(out_max - out_min)/(in_max - in_min) + out_min;
}

//funtion read variable resistor
void read_variableresistor(){
  value_variableresistor = ReadADC10(variableresistor);                         // doc ADC P1.0
  float as=value_variableresistor;//TACCR1 = value_variableresistor/2;                                          // cho gia tri ADC = TACCR1 
  TACCR1 = as;
}

// funtion read temperature
void read_temperature(){
  value_temperature = ReadADC10(temperature);                                   // doc nhiet do tho
  temp = map(value_temperature, 140, 1680, 5, 100);                             // doc nhiet do da bien doi
  
}

void read_amperage(){
  value_amperage = ReadADC10(amperage);
  amper = value_amperage +100;
  voutReal = 2.5 * ((float)amperage / 1023.0) + VZERO;
  current = (voutReal - VZERO) / (MVPERA * 1000.0);
}

void uart_putc( char ch){
  while((IFG2&UCA0TXIFG)==0);
  UCA0TXBUF = ch;	
}
void uart_write_char(unsigned char data)
{
	while (!(IFG2&UCA0TXIFG)); // Doi gui xong ky tu truoc
	UCA0TXBUF= data; // Moi cho phep gui ky tu tiep theo
}
void uart_send_str(char *str){
  while (*str != '\0') {
    uart_putc(*str);
    str++;
  }
  //uart_write_char(0);                                                           // G?i k? t? null vào cu?i chu?i
}

//funtion control fan
void control_fan(){
    if(value_variableresistor >= 1000){
    P2OUT = BIT0;
  }
  else{
    P2OUT &=~ BIT0;
    P2OUT = BIT1;
  }
}
//funtion control buzzer
void control_buzzer(){
  if(temp >= currentTemp){
    P2OUT = BIT1;
  }
  else{
    P2OUT &=~ BIT1;
  }
}

void button(){
 if(buttonPressed == 1){                                                        // Neu phim 1 duoc bam, tang nhiet do
      newTemp = currentTemp + 1;
      P2OUT = BIT1;
      buttonPressed = 0;
    } 
    else if(buttonPressed == 2){                                                 // Neu phim 2 duoc bam, tang nhiet do
      newTemp = currentTemp - 1;
      P2OUT = BIT0;
      buttonPressed = 0;
    }
    else if(buttonPressed == 3){                                                // Neu phim 3 duoc bam, tang nhiet do                                              
      currentTemp = newTemp;
      P2OUT &=~ BIT0;
      P2OUT &=~ BIT1;
      buttonPressed = 0;
    }
}
//----------------------------------------------------------------------------//


//----------------------   Declare the main program   ------------------------//

void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL  = WDTPW + WDTHOLD;
  init_uart();
  init_encoder();
  init_pwm();
  init_button();
  init_control();
  uart_send_str("Hello word\n");
  while(1){
    read_variableresistor();
    //read_temperature();
    //button();
    
    
   
    //char str[30];
    //sprintf(str,"A%da", value_variableresistor);  // Chuy?n ð?i giá tr? float thành chu?i k? t?
    //uart_send_str(str);  // G?i chu?i qua UART
    //__delay_cycles(1600000);
  }
}

//----------------------      interrupt program       ------------------------//

#pragma vector = PORT1_VECTOR
__interrupt void PORT1 (void){
  counter++;                                                                    // tang counter len 1 don vi
  P1IFG &= ~BIT3;                                                               // xoa co ngat
}

// encoder interrupt
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer0(void){
  timer++;                                                                      // tang bien timer len 1 don vi
  if(timer == 110){
    speed = counter;
    counter = 0;
    timer = 0;
  }
}

// button interrupt
#pragma vector=PORT2_VECTOR
__interrupt void Port2_ISR(void){
    switch(P2IFG & (BIT4 | BIT5 | BIT3)){
     case BIT4:
       buttonPressed = 1;                                                       // Ghi nhan phim 1 duoc bam
       break;
     case BIT5:
       buttonPressed = 2;                                                       // Ghi nhan phim 2 duoc bam
       break;
     case BIT3:
       buttonPressed = 3;                                                       // Ghi nhan phim 3 duoc bam
       break;
    }
  P2IFG &= ~(BIT4 | BIT5 | BIT3);                                               // Xoa co ngat tren cac chan P2.4, P2.5 và P2.3
}