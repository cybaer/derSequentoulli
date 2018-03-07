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
#include "HardwareConfig.h"



int main(void)
{
  sei();
  initHW();

  while(1)
  {
    static uint8_t step = 0;
    if (Adc::ready())
    {
      step = SwitchSteps::getValue();

      //index = Adc::Read(1) >> 2;
      Adc::StartConversion(AdcChannelSwitch);
    }

    if(ResetIn::isTriggered())
    {
      //BernoulliGate.onReset();
      //SequentialSwitch.onReset();
    }

    if(step == 0)
    {
       //BernoulliGate(Trigger::value());
    }
    else
    {
      //SequentialSwitch(Trigger::value());
    }





    _delay_ms(50);
  }
}
