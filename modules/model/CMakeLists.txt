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

add_library(fsweep_model STATIC "")
add_library(fsweep::model ALIAS fsweep_model)
target_include_directories(fsweep_model
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)
add_subdirectory(src)
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
