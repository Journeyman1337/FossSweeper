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
#include <fsweep/DesktopModel.hpp>
#include <fsweep/GameModel.hpp>
#include <fsweep/Point.hpp>
#include <fsweep/Sprite.hpp>

#include "TestTimer.hpp"

TEST_CASE("A DesktopModel is constructed")
{
  GIVEN("A default constructed GameModel")
  {
    fsweep::GameModel game_model;

    GIVEN("A DesktopModel constructed with the GameModel")
    {
      fsweep::DesktopModel desktop_model(game_model);

      THEN("The getters of the DesktopModel return expected values")
      {
        CHECK(desktop_model.GetPixelScale() == 1);
        CHECK(desktop_model.GetFaceDimension() == 24);
        CHECK(desktop_model.GetBorderSize() == 8);
        CHECK(desktop_model.GetButtonDimension() == 16);
        CHECK(desktop_model.GetLcdDigitWidth() == 16);
        CHECK(desktop_model.GetHeaderHeight() == 40);
        CHECK(desktop_model.GetFaceSprite() == fsweep::Sprite::ButtonSmile);
        CHECK(desktop_model.GetButtonSprite(0, 0) == fsweep::Sprite::ButtonNone);
        CHECK(desktop_model.GetFacePoint() == fsweep::Point(60, 8));
        CHECK(desktop_model.GetButtonPoint(0, 0) == fsweep::Point(8, 40));
        CHECK(desktop_model.GetScorePoint(0) == fsweep::Point(8, 8));
        CHECK(desktop_model.GetScorePoint(1) == fsweep::Point(24, 8));
        CHECK(desktop_model.GetTimerPoint(0) == fsweep::Point(88, 8));
        CHECK(desktop_model.GetTimerPoint(1) == fsweep::Point(104, 8));
        CHECK(desktop_model.GetSize() == fsweep::Point(144, 176));
      }
    }
  }
}

TEST_CASE("The pixel scale of a DesktopModel is changed")
{
  GIVEN("A default constructed GameModel")
  {
    fsweep::GameModel game_model;

    GIVEN("A DesktopModel constructed with the GameModel")
    {
      fsweep::DesktopModel desktop_model(game_model);

      WHEN("The pixel scale is changed to 1")
      {
        bool changed = desktop_model.TryChangePixelScale(1);

        THEN("Nothing changed") { CHECK(!changed); }
      }

      WHEN("The pixel scale is changed to 2")
      {
        bool changed = desktop_model.TryChangePixelScale(2);

        THEN("It changed") { CHECK(changed); }

        THEN("The returned values from all position and size getters are doubled")
        {
          CHECK(desktop_model.GetPixelScale() == 2);
          CHECK(desktop_model.GetFaceDimension() == 48);
          CHECK(desktop_model.GetBorderSize() == 16);
          CHECK(desktop_model.GetButtonDimension() == 32);
          CHECK(desktop_model.GetLcdDigitWidth() == 32);
          CHECK(desktop_model.GetHeaderHeight() == 80);
          CHECK(desktop_model.GetFacePoint() == fsweep::Point(120, 16));
          CHECK(desktop_model.GetButtonPoint(0, 0) == fsweep::Point(16, 80));
          CHECK(desktop_model.GetScorePoint(0) == fsweep::Point(16, 16));
          CHECK(desktop_model.GetScorePoint(1) == fsweep::Point(48, 16));
          CHECK(desktop_model.GetTimerPoint(0) == fsweep::Point(176, 16));
          CHECK(desktop_model.GetTimerPoint(1) == fsweep::Point(208, 16));
          CHECK(desktop_model.GetSize() == fsweep::Point(288, 352));
        }

        WHEN("The pixel scale is changed to 2")
        {
          changed = desktop_model.TryChangePixelScale(2);

          THEN("Nothing changed") { CHECK(!changed); }
        }
      }
    }
  }
}

