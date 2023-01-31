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

#ifndef FSWEEP_PIXEL_SCALE_DIALOG_HPP
#define FSWEEP_PIXEL_SCALE_DIALOG_HPP

#include <wx/spinctrl.h>

#include "wx_include.hpp"

namespace fsweep
{
  class PixelScaleDialog : public wxDialog
  {
   private:
    int pixel_scale = 1;

    wxSpinCtrl* pixel_scale_ctrl = nullptr;

   public:
    PixelScaleDialog(wxWindow* parent, int pixel_scale);

    void OnConfirm(wxCommandEvent& e);
    void OnCancel(wxCommandEvent& e);

    int GetPixelScale() const noexcept;
  };
}  // namespace fsweep

#endif