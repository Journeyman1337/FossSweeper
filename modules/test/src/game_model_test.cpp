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
#include <fsweep/GameModel.hpp>

SCENARIO("A GameModel is constructed with its default constructor")
{
  GIVEN("A default constructed GameModel")
  {
    const fsweep::GameModel game_model;

    THEN("The questions are not enabled") { CHECK(game_model.GetQuestionsEnabled() == false); }

    THEN("The flag count is 0") { CHECK(game_model.GetFlagCount() == 0); }

    THEN("There are bomb count bombs left")
    {
      CHECK(game_model.GetBombsLeft() == fsweep::GameConfiguration::BEGINNER_BOMB_COUNT);
    }

    THEN("There is a beginner difficulty amount of buttons left")
    {
      CHECK(game_model.GetButtonsLeft() == (fsweep::GameConfiguration::BEGINNER_BUTTONS_WIDE *
                                            fsweep::GameConfiguration::BEGINNER_BUTTONS_TALL) -
                                               fsweep::GameConfiguration::BEGINNER_BOMB_COUNT);
    }

    THEN("The GameState is None") { CHECK(game_model.GetGameState() == fsweep::GameState::None); }

    THEN("The GameDifficulty is Default (Beginner)")
    {
      CHECK(game_model.GetGameConfiguration().GetGameDifficulty() ==
            fsweep::GameDifficulty::Default);
    }
  }
}

SCENARIO("A GameModel is constructed with its overloaded constructor")
{
  GIVEN("A GameModel constructed with default properties")
  {
    const fsweep::GameModel game_model(fsweep::GameConfiguration(8, 8, 2), true,
                                       fsweep::GameState::Cool, 15,
                                       "dbxfcqr."
                                       "........"
                                       "........"
                                       "........"
                                       "........"
                                       "........"
                                       "........"
                                       "........");

    THEN("The GameDifficulty is Custom (8x8) 2b")
    {
      CHECK(game_model.GetGameConfiguration().GetGameDifficulty() ==
            fsweep::GameDifficulty::Custom);
      CHECK(game_model.GetGameConfiguration().GetButtonsWide() == 8);
      CHECK(game_model.GetGameConfiguration().GetButtonsTall() == 8);
      CHECK(game_model.GetGameConfiguration().GetBombCount() == 2);
    }

    THEN("The amount of Button objects in the buttons vector is correct")
    {
      CHECK(game_model.GetButtons().size() == 8 * 8);
    }

    THEN("The questions are enabled") { CHECK(game_model.GetQuestionsEnabled() == true); }

    THEN("The GameState is Cool") { CHECK(game_model.GetGameState() == fsweep::GameState::Cool); }

    THEN("The game time is 15") { CHECK(game_model.GetGameTime() == 15); }

    THEN("The Button at (0, 0) is Down state with no bomb")
    {
      CHECK(game_model.GetButton(0, 0).GetButtonState() == fsweep::ButtonState::Down);
      CHECK(game_model.GetButton(0, 0).GetHasBomb() == false);
    }

    THEN("The Button at (1, 0) is None state with a bomb")
    {
      CHECK(game_model.GetButton(1, 0).GetButtonState() == fsweep::ButtonState::None);
      CHECK(game_model.GetButton(1, 0).GetHasBomb() == true);
    }

    THEN("The Button at (2, 0) is Down state with a bomb")
    {
      CHECK(game_model.GetButton(2, 0).GetButtonState() == fsweep::ButtonState::Down);
      CHECK(game_model.GetButton(2, 0).GetHasBomb() == true);
    }

    THEN("The Button at (3, 0) is Flagged state with no bomb")
    {
      CHECK(game_model.GetButton(3, 0).GetButtonState() == fsweep::ButtonState::Flagged);
      CHECK(game_model.GetButton(3, 0).GetHasBomb() == false);
    }

    THEN("The Button at (4, 0) is Flagged state with a bomb")
    {
      CHECK(game_model.GetButton(4, 0).GetButtonState() == fsweep::ButtonState::Flagged);
      CHECK(game_model.GetButton(4, 0).GetHasBomb() == true);
    }

    THEN("The Button at (5, 0) is Questioned state with no bomb")
    {
      CHECK(game_model.GetButton(5, 0).GetButtonState() == fsweep::ButtonState::Questioned);
      CHECK(game_model.GetButton(5, 0).GetHasBomb() == false);
    }

    THEN("The Button at (6, 0) is Questioned state with a bomb")
    {
      CHECK(game_model.GetButton(6, 0).GetButtonState() == fsweep::ButtonState::Questioned);
      CHECK(game_model.GetButton(6, 0).GetHasBomb() == true);
    }

    THEN("The Button at (7, 0) is None state with no bomb")
    {
      CHECK(game_model.GetButton(7, 0).GetButtonState() == fsweep::ButtonState::None);
      CHECK(game_model.GetButton(7, 0).GetHasBomb() == false);
    }

    THEN("The flag count is 2") { CHECK(game_model.GetFlagCount() == 2); }
  }
}

