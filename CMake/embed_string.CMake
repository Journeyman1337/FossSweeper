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

function(embed_string VAR_NAME TEXT_FILE IN_FILE OUT_FILE)
    set(SOURCE "\"")
    file(STRINGS "${TEXT_FILE}" LINES)
    foreach(LINE ${LINES})   
    	string(FIND LINE "#" HASH_I)
    	if(HASH_I NOT EQUAL 0)
            string(REPLACE "\"" "\\\"" FORMATED_LINE ${LINE})
            set(SOURCE "${SOURCE}${FORMATED_LINE}\\n\"\n\"")
       	endif()
    endforeach()
    set(SOURCE "${SOURCE}\"")
    set(${VAR_NAME} "${SOURCE}")
    configure_file("${IN_FILE}"  "${OUT_FILE}")
endfunction()
