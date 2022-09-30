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

#ifndef FSWEEP_GAME_FRAME_HPP
#define FSWEEP_GAME_FRAME_HPP

#include <functional>
#include <fsweep/DesktopModel.hpp>
#include "wx_include.hpp"

namespace fsweep
{
  class DesktopView;
  class GamePanel;

  class GameFrame : public wxFrame
  {
   private:
    std::reference_wrapper<fsweep::DesktopView> view;
    fsweep::DesktopModel model;
    wxMenuItem* beginner_item;
    wxMenuItem* intermediate_item;
    wxMenuItem* expert_item;
    wxMenuItem* question_marks_item;
    fsweep::GamePanel* game_panel;

    void resizeGamePanel(int x, int y);

   public:
    GameFrame(fsweep::DesktopView& view);

    void OnNew(wxCommandEvent& e);
    void OnBeginner(wxCommandEvent& e);
    void OnIntermediate(wxCommandEvent& e);
    void OnExpert(wxCommandEvent& e);
    void OnCustom(wxCommandEvent& e);
    void OnPixelScale(wxCommandEvent& e);
    void OnQuestionMarks(wxCommandEvent& e);
    void OnExit(wxCommandEvent& e);
    void OnCredits(wxCommandEvent& e);
    void OnLicense(wxCommandEvent& e);
    void OnAbout(wxCommandEvent& e);

    DECLARE_EVENT_TABLE()
  };
}  // namespace fsweep

#endif