SCENARIO("A new game is started in a GameModel without a configuration change")
{
  GIVEN("A GameModel in dead game state with enabled questions")
  {
    fsweep::GameModel game_model(fsweep::GameConfiguration(fsweep::GameDifficulty::Beginner), true,
                                 fsweep::GameState::Dead, 30,
                                 "dbxfcqr."
                                 "........"
                                 "........"
                                 "........"
                                 "........"
                                 "........"
                                 "........"
                                 "........");

    WHEN("A new game is started without a configuration change")
    {
      game_model.NewGame();

      THEN("The GameState is None") { CHECK(game_model.GetGameState() == fsweep::GameState::None); }

      THEN("Questions are still enabled") { CHECK(game_model.GetQuestionsEnabled() == true); }

      THEN("The GameConfiguration has beginner difficulty")
      {
        CHECK(game_model.GetGameConfiguration().GetGameDifficulty() ==
              fsweep::GameDifficulty::Beginner);
        CHECK(game_model.GetGameConfiguration().GetButtonsWide() ==
              fsweep::GameConfiguration::BEGINNER_BUTTONS_WIDE);
        CHECK(game_model.GetGameConfiguration().GetButtonsTall() ==
              fsweep::GameConfiguration::BEGINNER_BUTTONS_TALL);
        CHECK(game_model.GetGameConfiguration().GetBombCount() ==
              fsweep::GameConfiguration::BEGINNER_BOMB_COUNT);
      }

      THEN("The timer has 0") { CHECK(game_model.GetGameTime() == 0); }

      THEN("The Button objects are all default constructed")
      {
        CHECK(game_model.GetButton(0, 0).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(0, 0).GetHasBomb() == false);
        CHECK(game_model.GetButton(1, 0).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(1, 0).GetHasBomb() == false);
        CHECK(game_model.GetButton(2, 0).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(2, 0).GetHasBomb() == false);
        CHECK(game_model.GetButton(3, 0).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(3, 0).GetHasBomb() == false);
        CHECK(game_model.GetButton(4, 0).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(4, 0).GetHasBomb() == false);
        CHECK(game_model.GetButton(5, 0).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(5, 0).GetHasBomb() == false);
        CHECK(game_model.GetButton(6, 0).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(6, 0).GetHasBomb() == false);
        CHECK(game_model.GetButton(7, 0).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(7, 0).GetHasBomb() == false);
      }
    }
  }
}

SCENARIO("A new game is started in a GameModel with a configuration change")
{
  GIVEN("A GameModel with beginner difficulty")
  {
    fsweep::GameModel game_model;

    WHEN("A new game is started with intermediate difficulty")
    {
      game_model.NewGame(fsweep::GameConfiguration(fsweep::GameDifficulty::Intermediate));

      THEN("The new game is intermediate difficulty")
      {
        CHECK(game_model.GetGameConfiguration().GetGameDifficulty() ==
              fsweep::GameDifficulty::Intermediate);
      }

      THEN(
          "The amount of Button objects in the buttons vector the amount for intermediate "
          "difficulty")
      {
        CHECK(game_model.GetButtons().size() ==
              fsweep::GameConfiguration::INTERMEDIATE_BUTTONS_WIDE *
                  fsweep::GameConfiguration::INTERMEDIATE_BUTTONS_TALL);
      }

      THEN("The GameState is None") { CHECK(game_model.GetGameState() == fsweep::GameState::None); }
    }
  }

  GIVEN("A GameModel constructed with one button pressed in playing state")
  {
    fsweep::GameModel game_model(fsweep::GameConfiguration(fsweep::GameDifficulty::Beginner), false,
                                 fsweep::GameState::Playing, 55,
                                 "db......"
                                 "bb......"
                                 ".b....b."
                                 "........"
                                 "...b...."
                                 "........"
                                 ".b....b."
                                 "........");

    WHEN("A new game is started with intermediate difficulty")
    {
      game_model.NewGame(fsweep::GameConfiguration(fsweep::GameDifficulty::Intermediate));

      THEN("The new game is intermediate difficulty")
      {
        CHECK(game_model.GetGameConfiguration().GetGameDifficulty() ==
              fsweep::GameDifficulty::Intermediate);
      }

      THEN(
          "The amount of Button objects in the buttons vector the amount for intermediate "
          "difficulty")
      {
        CHECK(game_model.GetButtons().size() ==
              fsweep::GameConfiguration::INTERMEDIATE_BUTTONS_WIDE *
                  fsweep::GameConfiguration::INTERMEDIATE_BUTTONS_TALL);
      }

      THEN("The GameState is None") { CHECK(game_model.GetGameState() == fsweep::GameState::None); }
    }
  }
}

