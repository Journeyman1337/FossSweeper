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

#include <catch2/catch_all.hpp>
#include <fsweep/ButtonPosition.hpp>

SCENARIO("Create a ButtonPosition")
{
  GIVEN("A ButtonPosition created with its default constructor")
  {
    fsweep::ButtonPosition button_position;

    THEN("The property values of the button_position are (-1, -1)")
    {
      CHECK(button_position.x == -1);
      CHECK(button_position.y == -1);
    }
  }

  GIVEN("A ButtonPosition created with its overloaded constructor given the arguments (5, 10)")
  {
    fsweep::ButtonPosition button_position(5, 10);

    THEN("The property values of the button_position are (5, 10)")
    {
      CHECK(button_position.x == 5);
      CHECK(button_position.y == 10);
    }
  }
}

SCENARIO("Determine if a ButtonPosition has a direction")
{
  GIVEN("A ButtonPosition at (0, 0)")
  {
    fsweep::ButtonPosition button_position(0, 0);

    THEN("The button_position does not have a left") { CHECK(!button_position.HasLeft()); }

    THEN("The button_position does not have an up") { CHECK(!button_position.HasUp()); }

    THEN("The button_position does not have a left up") { CHECK(!button_position.HasLeftUp()); }

    GIVEN("A button grid width and height of 1 and 1")
    {
      const int width = 1;
      const int height = 1;

      THEN("The button_position does not have a right") { CHECK(!button_position.HasRight(width)); }

      THEN("The button_position does not have a down") { CHECK(!button_position.HasDown(height)); }

      THEN("The button_position does not have a left down")
      {
        CHECK(!button_position.HasLeftDown(height));
      }

      THEN("The button_position does not have a right down")
      {
        CHECK(!button_position.HasRightDown(width, height));
      }

      THEN("The button_position does not have a right_up")
      {
        CHECK(!button_position.HasRightUp(width));
      }
    }

    GIVEN("A button grid width and height of 2 and 2")
    {
      const int width = 2;
      const int height = 2;

      THEN("The button_position has a right") { CHECK(button_position.HasRight(width)); }

      THEN("The button_position has a down") { CHECK(button_position.HasDown(height)); }

      THEN("The button_position has a right down")
      {
        CHECK(button_position.HasRightDown(width, height));
      }

      THEN("The button_position does not have a left down")
      {
        CHECK(!button_position.HasLeftDown(height));
      }

      THEN("The button_position does not have a right up")
      {
        CHECK(!button_position.HasRightUp(width));
      }
    }
  }

  GIVEN("A ButtonPosition at (1, 1)")
  {
    const fsweep::ButtonPosition button_position(1, 1);

    THEN("The button_position has a left") { CHECK(button_position.HasLeft()); }

    THEN("The button_position has an up") { CHECK(button_position.HasUp()); }

    THEN("The button_position has a left up") { CHECK(button_position.HasLeftUp()); }
  }
}

