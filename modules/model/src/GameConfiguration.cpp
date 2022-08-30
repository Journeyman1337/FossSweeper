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

#include <cmath>
#include <fsweep/GameConfiguration.hpp>

const int fsweep::GameConfiguration::BEGINNER_BUTTONS_WIDE = 8;
const int fsweep::GameConfiguration::BEGINNER_BUTTONS_TALL = 8;
const int fsweep::GameConfiguration::BEGINNER_BOMB_COUNT = 10;
const int fsweep::GameConfiguration::INTERMEDIATE_BUTTONS_WIDE = 16;
const int fsweep::GameConfiguration::INTERMEDIATE_BUTTONS_TALL = 16;
const int fsweep::GameConfiguration::INTERMEDIATE_BOMB_COUNT = 40;
const int fsweep::GameConfiguration::EXPERT_BUTTONS_WIDE = 30;
const int fsweep::GameConfiguration::EXPERT_BUTTONS_TALL = 16;
const int fsweep::GameConfiguration::EXPERT_BOMB_COUNT = 99;
const int fsweep::GameConfiguration::MIN_BUTTONS_WIDE = 8;
const int fsweep::GameConfiguration::MIN_BUTTONS_TALL = 1;
const int fsweep::GameConfiguration::MIN_BOMB_COUNT = 0;

fsweep::GameConfiguration::GameConfiguration(fsweep::GameDifficulty game_difficulty) noexcept
{
  switch (game_difficulty)
  {
  case fsweep::GameDifficulty::Intermediate:
    this->buttons_wide = fsweep::GameConfiguration::INTERMEDIATE_BUTTONS_WIDE;
    this->buttons_tall = fsweep::GameConfiguration::INTERMEDIATE_BUTTONS_TALL;
    this->bomb_count = fsweep::GameConfiguration::INTERMEDIATE_BOMB_COUNT;
    this->game_difficulty = game_difficulty;
    break;
  case fsweep::GameDifficulty::Expert:
    this->buttons_wide = fsweep::GameConfiguration::EXPERT_BUTTONS_WIDE;
    this->buttons_tall = fsweep::GameConfiguration::EXPERT_BUTTONS_TALL;
    this->bomb_count = fsweep::GameConfiguration::EXPERT_BOMB_COUNT;
    this->game_difficulty = game_difficulty;
    break;
  case fsweep::GameDifficulty::Beginner:
  default:
    this->buttons_wide = fsweep::GameConfiguration::BEGINNER_BUTTONS_WIDE;
    this->buttons_tall = fsweep::GameConfiguration::BEGINNER_BUTTONS_TALL;
    this->bomb_count = fsweep::GameConfiguration::BEGINNER_BOMB_COUNT;
    this->game_difficulty = fsweep::GameDifficulty::Beginner;
    break;
  }
}

fsweep::GameConfiguration::GameConfiguration(int buttons_wide, int buttons_tall,
                                             int bomb_count) noexcept
{
  if (buttons_wide == fsweep::GameConfiguration::BEGINNER_BUTTONS_WIDE &&
      buttons_tall == fsweep::GameConfiguration::BEGINNER_BUTTONS_TALL &&
      bomb_count == fsweep::GameConfiguration::BEGINNER_BOMB_COUNT)
  {
    this->game_difficulty = fsweep::GameDifficulty::Beginner;
  }
  else if (buttons_wide == fsweep::GameConfiguration::INTERMEDIATE_BUTTONS_WIDE &&
           buttons_tall == fsweep::GameConfiguration::INTERMEDIATE_BUTTONS_TALL &&
           bomb_count == fsweep::GameConfiguration::INTERMEDIATE_BOMB_COUNT)
  {
    this->game_difficulty = fsweep::GameDifficulty::Intermediate;
  }
  else if (buttons_wide == fsweep::GameConfiguration::EXPERT_BUTTONS_WIDE &&
           buttons_tall == fsweep::GameConfiguration::EXPERT_BUTTONS_TALL &&
           bomb_count == fsweep::GameConfiguration::EXPERT_BOMB_COUNT)
  {
    this->game_difficulty = fsweep::GameDifficulty::Expert;
  }
  else
  {
    this->game_difficulty = fsweep::GameDifficulty::Custom;
  }
  this->buttons_wide = std::max(buttons_wide, fsweep::GameConfiguration::MIN_BUTTONS_WIDE);
  this->buttons_tall = std::max(buttons_tall, fsweep::GameConfiguration::MIN_BUTTONS_TALL);
  const int button_count = this->buttons_wide * this->buttons_tall;
  this->bomb_count =
      std::clamp(bomb_count, fsweep::GameConfiguration::MIN_BOMB_COUNT, button_count);
}

bool fsweep::GameConfiguration::operator==(const fsweep::GameConfiguration& other) const noexcept
{
  if (this->game_difficulty != fsweep::GameDifficulty::Custom &&
      other.game_difficulty != fsweep::GameDifficulty::Custom)
  {
    return this->game_difficulty == other.game_difficulty;
  }
  return this->buttons_wide == other.buttons_wide && this->buttons_tall == other.buttons_tall &&
         this->bomb_count == other.bomb_count;
}

bool fsweep::GameConfiguration::operator!=(const fsweep::GameConfiguration& other) const noexcept
{
  return !this->operator==(other);
}

std::strong_ordering fsweep::GameConfiguration::operator<=>(
    const fsweep::GameConfiguration& other) const noexcept
{
  if (this->game_difficulty == other.game_difficulty)
  {
    return this->buttons_wide * this->buttons_tall <=> other.buttons_wide * other.buttons_tall;
  }
  return static_cast<int>(this->game_difficulty) <=> static_cast<int>(other.game_difficulty);
}

fsweep::GameDifficulty fsweep::GameConfiguration::GetGameDifficulty() const noexcept
{
  return this->game_difficulty;
}

int fsweep::GameConfiguration::GetButtonsWide() const noexcept { return this->buttons_wide; }

int fsweep::GameConfiguration::GetButtonsTall() const noexcept { return this->buttons_tall; }

int fsweep::GameConfiguration::GetBombCount() const noexcept { return this->bomb_count; }

int fsweep::GameConfiguration::GetButtonCount() const noexcept
{
  return static_cast<std::size_t>(this->buttons_wide * this->buttons_tall);
}
