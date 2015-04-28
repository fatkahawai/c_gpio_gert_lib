//=============================================================================
//
//
// Decoder: using the GPIO digital I/O ports, buttons and LEDs of Gertboard
//
// gpio_input.c
//

#include "gb_common.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>

//
// Set GPIO pins to the right mode
// Decoder GPIO mapping:
//         Function            Mode
// GPIO0=  LED (D12)           Output
// GPIO1=  LED (D11)           Output
// GPIO4=  LED (D10)           Output
// GPIO7=  LED (D9)            Output
// GPIO8=  LED (D8)            Output
// GPIO9=  LED (D7)            Output
// GPIO10= LED (D6)            Output
// GPIO11= LED (D5)            Output
// GPIO14= unused
// GPIO15= unused
// GPIO17= unused
// GPIO18= unused
// GPIO21= unused
// GPIO22= unused
// GPIO23= Pushbutton (B3)     Input
// GPIO24= Pushbutton (B2)     Input
// GPIO25= Pushbutton (B1)     Input
//
// Always call INP_GPIO(x) first
// as that is how the macros work

// ---------------------------------------------------------------------------
// enable pull-up on GPIO 23,24&25, set pull to 2 (code for pull high)
//
void pull_pin(int gpioPort) 
{
  if ((gpioPort >=0 ) && (gpioPort <=25))
  {
    GPIO_PULL = 2;
    short_wait();
    // setting bits 23, 24 & 25  means that the GPIO_PULL is applied to
    // GPIO 23, 24, & 25 // 0x03800000;
    GPIO_PULLCLK0 = 0x1 << gpioPort; 
    short_wait();
    GPIO_PULL = 0;
    GPIO_PULLCLK0 = 0;
  }
} // pull_pins

// ---------------------------------------------------------------------------
// remove pulling on pins so they can be used for somnething else next time
// gertboard is used
void unpull_pin(int gpioPort)
{
  if ((gpioPort >=0 ) && (gpioPort <=25))
  {
    // disable pull-up on GPIO 23,24&25, set pull to 0 (code for no pull)
    GPIO_PULL = 0;
    short_wait();
    // setting bits 23, 24 & 25 below means that the GPIO_PULL is applied to
    // GPIO 23, 24, & 25
    GPIO_PULLCLK0 = 0x1 << gpioPort; 
    short_wait();
    GPIO_PULL = 0;
    GPIO_PULLCLK0 = 0;
 }
} // unpull_pin

// ---------------------------------------------------------------------------
// setup the chosen GPIO port for input
//
void setup_gpio_input(int gpioPort)
{
  // Map the I/O sections
  setup_io();

  if ((gpioPort >=0 ) && (gpioPort <=25))
  {
    // GPIO ports 23-25 can be configured as inputs outputs or handling the pushbuttons
    INP_GPIO(gpioPort);
  }
} // setup_gpio_input


// ---------------------------------------------------------------------------
// reset_gpio_input
// 
int reset_gpio(void)
{
   // unmap gpio
    restore_io();
}

// ---------------------------------------------------------------------------
// read input signal
// 
int read_gpio_input(int gpioPort)
{ 
  int value;

#ifdef _DEBUG
  printf ("Make sure you have connected jumpers and straps.\n");
  printf (" e.g. to use GPIO25 to read an input signal on BUF1:\n");
  printf ("GP25 in J2 --- B1 in J3\n");
  printf ("jumper on U4-in-B1\n");
  printf ("When ready hit enter.\n");
  (void) getchar();
#endif  

  // Set GPIO pins 23, 24, and 25 to the required mode
  setup_gpio_input(gpioPort);
   
  value = GPIO_IN0;
#ifdef _DEBUG
  printf ("GPIO port %d. GPIO_IN0 macro returned %d\n", gpioPort, value);
#endif
  
  value = (value >> gpioPort ) & 0x01; // keep only the relevant bit

#ifdef _DEBUG
  printf ("GPIO port %d input is %d\n", gpioPort, value);
#endif

  return(value);
} // read_gpio_input

