/*
 * derSequentoulli.cpp
 *
 *  Created on: 03.03.2018
 *      Author: cybaer
 */


//#include <avr/interrupt.h>      // Header-Datei f. Interruptfunktion
#include "avrlib/time.h"
#include "avrlib/gpio.h"
#include "avrlib/adc.h"
#include "avrlib/devices/analogSwitch.h"


/*
extern "C" int __cxa_guard_acquire(__guard *);
extern "C" void __cxa_guard_release (__guard *);
extern "C" void __cxa_guard_abort (__guard *);
extern "C" void __cxa_pure_virtual();


// __Compiler Bug__
int __cxa_guard_acquire(__guard *g) {return !*(char *)(g);};
void __cxa_guard_release (__guard *g) {*(char *)g = 1;};
void __cxa_guard_abort (__guard *) {};
void __cxa_pure_virtual() {};
*/
using namespace avrlib;

volatile bool poll = false;

typedef Gpio<PortC, 0> Test;
typedef Gpio<PortD, 5> P0;
typedef Gpio<PortD, 6> P1;
typedef Gpio<PortD, 7> P2;
typedef Gpio<PortB, 0> P3;

typedef AnalogSwitch<Adc, 1, 19, 1> Switch;

int main(void)
{
  sei();
  //test
 

  Adc::Init();
  //Adc::set_reference(ADC_DEFAULT);
  //Adc::set_alignment(ADC_LEFT_ALIGNED);
  Adc::StartConversion(1);



  Switch::init();


  Test::set_mode(DIGITAL_OUTPUT);
  P0::set_mode(DIGITAL_OUTPUT);
  P1::set_mode(DIGITAL_OUTPUT);
  P2::set_mode(DIGITAL_OUTPUT);
  P3::set_mode(DIGITAL_OUTPUT);

  P0::Low();
  P1::Low();
  P2::Low();
  P3::Low();
  Test::set_value(true);
  
  while(1)
  {
    Test::Toggle();

    static uint8_t index = 0;
    if (Adc::ready())
    {
      index = Switch::getNewIndex(index);
      //index = Adc::Read(1) >> 2;
      P0::set_value(index & 0x1);
      P1::set_value(index>>1 & 0x1);
      P2::set_value(index>>2 & 0x1);
      P3::set_value(index>>3 & 0x1);
      Adc::StartConversion(1);
    }

    _delay_ms(50);
  }
}
