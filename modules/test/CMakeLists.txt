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

if(NOT FSWEEP_MONOLITHIC)
    find_package(Catch2 CONFIG REQUIRED)
else()
    Include(FetchContent)

    FetchContent_Declare(
      Catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2.git
      GIT_TAG        v3.1.0
    )

    FetchContent_MakeAvailable(Catch2)
endif()
add_executable(fsweep_test_auto "")
target_include_directories(fsweep_test_auto
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_sources(fsweep_test_auto
    PRIVATE
        "button_position_test.cpp"
        "button_test.cpp"
        "desktop_model_test.cpp"
        "game_configuration_test.cpp"
        "lcd_number_test.cpp"
        "game_model_test.cpp"
        "TestTimer.cpp"
        "TestTimer.hpp"
)
target_link_libraries(fsweep_test_auto
    PRIVATE
        Catch2::Catch2WithMain
        fsweep::generated
        fsweep::model
)
set_target_properties(fsweep_test_auto
    PROPERTIES
    OUTPUT_NAME "fsweep tests"
    CXX_STANDARD ${FSWEEP_CXX_STANDARD}
    CXX_STANDARD_REQUIRED TRUE
)
include(CTest)
include(Catch)
catch_discover_tests(
  fsweep_test_auto
  TEST_PREFIX "unittests."
  REPORTER junit
  OUTPUT_DIR ${CMAKE_BINARY_DIR}
  OUTPUT_PREFIX "unittests."
  OUTPUT_SUFFIX .xml
)