SCENARIO("Get an adjacent ButtonPosition from a ButtonPosition")
{
  GIVEN("A ButtonPosition at (1, 1)")
  {
    const fsweep::ButtonPosition button_position(1, 1);

    WHEN("The left position is calculated")
    {
      const fsweep::ButtonPosition left_position = button_position.GetLeft();

      THEN("The left position is (0, 1)")
      {
        CHECK(left_position.x == 0);
        CHECK(left_position.y == 1);
      }
    }

    WHEN("The right position is calculated")
    {
      const fsweep::ButtonPosition right_position = button_position.GetRight();

      THEN("The right position is (2, 1)")
      {
        CHECK(right_position.x == 2);
        CHECK(right_position.y == 1);
      }
    }

    WHEN("The up position is calculated")
    {
      const fsweep::ButtonPosition up_position = button_position.GetUp();

      THEN("The up position is (1, 0)")
      {
        CHECK(up_position.x == 1);
        CHECK(up_position.y == 0);
      }
    }

    WHEN("The down position is calculated")
    {
      const fsweep::ButtonPosition down_position = button_position.GetDown();

      THEN("The down position is (1, 2)")
      {
        CHECK(down_position.x == 1);
        CHECK(down_position.y == 2);
      }
    }

    WHEN("The left up position is calculated")
    {
      const fsweep::ButtonPosition left_up_position = button_position.GetLeftUp();

      THEN("The left up position is (0, 0)")
      {
        CHECK(left_up_position.x == 0);
        CHECK(left_up_position.y == 0);
      }
    }

    WHEN("The right up position is calculated")
    {
      const fsweep::ButtonPosition right_up_position = button_position.GetRightUp();

      THEN("The right up position is (2, 0)")
      {
        CHECK(right_up_position.x == 2);
        CHECK(right_up_position.y == 0);
      }
    }

    WHEN("The left down position is calculated")
    {
      const fsweep::ButtonPosition left_down_position = button_position.GetLeftDown();

      THEN("The left down position is (0, 2)")
      {
        CHECK(left_down_position.x == 0);
        CHECK(left_down_position.y == 2);
      }
    }

    WHEN("The right down position is calculated")
    {
      const fsweep::ButtonPosition right_down_position = button_position.GetRightDown();

      THEN("The right down position is (2, 2)")
      {
        CHECK(right_down_position.x == 2);
        CHECK(right_down_position.y == 2);
      }
    }
  }
}

SCENARIO("The equality is tested between two ButtonPosition objects")
{
  GIVEN("A ButtonPosition named a at (0,2)")
  {
    const fsweep::ButtonPosition a(0, 2);

    GIVEN("A ButtonPosition named b at (0,2)")
    {
      const fsweep::ButtonPosition b(0, 2);

      THEN("a equals b") { CHECK(a == b); }

      THEN("a does not equal b is not true") { CHECK(!(a != b)); }
    }

    GIVEN("A ButtonPosition named b at (1, 2)")
    {
      const fsweep::ButtonPosition b(1, 2);

      THEN("a equals b is not true") { CHECK(!(a == b)); }

      THEN("a does not equal b is true") { CHECK(a != b); }
    }

    GIVEN("A ButtonPosition named b at (0, 1)")
    {
      const fsweep::ButtonPosition b(0, 1);

      THEN("a equals b is not true") { CHECK(!(a == b)); }

      THEN("a does not equal b is true") { CHECK(a != b); }
    }
  }
}

SCENARIO("Nearness is determined between two ButtonPosition objects")
{
  GIVEN("A ButtonPosition named a at (2,2)")
  {
    const fsweep::ButtonPosition a(2, 2);

    GIVEN("A ButtonPosition named b at (1,1)")
    {
      const fsweep::ButtonPosition b(1, 1);

      THEN("a is near b")
      {
        CHECK(a.IsNear(b));
        CHECK(b.IsNear(a));
      }
    }

    GIVEN("A ButtonPosition named b at (1, 2)")
    {
      const fsweep::ButtonPosition b(1, 2);

      THEN("a is near b")
      {
        CHECK(a.IsNear(b));
        CHECK(b.IsNear(a));
      }
    }

    GIVEN("A ButtonPosition named b at (1, 3")
    {
      const fsweep::ButtonPosition b(1, 3);

      THEN("a is near b")
      {
        CHECK(a.IsNear(b));
        CHECK(b.IsNear(a));
      }
    }

    GIVEN("A ButtonPosition named b at (0, 0)")
    {
      const fsweep::ButtonPosition b(0, 0);

      THEN("a is not near b")
      {
        CHECK(!a.IsNear(b));
        CHECK(!b.IsNear(a));
      }
    }

    GIVEN("A ButtonPosition named b at (2, 0)")
    {
      const fsweep::ButtonPosition b(2, 0);

      THEN("a is not near b")
      {
        CHECK(!a.IsNear(b));
        CHECK(!b.IsNear(a));
      }
    }

    GIVEN("A ButtonPosition named b at (0, 2)")
    {
      const fsweep::ButtonPosition b(0, 2);

      THEN("a is not near b")
      {
        CHECK(!a.IsNear(b));
        CHECK(!b.IsNear(a));
      }
    }
  }
}