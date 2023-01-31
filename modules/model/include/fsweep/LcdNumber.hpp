// SPDX-FileCopyrightText: 2022-2023 Daniel Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

/*
 * Copyright (c) 2022-2023 Daniel Valcour
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

#ifndef FSWEEP_LCDNUMBER_HPP
#define FSWEEP_LCDNUMBER_HPP

#include <cstddef>
#include <fsweep/LcdDigit.hpp>

namespace fsweep
{
  class LcdNumber
  {
   public:
   private:
    int number = 0;
    fsweep::LcdDigit digits[3] = {
        fsweep::LcdDigit::None,
        fsweep::LcdDigit::None,
        fsweep::LcdDigit::None,
    };

   public:
    constexpr LcdNumber() noexcept = default;
    LcdNumber(const int number);

    fsweep::LcdDigit operator[](std::size_t digit_i) const;
    int GetNumber() const noexcept;
  };
}  // namespace fsweep

#endif
