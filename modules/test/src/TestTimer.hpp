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

#ifndef FSWEEP_TEST_TIMER_HPP
#define FSWEEP_TEST_TIMER_HPP

#include <fsweep/Timer.hpp>

namespace fsweep
{
  class TestTimer : public fsweep::Timer
  {
   private:
    bool is_running = false;

   public:
    unsigned long GetGameTime() override;
    void Start() override;
    void Stop() override;
    bool GetIsRunning() const noexcept;
  };
}  // namespace fsweep

#endif