/*
 * HardwareConfig.h
 *
 *  Created on: 09.02.2017
 *      Author: cybaer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef HARDWARECONFIG_H_
#define HARDWARECONFIG_H_

#include "lib/ui/EdgeTrigger.h"
#include "lib/ui/analogSwitch.h"
#include "avrlib/base.h"
#include "avrlib/gpio.h"
#include "avrlib/adc.h"

using namespace avrlib;

template <typename Out_1, typename Out_2, typename Out_3, typename Out_4>
class SequentialSwitch
{
public:
  void activateNextStep(void)
  {
    if(++m_Step == m_StepCount)
      m_Step = 0;
    m_ActivatFunctions[m_Step]();
  }
  void setStepCount(uint8_t count) { m_StepCount = count > 4 ? 4 : count; }
  void reset(void)
  {
    m_Step = 0;
    activate_1()
  }

private:
  static void inactivateAll(void)
  {
    Out_1::Low();
    Out_2::Low();
    Out_3::Low();
    Out_4::Low();
  }
  static void activate_1(void) { inactivateAll(); Out_1::High(); }
  static void activate_2(void) { inactivateAll(); Out_2::High(); }
  static void activate_3(void) { inactivateAll(); Out_3::High(); }
  static void activate_4(void) { inactivateAll(); Out_4::High(); }

  typedef void (*FP)(void);

  const FP m_ActivatFunctions[4] = {activate_1, activate_2, activate_3, activate_4};
  uint8_t m_StepCount;
  uint8_t m_Step;
};

typedef Inverter<Gpio<PortD, 7> > Trigger;  // 13
typedef EdgeTrigger<Gpio<PortB, 2>, 0> ResetIn;  // 16

typedef Inverter<Gpio<PortD, 4> > Output_1;  // 6
typedef Inverter<Gpio<PortD, 2> > Output_2;  // 4
typedef Inverter<Gpio<PortD, 1> > Output_3;  // 3
typedef Inverter<Gpio<PortD, 0> > Output_4;  // 2

typedef SequentialSwitch<Output_1, Output_2, Output_3, Output_4> SeqSwitch;

typedef Inverter<Gpio<PortB, 6> > OutputReturn;  // 9
typedef Gpio<PortB, 7> Debug;                    // 10

static const uint8_t AdcChannelSwitch = 4;
typedef AnalogSwitch<Adc, 0, AdcChannelSwitch> SwitchSteps;

extern Adc adc;

inline void initInputs(void)
{
  ResetIn::init();
  Trigger::set_mode(DIGITAL_INPUT);
  Trigger::High();
}
inline void initOutputs(void)
{
  Output_1::set_mode(DIGITAL_OUTPUT);
  Output_1::set_value(true);
  Output_2::set_mode(DIGITAL_OUTPUT);
  Output_2::set_value(true);
  Output_3::set_mode(DIGITAL_OUTPUT);
  Output_3::set_value(true);
  Output_4::set_mode(DIGITAL_OUTPUT);
  Output_4::set_value(true);
  OutputReturn::set_mode(DIGITAL_OUTPUT);
  OutputReturn::set_value(false);
  Debug::set_mode(DIGITAL_OUTPUT);
  Debug::set_value(true);
}

inline void initAnalogIn(void)
{
  adc.Init();
}

inline void initHW(void)
{
  initInputs();
  initOutputs();
  initAnalogIn();
}


#endif /* HARDWARECONFIG_H_ */
