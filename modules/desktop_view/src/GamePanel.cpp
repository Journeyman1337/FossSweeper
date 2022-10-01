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

const int MILLISECONDS_PER_SECOND = 1000;
const int TIMER_INTERVAL = MILLISECONDS_PER_SECOND / 15;

#include "GamePanel.hpp"

#include <cstddef>
#include <fsweep/Sprite.hpp>
#include <functional>
#include <optional>

#include "spritesheet.hpp"
#include "wx_include.hpp"

BEGIN_EVENT_TABLE(fsweep::GamePanel, wxPanel)
EVT_PAINT(fsweep::GamePanel::OnRender)
EVT_MOTION(fsweep::GamePanel::OnMouseMove)
EVT_LEFT_DOWN(fsweep::GamePanel::OnLeftPress)
EVT_LEFT_UP(fsweep::GamePanel::OnLeftRelease)
EVT_RIGHT_DOWN(fsweep::GamePanel::OnRightPress)
EVT_RIGHT_UP(fsweep::GamePanel::OnRightRelease)
EVT_ENTER_WINDOW(fsweep::GamePanel::OnMouseEnter)
EVT_LEAVE_WINDOW(fsweep::GamePanel::OnMouseLeave)
END_EVENT_TABLE()

wxBitmap& fsweep::GamePanel::getBitmap(fsweep::Sprite sprite)
{
  return this->scaled_bitmaps[static_cast<std::size_t>(sprite)];
}

fsweep::GamePanel::GamePanel(fsweep::DesktopModel& desktop_model, wxFrame* parent, int width,
                             int height)
    : wxPanel(parent, wxID_ANY), desktop_model(std::ref(desktop_model)), timer(this)
{
  Bind(wxEVT_TIMER, &GamePanel::OnTimer, this, this->timer.GetTimer().GetId());
  for (std::size_t bitmap_i = 0; bitmap_i < static_cast<std::size_t>(fsweep::Sprite::Count);
       bitmap_i++)
  {
    this->base_bitmaps[bitmap_i] = wxBitmap(fsweep::SPRITESHEET_XPM_DATA[bitmap_i]);
    this->scaled_bitmaps[bitmap_i] = wxBitmap(this->base_bitmaps[bitmap_i]);
  }
  this->SetSize(wxSize(width, height));
}

fsweep::GamePanel::~GamePanel() {}

void fsweep::GamePanel::OnRender(wxPaintEvent& WXUNUSED(e)) { this->DrawAll(); }

void fsweep::GamePanel::OnMouseMove(wxMouseEvent& e)
{
  auto& desktop_model = this->desktop_model.get();
  wxPoint mouse_position = e.GetPosition();
  desktop_model.MouseMove(mouse_position.x, mouse_position.y);
  this->DrawChanged();
}

void fsweep::GamePanel::OnLeftPress(wxMouseEvent& WXUNUSED(e))
{
  auto& desktop_model = this->desktop_model.get();
  desktop_model.LeftPress();
  this->DrawChanged();
}

void fsweep::GamePanel::OnLeftRelease(wxMouseEvent& WXUNUSED(e))
{
  auto& desktop_model = this->desktop_model.get();
  desktop_model.LeftRelease(this->timer);
  this->DrawChanged();
}

void fsweep::GamePanel::OnRightPress(wxMouseEvent& WXUNUSED(e))
{
  auto& desktop_model = this->desktop_model.get();
  desktop_model.RightPress(this->timer);
  this->DrawChanged();
}

void fsweep::GamePanel::OnRightRelease(wxMouseEvent& WXUNUSED(e))
{
  auto& desktop_model = this->desktop_model.get();
  desktop_model.RightRelease();
  this->DrawChanged();
}

void fsweep::GamePanel::OnMouseEnter(wxMouseEvent& WXUNUSED(e))
{
  auto& desktop_model = this->desktop_model.get();
  desktop_model.MouseEnter();
  this->DrawChanged();
}

void fsweep::GamePanel::OnMouseLeave(wxMouseEvent& WXUNUSED(e))
{
  auto& desktop_model = this->desktop_model.get();
  desktop_model.MouseLeave();
  this->DrawChanged();
}

void fsweep::GamePanel::OnTimer(wxTimerEvent& WXUNUSED(e))
{
  auto& desktop_model = this->desktop_model.get();
  desktop_model.UpdateTime(this->timer.GetGameTime());
  this->DrawChanged(true);
}