SCENARIO("A Button of a GameModel is clicked")
{
  GIVEN("A default constructed GameModel")
  {
    fsweep::GameModel game_model;

    WHEN("A Button is clicked")
    {
      game_model.ClickButton(6, 6);

      THEN("The Button is Down")
      {
        CHECK(game_model.GetButton(6, 6).GetButtonState() == fsweep::ButtonState::Down);
      }

      THEN("The GameState is Playing")
      {
        CHECK(game_model.GetGameState() == fsweep::GameState::Playing);
      }

      THEN("The GameModel has the correct amount of bombs")
      {
        int bomb_count = 0;
        for (auto& button : game_model.GetButtons())
        {
          if (button.GetHasBomb() == true)
          {
            bomb_count++;
          }
        }
        CHECK(bomb_count == fsweep::GameConfiguration::BEGINNER_BOMB_COUNT);
      }

      THEN("The clicked button has no bombs")
      {
        CHECK(game_model.GetButton(6, 6).GetHasBomb() == false);
      }
    }
  }

  GIVEN("A GameModel is in playing state")
  {
    fsweep::GameModel game_model(fsweep::GameConfiguration(fsweep::GameDifficulty::Beginner), false,
                                 fsweep::GameState::Playing, 0,
                                 "b......."
                                 "bb......"
                                 "......b."
                                 "........"
                                 "........"
                                 "........"
                                 ".b....bb"
                                 "......bd");

    WHEN("A bombed Button is clicked")
    {
      game_model.ClickButton(0, 0);

      THEN("The GameState is Dead") { CHECK(game_model.GetGameState() == fsweep::GameState::Dead); }
    }
  }

  GIVEN("A GameModel in dead state")
  {
    fsweep::GameModel game_model(fsweep::GameConfiguration(fsweep::GameDifficulty::Beginner), false,
                                 fsweep::GameState::Dead, 0,
                                 "x......."
                                 "bb......"
                                 "......b."
                                 "........"
                                 "........"
                                 "........"
                                 ".b....bb"
                                 "......bd");

    WHEN("A Button with None state is clicked")
    {
      game_model.ClickButton(5, 5);

      THEN("The Button is not down")
      {
        CHECK(game_model.GetButton(5, 5).GetButtonState() == fsweep::ButtonState::None);
      }
    }
  }

  GIVEN("A GameModel in cool state")
  {
    fsweep::GameModel game_model(fsweep::GameConfiguration(fsweep::GameDifficulty::Beginner), false,
                                 fsweep::GameState::Cool, 0,
                                 "bddddddd"
                                 "cbdddddd"
                                 "ddddddbd"
                                 "dddddddd"
                                 "dddddddd"
                                 "dddddddd"
                                 "dbddddbb"
                                 "ddddddbd");

    WHEN("A bombed Button is clicked")
    {
      game_model.ClickButton(0, 0);

      THEN("The Button is not down")
      {
        CHECK(game_model.GetButton(0, 0).GetButtonState() == fsweep::ButtonState::None);
      }
    }

    WHEN("A flagged Button is clicked")
    {
      game_model.ClickButton(0, 1);

      THEN("The Button is still flagged and not down")
      {
        CHECK(game_model.GetButton(0, 1).GetButtonState() == fsweep::ButtonState::Flagged);
      }
    }
  }

  GIVEN("A GameModel in playing state)")
  {
    fsweep::GameModel game_model(fsweep::GameConfiguration(fsweep::GameDifficulty::Beginner), false,
                                 fsweep::GameState::Playing, 0,
                                 "bf......"
                                 "bb......"
                                 "......b."
                                 "........"
                                 "........"
                                 "........"
                                 ".b....bb"
                                 "......bd");

    WHEN("A flagged Button is clicked")
    {
      game_model.ClickButton(1, 0);

      THEN("The Button is not down and still flagged")
      {
        CHECK(game_model.GetButton(1, 0).GetButtonState() == fsweep::ButtonState::Flagged);
      }
    }
  }

  GIVEN("A GameModel in playing state")
  {
    fsweep::GameModel game_model(fsweep::GameConfiguration(fsweep::GameDifficulty::Beginner), true,
                                 fsweep::GameState::Playing, 0,
                                 "bq......"
                                 "bb......"
                                 "......b."
                                 "........"
                                 "........"
                                 "........"
                                 ".b....bb"
                                 "......bd");

    WHEN("A questioned Button is clicked")
    {
      game_model.ClickButton(1, 0);

      THEN("The GameState is still playing")
      {
        CHECK(game_model.GetGameState() == fsweep::GameState::Playing);
      }

      THEN("The questioned Button is down")
      {
        CHECK(game_model.GetButton(1, 0).GetButtonState() == fsweep::ButtonState::Down);
      }
    }

    WHEN("A Button in the middle of an bombless are is clicked")
    {
      game_model.ClickButton(4, 4);

      THEN("The bombless area was floodfill pressed")
      {
        CHECK(game_model.GetButton(0, 4).GetButtonState() == fsweep::ButtonState::Down);
        CHECK(game_model.GetButton(4, 3).GetButtonState() == fsweep::ButtonState::Down);
      }
    }
  }
}

