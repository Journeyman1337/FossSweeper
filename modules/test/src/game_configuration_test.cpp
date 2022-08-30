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
#include <fsweep/GameConfiguration.hpp>
#include <fsweep/GameDifficulty.hpp>

SCENARIO("GameConfiguration object is created with a default constructor")
{
  GIVEN("A GameConfiguration object created with a default constructor")
  {
    const fsweep::GameConfiguration game_configuration;

    THEN("The properties are correct for beginner difficulty")
    {
      CHECK(game_configuration.GetButtonsWide() ==
            fsweep::GameConfiguration::BEGINNER_BUTTONS_WIDE);
      CHECK(game_configuration.GetButtonsTall() ==
            fsweep::GameConfiguration::BEGINNER_BUTTONS_TALL);
      CHECK(game_configuration.GetBombCount() == fsweep::GameConfiguration::BEGINNER_BOMB_COUNT);
      CHECK(game_configuration.GetGameDifficulty() == fsweep::GameDifficulty::Beginner);
    }
  }
}

SCENARIO("GameConfiguration objects are created from a GameDifficulty")
{
  GIVEN("A GameConfiguration created with GameDifficulty::Beginner")
  {
    const fsweep::GameConfiguration game_configuration(fsweep::GameDifficulty::Beginner);

    THEN("The properties are correct for beginner difficulty")
    {
      CHECK(game_configuration.GetButtonsWide() ==
            fsweep::GameConfiguration::BEGINNER_BUTTONS_WIDE);
      CHECK(game_configuration.GetButtonsTall() ==
            fsweep::GameConfiguration::BEGINNER_BUTTONS_TALL);
      CHECK(game_configuration.GetBombCount() == fsweep::GameConfiguration::BEGINNER_BOMB_COUNT);
      CHECK(game_configuration.GetGameDifficulty() == fsweep::GameDifficulty::Beginner);
    }
  }

  GIVEN("A GameConfiguration created with GameDifficulty::Intermediate")
  {
    const fsweep::GameConfiguration game_configuration(fsweep::GameDifficulty::Intermediate);

    THEN("The properties are correct for intermediate difficulty")
    {
      CHECK(game_configuration.GetButtonsWide() ==
            fsweep::GameConfiguration::INTERMEDIATE_BUTTONS_WIDE);
      CHECK(game_configuration.GetButtonsTall() ==
            fsweep::GameConfiguration::INTERMEDIATE_BUTTONS_TALL);
      CHECK(game_configuration.GetBombCount() ==
            fsweep::GameConfiguration::INTERMEDIATE_BOMB_COUNT);
      CHECK(game_configuration.GetGameDifficulty() == fsweep::GameDifficulty::Intermediate);
    }
  }

  GIVEN("A GameConfiguration created with GameDifficulty::Expert")
  {
    const fsweep::GameConfiguration game_configuration(fsweep::GameDifficulty::Expert);

    THEN("The properties are correct for expert difficulty")
    {
      CHECK(game_configuration.GetButtonsWide() == fsweep::GameConfiguration::EXPERT_BUTTONS_WIDE);
      CHECK(game_configuration.GetButtonsTall() == fsweep::GameConfiguration::EXPERT_BUTTONS_TALL);
      CHECK(game_configuration.GetBombCount() == fsweep::GameConfiguration::EXPERT_BOMB_COUNT);
      CHECK(game_configuration.GetGameDifficulty() == fsweep::GameDifficulty::Expert);
    }
  }

  GIVEN("A GameConfiguration created with GameDifficulty::Custom")
  {
    const fsweep::GameConfiguration game_configuration(fsweep::GameDifficulty::Custom);

    THEN("The properties are correct for beginner difficulty")
    {
      CHECK(game_configuration.GetButtonsWide() ==
            fsweep::GameConfiguration::BEGINNER_BUTTONS_WIDE);
      CHECK(game_configuration.GetButtonsTall() ==
            fsweep::GameConfiguration::BEGINNER_BUTTONS_TALL);
      CHECK(game_configuration.GetBombCount() == fsweep::GameConfiguration::BEGINNER_BOMB_COUNT);
      CHECK(game_configuration.GetGameDifficulty() == fsweep::GameDifficulty::Beginner);
    }
  }
}

