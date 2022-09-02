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

#include "GamePanel.hpp"

#include <cstddef>
#include <functional>
#include <optional>

#include "spritesheet.hpp"
#include "wx_include.hpp"

BEGIN_EVENT_TABLE(fsweep::GamePanel, wxPanel)
EVT_PAINT(fsweep::GamePanel::OnRender)
EVT_MOTION(fsweep::GamePanel::OnMouseMove)
EVT_LEFT_DOWN(fsweep::GamePanel::OnLeftDown)
EVT_LEFT_UP(fsweep::GamePanel::OnLeftRelease)
EVT_RIGHT_DOWN(fsweep::GamePanel::OnRightDown)
EVT_RIGHT_UP(fsweep::GamePanel::OnRightRelease)
EVT_ENTER_WINDOW(fsweep::GamePanel::OnMouseEnter)
EVT_LEAVE_WINDOW(fsweep::GamePanel::OnMouseLeave)
END_EVENT_TABLE()

const int FACE_BUTTON_DIMENSION = 24;
const int BORDER_SIZE = 8;
const int BUTTON_DIMENSION = 16;
const int LCD_DIGIT_WIDTH = 16;
const int HEADER_HEIGHT = BORDER_SIZE * 2 + FACE_BUTTON_DIMENSION;

std::optional<fsweep::ButtonPosition> fsweep::GamePanel::getHoverButton(wxPoint mouse_position)
{
  if (mouse_position.x >= this->getBorderSize() &&
      mouse_position.x < this->GetSize().x - this->getBorderSize() &&
      mouse_position.y >= this->getHeaderHeight() &&
      mouse_position.y < this->GetSize().y - this->getBorderSize())
  {
    return fsweep::ButtonPosition(
        (mouse_position.x - this->getBorderSize()) / this->getButtonDimension(),
        (mouse_position.y - this->getHeaderHeight()) / this->getButtonDimension());
  }
  return std::nullopt;
}

bool fsweep::GamePanel::getHoverFace(wxPoint mouse_position)
{
  const auto face_point = this->getFaceButtonPoint();
  return mouse_position.x >= face_point.x &&
         mouse_position.x < face_point.x + this->getFaceButtonDimension() &&
         mouse_position.y >= face_point.y &&
         mouse_position.y < face_point.y + this->getFaceButtonDimension();
}

wxPoint fsweep::GamePanel::getFaceButtonPoint()
{
  return wxPoint((this->GetSize().x / 2) - (this->getFaceButtonDimension() / 2),
                 this->getBorderSize());
}

wxPoint fsweep::GamePanel::getButtonPoint(int x, int y)
{
  return wxPoint(this->getBorderSize() + (x * this->getButtonDimension()),
                 this->getHeaderHeight() + (y * this->getButtonDimension()));
}

wxPoint fsweep::GamePanel::getScorePoint(std::size_t digit)
{
  return wxPoint(this->getBorderSize() + (this->getLcdDigitWidth() * digit), this->getBorderSize());
}

wxPoint fsweep::GamePanel::getTimerPoint(std::size_t digit)
{
  return wxPoint(
      this->GetSize().x - (this->getBorderSize() + (this->getLcdDigitWidth() * (3 - digit))),
      this->getBorderSize());
}

wxBitmap& fsweep::GamePanel::getBitmap(fsweep::Sprite sprite)
{
  return this->scaled_bitmaps[static_cast<std::size_t>(sprite)];
}

unsigned long fsweep::GamePanel::getDeltaTime()
{
  const auto& model = this->model.get();
  const unsigned long new_time = this->stopwatch.Time();
  const unsigned long delta_time = new_time - this->last_time;
  this->last_time = new_time;
  return delta_time;
}

const int MILLISECONDS_PER_SECOND = 1000;

void fsweep::GamePanel::startClock()
{
  this->stopwatch = wxStopWatch();
  this->stopwatch.Start();
  this->last_time = 0;
  this->timer.Start(MILLISECONDS_PER_SECOND);
}

void fsweep::GamePanel::stopClock()
{
  auto& model = this->model.get();
  this->timer.Stop();
  this->stopwatch.Pause();
  model.UpdateTime(this->getDeltaTime());
}

