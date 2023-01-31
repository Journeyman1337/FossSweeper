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

#ifndef FSWEEP_BUTTON_HPP
#define FSWEEP_BUTTON_HPP

#include <fsweep/ButtonState.hpp>

namespace fsweep
{
  class Button
  {
   private:
    fsweep::ButtonState button_state = fsweep::ButtonState::Default;
    bool has_bomb = false;
    int surrounding_bombs = 0;

   public:
    constexpr Button() noexcept = default;
    Button(char c) noexcept;

    void Unpress() noexcept;
    void Press() noexcept;
    void AltPress(bool questions_enabled) noexcept;
    void RemoveQuestion() noexcept;
    void SetHasBomb(bool has_bomb) noexcept;
    void SetSurroundingBombs(int surrounding_bombs) noexcept;
    void AddSurroundingBomb() noexcept;
    bool GetIsPressable() const noexcept;
    bool GetHasBomb() const noexcept;
    int GetSurroundingBombs() const noexcept;
    fsweep::ButtonState GetButtonState() const noexcept;
  };
}  // namespace fsweep

#endif
