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

# configure version file
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/version.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/include/fsweep/version.hpp")
# configure short hash file
include("${FSWEEP_CMAKE_SCRIPT_DIR}/get_short_hash.CMake")
get_short_hash("${FSWEEP_CMAKE_SOURCE_DIR}" "FSWEEP_SHORT_HASH")
set(FSWEEP_HASH_INPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/short_hash.hpp.in")
set(FSWEEP_HASH_OUTPUT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/include/fsweep/short_hash.hpp")
configure_file("${FSWEEP_HASH_INPUT_FILE}" "${FSWEEP_HASH_OUTPUT_FILE}")
# save short hash cache
file(WRITE "${CMAKE_BINARY_DIR}/short_hash.cache" "${FSWEEP_SHORT_HASH}")
# create target to update short hash if it changes
add_custom_target(fsweep_short_hash_check 
    COMMAND ${CMAKE_COMMAND}
    -D HASH_INPUT_FILE="${FSWEEP_HASH_INPUT_FILE}"
    -D HASH_OUTPUT_FILE="${FSWEEP_HASH_OUTPUT_FILE}"
    -D CMAKE_SCRIPT_DIR="${FSWEEP_CMAKE_SCRIPT_DIR}"
    -D CACHE_DIR="${CMAKE_BINARY_DIR}"
    -D GIT_SOURCE_DIR="${FSWEEP_CMAKE_SOURCE_DIR}"
    -P "${FSWEEP_CMAKE_SCRIPT_DIR}/hash_check.CMake"
    BYPRODUCTS "${CMAKE_BINARY_DIR}/short_hash.cache"
)
# embed license and credits text
include("${FSWEEP_CMAKE_SCRIPT_DIR}/embed_string.CMake")
embed_string("FSWEEP_LICENSE_TEXT" "${FSWEEP_CMAKE_SOURCE_DIR}/COPYING" "${CMAKE_CURRENT_SOURCE_DIR}/src/license.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/license.cpp")
embed_string("FSWEEP_CREDITS_TEXT" "${FSWEEP_CMAKE_SOURCE_DIR}/CREDITS" "${CMAKE_CURRENT_SOURCE_DIR}/src/credits.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/credits.cpp")

# setup library target
add_library(fsweep_generated STATIC "")
add_library(fsweep::generated ALIAS fsweep_generated)
target_include_directories(fsweep_generated
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)
add_subdirectory(src)
add_dependencies(fsweep_generated fsweep_short_hash_check)
set_target_properties(fsweep_generated
    PROPERTIES
    OUTPUT_NAME "fsweepgenerated"
    CXX_STANDARD ${FSWEEP_CXX_STANDARD}
    CXX_STANDARD_REQUIRED TRUE
)