fsweep::Sprite fsweep::GamePanel::getFaceSprite()
{
  const auto& model = this->model.get();
  if (model.GetGameState() == fsweep::GameState::None ||
      model.GetGameState() == fsweep::GameState::Playing)
  {
    if (this->left_down && this->hover_face)
    {
      return fsweep::Sprite::ButtonSmileDown;
    }
    else if (this->left_down && this->hover_button_o.has_value())
    {
      const auto& hover_button = this->hover_button_o.value();
      const auto& button = model.GetButton(hover_button.x, hover_button.y);
      if (button.GetButtonState() != fsweep::ButtonState::Down &&
          button.GetButtonState() != fsweep::ButtonState::Flagged)
      {
        return fsweep::Sprite::ButtonShocked;
      }
    }
  }
  else if (model.GetGameState() == fsweep::GameState::Cool)
  {
    if (this->left_down && this->hover_face)
    {
      return fsweep::Sprite::ButtonSmileDown;
    }
    else
    {
      return fsweep::Sprite::ButtonCool;
    }
  }
  else  // if (model.GetGameState() == fsweep::GameState::Dead)
  {
    if (this->left_down && this->hover_face)
    {
      return fsweep::Sprite::ButtonSmileDown;
    }
    else
    {
      return fsweep::Sprite::ButtonDead;
    }
  }
  return fsweep::Sprite::ButtonSmile;
}

fsweep::Sprite fsweep::GamePanel::getButtonSprite(int x, int y)
{
  const auto& model = this->model.get();
  const auto& button = model.GetButton(x, y);
  const fsweep::ButtonPosition button_position(x, y);
  if (model.GetGameState() == fsweep::GameState::None ||
      model.GetGameState() == fsweep::GameState::Playing)
  {
    if (button.GetButtonState() != fsweep::ButtonState::Flagged &&
        button.GetButtonState() != fsweep::ButtonState::Down && this->left_down &&
        this->hover_button_o.has_value())
    {
      const auto& hover_button = this->hover_button_o.value();
      if ((hover_button == button_position) ||
          (model.GetGameState() == fsweep::GameState::Playing && this->right_down && hover_button.IsNear(button_position)))
      {
        if (fsweep::ButtonState() == fsweep::ButtonState::Questioned)
        {
          return fsweep::Sprite::ButtonQuestionDown;
        }
        return fsweep::Sprite::ButtonDown;
      }
    }
    else if (button.GetButtonState() == fsweep::ButtonState::Flagged)
    {
      return fsweep::Sprite::ButtonFlag;
    }
    else if (button.GetButtonState() == fsweep::ButtonState::Questioned)
    {
      return fsweep::Sprite::ButtonQuestion;
    }
    else if (button.GetButtonState() == fsweep::ButtonState::Down)
    {
      return fsweep::getDownButtonSprite(button.GetSurroundingBombs());
    }
    else
    {
      return fsweep::Sprite::ButtonNone;
    }
  }
  else  // if (model.GetGameState() == fsweep::GameState::Cool || model.GetGameState() ==
        // fsweep::GameState::Dead)
  {
    if (button.GetButtonState() == fsweep::ButtonState::None ||
        button.GetButtonState() == fsweep::ButtonState::Questioned)
    {
      if (button.GetHasBomb())
      {
        return fsweep::Sprite::ButtonBomb;
      }
      else
      {
        return fsweep::Sprite::ButtonNone;
      }
    }
    else if (button.GetButtonState() == fsweep::ButtonState::Flagged)
    {
      if (button.GetHasBomb())
      {
        return fsweep::Sprite::ButtonFlagHit;
      }
      else
      {
        return fsweep::Sprite::ButtonFlagMiss;
      }
    }
    else if (button.GetButtonState() == fsweep::ButtonState::Down)
    {
      if (button.GetHasBomb())
      {
        return fsweep::Sprite::ButtonBombExplode;
      }
      else
      {
        return fsweep::getDownButtonSprite(button.GetSurroundingBombs());
      }
    }
  }
  return fsweep::Sprite::ButtonNone;
}

int fsweep::GamePanel::getTimerSeconds()
{
  const auto& model = this->model.get();
  const auto game_time = static_cast<int>(model.GetGameTime());
  return (game_time / MILLISECONDS_PER_SECOND);
}

