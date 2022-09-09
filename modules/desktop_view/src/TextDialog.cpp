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

#include <string>
#include "TextDialog.hpp"

#include <wx/hyperlink.h>

#include "license.hpp"
#include "wx_include.hpp"

fsweep::TextDialog::TextDialog(wxWindow* parent, std::string_view title, std::string_view text)
    : wxDialog(parent, wxID_ANY, title.data())
{
  this->SetSize(768, 512);
  new wxTextCtrl(this, wxID_ANY, text.data(), wxDefaultPosition, wxDefaultSize,
                 wxTE_READONLY | wxTE_MULTILINE | wxTE_AUTO_URL | wxTE_CENTER | wxTE_BESTWRAP);
}