bool fsweep::GamePanel::TryChangePixelScale(int new_pixel_scale)
{
  auto& desktop_model = this->desktop_model.get();
  if (desktop_model.TryChangePixelScale(new_pixel_scale))
  {
    for (std::size_t bitmap_i = 0; bitmap_i < static_cast<std::size_t>(fsweep::Sprite::Count);
         bitmap_i++)
    {
      const auto& base_bitmap = this->base_bitmaps[bitmap_i];
      auto image = base_bitmap.ConvertToImage();
      image.Rescale(base_bitmap.GetWidth() * new_pixel_scale,
                    base_bitmap.GetHeight() * new_pixel_scale);
      this->scaled_bitmaps[bitmap_i] = wxBitmap(image);
    }
    return true;
  }
  else
    return false;
}

int fsweep::GamePanel::GetPixelScale() const noexcept
{
  auto& desktop_model = this->desktop_model.get();
  return desktop_model.GetPixelScale();
}

void fsweep::GamePanel::DrawAll()
{
  const auto& desktop_model = this->desktop_model.get();
  fsweep::Point point;
  wxPoint wx_point;
  wxClientDC dc(this);
  dc.SetBrush(wxBrush(wxColour(142, 142, 142)));
  point = desktop_model.GetSize();
  wx_point = wxPoint(point.x, point.y);
  dc.DrawRectangle(wxRect(wxPoint(0, 0), wx_point));
  dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderLeftTop), wxPoint(0, 0), false);
  dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderRightTop),
                wxPoint(desktop_model.GetSize().x - desktop_model.GetBorderSize(), 0), false);
  dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderLeftBottom),
                wxPoint(0, desktop_model.GetSize().y - desktop_model.GetBorderSize()), false);
  dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderRightBottom),
                wxPoint(desktop_model.GetSize().x - desktop_model.GetBorderSize(),
                        desktop_model.GetSize().y - desktop_model.GetBorderSize()),
                false);
  for (std::size_t i = 0; i < (desktop_model.GetSize().x / desktop_model.GetBorderSize()) - 2; i++)
  {
    dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderTop),
                  wxPoint(desktop_model.GetBorderSize() + (i * desktop_model.GetBorderSize()), 0),
                  false);
  }
  for (std::size_t i = 0; i < (this->GetSize().x / desktop_model.GetBorderSize()) - 2; i++)
  {
    dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderBottom),
                  wxPoint(desktop_model.GetBorderSize() + (i * desktop_model.GetBorderSize()),
                          desktop_model.GetSize().y - desktop_model.GetBorderSize()),
                  false);
  }
  dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderLeftIntersection),
                wxPoint(0, desktop_model.GetBorderSize() * 4), false);
  dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderRightIntersection),
                wxPoint(desktop_model.GetSize().x - desktop_model.GetBorderSize(),
                        desktop_model.GetBorderSize() * 4),
                false);
  for (std::size_t i = 0; i < (desktop_model.GetSize().x / desktop_model.GetBorderSize()) - 2; i++)
  {
    dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderTop),
                  wxPoint(desktop_model.GetBorderSize() + (i * desktop_model.GetBorderSize()),
                          desktop_model.GetBorderSize() * 4),
                  false);
  }
  for (std::size_t i = 1; i < 4; i++)
  {
    dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderLeft),
                  wxPoint(0, i * desktop_model.GetBorderSize()), false);
  }
  for (std::size_t i = 1; i < 4; i++)
  {
    dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderRight),
                  wxPoint(desktop_model.GetSize().x - desktop_model.GetBorderSize(),
                          i * desktop_model.GetBorderSize()),
                  false);
  }
  for (std::size_t i = 5; i < (desktop_model.GetSize().y / desktop_model.GetBorderSize()) - 1; i++)
  {
    dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderLeft),
                  wxPoint(0, i * desktop_model.GetBorderSize()), false);
  }
  for (std::size_t i = 5; i < (desktop_model.GetSize().y / desktop_model.GetBorderSize()) - 1; i++)
  {
    dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderRight),
                  wxPoint(desktop_model.GetSize().x - desktop_model.GetBorderSize(),
                          i * desktop_model.GetBorderSize()),
                  false);
  }
  const auto score_lcd = fsweep::LcdNumber(desktop_model.GetBombsLeft());
  for (std::size_t digit_i = 0; digit_i < 3; digit_i++)
  {
    const auto lcd_sprite = fsweep::getSpriteFromDigit(score_lcd[digit_i]);
    point = desktop_model.GetScorePoint(digit_i);
    wx_point = wxPoint(point.x, point.y);
    dc.DrawBitmap(this->getBitmap(lcd_sprite), wx_point, false);
    this->game_panel_state.score_lcd[digit_i] = lcd_sprite;
  }
  const auto time_lcd = fsweep::LcdNumber(desktop_model.GetTimerSeconds());
  for (std::size_t digit_i = 0; digit_i < 3; digit_i++)
  {
    const auto lcd_sprite = fsweep::getSpriteFromDigit(time_lcd[digit_i]);
    point = desktop_model.GetTimerPoint(digit_i);
    wx_point = wxPoint(point.x, point.y);
    dc.DrawBitmap(this->getBitmap(lcd_sprite), wx_point, false);
    this->game_panel_state.time_lcd[digit_i] = lcd_sprite;
  }
  const auto face_sprite = desktop_model.GetFaceSprite();
  point = desktop_model.GetFaceButtonPoint();
  wx_point = wxPoint(point.x, point.y);
  dc.DrawBitmap(this->getBitmap(face_sprite), wx_point, false);
  this->game_panel_state.face_sprite = face_sprite;
  this->game_panel_state.button_sprites.clear();
  this->game_panel_state.button_sprites.reserve(
      desktop_model.GetGameConfiguration().GetButtonCount());
  for (int x = 0; x < desktop_model.GetGameConfiguration().GetButtonsWide(); x++)
  {
    for (int y = 0; y < desktop_model.GetGameConfiguration().GetButtonsTall(); y++)
    {
      const auto button_sprite = desktop_model.GetButtonSprite(x, y);
      point = desktop_model.GetButtonPoint(x, y);
      wx_point = wxPoint(point.x, point.y);
      dc.DrawBitmap(this->getBitmap(desktop_model.GetButtonSprite(x, y)), wx_point, false);
      this->game_panel_state.button_sprites.push_back(button_sprite);
    }
  }
}

