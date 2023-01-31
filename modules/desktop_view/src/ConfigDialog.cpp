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

#include "ConfigDialog.hpp"

#include "wx_include.hpp"

fsweep::ConfigDialog::ConfigDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "FossSweeper Custom Configuration")
{
  auto* const sizer = new wxBoxSizer(wxVERTICAL);

  auto* const buttons_wide_sizer = new wxBoxSizer(wxHORIZONTAL);
  buttons_wide_sizer->Add(new wxStaticText(this, wxID_ANY, "Buttons Wide: "));
  this->buttons_wide_ctrl = new wxSpinCtrl(this, wxID_ANY);
  this->buttons_wide_ctrl->SetRange(fsweep::GameConfiguration::MIN_BUTTONS_WIDE, 64);
  buttons_wide_sizer->Add(this->buttons_wide_ctrl);
  sizer->Add(buttons_wide_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  auto* const buttons_tall_sizer = new wxBoxSizer(wxHORIZONTAL);
  buttons_tall_sizer->Add(new wxStaticText(this, wxID_ANY, "Buttons Tall: "));
  this->buttons_tall_ctrl = new wxSpinCtrl(this, wxID_ANY);
  this->buttons_tall_ctrl->SetRange(fsweep::GameConfiguration::MIN_BUTTONS_TALL, 64);
  buttons_tall_sizer->Add(this->buttons_tall_ctrl);
  sizer->Add(buttons_tall_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  auto* const bomb_count_sizer = new wxBoxSizer(wxHORIZONTAL);
  bomb_count_sizer->Add(new wxStaticText(this, wxID_ANY, "Snake Count: "));
  this->bombs_ctrl = new wxSpinCtrl(this, wxID_ANY);
  bomb_count_sizer->Add(this->bombs_ctrl);
  sizer->Add(bomb_count_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  auto* const button_sizer = new wxBoxSizer(wxHORIZONTAL);
  auto* const cancel_button = new wxButton(this, wxID_CANCEL, "Cancel");
  button_sizer->Add(cancel_button, 0, wxALIGN_CENTER | wxALL, 10);
  Bind(wxEVT_BUTTON, &fsweep::ConfigDialog::OnCancel, this, cancel_button->GetId());
  auto* const confirm_button = new wxButton(this, wxID_OK, "Confirm");
  confirm_button->SetDefault();
  Bind(wxEVT_BUTTON, &fsweep::ConfigDialog::OnConfirm, this, confirm_button->GetId());
  button_sizer->Add(confirm_button, 0, wxALIGN_CENTER | wxALL, 10);
  sizer->Add(button_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  this->SetSizerAndFit(sizer);
  sizer->Layout();
}

void fsweep::ConfigDialog::OnConfirm(wxCommandEvent& WXUNUSED(e))
{
  this->buttons_wide = this->buttons_wide_ctrl->GetValue();
  this->buttons_tall = this->buttons_tall_ctrl->GetValue();
  this->bomb_count = this->bombs_ctrl->GetValue();
  this->EndModal(wxOK);
}

void fsweep::ConfigDialog::OnCancel(wxCommandEvent& WXUNUSED(e)) { this->EndModal(wxCANCEL); }

int fsweep::ConfigDialog::GetButtonsWide() const noexcept { return this->buttons_wide; }

int fsweep::ConfigDialog::GetButtonsTall() const noexcept { return this->buttons_tall; }

int fsweep::ConfigDialog::GetBombCount() const noexcept { return this->bomb_count; }