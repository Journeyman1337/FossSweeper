# SPDX-FileCopyrightText: 2022 Daniel Valcour <fosssweeper@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later

#
# Copyright (c) 2022 Daniel Valcour
#
# This file is part of FossSweeper.
# 
# FossSweeper is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# 
# FossSweeper is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along with FossSweeper. If not, see <https://www.gnu.org/licenses/>.
# 

cmake_minimum_required(VERSION 3.19)

project(
    fosssweeper
    VERSION 0.5.0.0
    DESCRIPTION "An open source clone of a popular mine avoidance game"
    LANGUAGES C CXX
)

set(FSWEEP_CXX_STANDARD 20)
set(FSWEEP_CMAKE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(FSWEEP_CMAKE_SCRIPT_DIR "${FSWEEP_CMAKE_SOURCE_DIR}/CMake/")

if(DEFINED PROJECT_NAME)
  set(FSWEEP_MAIN_PROJECT ON)
else()
  set(FSWEEP_MAIN_PROJECT OFF)
endif()

option(FSWEEP_MONOLITHIC "Find wxWidgets in the extern folder and add catch2 via CMake fetch_content." ${FSWEEP_MAIN_PROJECT})
option(FSWEEP_BUILD_DESKTOP "Build the desktop application." ON)
option(FSWEEP_BUILD_TESTS "Enable the automatic test framework." ON)
option(FSWEEP_INSTALL_DESKTOP "Install the desktop application using CPack." ON)

if (FSWEEP_MONOLITHIC)
    add_subdirectory(extern)
endif()

add_subdirectory(modules)
