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

#ifndef FSWEEP_CONFIG_DIALOG_HPP
#define FSWEEP_CONFIG_DIALOG_HPP

#include <wx/spinctrl.h>

#include <fsweep/GameConfiguration.hpp>

#include "wx_include.hpp"

namespace fsweep
{
  class ConfigDialog : public wxDialog
  {
   private:
    int buttons_wide = fsweep::GameConfiguration::BEGINNER_BUTTONS_WIDE;
    int buttons_tall = fsweep::GameConfiguration::BEGINNER_BUTTONS_TALL;
    int bomb_count = fsweep::GameConfiguration::BEGINNER_BOMB_COUNT;

    wxSpinCtrl* buttons_wide_ctrl = nullptr;
    wxSpinCtrl* buttons_tall_ctrl = nullptr;
    wxSpinCtrl* bombs_ctrl = nullptr;
    wxStaticText* invalid_value_text = nullptr;

   public:
    ConfigDialog(wxWindow* parent);

    void OnConfirm(wxCommandEvent& e);
    void OnCancel(wxCommandEvent& e);

    int GetButtonsWide() const noexcept;
    int GetButtonsTall() const noexcept;
    int GetBombCount() const noexcept;
  };
}  // namespace fsweep

#endif