fsweep::GamePanel::GamePanel(fsweep::Model& model, wxFrame* parent, wxSize size)
    : wxPanel(parent, wxID_ANY), model(std::ref(model)), timer(this)
{
  Bind(wxEVT_TIMER, &GamePanel::OnTimer, this, this->timer.GetId());
  for (std::size_t bitmap_i = 0; bitmap_i < static_cast<std::size_t>(fsweep::Sprite::Count);
       bitmap_i++)
  {
    this->base_bitmaps[bitmap_i] = wxBitmap(fsweep::SPRITESHEET_XPM_DATA[bitmap_i]);
    this->scaled_bitmaps[bitmap_i] = wxBitmap(this->base_bitmaps[bitmap_i]);
  }
  this->SetSize(size);
}

int fsweep::GamePanel::getFaceButtonDimension() const noexcept
{
  return this->pixel_scale * FACE_BUTTON_DIMENSION;
}

int fsweep::GamePanel::getBorderSize() const noexcept { return this->pixel_scale * BORDER_SIZE; }

int fsweep::GamePanel::getButtonDimension() const noexcept
{
  return this->pixel_scale * BUTTON_DIMENSION;
}

int fsweep::GamePanel::getLcdDigitWidth() const noexcept
{
  return this->pixel_scale * LCD_DIGIT_WIDTH;
}

int fsweep::GamePanel::getHeaderHeight() const noexcept
{
  return this->pixel_scale * HEADER_HEIGHT;
}

fsweep::GamePanel::~GamePanel() {}

void fsweep::GamePanel::OnRender(wxPaintEvent& WXUNUSED(e)) { this->DrawAll(); }

void fsweep::GamePanel::OnMouseMove(wxMouseEvent& e)
{
  auto& model = this->model.get();
  this->mouse_position = e.GetPosition();
  this->hover_button_o = this->getHoverButton(this->mouse_position);
  this->hover_face = this->getHoverFace(this->mouse_position);
  this->DrawChanged();
}

void fsweep::GamePanel::OnLeftDown(wxMouseEvent& WXUNUSED(e))
{
  this->left_down = true;
  this->DrawChanged();
}

void fsweep::GamePanel::OnLeftRelease(wxMouseEvent& WXUNUSED(e))
{
  auto& model = this->model.get();
  if (model.GetGameState() == fsweep::GameState::Playing)
  {
    model.UpdateTime(this->getDeltaTime());
  }
  auto initially_playing = model.GetGameState() == fsweep::GameState::Playing;
  if (this->hover_button_o.has_value())
  {
    auto& hover_button = this->hover_button_o.value();
    if (this->right_down)
    {
      model.AreaClickButton(hover_button.x, hover_button.y);
    }
    else
    {
      model.ClickButton(hover_button.x, hover_button.y);
    }
    if (model.GetGameState() == fsweep::GameState::Playing && !initially_playing)
    {
      this->startClock();
    }
    else if (model.GetGameState() == fsweep::GameState::Dead && initially_playing)
    {
      this->stopClock();
    }
  }
  else if (this->hover_face)
  {
    model.NewGame();
    this->stopClock();
  }
  this->left_down = false;
  this->DrawChanged();
}

void fsweep::GamePanel::OnRightDown(wxMouseEvent& WXUNUSED(e))
{
  auto& model = this->model.get();
  this->right_down = true;
  if (model.GetGameState() == fsweep::GameState::Playing)
  {
    model.UpdateTime(this->getDeltaTime());
  }
  if (!this->left_down && this->hover_button_o.has_value())
  {
    auto& hover_button = this->hover_button_o.value();
    model.AltClickButton(hover_button.x, hover_button.y);
  }
  this->DrawChanged();
}

void fsweep::GamePanel::OnRightRelease(wxMouseEvent& WXUNUSED(e))
{
  this->right_down = false;
  this->DrawChanged();
}

void fsweep::GamePanel::OnMouseEnter(wxMouseEvent& WXUNUSED(e))
{
  this->mouse_hover = true;
  this->DrawChanged();
}

void fsweep::GamePanel::OnMouseLeave(wxMouseEvent& WXUNUSED(e))
{
  this->mouse_hover = false;
  this->DrawChanged();
}