SCENARIO("A GameConfiguration created with specific dimensions and bomb count")
{
  GIVEN("A GameConfiguration created with beginner difficulty properties")
  {
    const fsweep::GameConfiguration game_configuration(
        fsweep::GameConfiguration::BEGINNER_BUTTONS_WIDE,
        fsweep::GameConfiguration::BEGINNER_BUTTONS_TALL,
        fsweep::GameConfiguration::BEGINNER_BOMB_COUNT);

    THEN("The properties are correct for beginner difficulty")
    {
      CHECK(game_configuration.GetButtonsWide() ==
            fsweep::GameConfiguration::BEGINNER_BUTTONS_WIDE);
      CHECK(game_configuration.GetButtonsTall() ==
            fsweep::GameConfiguration::BEGINNER_BUTTONS_TALL);
      CHECK(game_configuration.GetBombCount() == fsweep::GameConfiguration::BEGINNER_BOMB_COUNT);
      CHECK(game_configuration.GetGameDifficulty() == fsweep::GameDifficulty::Beginner);
    }
  }

  GIVEN("A GameConfiguration created with intermediate difficulty properties")
  {
    const fsweep::GameConfiguration game_configuration(
        fsweep::GameConfiguration::INTERMEDIATE_BUTTONS_WIDE,
        fsweep::GameConfiguration::INTERMEDIATE_BUTTONS_TALL,
        fsweep::GameConfiguration::INTERMEDIATE_BOMB_COUNT);

    THEN("The properties are correct for intermediate difficulty")
    {
      CHECK(game_configuration.GetButtonsWide() ==
            fsweep::GameConfiguration::INTERMEDIATE_BUTTONS_WIDE);
      CHECK(game_configuration.GetButtonsTall() ==
            fsweep::GameConfiguration::INTERMEDIATE_BUTTONS_TALL);
      CHECK(game_configuration.GetBombCount() ==
            fsweep::GameConfiguration::INTERMEDIATE_BOMB_COUNT);
      CHECK(game_configuration.GetGameDifficulty() == fsweep::GameDifficulty::Intermediate);
    }
  }

  GIVEN("A GameConfiguration created with expert difficulty properties")
  {
    const fsweep::GameConfiguration game_configuration(
        fsweep::GameConfiguration::EXPERT_BUTTONS_WIDE,
        fsweep::GameConfiguration::EXPERT_BUTTONS_TALL,
        fsweep::GameConfiguration::EXPERT_BOMB_COUNT);

    THEN("The properties are correct for expert difficulty")
    {
      CHECK(game_configuration.GetButtonsWide() == fsweep::GameConfiguration::EXPERT_BUTTONS_WIDE);
      CHECK(game_configuration.GetButtonsTall() == fsweep::GameConfiguration::EXPERT_BUTTONS_TALL);
      CHECK(game_configuration.GetBombCount() == fsweep::GameConfiguration::EXPERT_BOMB_COUNT);
      CHECK(game_configuration.GetGameDifficulty() == fsweep::GameDifficulty::Expert);
    }
  }

  GIVEN("A GameConfiguration created with 64x32 dimensions and 110 bombs")
  {
    const fsweep::GameConfiguration game_configuration(64, 32, 110);

    THEN("The properties are correct")
    {
      CHECK(game_configuration.GetButtonsWide() == 64);
      CHECK(game_configuration.GetButtonsTall() == 32);
      CHECK(game_configuration.GetBombCount() == 110);
      CHECK(game_configuration.GetGameDifficulty() == fsweep::GameDifficulty::Custom);
    }
  }

  GIVEN("A GameConfiguration created with 8x8 dimensions and 100 bombs")
  {
    const fsweep::GameConfiguration game_configuration(8, 8, 110);

    THEN("The dimensions are the same, but bomb count is clamped to the button count")
    {
      CHECK(game_configuration.GetButtonsWide() == 8);
      CHECK(game_configuration.GetButtonsTall() == 8);
      CHECK(game_configuration.GetBombCount() == 64);
      CHECK(game_configuration.GetGameDifficulty() == fsweep::GameDifficulty::Custom);
    }
  }

  GIVEN("A GameConfiguration created with properties that are bellow the minimum")
  {
    const fsweep::GameConfiguration game_configuration(-50, -99, -5);

    THEN("The properties are clamped to the minimum")
    {
      CHECK(game_configuration.GetButtonsWide() == fsweep::GameConfiguration::MIN_BUTTONS_WIDE);
      CHECK(game_configuration.GetButtonsTall() == fsweep::GameConfiguration::MIN_BUTTONS_TALL);
      CHECK(game_configuration.GetBombCount() == fsweep::GameConfiguration::MIN_BOMB_COUNT);
      CHECK(game_configuration.GetGameDifficulty() == fsweep::GameDifficulty::Custom);
    }
  }
}

