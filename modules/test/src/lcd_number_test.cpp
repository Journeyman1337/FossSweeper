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

#include <catch2/catch_all.hpp>
#include <fsweep/LcdNumber.hpp>

SCENARIO("An LcdNumber is created")
{
  GIVEN("An LcdNumber created with a value less than -99")
  {
    const fsweep::LcdNumber lcd_number(-100);

    THEN("The digits should be - 9 and 9")
    {
      CHECK(lcd_number[0] == fsweep::LcdDigit::Minus);
      CHECK(lcd_number[1] == fsweep::LcdDigit::Nine);
      CHECK(lcd_number[2] == fsweep::LcdDigit::Nine);
    }
  }

  GIVEN("An LcdNumber with -50")
  {
    const fsweep::LcdNumber lcd_number(-50);

    THEN("The digits should be - 5 and 0")
    {
      CHECK(lcd_number[0] == fsweep::LcdDigit::Minus);
      CHECK(lcd_number[1] == fsweep::LcdDigit::Five);
      CHECK(lcd_number[2] == fsweep::LcdDigit::Zero);
    }
  }

  GIVEN("An LcdNumber with -4")
  {
    const fsweep::LcdNumber lcd_number(-4);

    THEN("The digits should be None - and 4")
    {
      CHECK(lcd_number[0] == fsweep::LcdDigit::None);
      CHECK(lcd_number[1] == fsweep::LcdDigit::Minus);
      CHECK(lcd_number[2] == fsweep::LcdDigit::Four);
    }
  }

  GIVEN("An LcdNumber with 0")
  {
    const fsweep::LcdNumber lcd_number(0);

    THEN("The digits should be None None and 0")
    {
      CHECK(lcd_number[0] == fsweep::LcdDigit::None);
      CHECK(lcd_number[1] == fsweep::LcdDigit::None);
      CHECK(lcd_number[2] == fsweep::LcdDigit::Zero);
    }
  }

  GIVEN("An LcdNumber with 7")
  {
    const fsweep::LcdNumber lcd_number(7);

    THEN("The digits should be None None and 7")
    {
      CHECK(lcd_number[0] == fsweep::LcdDigit::None);
      CHECK(lcd_number[1] == fsweep::LcdDigit::None);
      CHECK(lcd_number[2] == fsweep::LcdDigit::Seven);
    }
  }

  GIVEN("An LcdNumber with 78")
  {
    const fsweep::LcdNumber lcd_number(78);

    THEN("The digits should be None 7 and 8")
    {
      CHECK(lcd_number[0] == fsweep::LcdDigit::None);
      CHECK(lcd_number[1] == fsweep::LcdDigit::Seven);
      CHECK(lcd_number[2] == fsweep::LcdDigit::Eight);
    }
  }

  GIVEN("An LcdNumber with 356")
  {
    const fsweep::LcdNumber lcd_number(356);

    THEN("The digits should be 3 5 and 6")
    {
      CHECK(lcd_number[0] == fsweep::LcdDigit::Three);
      CHECK(lcd_number[1] == fsweep::LcdDigit::Five);
      CHECK(lcd_number[2] == fsweep::LcdDigit::Six);
    }
  }

  GIVEN("An LcdNumber greater than 999")
  {
    const fsweep::LcdNumber lcd_number(1000);

    THEN("The digits should be 9 9 and 9")
    {
      CHECK(lcd_number[0] == fsweep::LcdDigit::Nine);
      CHECK(lcd_number[1] == fsweep::LcdDigit::Nine);
      CHECK(lcd_number[2] == fsweep::LcdDigit::Nine);
    }
  }
}