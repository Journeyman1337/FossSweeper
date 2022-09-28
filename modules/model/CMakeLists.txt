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

set(FSWEEP_MODEL_SOURCE_FILES
    "Button.cpp"
    "GameConfiguration.cpp"
    "LcdNumber.cpp"
    "Model.cpp"
)
list(
    TRANSFORM FSWEEP_MODEL_SOURCE_FILES
    PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)
source_group("sources"
    FILES ${FSWEEP_MODEL_SOURCE_FILES}
)
set(FSWEEP_MODEL_INCLUDE_FILES
    "Button.hpp"
    "ButtonPosition.hpp"
    "ButtonState.hpp"
    "GameConfiguration.hpp"
    "GameDifficulty.hpp"
    "GameState.hpp"
    "LcdDigit.hpp"
    "LcdNumber.hpp"
    "Model.hpp"
)
list(
    TRANSFORM FSWEEP_MODEL_INCLUDE_FILES
    PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/include/fsweep/"
)
source_group("includes"
    FILES ${FSWEEP_MODEL_INCLUDE_FILES}
)
add_library(fsweep_model STATIC
    ${FSWEEP_MODEL_SOURCE_FILES}
    ${FSWEEP_MODEL_INCLUDE_FILES}
)
add_library(fsweep::model ALIAS fsweep_model)
target_precompile_headers(fsweep_model
    PUBLIC
        ${FSWEEP_MODEL_INCLUDE_FILES}
)
target_include_directories(fsweep_model
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)
target_link_libraries(fsweep_model
    PUBLIC
    	fsweep::generated
)
set_target_properties(fsweep_model
    PROPERTIES
    OUTPUT_NAME "fsweepmodel"
    CXX_STANDARD ${FSWEEP_CXX_STANDARD}
    CXX_STANDARD_REQUIRED TRUE
)