SCENARIO("A Button of a GameModel is alt clicked")
{
  GIVEN("A default constructed GameModel")
  {
    fsweep::GameModel game_model;

    WHEN("The Button at (0, 0) is alt clicked")
    {
      game_model.AltClickButton(0, 0);

      THEN("The state of the Button at (0, 0) is None")
      {
        CHECK(game_model.GetButton(0, 0).GetButtonState() == fsweep::ButtonState::None);
      }

      THEN("The Button at (0, 0) has no bomb")
      {
        CHECK(game_model.GetButton(0, 0).GetHasBomb() == false);
      }
    }
  }

  GIVEN("A GameModel in playing state with questions enabled")
  {
    fsweep::GameModel game_model(fsweep::GameConfiguration(fsweep::GameDifficulty::Beginner), true,
                                 fsweep::GameState::Playing, 0,
                                 "bfq....."
                                 "bb......"
                                 "......b."
                                 "........"
                                 "........"
                                 "........"
                                 ".b....bb"
                                 "......bd");

    WHEN("A down Button is alt clicked")
    {
      game_model.AltClickButton(7, 7);

      THEN("The Button is still down")
      {
        CHECK(game_model.GetButton(7, 7).GetButtonState() == fsweep::ButtonState::Down);
      }
    }

    WHEN("A questioned Button is alt clicked")
    {
      game_model.AltClickButton(2, 0);

      THEN("The Button is now has None state")
      {
        CHECK(game_model.GetButton(2, 0).GetButtonState() == fsweep::ButtonState::None);
      }
    }

    WHEN("A flagged Button is alt clicked")
    {
      game_model.AltClickButton(1, 0);

      THEN("The Button now has Questioned state")
      {
        CHECK(game_model.GetButton(1, 0).GetButtonState() == fsweep::ButtonState::Questioned);
      }

      THEN("The flag count is decremented") { CHECK(game_model.GetFlagCount() == 0); }
    }

    WHEN("A Button with None state is alt clicked")
    {
      game_model.AltClickButton(3, 0);

      THEN("The Button is now flagged")
      {
        CHECK(game_model.GetButton(3, 0).GetButtonState() == fsweep::ButtonState::Flagged);
      }

      THEN("The flag count is incremented") { CHECK(game_model.GetFlagCount() == 2); }
    }
  }

  GIVEN("A GameModel in playing state with questions disabled")
  {
    fsweep::GameModel game_model(fsweep::GameConfiguration(fsweep::GameDifficulty::Beginner), false,
                                 fsweep::GameState::Playing, 0,
                                 "bf......"
                                 "bb......"
                                 "......b."
                                 "........"
                                 "........"
                                 "........"
                                 ".b....bb"
                                 "......bd");

    WHEN("A down Button is alt clicked")
    {
      game_model.AltClickButton(7, 7);

      THEN("The Button is still down")
      {
        CHECK(game_model.GetButton(7, 7).GetButtonState() == fsweep::ButtonState::Down);
      }
    }

    WHEN("A flagged Button is alt clicked")
    {
      game_model.AltClickButton(1, 0);

      THEN("The Button now has None state")
      {
        CHECK(game_model.GetButton(1, 0).GetButtonState() == fsweep::ButtonState::None);
      }

      THEN("The flag count is decremented") { CHECK(game_model.GetFlagCount() == 0); }
    }

    WHEN("A Button with None state is alt clicked")
    {
      game_model.AltClickButton(3, 0);

      THEN("The Button is now flagged")
      {
        CHECK(game_model.GetButton(3, 0).GetButtonState() == fsweep::ButtonState::Flagged);
      }

      THEN("The flag count is incremented") { CHECK(game_model.GetFlagCount() == 2); }
    }
  }
}

