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

#ifndef FSWEEP_SPRITE_HPP
#define FSWEEP_SPRITE_HPP

#include <fsweep/LcdDigit.hpp>

namespace fsweep
{
  enum class Sprite
  {
    ButtonNone = 0,
    ButtonDown,
    ButtonFlag,
    ButtonQuestion,
    ButtonQuestionDown,
    ButtonFlagMiss,
    ButtonBombExplode,
    ButtonBomb,
    ButtonFlagHit,
    ButtonDownOne,
    ButtonDownTwo,
    ButtonDownThree,
    ButtonDownFour,
    ButtonDownFive,
    ButtonDownSix,
    ButtonDownSeven,
    ButtonDownEight,
    ButtonSmile,
    ButtonSmileDown,
    ButtonShocked,
    ButtonDead,
    ButtonCool,
    LcdOne,
    LcdTwo,
    LcdThree,
    LcdFour,
    LcdFive,
    LcdSix,
    LcdSeven,
    LcdEight,
    LcdNine,
    LcdZero,
    LcdHythen,
    LcdNone,
    BorderLeftTop,
    BorderTop,
    BorderLeft,
    BorderRight,
    BorderRightTop,
    BorderRightBottom,
    BorderLeftBottom,
    BorderBottom,
    BorderRightIntersection,
    BorderLeftIntersection,
    Count
  };

  fsweep::Sprite getSpriteFromDigit(fsweep::LcdDigit digit) noexcept;
  fsweep::Sprite getDownButtonSprite(int surrounding_bombs) noexcept;
}  // namespace fsweep

#endif
