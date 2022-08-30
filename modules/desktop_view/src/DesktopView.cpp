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

#include "DesktopView.hpp"

#include <functional>
#include <sstream>
#include <stdexcept>

#include "GameFrame.hpp"
#include "wx_include.hpp"

fsweep::DesktopView::DesktopView(fsweep::Model& model) noexcept : model(std::ref(model)) {}

bool fsweep::DesktopView::Run() noexcept
{
  try
  {
    auto* const game_frame = new GameFrame(*this);
    game_frame->Show();
  }
  catch (const std::exception& e)
  {
    std::stringstream ss("");
    ss << "FossSweeper crashed due to unhandled exception:\n\n\"" << e.what() << "\"";
    wxMessageBox(_(ss.str()), _("FossSweeper"), wxICON_ERROR);
    return false;
  }

  return true;
}

fsweep::Model& fsweep::DesktopView::GetModel() noexcept { return this->model.get(); }