SCENARIO("A Button of a GameModel is area clicked")
{
  GIVEN("A GameModel with GameState::None")
  {
    fsweep::GameModel game_model;

    WHEN("A Button is area clicked")
    {
      game_model.AreaClickButton(5, 5);

      THEN("The GameState is None") { CHECK(game_model.GetGameState() == fsweep::GameState::None); }

      THEN("All Button objects in the area still have None state")
      {
        CHECK(game_model.GetButton(4, 4).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(5, 4).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(6, 4).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(4, 5).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(5, 5).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(6, 5).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(4, 6).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(5, 6).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(6, 6).GetButtonState() == fsweep::ButtonState::None);
      }
    }
  }

  GIVEN("A GameModel in playing state")
  {
    fsweep::GameModel game_model(fsweep::GameConfiguration(fsweep::GameDifficulty::Beginner), true,
                                 fsweep::GameState::Playing, 0,
                                 "bq...dc."
                                 "bb...b.."
                                 "..ddddd."
                                 ".bd.c.d."
                                 "ccdddd.."
                                 "b.f.c.d."
                                 "...dddbb"
                                 "ddddddbd");

    WHEN("A Button is area clicked where chording is possible and no bombs are hit")
    {
      game_model.AreaClickButton(4, 4);

      THEN("The GameState is still playing")
      {
        CHECK(game_model.GetGameState() == fsweep::GameState::Playing);
      }

      THEN("All the near Button objects have the correct state")
      {
        CHECK(game_model.GetButton(3, 3).GetButtonState() == fsweep::ButtonState::Down);
        CHECK(game_model.GetButton(4, 3).GetButtonState() == fsweep::ButtonState::Flagged);
        CHECK(game_model.GetButton(5, 3).GetButtonState() == fsweep::ButtonState::Down);
        CHECK(game_model.GetButton(3, 4).GetButtonState() == fsweep::ButtonState::Down);
        CHECK(game_model.GetButton(4, 4).GetButtonState() == fsweep::ButtonState::Down);
        CHECK(game_model.GetButton(5, 4).GetButtonState() == fsweep::ButtonState::Down);
        CHECK(game_model.GetButton(3, 5).GetButtonState() == fsweep::ButtonState::Down);
        CHECK(game_model.GetButton(4, 5).GetButtonState() == fsweep::ButtonState::Flagged);
        CHECK(game_model.GetButton(5, 5).GetButtonState() == fsweep::ButtonState::Down);
      }
    }

    WHEN("A Button is area clicked where chording is possible and a bomb is hit")
    {
      game_model.AreaClickButton(2, 4);

      THEN("The GameState is Dead") { CHECK(game_model.GetGameState() == fsweep::GameState::Dead); }

      THEN("All the near Button objects have the correct state")
      {
        CHECK(game_model.GetButton(1, 3).GetButtonState() == fsweep::ButtonState::Down);
        CHECK(game_model.GetButton(2, 3).GetButtonState() == fsweep::ButtonState::Down);
        CHECK(game_model.GetButton(3, 3).GetButtonState() == fsweep::ButtonState::Down);
        CHECK(game_model.GetButton(1, 4).GetButtonState() == fsweep::ButtonState::Flagged);
        CHECK(game_model.GetButton(2, 4).GetButtonState() == fsweep::ButtonState::Down);
        CHECK(game_model.GetButton(3, 4).GetButtonState() == fsweep::ButtonState::Down);
        CHECK(game_model.GetButton(1, 5).GetButtonState() == fsweep::ButtonState::Down);
        CHECK(game_model.GetButton(2, 5).GetButtonState() == fsweep::ButtonState::Flagged);
        CHECK(game_model.GetButton(3, 5).GetButtonState() == fsweep::ButtonState::Down);
      }
    }

    WHEN(
        "A button is area clicked where chording is not possible because there are more "
        "surrounding bombs than surrounding flags")
    {
      game_model.AreaClickButton(5, 0);

      THEN("The GameState is still Playing")
      {
        CHECK(game_model.GetGameState() == fsweep::GameState::Playing);
      }

      THEN("All the near Button objects have the same state")
      {
        CHECK(game_model.GetButton(4, 0).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(5, 0).GetButtonState() == fsweep::ButtonState::Down);
        CHECK(game_model.GetButton(6, 0).GetButtonState() == fsweep::ButtonState::Flagged);
        CHECK(game_model.GetButton(4, 1).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(5, 1).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(6, 1).GetButtonState() == fsweep::ButtonState::None);
      }
    }

    WHEN("A button is area clicked where chording is not possible because it is not down")
    {
      game_model.AreaClickButton(3, 0);

      THEN("The GameState is still Playing")
      {
        CHECK(game_model.GetGameState() == fsweep::GameState::Playing);
      }

      THEN("All the near Button objects have the same state")
      {
        CHECK(game_model.GetButton(2, 0).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(3, 0).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(4, 0).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(2, 1).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(3, 1).GetButtonState() == fsweep::ButtonState::None);
        CHECK(game_model.GetButton(4, 1).GetButtonState() == fsweep::ButtonState::None);
      }
    }
  }
}

