/*
 * BernoulliGate.h
 *
 *  Created on: 06.03.2018
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

#ifndef BERNOULLIGATE_H_
#define BERNOULLIGATE_H_

#include "avrlib/random.h"

template<typename Out_1, typename Out_2>
class BernoulliGate
{
public:
  int8_t operator() (bool in)
  {
    int8_t ret = 0;
    if(in && !m_Old)
    {
      ret = 1;
      activateNextStep();
    }
    m_Old = in;
    return ret;
  }

  void activateNextStep(void)
  {
    uint8_t rnd = avrlib::Random::GetByte() & 0x7F;
    if(rnd < m_Threshold)
    {
      Out_1::Low();
      Out_2::High();
    }
    else
    {
      Out_1::High();
      Out_2::Low();
    }
  }
  void onReset();
  void setThreshold(uint8_t threshold) { m_Threshold = threshold; }
private:
  uint8_t m_Threshold;
  bool m_Old;

};






#endif /* BERNOULLIGATE_H_ */
