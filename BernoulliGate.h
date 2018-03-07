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


class BernoulliGate
{
public:
  void operator() (bool in)
  {
    uint8_t rnd = avrlib::Random::GetByte();
    if(rnd > m_threshold)
  }
  void onReset();
private:
  uint8_t m_threshold;

};






#endif /* BERNOULLIGATE_H_ */
