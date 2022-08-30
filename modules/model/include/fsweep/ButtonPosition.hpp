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

#ifndef FSWEEP_BUTTON_POSITION_H
#define FSWEEP_BUTTON_POSITION_H

#include <cmath>
#include <cstddef>

namespace fsweep
{
  struct ButtonPosition
  {
    int x, y;

    constexpr ButtonPosition() noexcept : x(-1), y(-1) {}

    constexpr ButtonPosition(const int x, const int y) noexcept : x(x), y(y) {}

    constexpr bool HasLeft() const noexcept { return this->x > 0; }

    constexpr bool HasRight(const int buttons_wide) const noexcept
    {
      return this->x < buttons_wide - 1;
    }

    constexpr bool HasUp() const noexcept { return this->y > 0; }

    constexpr bool HasDown(const int buttons_tall) const noexcept
    {
      return this->y < buttons_tall - 1;
    }

    constexpr bool HasLeftUp() const noexcept { return this->x > 0 && this->y > 0; }

    constexpr bool HasLeftDown(const int buttons_tall) const noexcept
    {
      return this->x > 0 && this->y < buttons_tall - 1;
    }

    constexpr bool HasRightUp(const int buttons_wide) const noexcept
    {
      return this->x < buttons_wide - 1 && this->y > 0;
    }

    constexpr bool HasRightDown(const int buttons_wide, const int buttons_tall) const noexcept
    {
      return this->x < buttons_wide - 1 && this->y < buttons_tall - 1;
    }

    constexpr fsweep::ButtonPosition GetLeft() const noexcept
    {
      return fsweep::ButtonPosition(this->x - 1, this->y);
    }

    constexpr fsweep::ButtonPosition GetRight() const noexcept
    {
      return fsweep::ButtonPosition(this->x + 1, this->y);
    }

    constexpr fsweep::ButtonPosition GetUp() const noexcept
    {
      return fsweep::ButtonPosition(this->x, this->y - 1);
    }

    constexpr fsweep::ButtonPosition GetDown() const noexcept
    {
      return fsweep::ButtonPosition(this->x, this->y + 1);
    }

    constexpr fsweep::ButtonPosition GetLeftUp() const noexcept
    {
      return fsweep::ButtonPosition(this->x - 1, this->y - 1);
    }

    constexpr fsweep::ButtonPosition GetLeftDown() const noexcept
    {
      return fsweep::ButtonPosition(this->x - 1, this->y + 1);
    }

    constexpr fsweep::ButtonPosition GetRightUp() const noexcept
    {
      return fsweep::ButtonPosition(this->x + 1, this->y - 1);
    }

    constexpr fsweep::ButtonPosition GetRightDown() const noexcept
    {
      return fsweep::ButtonPosition(this->x + 1, this->y + 1);
    }

    constexpr std::size_t GetIndex(const int buttons_wide) const noexcept
    {
      return static_cast<std::size_t>((buttons_wide * this->y) + this->x);
    }

    constexpr bool operator==(const ButtonPosition& other) const noexcept
    {
      return (this->x == other.x) && (this->y == other.y);
    }

    constexpr bool operator!=(const ButtonPosition& other) const noexcept
    {
      return (this->x != other.x) || (this->y != other.y);
    }

    bool IsNear(const fsweep::ButtonPosition& other) const noexcept
    {
      return (std::abs(this->x - other.x) <= 1) && (std::abs(this->y - other.y) <= 1);
    }
  };
}  // namespace fsweep

#endif
