// SPDX-FileCopyrightText: 2022 Daniel Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

/*
 * Copyright (c) 2022 Daniel Valcour
 *
 * This file is part of FossSweeper.
 *
 * FossSweeper is free software: you can redistribute it and/or modify it under the terms of the GNU
 * General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * FossSweeper is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with FossSweeper. If not,
 * see <https://www.gnu.org/licenses/>.
 *
 */

#include <cstddef>
#include <fsweep/LcdNumber.hpp>
#include <stdexcept>

fsweep::LcdNumber::LcdNumber(const int number) : number(number)
{
  if (number >= 999)
  {
    this->digits[0] = fsweep::LcdDigit::Nine;
    this->digits[1] = fsweep::LcdDigit::Nine;
    this->digits[2] = fsweep::LcdDigit::Nine;
  }
  else if (number <= -99)
  {
    this->digits[0] = fsweep::LcdDigit::Minus;
    this->digits[1] = fsweep::LcdDigit::Nine;
    this->digits[2] = fsweep::LcdDigit::Nine;
  }
  else if (number < -9)
  {
    this->digits[0] = fsweep::LcdDigit::Minus;
    const int tens = (number / -10);
    this->digits[1] = static_cast<fsweep::LcdDigit>(tens);
    const int ones = -(number % 10);
    this->digits[2] = static_cast<fsweep::LcdDigit>(ones);
  }
  else if (number < 0)
  {
    this->digits[0] = fsweep::LcdDigit::None;
    this->digits[1] = fsweep::LcdDigit::Minus;
    const int ones = -number;
    this->digits[2] = static_cast<fsweep::LcdDigit>(ones);
  }
  else if (number < 10)
  {
    this->digits[0] = fsweep::LcdDigit::None;
    this->digits[1] = fsweep::LcdDigit::None;
    const int ones = number;
    this->digits[2] = static_cast<fsweep::LcdDigit>(number);
  }
  else if (number < 100)
  {
    this->digits[0] = fsweep::LcdDigit::None;
    const int tens = number / 10;
    this->digits[1] = static_cast<fsweep::LcdDigit>(tens);
    const int ones = number - (tens * 10);
    this->digits[2] = static_cast<fsweep::LcdDigit>(ones);
  }
  else  // if (number < 999)
  {
    const int hundreds = number / 100;
    this->digits[0] = static_cast<fsweep::LcdDigit>(hundreds);
    const int tens = (number % 100) / 10;
    this->digits[1] = static_cast<fsweep::LcdDigit>(tens);
    const int ones = (number % 10);
    this->digits[2] = static_cast<fsweep::LcdDigit>(ones);
  }
}

fsweep::LcdDigit fsweep::LcdNumber::operator[](std::size_t digit_i) const
{
  if (digit_i > 3)
  {
    throw std::out_of_range("number index out of range");
  }
  return this->digits[digit_i];
}

int fsweep::LcdNumber::GetNumber() const noexcept { return this->number; }