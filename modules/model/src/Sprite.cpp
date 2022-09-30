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

 #include <fsweep/Sprite.hpp>
 #include <fsweep/LcdDigit.hpp>

fsweep::Sprite fsweep::getSpriteFromDigit(fsweep::LcdDigit digit) noexcept
{
  switch (digit)
  {
  case fsweep::LcdDigit::One:
    return fsweep::Sprite::LcdOne;
  case fsweep::LcdDigit::Two:
    return fsweep::Sprite::LcdTwo;
  case fsweep::LcdDigit::Three:
    return fsweep::Sprite::LcdThree;
  case fsweep::LcdDigit::Four:
    return fsweep::Sprite::LcdFour;
  case fsweep::LcdDigit::Five:
    return fsweep::Sprite::LcdFive;
  case fsweep::LcdDigit::Six:
    return fsweep::Sprite::LcdSix;
  case fsweep::LcdDigit::Seven:
    return fsweep::Sprite::LcdSeven;
  case fsweep::LcdDigit::Eight:
    return fsweep::Sprite::LcdEight;
  case fsweep::LcdDigit::Nine:
    return fsweep::Sprite::LcdNine;
  case fsweep::LcdDigit::Zero:
    return fsweep::Sprite::LcdZero;
  case fsweep::LcdDigit::Minus:
    return fsweep::Sprite::LcdHythen;
  default:
    return fsweep::Sprite::LcdNone;
  }
}

fsweep::Sprite fsweep::getDownButtonSprite(int surrounding_bombs) noexcept
{
  switch (surrounding_bombs)
  {
  case 1:
    return fsweep::Sprite::ButtonDownOne;
  case 2:
    return fsweep::Sprite::ButtonDownTwo;
  case 3:
    return fsweep::Sprite::ButtonDownThree;
  case 4:
    return fsweep::Sprite::ButtonDownFour;
  case 5:
    return fsweep::Sprite::ButtonDownFive;
  case 6:
    return fsweep::Sprite::ButtonDownSix;
  case 7:
    return fsweep::Sprite::ButtonDownSeven;
  case 8:
    return fsweep::Sprite::ButtonDownEight;
  default:
    return fsweep::Sprite::ButtonDown;
  }
}