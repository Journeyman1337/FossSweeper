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

#include <functional>
#include <optional>
#include <fsweep/ButtonPosition.hpp>
#include <cstddef>
#include <fsweep/Point.hpp>
#include <fsweep/GameModel.hpp>
#include <fsweep/Sprite.hpp>

namespace fsweep
{
    class Timer;

    class DesktopModel : protected fsweep::GameModel
    {
    private:
        std::optional<fsweep::ButtonPosition> hover_button_o = std::nullopt;
        bool left_down = false;
        bool right_down = false;
        bool buttons_locked = false;
        bool hover_face = false;
        bool mouse_hover = true;
        int pixel_scale = 1;

    public:
        DesktopModel() noexcept = default;

        bool TryChangePixelScale(int new_pixel_scale);
        int GetPixelScale() const noexcept;
        void LeftPress();
        void LeftRelease(fsweep::Timer& timer);
        void RightPress(fsweep::Timer& timer);
        void RightRelease();
        void MouseEnter();
        void MouseLeave();
        void MouseMove(int x, int y);

        int GetFaceButtonDimension() const noexcept;
        int GetBorderSize() const noexcept;
        int GetButtonDimension() const noexcept;
        int GetLcdDigitWidth() const noexcept;
        int GetHeaderHeight() const noexcept;
        fsweep::Sprite GetFaceSprite() const noexcept;
        fsweep::Sprite GetButtonSprite(int x, int y) const noexcept;
        fsweep::Point GetFaceButtonPoint() const noexcept;
        fsweep::Point GetButtonPoint(int x, int y) const noexcept;
        fsweep::Point GetScorePoint(std::size_t digit) const noexcept;
        fsweep::Point GetTimerPoint(std::size_t digit) const noexcept;
        fsweep::Point GetSize() const noexcept;

        using GameModel::NewGame;
        using GameModel::UpdateTime;
        using GameModel::GetTimerSeconds;
        using GameModel::SetQuestionsEnabled;
        using GameModel::GetQuestionsEnabled;
        using GameModel::GetFlagCount;
        using GameModel::GetBombsLeft;
        using GameModel::GetButtonsLeft;
        using GameModel::GetGameState;
        using GameModel::GetGameConfiguration;
        using GameModel::GetGameTime;
        using GameModel::GetButton;
        using GameModel::GetButtons;
    };
}

#endif