TEST_CASE("Buttons are clicked in through a DesktopModel")
{
  GIVEN("A default constructed TestTimer that is running")
  {
    fsweep::TestTimer timer;
    timer.Start();

    GIVEN("A GameModel with a Playing GameState")
    {
      fsweep::GameModel game_model(fsweep::GameConfiguration(fsweep::GameDifficulty::Beginner),
                                   true, fsweep::GameState::Playing, 30,
                                   ".bdddddd"
                                   "bdbddddd"
                                   "bbdddddd"
                                   "dddddddd"
                                   "dddddddd"
                                   "ddddddbb"
                                   "dddddb.b"
                                   "dddddb..");

      GIVEN("A DesktopModel constructed with the GameModel")
      {
        fsweep::DesktopModel desktop_model(game_model);

        WHEN("The Button at (0, 0) is left pressed")
        {
          desktop_model.MouseMove(9, 41);
          desktop_model.LeftPress();

          WHEN("The left mouse button is released")
          {
            desktop_model.LeftRelease(timer);

            THEN("The Button at (0, 0) has ButtonState::Down")
            {
              CHECK(game_model.GetButton(0, 0).GetButtonState() == fsweep::ButtonState::Down);
            }

            THEN("The timer is running") { CHECK(timer.GetIsRunning()); }
          }

          WHEN("The mouse is moved to the Button at (7, 7) and the left mouse button is released")
          {
            desktop_model.MouseMove(120, 153);
            desktop_model.LeftRelease(timer);

            THEN("The Button at (0, 0) has ButtonState::None")
            {
              CHECK(game_model.GetButton(0, 0).GetButtonState() == fsweep::ButtonState::None);
            }

            THEN("The Button at (7, 7) has ButtonState::Down")
            {
              CHECK(game_model.GetButton(7, 7).GetButtonState() == fsweep::ButtonState::Down);
            }

            THEN("The timer is running") { CHECK(timer.GetIsRunning()); }
          }
        }
      }
    }

    GIVEN("A GameModel with a Playing GameState")
    {
      fsweep::GameModel game_model(fsweep::GameConfiguration(fsweep::GameDifficulty::Beginner),
                                   true, fsweep::GameState::Playing, 30,
                                   ".bdddddd"
                                   "bdbddddd"
                                   "bbdddddd"
                                   "dddddddd"
                                   "dddddddd"
                                   "ddddddbb"
                                   "dddddbdb"
                                   "dddddbdd");

      GIVEN("A DesktopModel constructed with the GameModel")
      {
        fsweep::DesktopModel desktop_model(game_model);

        WHEN("The final unbombed Button not pressed at (0, 0) is left pressed and released")
        {
          desktop_model.MouseMove(9, 41);
          desktop_model.LeftPress();
          desktop_model.LeftRelease(timer);

          THEN("The timer is not running") { CHECK(!timer.GetIsRunning()); }
        }
      }
    }
  }
}

TEST_CASE("Buttons are chorded (area clicked) through the DesktopModel")
{
  GIVEN("A default constructed TestTimer that is running")
  {
    fsweep::TestTimer timer;
    timer.Start();

    GIVEN("A GameModel with some chordable Buttons")
    {
      fsweep::GameModel game_model(fsweep::GameConfiguration(fsweep::GameDifficulty::Beginner),
                                   true, fsweep::GameState::Playing, 30,
                                   "df..dc.."
                                   "b....c.."
                                   "........"
                                   "b....c.."
                                   "b...cdc."
                                   "...c...."
                                   "...db..."
                                   "........");

      GIVEN("A DesktopModel constructed with the GameModel")
      {
        fsweep::DesktopModel desktop_model(game_model);

        WHEN("An up Button is chorded")
        {
          desktop_model.MouseMove(48, 129);
          desktop_model.LeftPress();
          desktop_model.RightPress(timer);
          desktop_model.LeftRelease(timer);
          desktop_model.RightRelease();

          THEN("The amount of Buttons left is correct")
          {
            CHECK(game_model.GetButtonsLeft() == 50);
          }
        }

        WHEN("A non-chordable down Button is chorded")
        {
          desktop_model.MouseMove(73, 153);
          desktop_model.LeftPress();
          desktop_model.RightPress(timer);
          desktop_model.LeftRelease(timer);
          desktop_model.RightRelease();

          THEN("The amount of Buttons left is correct")
          {
            CHECK(game_model.GetButtonsLeft() == 50);
          }
        }

        WHEN("A chordable down Button is chorded")
        {
          desktop_model.MouseMove(81, 41);
          desktop_model.LeftPress();
          desktop_model.RightPress(timer);
          desktop_model.LeftRelease(timer);
          desktop_model.RightRelease();

          THEN("The amount of Buttons left is correct")
          {
            CHECK(game_model.GetButtonsLeft() == 33);
          }
        }

        WHEN("Two Buttons were chorded without releasing the right mouse button")
        {
          desktop_model.MouseMove(81, 41);
          desktop_model.LeftPress();
          desktop_model.RightPress(timer);
          desktop_model.LeftRelease(timer);
          desktop_model.MouseMove(89, 113);
          desktop_model.LeftPress();
          desktop_model.LeftRelease(timer);
          desktop_model.RightRelease();

          THEN("The amount of Buttons left is correct")
          {
            CHECK(game_model.GetButtonsLeft() == 29);
          }
        }
      }
    }
  }
}

TEST_CASE("The mouse leaves the game area of a DesktopModel")
{
  GIVEN("A default constructed GameModel")
  {
    fsweep::GameModel game_model;

    GIVEN("A default constructed TestTimer")
    {
      fsweep::TestTimer timer;

      GIVEN("A DesktopModel constructed with the GameModel")
      {
        fsweep::DesktopModel desktop_model(game_model);

        WHEN("The Button at (0, 0) is held down with the left mouse button")
        {
          desktop_model.MouseMove(9, 41);
          desktop_model.LeftPress();

          WHEN("The mouse is moved out of the game area")
          {
            desktop_model.MouseLeave();

            THEN("The Sprite of the Button at (0, 0) is ButtonNone")
            {
              CHECK(desktop_model.GetButtonSprite(0, 0) == fsweep::Sprite::ButtonNone);
            }

            WHEN("The left mouse button is released")
            {
              desktop_model.LeftRelease(timer);

              THEN("The GameState is None")
              {
                CHECK(game_model.GetGameState() == fsweep::GameState::None);
              }
            }
          }
        }
      }
    }
  }
}