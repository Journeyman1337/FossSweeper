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
#include <fsweep/Button.hpp>

SCENARIO("A Button is constructed with its default constructor")
{
  GIVEN("A default constructed Button")
  {
    const fsweep::Button button;

    THEN("The ButtonState is None") { CHECK(button.GetButtonState() == fsweep::ButtonState::None); }

    THEN("The Button has no bomb") { CHECK(button.GetHasBomb() == false); }

    THEN("The Button has 0 surrounding bombs") { CHECK(button.GetSurroundingBombs() == 0); }
  }
}

SCENARIO("A Button is constructed with its char constructor")
{
  GIVEN("A Button constructed with 'd'")
  {
    const fsweep::Button button('d');

    THEN("The Button is down but has no bomb.")
    {
      CHECK(button.GetButtonState() == fsweep::ButtonState::Down);
      CHECK(button.GetHasBomb() == false);
    }
  }

  GIVEN("A Button constructed with 'b'")
  {
    const fsweep::Button button('b');

    THEN("The Button is up with a bomb")
    {
      CHECK(button.GetButtonState() == fsweep::ButtonState::None);
      CHECK(button.GetHasBomb() == true);
    }
  }

  GIVEN("A Button is constructed with 'x'")
  {
    const fsweep::Button button('x');

    THEN("The Button is down with a bomb")
    {
      CHECK(button.GetButtonState() == fsweep::ButtonState::Down);
      CHECK(button.GetHasBomb() == true);
    }
  }

  GIVEN("A Button is constructed with 'f'")
  {
    const fsweep::Button button('f');

    THEN("The Button has a flag and has no bomb")
    {
      CHECK(button.GetButtonState() == fsweep::ButtonState::Flagged);
      CHECK(button.GetHasBomb() == false);
    }
  }

  GIVEN("A Button is constructed with 'c'")
  {
    const fsweep::Button button('c');

    THEN("The Button has a flag and has a bomb")
    {
      CHECK(button.GetButtonState() == fsweep::ButtonState::Flagged);
      CHECK(button.GetHasBomb() == true);
    }
  }

  GIVEN("A Button is constructed with 'q'")
  {
    const fsweep::Button button('q');

    THEN("The Button is questioned and has no bomb")
    {
      CHECK(button.GetButtonState() == fsweep::ButtonState::Questioned);
      CHECK(button.GetHasBomb() == false);
    }
  }

  GIVEN("A Button is constructed with 'r'")
  {
    const fsweep::Button button('r');

    THEN("The Button is questioned and has a bomb")
    {
      CHECK(button.GetButtonState() == fsweep::ButtonState::Questioned);
      CHECK(button.GetHasBomb() == true);
    }
  }
}

SCENARIO("A Button is pressed")
{
  GIVEN("A Button")
  {
    fsweep::Button button;

    THEN("The ButtonState is None") { CHECK(button.GetButtonState() == fsweep::ButtonState::None); }

    WHEN("The Button is pressed")
    {
      button.Press();

      THEN("The ButtonState is Down")
      {
        CHECK(button.GetButtonState() == fsweep::ButtonState::Down);
      }
    }
  }
}

SCENARIO("A Button is alt pressed")
{
  GIVEN("A Button")
  {
    fsweep::Button button;

    WHEN("The Button is alt pressed without questions enabled")
    {
      button.AltPress(false);

      THEN("The ButtonState is Flagged")
      {
        CHECK(button.GetButtonState() == fsweep::ButtonState::Flagged);
      }

      WHEN("The Button is alt pressed without questions enabled")
      {
        button.AltPress(false);

        THEN("The ButtonState is None")
        {
          CHECK(button.GetButtonState() == fsweep::ButtonState::None);
        }
      }
    }

    WHEN("The Button is alt pressed with questions enabled")
    {
      button.AltPress(true);

      THEN("The ButtonState is Flagged")
      {
        CHECK(button.GetButtonState() == fsweep::ButtonState::Flagged);
      }

      WHEN("The Button is alt pressed with questions enabled")
      {
        button.AltPress(true);

        THEN("The ButtonState is Questioned")
        {
          CHECK(button.GetButtonState() == fsweep::ButtonState::Questioned);
        }

        WHEN("The Button is alt pressed with questions enabled")
        {
          button.AltPress(true);

          THEN("The ButtonState is None")
          {
            CHECK(button.GetButtonState() == fsweep::ButtonState::None);
          }
        }
      }
    }
  }
}

SCENARIO("The Questioned state of a Button is removed")
{
  GIVEN("A Button with ButtonState::Questioned")
  {
    fsweep::Button button;
    button.AltPress(true);
    button.AltPress(true);

    WHEN("The question is removed")
    {
      button.RemoveQuestion();

      THEN("The ButtonState is None")
      {
        CHECK(button.GetButtonState() == fsweep::ButtonState::None);
      }
    }
  }

  GIVEN("A Button with ButtonState::Flagged")
  {
    fsweep::Button button;
    button.AltPress(true);

    WHEN("The question is removed")
    {
      button.RemoveQuestion();

      THEN("The ButtonState is Flagged")
      {
        CHECK(button.GetButtonState() == fsweep::ButtonState::Flagged);
      }
    }
  }
}

SCENARIO("A Button is set having a bomb")
{
  GIVEN("A Button")
  {
    fsweep::Button button;

    WHEN("The Button is set having a bomb")
    {
      button.SetHasBomb(true);

      THEN("The Button has a bomb") { CHECK(button.GetHasBomb() == true); }
    }

    WHEN("The Button is set not having a bomb")
    {
      button.SetHasBomb(false);

      THEN("The Button does not have a bomb") { CHECK(button.GetHasBomb() == false); }
    }
  }
}

SCENARIO("The surrounding bombs of a button are set")
{
  GIVEN("A Button")
  {
    fsweep::Button button;

    WHEN("The surrounding bombs of the Button are set to 2")
    {
      button.SetSurroundingBombs(2);

      THEN("The surrounding bombs of the Button are 2")
      {
        CHECK(button.GetSurroundingBombs() == 2);
      }
    }
  }
}

SCENARIO("A surrounding bombs are added to a Button")
{
  GIVEN("A Button")
  {
    fsweep::Button button;

    WHEN("A surrounding bomb is added to the Button")
    {
      button.AddSurroundingBomb();

      THEN("The Button has 1 surrounding bombs") { CHECK(button.GetSurroundingBombs() == 1); }

      WHEN("A surrounding bomb is added to the Button")
      {
        button.AddSurroundingBomb();

        THEN("The button has 2 surrounding bombs") { CHECK(button.GetSurroundingBombs() == 2); }
      }
    }
  }
}

SCENARIO("It is determined if a Button is pressable")
{
  GIVEN("A Button")
  {
    fsweep::Button button;

    THEN("The Button is pressable") { CHECK(button.GetIsPressable() == true); }

    WHEN("The Button is Down")
    {
      button.Press();

      THEN("The Button is not pressable") { CHECK(button.GetIsPressable() == false); }
    }

    WHEN("The Button is Flagged")
    {
      button.AltPress(false);

      THEN("The Button is not pressable") { CHECK(button.GetIsPressable() == false); }
    }

    WHEN("The Button is Questioned")
    {
      button.AltPress(true);
      button.AltPress(true);

      THEN("The Button is pressable") { CHECK(button.GetIsPressable() == true); }
    }
  }
}