void fsweep::GamePanel::DrawChanged(bool timer_only)
{
  fsweep::Point point;
  wxPoint wx_point;
  const auto& desktop_model = this->desktop_model.get();
  const auto buttons_wide = desktop_model.GetGameConfiguration().GetButtonsWide();
  [[maybe_unused]] wxClientDC dc(this);
  const auto time_lcd = fsweep::LcdNumber(desktop_model.GetTimerSeconds());
  for (std::size_t digit_i = 0; digit_i < 3; digit_i++)
  {
    const auto lcd_sprite = fsweep::getSpriteFromDigit(time_lcd[digit_i]);
    if (this->game_panel_state.time_lcd[digit_i] != lcd_sprite)
    {
      point = desktop_model.GetTimerPoint(digit_i);
      wx_point = wxPoint(point.x, point.y);
      dc.DrawBitmap(this->getBitmap(lcd_sprite), wx_point, false);
      this->game_panel_state.time_lcd[digit_i] = lcd_sprite;
    }
  }
  if (timer_only) return;
  auto score_lcd = fsweep::LcdNumber(desktop_model.GetBombsLeft());
  for (std::size_t digit_i = 0; digit_i < 3; digit_i++)
  {
    const auto lcd_sprite = fsweep::getSpriteFromDigit(score_lcd[digit_i]);
    if (this->game_panel_state.score_lcd[digit_i] != lcd_sprite)
    {
      point = desktop_model.GetScorePoint(digit_i);
      wx_point = wxPoint(point.x, point.y);
      dc.DrawBitmap(this->getBitmap(lcd_sprite), wx_point, false);
      this->game_panel_state.score_lcd[digit_i] = lcd_sprite;
    }
  }
  const auto face_sprite = desktop_model.GetFaceSprite();
  if (face_sprite != this->game_panel_state.face_sprite)
  {
    point = desktop_model.GetFaceButtonPoint();
    wx_point = wxPoint(point.x, point.y);
    dc.DrawBitmap(this->getBitmap(face_sprite), wx_point, false);
    this->game_panel_state.face_sprite = face_sprite;
  }
  for (int x = 0; x < desktop_model.GetGameConfiguration().GetButtonsWide(); x++)
  {
    for (int y = 0; y < desktop_model.GetGameConfiguration().GetButtonsTall(); y++)
    {
      const fsweep::ButtonPosition button_position(x, y);
      const auto button_sprite = desktop_model.GetButtonSprite(x, y);
      if (button_sprite !=
          this->game_panel_state.button_sprites[button_position.GetIndex(buttons_wide)])
      {
        point = desktop_model.GetButtonPoint(x, y);
        wx_point = wxPoint(point.x, point.y);
        dc.DrawBitmap(this->getBitmap(button_sprite), wx_point, false);
        this->game_panel_state.button_sprites[button_position.GetIndex(buttons_wide)] =
            button_sprite;
      }
    }
  }
}