void fsweep::GamePanel::OnTimer(wxTimerEvent& WXUNUSED(e))
{
  auto& model = this->model.get();
  model.UpdateTime(this->getDeltaTime());
  this->DrawChanged();
}

bool fsweep::GamePanel::TryChangePixelScale(int new_pixel_scale)
{
  if (this->pixel_scale == new_pixel_scale) return false;
  for (std::size_t bitmap_i = 0; bitmap_i < static_cast<std::size_t>(fsweep::Sprite::Count);
       bitmap_i++)
  {
    const auto& base_bitmap = this->base_bitmaps[bitmap_i];
    auto image = base_bitmap.ConvertToImage();
    image.Rescale(base_bitmap.GetWidth() * new_pixel_scale,
                  base_bitmap.GetHeight() * new_pixel_scale);
    this->scaled_bitmaps[bitmap_i] = wxBitmap(image);
  }
  this->pixel_scale = new_pixel_scale;
  return true;
}

int fsweep::GamePanel::GetPixelScale() const noexcept { return this->pixel_scale; }

void fsweep::GamePanel::DrawAll()
{
  const auto& model = this->model.get();
  wxClientDC dc(this);
  dc.SetBrush(wxBrush(wxColour(198, 198, 198)));
  dc.DrawRectangle(wxRect(wxPoint(0, 0), this->GetSize()));
  dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderLeftTop), wxPoint(0, 0), false);
  dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderRightTop),
                wxPoint(this->GetSize().x - this->getBorderSize(), 0), false);
  dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderLeftBottom),
                wxPoint(0, this->GetSize().y - this->getBorderSize()), false);
  dc.DrawBitmap(
      this->getBitmap(fsweep::Sprite::BorderRightBottom),
      wxPoint(this->GetSize().x - this->getBorderSize(), this->GetSize().y - this->getBorderSize()),
      false);
  for (std::size_t i = 0; i < (this->GetSize().x / this->getBorderSize()) - 2; i++)
  {
    dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderTop),
                  wxPoint(this->getBorderSize() + (i * this->getBorderSize()), 0), false);
  }
  for (std::size_t i = 0; i < (this->GetSize().x / this->getBorderSize()) - 2; i++)
  {
    dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderBottom),
                  wxPoint(this->getBorderSize() + (i * this->getBorderSize()),
                          this->GetSize().y - this->getBorderSize()),
                  false);
  }
  dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderLeftIntersection),
                wxPoint(0, this->getBorderSize() * 4), false);
  dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderRightIntersection),
                wxPoint(this->GetSize().x - this->getBorderSize(), this->getBorderSize() * 4),
                false);
  for (std::size_t i = 0; i < (this->GetSize().x / this->getBorderSize()) - 2; i++)
  {
    dc.DrawBitmap(
        this->getBitmap(fsweep::Sprite::BorderTop),
        wxPoint(this->getBorderSize() + (i * this->getBorderSize()), this->getBorderSize() * 4),
        false);
  }
  for (std::size_t i = 1; i < 4; i++)
  {
    dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderLeft),
                  wxPoint(0, i * this->getBorderSize()), false);
  }
  for (std::size_t i = 1; i < 4; i++)
  {
    dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderRight),
                  wxPoint(this->GetSize().x - this->getBorderSize(), i * this->getBorderSize()),
                  false);
  }
  for (std::size_t i = 5; i < (this->GetSize().y / this->getBorderSize()) - 1; i++)
  {
    dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderLeft),
                  wxPoint(0, i * this->getBorderSize()), false);
  }
  for (std::size_t i = 5; i < (this->GetSize().y / this->getBorderSize()) - 1; i++)
  {
    dc.DrawBitmap(this->getBitmap(fsweep::Sprite::BorderRight),
                  wxPoint(this->GetSize().x - this->getBorderSize(), i * this->getBorderSize()),
                  false);
  }
  const auto score_lcd = fsweep::LcdNumber(model.GetBombsLeft());
  for (std::size_t digit_i = 0; digit_i < 3; digit_i++)
  {
    const auto lcd_sprite = fsweep::getSpriteFromDigit(score_lcd[digit_i]);
    dc.DrawBitmap(this->getBitmap(lcd_sprite), this->getScorePoint(digit_i), false);
    this->game_panel_state.score_lcd[digit_i] = lcd_sprite;
  }
  const auto time_lcd = fsweep::LcdNumber(this->getTimerSeconds());
  for (std::size_t digit_i = 0; digit_i < 3; digit_i++)
  {
    const auto lcd_sprite = fsweep::getSpriteFromDigit(time_lcd[digit_i]);
    dc.DrawBitmap(this->getBitmap(lcd_sprite), this->getTimerPoint(digit_i), false);
    this->game_panel_state.time_lcd[digit_i] = lcd_sprite;
  }
  const auto face_sprite = this->getFaceSprite();
  dc.DrawBitmap(this->getBitmap(face_sprite), this->getFaceButtonPoint(), false);
  this->game_panel_state.face_sprite = face_sprite;
  this->game_panel_state.button_sprites.clear();
  this->game_panel_state.button_sprites.reserve(model.GetGameConfiguration().GetButtonCount());
  for (int x = 0; x < model.GetGameConfiguration().GetButtonsWide(); x++)
  {
    for (int y = 0; y < model.GetGameConfiguration().GetButtonsTall(); y++)
    {
      const auto button_sprite = this->getButtonSprite(x, y);
      dc.DrawBitmap(this->getBitmap(this->getButtonSprite(x, y)), this->getButtonPoint(x, y),
                    false);
      this->game_panel_state.button_sprites.push_back(button_sprite);
    }
  }
}

