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

#ifndef FSWEEP_DESKTOP_MODEL_HPP
#define FSWEEP_DESKTOP_MODEL_HPP

#include <cstddef>
#include <fsweep/ButtonPosition.hpp>
#include <fsweep/GameModel.hpp>
#include <fsweep/Point.hpp>
#include <fsweep/Sprite.hpp>
#include <functional>
#include <optional>

namespace fsweep
{
  class Timer;

  class DesktopModel
  {
   private:
    std::reference_wrapper<fsweep::GameModel> game_model;
    std::optional<fsweep::ButtonPosition> hover_button_o = std::nullopt;
    bool left_down = false;
    bool right_down = false;
    bool hover_face = false;
    int pixel_scale = 1;

   public:
    DesktopModel(fsweep::GameModel& game_model) noexcept;

    bool TryChangePixelScale(int new_pixel_scale);
    void LeftPress();
    void LeftRelease(fsweep::Timer& timer);
    void RightPress(fsweep::Timer& timer);
    void RightRelease();
    void MouseLeave();
    void MouseMove(int x, int y);
    int GetPixelScale() const noexcept;
    int GetFaceDimension() const noexcept;
    int GetBorderSize() const noexcept;
    int GetButtonDimension() const noexcept;
    int GetLcdDigitWidth() const noexcept;
    int GetHeaderHeight() const noexcept;
    fsweep::Sprite GetFaceSprite() const noexcept;
    fsweep::Sprite GetButtonSprite(int x, int y) const noexcept;
    fsweep::Point GetFacePoint() const noexcept;
    fsweep::Point GetButtonPoint(int x, int y) const noexcept;
    fsweep::Point GetScorePoint(std::size_t digit) const noexcept;
    fsweep::Point GetTimerPoint(std::size_t digit) const noexcept;
    fsweep::Point GetSize() const noexcept;
  };
}  // namespace fsweep

#endif