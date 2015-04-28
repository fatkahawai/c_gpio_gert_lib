//=============================================================================
//
//
// Decoder: using the GPIO digital I/O ports, buttons and LEDs of Gertboard
//
// gpio_input.h
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

void pull_pin(int);
void unpull_pin(int);
void setup_gpio_input(int);
int reset_gpio(void);
int read_gpio_input(int);
