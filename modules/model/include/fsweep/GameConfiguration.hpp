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

#ifndef FSWEEP_GAME_CONFIGURATION_HPP
#define FSWEEP_GAME_CONFIGURATION_HPP

#include <compare>
#include <fsweep/GameDifficulty.hpp>

namespace fsweep
{
  class GameConfiguration
  {
   public:
    static const int BEGINNER_BUTTONS_WIDE;
    static const int BEGINNER_BUTTONS_TALL;
    static const int BEGINNER_BOMB_COUNT;
    static const int INTERMEDIATE_BUTTONS_WIDE;
    static const int INTERMEDIATE_BUTTONS_TALL;
    static const int INTERMEDIATE_BOMB_COUNT;
    static const int EXPERT_BUTTONS_WIDE;
    static const int EXPERT_BUTTONS_TALL;
    static const int EXPERT_BOMB_COUNT;
    static const int MIN_BUTTONS_WIDE;
    static const int MIN_BUTTONS_TALL;
    static const int MIN_BOMB_COUNT;

   private:
    fsweep::GameDifficulty game_difficulty = fsweep::GameDifficulty::Default;
    int buttons_wide = fsweep::GameConfiguration::BEGINNER_BUTTONS_WIDE;
    int buttons_tall = fsweep::GameConfiguration::BEGINNER_BUTTONS_TALL;
    int bomb_count = fsweep::GameConfiguration::BEGINNER_BOMB_COUNT;

   public:
    constexpr GameConfiguration() noexcept = default;
    GameConfiguration(fsweep::GameDifficulty game_difficulty) noexcept;
    GameConfiguration(int buttons_wide, int buttons_tall, int bomb_count) noexcept;

    bool operator==(const fsweep::GameConfiguration& other) const noexcept;
    bool operator!=(const fsweep::GameConfiguration& other) const noexcept;
    std::strong_ordering operator<=>(const fsweep::GameConfiguration& other) const noexcept;

    fsweep::GameDifficulty GetGameDifficulty() const noexcept;
    int GetButtonsWide() const noexcept;
    int GetButtonsTall() const noexcept;
    int GetBombCount() const noexcept;
    int GetButtonCount() const noexcept;
  };
}  // namespace fsweep

#endif