SCENARIO("Two GameConfiguration objects are compared")
{
  GIVEN("A GameConfiguration object named a created with beginner difficulty")
  {
    const fsweep::GameConfiguration a(fsweep::GameDifficulty::Beginner);

    GIVEN("A GameConfiguration object named b created with beginner difficulty")
    {
      const fsweep::GameConfiguration b(fsweep::GameDifficulty::Beginner);

      THEN("The objects are equal") { CHECK(a == b); }
      THEN("a is not equal to b is false") { CHECK(!(a != b)); }
    }

    GIVEN("A GameConfiguration object named b created with intermediate difficulty")
    {
      const fsweep::GameConfiguration b(fsweep::GameDifficulty::Intermediate);

      THEN("a is less than b") { CHECK(a < b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with expert difficulty")
    {
      const fsweep::GameConfiguration b(fsweep::GameDifficulty::Expert);

      THEN("a is less than b") { CHECK(a < b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with a min sized custom difficulty")
    {
      const fsweep::GameConfiguration b(fsweep::GameConfiguration::MIN_BUTTONS_WIDE,
                                        fsweep::GameConfiguration::MIN_BUTTONS_TALL,
                                        fsweep::GameConfiguration::MIN_BOMB_COUNT);

      THEN("a is less than b") { CHECK(a < b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }
  }

  GIVEN("A GameConfiguration object named a created with intermediate difficulty")
  {
    const fsweep::GameConfiguration a(fsweep::GameDifficulty::Intermediate);

    GIVEN("A GameConfiguration object named b crated with beginner difficulty")
    {
      const fsweep::GameConfiguration b(fsweep::GameDifficulty::Beginner);

      THEN("a is greater than b") { CHECK(a > b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with intermediate difficulty")
    {
      const fsweep::GameConfiguration b(fsweep::GameDifficulty::Intermediate);

      THEN("a equals b") { CHECK(a == b); }
      THEN("a is not equal to b is false") { CHECK(!(a != b)); }
    }

    GIVEN("A GameConfiguration object named b created with expert difficulty")
    {
      const fsweep::GameConfiguration b(fsweep::GameDifficulty::Expert);

      THEN("a is less than b") { CHECK(a < b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with a min sized custom difficulty")
    {
      const fsweep::GameConfiguration b(fsweep::GameConfiguration::MIN_BUTTONS_WIDE,
                                        fsweep::GameConfiguration::MIN_BUTTONS_TALL,
                                        fsweep::GameConfiguration::MIN_BOMB_COUNT);

      THEN("a is less than b") { CHECK(a < b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }
  }

  GIVEN("A GameConfiguration object named a created with expert difficulty")
  {
    const fsweep::GameConfiguration a(fsweep::GameDifficulty::Expert);

    GIVEN("A GameConfiguration object named b crated with beginner difficulty")
    {
      const fsweep::GameConfiguration b(fsweep::GameDifficulty::Beginner);

      THEN("a is greater than b") { CHECK(a > b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with intermediate difficulty")
    {
      const fsweep::GameConfiguration b(fsweep::GameDifficulty::Intermediate);

      THEN("a is greater than b") { CHECK(a > b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with expert difficulty")
    {
      const fsweep::GameConfiguration b(fsweep::GameDifficulty::Expert);

      THEN("a equals b") { CHECK(a == b); }
      THEN("a is not equal to b is false") { CHECK(!(a != b)); }
    }

    GIVEN("A GameConfiguration object named b created with a min sized custom difficulty")
    {
      const fsweep::GameConfiguration b(fsweep::GameConfiguration::MIN_BUTTONS_WIDE,
                                        fsweep::GameConfiguration::MIN_BUTTONS_TALL,
                                        fsweep::GameConfiguration::MIN_BOMB_COUNT);

      THEN("a is less than b") { CHECK(a < b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }
  }

  GIVEN("A GameConfiguration object named a created with a min sized custom difficulty")
  {
    const fsweep::GameConfiguration a(fsweep::GameConfiguration::MIN_BUTTONS_WIDE,
                                      fsweep::GameConfiguration::MIN_BUTTONS_TALL,
                                      fsweep::GameConfiguration::MIN_BOMB_COUNT);

    GIVEN("A GameConfiguration object named b crated with beginner difficulty")
    {
      const fsweep::GameConfiguration b(fsweep::GameDifficulty::Beginner);

      THEN("a is greater than b") { CHECK(a > b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with intermediate difficulty")
    {
      const fsweep::GameConfiguration b(fsweep::GameDifficulty::Intermediate);

      THEN("a is greater than b") { CHECK(a > b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with expert difficulty")
    {
      const fsweep::GameConfiguration b(fsweep::GameDifficulty::Expert);

      THEN("a is greater than b") { CHECK(a > b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }

    GIVEN("A GameConfiguration object named b created with a min sized custom difficulty")
    {
      const fsweep::GameConfiguration b(fsweep::GameConfiguration::MIN_BUTTONS_WIDE,
                                        fsweep::GameConfiguration::MIN_BUTTONS_TALL,
                                        fsweep::GameConfiguration::MIN_BOMB_COUNT);

      THEN("a equals b") { CHECK(a == b); }
      THEN("a is not equal to b is false") { CHECK(!(a != b)); }
    }

    GIVEN("A GameConfigruation object named b created with 100x100 dimensions and 50 bombs")
    {
      const fsweep::GameConfiguration b(100, 100, 50);

      THEN("a is less than b") { CHECK(a < b); }
      THEN("a equals b is false") { CHECK(!(a == b)); }
      THEN("a is not equal to b") { CHECK(a != b); }
    }
  }
}