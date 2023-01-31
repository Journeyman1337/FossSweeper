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

#include "AboutDialog.hpp"

#include <wx/clipbrd.h>
#include <wx/hyperlink.h>

#include <fsweep/credits.hpp>
#include <fsweep/license.hpp>
#include <fsweep/version.hpp>
#include <fsweep/short_hash.hpp>
#include <sstream>

#include "TextDialog.hpp"
#include "wx_include.hpp"

fsweep::AboutDialog::AboutDialog(wxWindow* parent) : wxDialog(parent, wxID_ANY, "About FossSweeper")
{
  auto* const sizer = new wxBoxSizer(wxVERTICAL);

  auto* const header = new wxStaticText(this, wxID_ANY, "FossSweeper");
  auto header_font = header->GetFont();
  header_font.SetPointSize(24);
  header_font.SetWeight(wxFONTWEIGHT_BOLD);
  header->SetFont(header_font);
  sizer->Add(header, 0, wxALIGN_CENTER | wxUP | wxLEFT | wxRIGHT, 20);

  std::stringstream version_ss("");
  version_ss << "v" << FSWEEP_VERSION << " " << FSWEEP_SHORT_HASH;
  auto* const version = new wxStaticText(this, wxID_ANY, version_ss.str().data());
  auto version_font = version->GetFont();
  version_font.SetPointSize(18);
  version_font.SetWeight(wxFONTWEIGHT_LIGHT);
  version_font.SetStyle(wxFONTSTYLE_ITALIC);
  version->SetFont(version_font);
  sizer->Add(version, 0, wxALIGN_CENTER | wxDOWN | wxLEFT | wxRIGHT, 20);

  auto* const subtext =
      new wxStaticText(this, wxID_ANY, "An open source clone of a popular mine avoidance game.");
  auto subtext_font = subtext->GetFont();
  subtext_font.SetStyle(wxFONTSTYLE_ITALIC);
  sizer->Add(subtext, 0, wxALIGN_CENTER | wxALL, 20);
  auto* const info_sizer = new wxBoxSizer(wxHORIZONTAL);
  info_sizer->AddSpacer(20);
  auto* const info_text = new wxStaticText(
      this, wxID_ANY,
      "FossSweeper is released under the GNU General Public License version 3. It was created "
      "using the wxWidgets library, which is released under the GNU General Public License "
      "version 2 and is covered by FossSweeper's license.");
  info_text->Wrap(540);
  info_sizer->AddSpacer(20);
  info_sizer->Add(info_text, 0, wxALIGN_CENTER, 20);
  info_sizer->AddSpacer(20);
  sizer->Add(info_sizer);

  sizer->AddSpacer(20);

  auto* const itch_sizer = new wxBoxSizer(wxHORIZONTAL);
  itch_sizer->Add(new wxStaticText(this, wxID_ANY, "Download Page: "));
  itch_sizer->Add(new wxHyperlinkCtrl(this, wxID_ANY, "https://journeyman-dev.itch.io/FossSweeper",
                                      "https://journeyman-dev.itch.io/FossSweeper"));
  sizer->Add(itch_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  auto* const source_sizer = new wxBoxSizer(wxHORIZONTAL);
  source_sizer->Add(new wxStaticText(this, wxID_ANY, _("Source Code: ")));
  source_sizer->Add(new wxHyperlinkCtrl(this, wxID_ANY,
                                        "https://github.com/Journeyman-dev/FossSweeper",
                                        "https://github.com/Journeyman-dev/FossSweeper"));
  sizer->Add(source_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  auto* const wxwidgets_sizer = new wxBoxSizer(wxHORIZONTAL);
  wxwidgets_sizer->Add(new wxStaticText(this, wxID_ANY, "wxWidgets: "));
  wxwidgets_sizer->Add(new wxHyperlinkCtrl(this, wxID_ANY, "https://www.wxwidgets.org/",
                                           "https://www.wxwidgets.org/"));
  sizer->Add(wxwidgets_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  auto* const gnu_sizer = new wxBoxSizer(wxHORIZONTAL);
  gnu_sizer->Add(new wxStaticText(this, wxID_ANY, "License Info: "));
  gnu_sizer->Add(new wxHyperlinkCtrl(this, wxID_ANY, "https://www.gnu.org/licenses/gpl-3.0.en.html",
                                     "https://www.gnu.org/licenses/gpl-3.0.en.html"));
  sizer->Add(gnu_sizer, 0, wxALIGN_CENTER | wxALL, 5);

  auto* const button_sizer = new wxBoxSizer(wxHORIZONTAL);
  auto* const copy_version_button = new wxButton(this, wxID_ANY, "Copy Version");
  Bind(wxEVT_BUTTON, &fsweep::AboutDialog::OnCopyVersion, this, copy_version_button->GetId());
  button_sizer->Add(copy_version_button, 0, wxALIGN_CENTER | wxALL, 10);
  auto* const copy_hash_button = new wxButton(this, wxID_ANY, "Copy Hash");
  Bind(wxEVT_BUTTON, &fsweep::AboutDialog::OnCopyHash, this, copy_hash_button->GetId());
  button_sizer->Add(copy_hash_button, 0, wxALIGN_CENTER | wxALL, 10);
  auto* const license_button = new wxButton(this, wxID_ANY, "License");
  Bind(wxEVT_BUTTON, &fsweep::AboutDialog::OnLicense, this, license_button->GetId());
  button_sizer->Add(license_button, 0, wxALIGN_CENTER | wxALL, 10);
  auto* const credits_button = new wxButton(this, wxID_ANY, "Credits");
  Bind(wxEVT_BUTTON, &fsweep::AboutDialog::OnCredits, this, credits_button->GetId());
  button_sizer->Add(credits_button, 0, wxALIGN_CENTER | wxALL, 10);
  auto* const close_button = new wxButton(this, wxID_OK, "Close");
  close_button->SetDefault();
  button_sizer->Add(close_button, 0, wxALIGN_CENTER | wxALL, 10);
  sizer->Add(button_sizer, 0, wxALIGN_CENTER | wxALL, 0);

  this->SetSizerAndFit(sizer);
  sizer->Layout();
}

void fsweep::AboutDialog::OnCredits(wxCommandEvent& WXUNUSED(e))
{
  auto credits_dialog = fsweep::createCreditsDialog(this);
  credits_dialog.ShowModal();
}

void fsweep::AboutDialog::OnLicense(wxCommandEvent& WXUNUSED(e))
{
  auto license_dialog = fsweep::createLicenseDialog(this);
  license_dialog.ShowModal();
}

void fsweep::AboutDialog::OnCopyVersion(wxCommandEvent& e)
{
  if (wxTheClipboard->Open())
  {
    wxTheClipboard->SetData(new wxTextDataObject(FSWEEP_VERSION));
    wxTheClipboard->Close();
  }
}

void fsweep::AboutDialog::OnCopyHash(wxCommandEvent& e)
{
  if (wxTheClipboard->Open())
  {
    wxTheClipboard->SetData(new wxTextDataObject(FSWEEP_SHORT_HASH));
    wxTheClipboard->Close();
  }
}