void fsweep::GamePanel::DrawChanged()
{
  const auto& model = this->model.get();
  const auto buttons_wide = model.GetGameConfiguration().GetButtonsWide();
  [[maybe_unused]] wxClientDC dc(this);
  auto score_lcd = fsweep::LcdNumber(model.GetBombsLeft());
  for (std::size_t digit_i = 0; digit_i < 3; digit_i++)
  {
    const auto lcd_sprite = fsweep::getSpriteFromDigit(score_lcd[digit_i]);
    if (this->game_panel_state.score_lcd[digit_i] != lcd_sprite)
    {
      dc.DrawBitmap(this->getBitmap(lcd_sprite), this->getScorePoint(digit_i), false);
      this->game_panel_state.score_lcd[digit_i] = lcd_sprite;
    }
  }
  const auto time_lcd = fsweep::LcdNumber(this->getTimerSeconds());
  for (std::size_t digit_i = 0; digit_i < 3; digit_i++)
  {
    const auto lcd_sprite = fsweep::getSpriteFromDigit(time_lcd[digit_i]);
    if (this->game_panel_state.time_lcd[digit_i] != lcd_sprite)
    {
      dc.DrawBitmap(this->getBitmap(lcd_sprite), this->getTimerPoint(digit_i), false);
      this->game_panel_state.time_lcd[digit_i] = lcd_sprite;
    }
  }
  const auto face_sprite = this->getFaceSprite();
  if (face_sprite != this->game_panel_state.face_sprite)
  {
    dc.DrawBitmap(this->getBitmap(face_sprite), this->getFaceButtonPoint(), false);
    this->game_panel_state.face_sprite = face_sprite;
  }
  for (int x = 0; x < model.GetGameConfiguration().GetButtonsWide(); x++)
  {
    for (int y = 0; y < model.GetGameConfiguration().GetButtonsTall(); y++)
    {
      const fsweep::ButtonPosition button_position(x, y);
      const auto button_sprite = this->getButtonSprite(x, y);
      if (button_sprite !=
          this->game_panel_state.button_sprites[button_position.GetIndex(buttons_wide)])
      {
        dc.DrawBitmap(this->getBitmap(button_sprite), this->getButtonPoint(x, y), false);
        this->game_panel_state.button_sprites[button_position.GetIndex(buttons_wide)] =
            button_sprite;
      }
    }
  }
}

wxSize fsweep::GamePanel::GetPixelDimensions(
    int pixel_scale, const fsweep::GameConfiguration& configuration) noexcept
{
  return wxSize((configuration.GetButtonsWide() * (pixel_scale * BUTTON_DIMENSION)) +
                    ((pixel_scale * BORDER_SIZE) * 2),
                (configuration.GetButtonsTall() * (pixel_scale * BUTTON_DIMENSION)) +
                    ((pixel_scale * BORDER_SIZE) + (pixel_scale * HEADER_HEIGHT)));
}