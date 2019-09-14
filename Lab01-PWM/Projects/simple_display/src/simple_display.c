#include <stdbool.h>
#include <stdint.h>
#include "inc/tm4c1294ncpdt.h" // CMSIS-Core
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h" // driverlib
#include "driverlib/gpio.h"
#include "driverlib/systick.h"
#include "grlib/grlib.h"
//#include "system_tm4c1294ncpdt.h" // CMSIS-Core
#include "cfaf128x128x16.h"
#include "utils/uartstdio.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "driverlib/timer.h"
#include "inc/hw_timer.h"

#define MULT_TIMER 1; // Ajuste do Timer para teste

uint32_t MAXIMO = 0x0000fff0;


uint8_t LED_D1 = 0;
uint8_t i = 0;
uint8_t Period = 0;
uint32_t TIME = 0;
uint32_t larg_pulso = 0;

uint32_t vet_larg_pulso[9]; //Lembrar como declara o vetor aqui
uint32_t vet_periodo[9];

uint32_t evento = 0;
uint8_t HZ = 0x00000;

//inicia timer
void InicializaTimerModeContador(void){
    SYSCTL_RCGCTIMER_R = 0x01;
    while((SYSCTL_PRTIMER_R & (SYSCTL_RCGCTIMER_R)) != (SYSCTL_RCGCTIMER_R)){};
    TIMER0_CTL_R = 0x00;        
    TIMER0_CFG_R = 0x04;
    TIMER0_TAMR_R = 0x03;
    TIMER0_TBMR_R = 0x03;
    TIMER0_TAILR_R = MAXIMO; 
    TIMER0_ICR_R = 0x01;
    TIMER0_IMR_R = 0x01;
    NVIC_PRI4_R = 0xE0E0E0;
    NVIC_EN0_R = 0x80000;
    TIMER0_CTL_R = 0x01;  
    
}


// -------------Configuração da comunicação UART--------------------
void ConfigureUART(void) // Função retirada do exemplo hello.c
{
   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
   SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
   GPIOPinConfigure(GPIO_PA0_U0RX);
   GPIOPinConfigure(GPIO_PA1_U0TX);
   GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
   UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
   UARTStdioConfig(0, 115200, 16000000);
}
//--------------------------------------------------------------------


// --------------------Configuração do pino F-------------------------
void InicializacaoPortF(void)
{
   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
   while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
   GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4); // LEDs D3 e D4 como saída
   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, 0); // LEDs D3 e D4 apagados
   GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);  
}
//--------------------------------------------------------------------

// --------------------Configuração do pino L-------------------------
void InicializacaoPortL(void)
{
   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
   while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL));
    
   GPIOPinConfigure(GPIO_PL4_T0CCP0); // habilita o PL4 como CCP
   GPIOPinTypeTimer(GPIO_PORTL_BASE, GPIO_PIN_4); 
   
}
//--------------------------------------------------------------------

// --------------------Configuração do pino N-------------------------
void InicializacaoPortN(void)
{
   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
   while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));
   GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0|GPIO_PIN_1); // LEDs D3 e D4 como saída
   GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_4, 0); // LEDs D3 e D4 apagados
   GPIOPadConfigSet(GPIO_PORTN_BASE, GPIO_PIN_0 |GPIO_PIN_1, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);  
}
//--------------------------------------------------------------------

// --------------------Configuração do pino J-------------------------
void InicializacaoPortJ(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ); // Habilita GPIO J (push-button SW1 = PJ0, push-button SW2 = PJ1)
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)); // Aguarda final da habilitação
  GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1); // push-buttons SW1 e SW2 como entrada
  GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); 
}
//--------------------------------------------------------------------

//uint8_t ContadorDePulsos()

  

void demo(void){
    
  
  GPIOPinRead(GPIO_PORTL_BASE, GPIO_PIN_4); // 
  //evento = MAXIMO - TIMER0_TAV_R;
  while(i<10){
    evento = MAXIMO - TIMER0_TAV_R;
    if ((evento = 1)){      
        
      if(evento2 = 1){
      larg_pulso = MAXIMO - TIMER0_TAV_R;
      evento2 = 0;
      }
    Periodo =  MAXIMO - TIMER0_TAV_R;
    evento = 0;  
    i = i+1;
    vet_larg_pulso[i] = larg_pulso;
    TIMER0_TAV_R = MAXIMO;       
  }
  
  }
    
    
} // 

void main(void){
  SystemInit(); // SystemCoreClock = 24Mhz (system_tm4c1294ncpdt.c)
 
  //SysTickEnable();
  InicializaTimerModeContador();
  ConfigureUART();
  InicializacaoPortF();
  InicializacaoPortJ();
  InicializacaoPortN();
  InicializacaoPortL();
  demo();
  SysTickIntEnable();
  SysTickPeriodSet(12000000);
   
  
  while(1){
    
    if(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0) == GPIO_PIN_0){ // 
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0); //
      
    }
    else
    {
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4); 
      SysTickPeriodSet(12000000);
      UARTprintf("%d hz\n", TIME);
     // printf("%d hz\r\n", TIME);
      
    } 

    if(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1) == GPIO_PIN_1) 
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0); 
     
    else{
      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0); // 
      SysTickPeriodSet(12000);
      UARTprintf("%d khz\n", TIME);
      //printf("%d khz\r\n", TIME/1000);  
    }
    
    
  } // while
} // main