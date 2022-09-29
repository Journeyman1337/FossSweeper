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

#ifndef FSWEEP_GAME_MODEL_HPP
#define FSWEEP_GAME_MODEL_HPP

#include <fsweep/Button.hpp>
#include <fsweep/GameConfiguration.hpp>
#include <fsweep/GameState.hpp>
#include <functional>
#include <random>
#include <stack>
#include <string>

namespace fsweep
{
  struct GameModel
  {
   private:
    std::vector<fsweep::Button> buttons =
        std::vector<fsweep::Button>(fsweep::GameConfiguration::BEGINNER_BUTTONS_WIDE *
                                    fsweep::GameConfiguration::BEGINNER_BUTTONS_TALL);
    fsweep::GameConfiguration game_configuration = fsweep::GameConfiguration();
    fsweep::GameState game_state = fsweep::GameState::Default;
    bool questions_enabled = false;
    int flag_count = 0;
    int buttons_left = 0;
    unsigned long game_time = 0;
    std::random_device rnd = std::random_device();
    std::mt19937 rng = std::mt19937(rnd());
    std::vector<fsweep::ButtonPosition> flood_fill_stack = std::vector<fsweep::ButtonPosition>();

   private:
    fsweep::Button& getButton(int x, int y);
    void pressButton(int x, int y);
    void floodFillClick(int x, int y);
    bool choordingPossible(int x, int y);
    void surroundingButtonAction(
        const fsweep::ButtonPosition& center_position,
        std::function<void(const fsweep::Button&, const fsweep::ButtonPosition&)> action);
    void placeBombs(int initial_x, int initial_y);
    void calculateSurroundingBombs();
    void tryWin() noexcept;

   public:
    GameModel() noexcept;
    GameModel(fsweep::GameConfiguration game_configuration, bool questions_enabled,
          fsweep::GameState game_state, int game_time, std::string_view button_string);

    void NewGame();
    void NewGame(fsweep::GameConfiguration game_configuration);
    void ClickButton(int x, int y);
    void AltClickButton(int x, int y);
    void AreaClickButton(int x, int y);
    void UpdateTime(unsigned long delta_time);
    void SetQuestionsEnabled(bool questions_enabled);

    bool GetQuestionsEnabled() const noexcept;
    int GetFlagCount() const noexcept;
    int GetBombsLeft() const noexcept;
    int GetButtonsLeft() const noexcept;
    fsweep::GameState GetGameState() const noexcept;
    fsweep::GameConfiguration GetGameConfiguration() const noexcept;
    unsigned long GetGameTime() const noexcept;
    const fsweep::Button& GetButton(int x, int y) const;
    const std::vector<fsweep::Button>& GetButtons() const noexcept;
  };
}  // namespace fsweep

#endif
