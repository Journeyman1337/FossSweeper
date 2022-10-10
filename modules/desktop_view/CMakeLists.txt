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

add_executable(fsweep_desktop_view WIN32 MACOSX_BUNDLE "")
target_include_directories(fsweep_desktop_view
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        "${FSWEEP_CMAKE_SOURCE_DIR}/extern/wxWidgets/include"
)
add_subdirectory(src)
add_subdirectory(rc)
target_link_libraries(fsweep_desktop_view
    PUBLIC
        fsweep::generated
        fsweep::model
        wx::net
        wx::core
        wx::base
)
set_target_properties(fsweep_desktop_view
    PROPERTIES
    OUTPUT_NAME "FossSweeper"
    CXX_STANDARD ${FSWEEP_CXX_STANDARD}
    CXX_STANDARD_REQUIRED TRUE
)
if(FSWEEP_INSTALL_DESKTOP)
    include(GNUInstallDirs)
    install(TARGETS fsweep_desktop_view DESTINATION ${CMAKE_INSTALL_BINDIR})
    install(FILES "${FSWEEP_CMAKE_SOURCE_DIR}/COPYING" DESTINATION ${CMAKE_INSTALL_BINDIR})
    if(UNIX AND NOT APPLE)
      install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/rc/fosssweeper.png" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/16x16/apps")
      install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/rc/fosssweeper.desktop" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/applications")
    elseif(APPLE)
        string(APPEND CMAKE_INSTALL_PREFIX "FossSweeper.app/Contents")
    endif()
    set(CPACK_RESOURCE_FILE_LICENSE "${FSWEEP_CMAKE_SOURCE_DIR}/COPYING")
    set(CPACK_STRIP_FILES TRUE)
    set(CPACK_THREADS 0)
    include(CPack)
endif()
