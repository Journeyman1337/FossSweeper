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

#ifndef FSWEEP_GAME_PANEL_STATE_HPP
#define FSWEEP_GAME_PANEL_STATE_HPP

#include <array>
#include <vector>

#include "spritesheet.hpp"

namespace fsweep
{
  struct GamePanelState
  {
    fsweep::Sprite face_sprite = fsweep::Sprite::ButtonSmile;
    std::vector<fsweep::Sprite> button_sprites = std::vector<fsweep::Sprite>();
    std::array<fsweep::Sprite, 3> score_lcd = std::array<fsweep::Sprite, 3>();
    std::array<fsweep::Sprite, 3> time_lcd = std::array<fsweep::Sprite, 3>();

    constexpr GamePanelState() noexcept = default;
  };
}  // namespace fsweep

#endif