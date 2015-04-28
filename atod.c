//
// atod.c    library function to read from Gertboard ADC 
//
// SPI (ADC/DAC) control code
//
//
// Copyright (C) Pink Pelican NZ Ltd 2015
// No rights reserved
// You may treat this program as if it was in the public domain
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
//
// Try to strike a balance between keep code simple for
// novice programmers but still have reasonable quality code
//

#include "gb_common.h"
#include "gb_spi.h"
#include "atod.h"

// Set GPIO pins to the right mode
// DEMO GPIO mapping:
//         Function            Mode
// GPIO0=  unused
// GPIO1=  unused
// GPIO4=  unused
// GPIO7=  unused
// GPIO8=  SPI chip select A   Alt. 0
// GPIO9=  SPI MISO            Alt. 0
// GPIO10= SPI MOSI            Alt. 0
// GPIO11= SPI CLK             Alt. 0
// GPIO14= unused
// GPIO15= unused
// GPIO17= unused
// GPIO18= unused
// GPIO21= unused
// GPIO22= unused
// GPIO23= unused
// GPIO24= unused
// GPIO25= unused
//

// For A to D we only need the SPI bus and SPI chip select A
void setup_gpio()
{
   INP_GPIO(8);  SET_GPIO_ALT(8,0);
   INP_GPIO(9);  SET_GPIO_ALT(9,0);
   INP_GPIO(10); SET_GPIO_ALT(10,0);
   INP_GPIO(11); SET_GPIO_ALT(11,0);
} // setup_gpio


//
//  Read ADC input 0 and show as horizontal bar
//
int atod(int chan)
{ 
  int analogVal;

#ifdef _DEBUG
  printf("_DEBUG Mode: atod(%d)\n", chan);

  printf ("These are the connections for the analogue to digital test:\n");
  printf ("jumper connecting GP11 to SCLK\n");
  printf ("jumper connecting GP10 to MOSI\n");
  printf ("jumper connecting GP9 to MISO\n");
  printf ("jumper connecting GP8 to CSnA\n");
  printf ("Potentiometer connections:\n");
  printf ("  (call 1 and 3 the ends of the resistor and 2 the wiper)\n");
  printf ("  connect 3 to 3V3\n");
  printf ("  connect 2 to AD%d\n", chan);
  printf ("  connect 1 to GND\n");
  printf ("When ready hit enter.\n");
  (void) getchar();
#endif

  // Map the I/O sections
  setup_io();

  // activate SPI bus pins
  setup_gpio();

  // Setup SPI bus
  setup_spi();

  // The value returned by the A to D can jump around quite a bit, so 

  analogVal= read_adc(chan);
  // should be in range 0-1023
#ifdef _DEBUG
  printf("read_adc(%d) returned %d [on a scale of 0 to 1023]\n", chan, analogVal);
#endif

  restore_io();

  return(analogVal);
} // atod
