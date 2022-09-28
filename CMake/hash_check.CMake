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

include("${CMAKE_SCRIPT_DIR}/get_short_hash.CMake")
get_short_hash("${GIT_SOURCE_DIR}" FSWEEP_SHORT_HASH)
set(CACHE_FILE "${CACHE_DIR}/short_hash.cache")
if (EXISTS "${CACHE_FILE}")
    file(STRINGS "${CACHE_FILE}" CACHE_FILE_CONTENT)
    LIST(GET CACHE_FILE_CONTENT 0 CACHE_SHORT_HASH)
endif()
if(NOT "${FSWEEP_SHORT_HASH}" STREQUAL "${CACHE_SHORT_HASH}")
    configure_file("${HASH_INPUT_FILE}" "${HASH_OUTPUT_FILE}")
    file(WRITE "${CACHE_FILE}" "${FSWEEP_SHORT_HASH}")
endif()
