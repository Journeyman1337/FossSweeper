// SPDX-FileCopyrightText: 2022 Daniel Valcour <fosssweeper@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

/*
 * Copyright (c) 2022 Daniel Valcour
 *model
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

#include <algorithm>
#include <cstddef>
#include <fsweep/ButtonPosition.hpp>
#include <fsweep/GameModel.hpp>
#include <stdexcept>
#include <string>
#include <fsweep/Timer.hpp>

fsweep::GameModel::GameModel(fsweep::GameConfiguration game_configuration, bool questions_enabled,
                     fsweep::GameState game_state, int game_time, std::string_view button_string)
    : game_configuration(game_configuration)
    , flag_count(0)
    , game_time(game_time)
    , buttons_left(game_configuration.GetButtonCount())
    , questions_enabled(questions_enabled)
    , buttons()
    , game_state(game_state)
{
  if (button_string.length() != game_configuration.GetButtonCount())
  {
    throw std::runtime_error("invalid button string length");
  }
  this->buttons.reserve(game_configuration.GetButtonCount());
  for (std::size_t button_i = 0; button_i < game_configuration.GetButtonCount(); button_i++)
  {
    this->buttons.emplace_back(button_string[button_i]);
    const auto& button = this->buttons.back();
    if (button.GetButtonState() == fsweep::ButtonState::Flagged)
    {
      this->flag_count++;
    }
  }
  this->calculateSurroundingBombs();
}

fsweep::Button& fsweep::GameModel::getButton(int x, int y)
{
  const fsweep::ButtonPosition position(x, y);
  return this->buttons[position.GetIndex(this->game_configuration.GetButtonsWide())];
}

void fsweep::GameModel::pressButton(int x, int y)
{
  auto& button = this->getButton(x, y);
  if (button.GetIsPressable())
  {
    if (button.GetHasBomb())
    {
      button.Press();
      this->game_state = fsweep::GameState::Dead;
    }
    else
    {
      this->floodFillClick(x, y);
    }
  }
}

void fsweep::GameModel::floodFillClick(int x, int y)
{
  const fsweep::ButtonPosition start_position(x, y);
  const auto buttons_wide = this->game_configuration.GetButtonsWide();
  const auto buttons_tall = this->game_configuration.GetButtonsTall();
  this->flood_fill_stack.clear();
  this->flood_fill_stack.push_back(start_position);
  do
  {
    const auto cur_position = this->flood_fill_stack.back();
    this->flood_fill_stack.pop_back();
    auto& cur_button = this->getButton(cur_position.x, cur_position.y);
    cur_button.Press();
    this->buttons_left--;
    if (cur_button.GetSurroundingBombs() == 0)
    {
      this->surroundingButtonAction(
          cur_position,
          [&](const fsweep::Button& button, const fsweep::ButtonPosition& position)
          {
            if (button.GetIsPressable() &&
                std::find(this->flood_fill_stack.begin(), this->flood_fill_stack.end(), position) ==
                    this->flood_fill_stack.end())
            {
              this->flood_fill_stack.push_back(position);
            }
          });
    }
  } while (!this->flood_fill_stack.empty());
}

bool fsweep::GameModel::choordingPossible(int x, int y)
{
  const auto& button = this->getButton(x, y);
  if (button.GetButtonState() != fsweep::ButtonState::Down) return false;
  auto surrounding_flags = 0;
  this->surroundingButtonAction(
      fsweep::ButtonPosition(x, y),
      [&](const fsweep::Button& button, const fsweep::ButtonPosition position)
      {
        if (button.GetButtonState() == fsweep::ButtonState::Flagged)
        {
          surrounding_flags++;
        }
      });
  return surrounding_flags == button.GetSurroundingBombs();
}

void fsweep::GameModel::surroundingButtonAction(
    const fsweep::ButtonPosition& center_position,
    std::function<void(const fsweep::Button&, const fsweep::ButtonPosition&)> action)
{
  const auto buttons_wide = this->game_configuration.GetButtonsWide();
  const auto buttons_tall = this->game_configuration.GetButtonsTall();
  if (center_position.HasLeftUp())
  {
    const auto left_up_position = center_position.GetLeftUp();
    auto& left_up_button = this->getButton(left_up_position.x, left_up_position.y);
    action(left_up_button, left_up_position);
  }
  if (center_position.HasUp())
  {
    const auto up_position = center_position.GetUp();
    auto& up_button = this->getButton(up_position.x, up_position.y);
    action(up_button, up_position);
  }
  if (center_position.HasRightUp(buttons_wide))
  {
    const auto right_up_position = center_position.GetRightUp();
    auto& right_up_button = this->getButton(right_up_position.x, right_up_position.y);
    action(right_up_button, right_up_position);
  }
  if (center_position.HasLeft())
  {
    const auto left_position = center_position.GetLeft();
    auto& left_button = this->getButton(left_position.x, left_position.y);
    action(left_button, left_position);
  }
  if (center_position.HasRight(buttons_wide))
  {
    const auto right_position = center_position.GetRight();
    auto& right_button = this->getButton(right_position.x, right_position.y);
    action(right_button, right_position);
  }
  if (center_position.HasLeftDown(buttons_tall))
  {
    const auto left_down_position = center_position.GetLeftDown();
    auto& left_down_button = this->getButton(left_down_position.x, left_down_position.y);
    action(left_down_button, left_down_position);
  }
  if (center_position.HasDown(buttons_tall))
  {
    const auto down_position = center_position.GetDown();
    auto& down_button = this->getButton(down_position.x, down_position.y);
    action(down_button, down_position);
  }
  if (center_position.HasRightDown(buttons_wide, buttons_tall))
  {
    const auto right_down_position = center_position.GetRightDown();
    auto& right_down_button = this->getButton(right_down_position.x, right_down_position.y);
    action(right_down_button, right_down_position);
  }
}

void fsweep::GameModel::placeBombs(int initial_x, int initial_y)
{
  const auto bomb_count = this->game_configuration.GetBombCount();
  for (auto& button : this->buttons)
  {
    button = fsweep::Button();
  }
  for (std::size_t button_i = 0; button_i < bomb_count; button_i++)
  {
    this->buttons[button_i].SetHasBomb(true);
  }
  if (bomb_count == this->buttons.size())
  {
    for (auto& cur_button : this->buttons)
    {
      cur_button.SetSurroundingBombs(8);
    }
    return;
  }
  const auto last_minable_button_i = this->buttons.size() - 2;
  std::uniform_int_distribution<std::mt19937::result_type> distributor(0, last_minable_button_i);
  for (std::size_t button_i = 0; button_i <= last_minable_button_i; button_i++)
  {
    const std::size_t swap_i = static_cast<std::size_t>(distributor(this->rng));
    std::swap(this->buttons[button_i], this->buttons[swap_i]);
  }
  std::swap(this->getButton(initial_x, initial_y), this->buttons.back());
  this->calculateSurroundingBombs();
}

void fsweep::GameModel::calculateSurroundingBombs()
{
  const auto buttons_wide = this->game_configuration.GetButtonsWide();
  const auto buttons_tall = this->game_configuration.GetButtonsTall();
  for (int x = 0; x < buttons_wide; x++)
  {
    for (int y = 0; y < buttons_tall; y++)
    {
      const fsweep::ButtonPosition cur_button_position(x, y);
      auto& cur_button = this->getButton(x, y);
      this->surroundingButtonAction(
          cur_button_position,
          [&](const fsweep::Button& button, const fsweep::ButtonPosition& position)
          {
            if (button.GetHasBomb())
            {
              cur_button.AddSurroundingBomb();
            }
          });
    }
  }
}

void fsweep::GameModel::tryWin() noexcept
{
  if (this->buttons_left <= 0)
  {
    this->game_state = fsweep::GameState::Cool;
  }
}

void fsweep::GameModel::NewGame()
{
  std::fill(this->buttons.begin(), this->buttons.end(), fsweep::Button());
  this->game_time = 0;
  this->game_state = fsweep::GameState::None;
  this->flag_count = 0;
  this->buttons_left =
      this->game_configuration.GetButtonCount() - this->game_configuration.GetBombCount();
}

void fsweep::GameModel::NewGame(fsweep::GameConfiguration game_configuration)
{
  if (this->game_configuration != game_configuration)
  {
    const std::size_t button_count = game_configuration.GetButtonCount();
    this->game_configuration = game_configuration;
    this->buttons.clear();
    this->buttons.reserve(button_count);
    for (auto button_i = 0; button_i < button_count; button_i++)
    {
      this->buttons.emplace_back();
    }
    this->flood_fill_stack.reserve(button_count);
    this->game_time = 0;
    this->game_state = fsweep::GameState::None;
    this->flag_count = 0;
    this->buttons_left =
        this->game_configuration.GetButtonCount() - this->game_configuration.GetBombCount();
  }
  else
  {
    this->NewGame();
  }
}

void fsweep::GameModel::ClickButton(int x, int y)
{
  if (this->game_state != fsweep::GameState::Playing && this->game_state != fsweep::GameState::None)
    return;
  if (this->game_state == fsweep::GameState::None)
  {
    this->placeBombs(x, y);
    this->game_state = fsweep::GameState::Playing;
  }
  this->pressButton(x, y);
  if (this->game_configuration.GetBombCount() == this->game_configuration.GetButtonCount())
  {
    this->game_state = fsweep::GameState::Dead;
  }
  this->tryWin();
}

void fsweep::GameModel::AltClickButton(int x, int y)
{
  if (this->game_state != fsweep::GameState::Playing) return;
  auto& button = this->getButton(x, y);
  if (button.GetButtonState() == fsweep::ButtonState::Flagged)
  {
    this->flag_count--;
  }
  button.AltPress(this->questions_enabled);
  if (button.GetButtonState() == fsweep::ButtonState::Flagged)
  {
    this->flag_count++;
  }
}

void fsweep::GameModel::AreaClickButton(int x, int y)
{
  if (this->game_state != fsweep::GameState::Playing) return;
  if (!this->choordingPossible(x, y)) return;
  const auto buttons_wide = this->game_configuration.GetButtonsWide();
  const auto buttons_tall = this->game_configuration.GetButtonsTall();
  const fsweep::ButtonPosition center_position(x, y);
  auto& center_button = this->getButton(center_position.x, center_position.y);
  if (center_button.GetIsPressable())
  {
    this->pressButton(center_position.x, center_position.y);
  }
  this->surroundingButtonAction(
      center_position,
      [&](const fsweep::Button& button, const fsweep::ButtonPosition& position)
      {
        if (button.GetIsPressable())
        {
          this->pressButton(position.x, position.y);
        }
      });
  this->tryWin();
}

void fsweep::GameModel::SetQuestionsEnabled(bool questions_enabled)
{
  if (this->questions_enabled == questions_enabled) return;
  if (!questions_enabled)
  {
    for (auto& button : this->buttons)
    {
      button.RemoveQuestion();
    }
  }
  this->questions_enabled = questions_enabled;
}

bool fsweep::GameModel::GetQuestionsEnabled() const noexcept { return this->questions_enabled; }

int fsweep::GameModel::GetFlagCount() const noexcept { return this->flag_count; }

int fsweep::GameModel::GetBombsLeft() const noexcept
{
  return this->game_configuration.GetBombCount() - this->flag_count;
}

int fsweep::GameModel::GetButtonsLeft() const noexcept { return this->buttons_left; }

fsweep::GameState fsweep::GameModel::GetGameState() const noexcept { return this->game_state; }

fsweep::GameConfiguration fsweep::GameModel::GetGameConfiguration() const noexcept
{
  return this->game_configuration;
}

void fsweep::GameModel::UpdateTime(unsigned int game_time)
{
  this->game_time = game_time;
}

unsigned long fsweep::GameModel::GetGameTime() const noexcept { return this->game_time; }

const unsigned long MILLISECONDS_PER_SECOND = 1000;

unsigned long fsweep::GameModel::GetTimerSeconds() const noexcept
{
  return this->game_time / MILLISECONDS_PER_SECOND;
}

const fsweep::Button& fsweep::GameModel::GetButton(int x, int y) const
{
  const fsweep::ButtonPosition position(x, y);
  return this->buttons.at(position.GetIndex(this->game_configuration.GetButtonsWide()));
}

const std::vector<fsweep::Button>& fsweep::GameModel::GetButtons() const noexcept
{
  return this->buttons;
}