SCENARIO("The game time of a GameModel is updated")
{
  GIVEN("A GameModel with GameState::None")
  {
    fsweep::GameModel game_model;

    WHEN("The timer is updated")
    {
      game_model.UpdateTime(14);

      THEN("The timer value is still 0") { CHECK(game_model.GetGameTime() == 0); }
    }
  }

  GIVEN("A GameModel with GameState::Playing")
  {
    fsweep::GameModel game_model(fsweep::GameConfiguration(fsweep::GameDifficulty::Beginner), true,
                                 fsweep::GameState::Playing, 0,
                                 "bq......"
                                 "bb......"
                                 "......b."
                                 "........"
                                 "........"
                                 "........"
                                 ".b....bb"
                                 "......bd");

    WHEN("The timer is updated to 14")
    {
      game_model.UpdateTime(14);

      THEN("The timer value is 14") { CHECK(game_model.GetGameTime() == 14); }

      WHEN("The timer is updated again to 16")
      {
        game_model.UpdateTime(16);

        THEN("The timer value is 16") { CHECK(game_model.GetGameTime() == 16); }
      }
    }
  }
}

SCENARIO("Questions are enabled or disabled throughout a GameModel")
{
  GIVEN("A GameModel with GameState::None with questions disabled")
  {
    fsweep::GameModel game_model;

    WHEN("Questions are enabled")
    {
      game_model.SetQuestionsEnabled(true);

      THEN("Questions are enabled") { CHECK(game_model.GetQuestionsEnabled() == true); }
    }
  }

  GIVEN("A GameModel with GameState::Playing with questions enabled")
  {
    fsweep::GameModel game_model(fsweep::GameConfiguration(fsweep::GameDifficulty::Beginner), true,
                                 fsweep::GameState::Playing, 0,
                                 "bfq....."
                                 "bb......"
                                 "......b."
                                 "........"
                                 "........"
                                 "........"
                                 ".b....bb"
                                 "......bd");

    WHEN("Questions are disabled")
    {
      game_model.SetQuestionsEnabled(false);

      THEN("All questioned buttons now have ButtonState::None")
      {
        CHECK(game_model.GetButton(2, 0).GetButtonState() == fsweep::ButtonState::None);
      }
    }
  }
}