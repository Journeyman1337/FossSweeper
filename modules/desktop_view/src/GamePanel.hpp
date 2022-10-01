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

#ifndef FSWEEP_GAME_PANEL_HPP
#define FSWEEP_GAME_PANEL_HPP

#include <array>
#include <fsweep/ButtonPosition.hpp>
#include <functional>
#include <optional>

#include "DesktopTimer.hpp"
#include "GamePanelState.hpp"
#include "spritesheet.hpp"
#include "wx_include.hpp"

namespace fsweep
{
  class DesktopView;

  class GamePanel : public wxPanel
  {
   private:
    std::reference_wrapper<fsweep::DesktopView> desktop_view;
    fsweep::DesktopTimer timer;
    std::array<wxBitmap, static_cast<std::size_t>(fsweep::Sprite::Count)> base_bitmaps;
    std::array<wxBitmap, static_cast<std::size_t>(fsweep::Sprite::Count)> scaled_bitmaps;
    fsweep::GamePanelState game_panel_state;
    wxBitmap& getBitmap(fsweep::Sprite sprite);

   public:
    GamePanel(fsweep::DesktopView& desktop_view, wxFrame* parent, int width, int height);
    virtual ~GamePanel();

    void OnRender(wxPaintEvent& evt);
    void OnMouseMove(wxMouseEvent& evt);
    void OnLeftPress(wxMouseEvent& evt);
    void OnLeftRelease(wxMouseEvent& evt);
    void OnRightPress(wxMouseEvent& evt);
    void OnRightRelease(wxMouseEvent& evt);
    void OnMouseEnter(wxMouseEvent& evt);
    void OnMouseLeave(wxMouseEvent& evt);
    void OnTimer(wxTimerEvent& evt);

    bool TryChangePixelScale(int new_pixel_scale);
    int GetPixelScale() const noexcept;
    void DrawAll();
    void DrawChanged(bool timer_only = false);

    DECLARE_EVENT_TABLE();
  };
}  // namespace fsweep

#endif
