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
#include "BernoulliGate.h"



int main(void)
{
  sei();
  initHW();
  Adc::StartConversion(AdcChannelSwitch);

  while(1)
  {
    static uint8_t step = 4;

    if (Adc::ready())
    {
      step = SwitchSteps::getValue();

      //index = Adc::Read(1) >> 2;
      Adc::StartConversion(AdcChannelSwitch);
      SeqSwitch.setStepCount(step+1);
    }

    if(ResetIn::isTriggered())
    {
      //BernoulliGate.onReset();
      SeqSwitch.onReset();
    }

    if(step == 0)
    {
       //BernoulliGate(Trigger::value());
    }
    else
    {
      if(Trigger::isTriggered())
      {
        SeqSwitch.activateNextStep();
        Debug::Toggle();
      }
    }





    //_delay_ms(250);
  }
}
