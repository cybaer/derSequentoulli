/*
 * derSequentoulli.cpp
 *
 *  Created on: 03.03.2018
 *      Author: cybaer
 */


#include "avrlib/time.h"
#include "avrlib/gpio.h"
#include "avrlib/adc.h"
#include "HardwareConfig.h"
#include "BernoulliGate.h"

BernoulliGate<Output_1, Output_2> bernoulliGate;

int main(void)
{
  sei();
  initHW();
  Adc::StartConversion(AdcChannelSwitch);
  bernoulliGate.setThreshold(64);

  while(1)
  {
    static uint8_t step = 3;

    if (Adc::ready())
    {
      step = SwitchSteps::getValue();

      //index = Adc::Read(1) >> 2;
      Adc::StartConversion(AdcChannelSwitch);
      SeqSwitch.setStepCount(step);
    }

    if(ResetIn::isTriggered())
    {
      //BernoulliGate.onReset();
      SeqSwitch.onReset();
    }

    if(step == 0)
    {
      if(Trigger::isTriggered())
      {
        bernoulliGate.activateNextStep();
      }
      Debug::set_value(Trigger::getValue());
      OutputReturn::set_value(Trigger::getValue());
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
