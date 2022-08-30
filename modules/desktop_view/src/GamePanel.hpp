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
#include <fsweep/Model.hpp>
#include <functional>
#include <optional>

#include "GamePanelState.hpp"
#include "spritesheet.hpp"
#include "wx_include.hpp"

namespace fsweep
{
  class GamePanel : public wxPanel
  {
   private:
    std::reference_wrapper<fsweep::Model> model;
    std::array<wxBitmap, static_cast<std::size_t>(fsweep::Sprite::Count)> base_bitmaps;
    std::array<wxBitmap, static_cast<std::size_t>(fsweep::Sprite::Count)> scaled_bitmaps;
    bool left_down = false;
    bool right_down = false;
    bool hover_face = false;
    bool mouse_hover = true;
    int pixel_scale = 1;
    wxPoint mouse_position;
    std::optional<fsweep::ButtonPosition> hover_button_o;
    wxTimer timer;
    wxStopWatch stopwatch;
    unsigned long last_time = 0;
    fsweep::GamePanelState game_panel_state;

    std::optional<fsweep::ButtonPosition> getHoverButton(wxPoint mouse_position);
    bool getHoverFace(wxPoint mouse_position);
    wxBitmap& getBitmap(fsweep::Sprite sprite);
    wxPoint getFaceButtonPoint();
    wxPoint getButtonPoint(int x, int y);
    wxPoint getScorePoint(std::size_t digit);
    wxPoint getTimerPoint(std::size_t digit);
    void stopClock();
    void startClock();
    unsigned long getDeltaTime();
    fsweep::Sprite getFaceSprite();
    fsweep::Sprite getButtonSprite(int x, int y);
    int getTimerSeconds();
    int getFaceButtonDimension() const noexcept;
    int getBorderSize() const noexcept;
    int getButtonDimension() const noexcept;
    int getLcdDigitWidth() const noexcept;
    int getHeaderHeight() const noexcept;

   public:
    GamePanel(fsweep::Model& model, wxFrame* parent, wxSize size);
    virtual ~GamePanel();

    void OnRender(wxPaintEvent& evt);
    void OnMouseMove(wxMouseEvent& evt);
    void OnLeftDown(wxMouseEvent& evt);
    void OnLeftRelease(wxMouseEvent& evt);
    void OnRightDown(wxMouseEvent& evt);
    void OnRightRelease(wxMouseEvent& evt);
    void OnMouseEnter(wxMouseEvent& evt);
    void OnMouseLeave(wxMouseEvent& evt);
    void OnTimer(wxTimerEvent& evt);

    bool TryChangePixelScale(int new_pixel_scale);
    int GetPixelScale() const noexcept;
    void DrawAll();
    void DrawChanged();

    static wxSize GetPixelDimensions(int pixel_scale,
                                     const fsweep::GameConfiguration& configuration) noexcept;

    DECLARE_EVENT_TABLE();
  };
}  // namespace fsweep

#endif
