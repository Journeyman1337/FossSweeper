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

function(get_short_hash GIT_ROOT_DIR OUT_HASH_VAR)
    execute_process(
        COMMAND git rev-parse HEAD
        WORKING_DIRECTORY "${GIT_ROOT_DIRECTORY}"
        OUTPUT_VARIABLE OUTPUT
        RESULT_VARIABLE EXIT_CODE
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    set("${OUT_HASH_VAR}" "${OUTPUT}" PARENT_SCOPE)
    if(NOT EXIT_CODE EQUAL 0)
        message(WARNING "Failed to get git hash.")
        set("${OUT_HASH_VAR}" "FAILED TO GET HASH" PARENT_SCOPE)
    else()
        string(SUBSTRING "${OUTPUT}" 0 8 OUTPUT)
        set("${OUT_HASH_VAR}" "#${OUTPUT}" PARENT_SCOPE)
    endif()
endfunction()