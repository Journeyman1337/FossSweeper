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

#include "PixelScaleDialog.hpp"

#include "wx_include.hpp"

fsweep::PixelScaleDialog::PixelScaleDialog(wxWindow* parent, int pixel_scale)
    : wxDialog(parent, wxID_ANY, "FossSweeper Pixel Scale")
{
  auto* const sizer = new wxBoxSizer(wxVERTICAL);

  auto* const pixel_scale_sizer = new wxBoxSizer(wxHORIZONTAL);
  pixel_scale_sizer->Add(new wxStaticText(this, wxID_ANY, "Pixel Scale: "));
  this->pixel_scale_ctrl = new wxSpinCtrl(this, wxID_ANY);
  this->pixel_scale_ctrl->SetRange(1, 16);
  this->pixel_scale_ctrl->SetValue(pixel_scale);
  pixel_scale_sizer->Add(this->pixel_scale_ctrl);
  sizer->Add(pixel_scale_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  auto* const button_sizer = new wxBoxSizer(wxHORIZONTAL);
  auto* const cancel_button = new wxButton(this, wxID_CANCEL, "Cancel");
  button_sizer->Add(cancel_button, 0, wxALIGN_CENTER | wxALL, 10);
  Bind(wxEVT_BUTTON, &fsweep::PixelScaleDialog::OnCancel, this, cancel_button->GetId());
  auto* const confirm_button = new wxButton(this, wxID_OK, "Confirm");
  confirm_button->SetDefault();
  Bind(wxEVT_BUTTON, &fsweep::PixelScaleDialog::OnConfirm, this, confirm_button->GetId());
  button_sizer->Add(confirm_button, 0, wxALIGN_CENTER | wxALL, 10);
  sizer->Add(button_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  this->SetSizerAndFit(sizer);
  sizer->Layout();
}

void fsweep::PixelScaleDialog::OnConfirm(wxCommandEvent& WXUNUSED(e))
{
  this->pixel_scale = this->pixel_scale_ctrl->GetValue();
  this->EndModal(wxOK);
}

void fsweep::PixelScaleDialog::OnCancel(wxCommandEvent& WXUNUSED(e)) { this->EndModal(wxCANCEL); }

int fsweep::PixelScaleDialog::GetPixelScale() const noexcept { return this->pixel_scale; }