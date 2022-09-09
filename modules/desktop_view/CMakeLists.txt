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

include(${FSWEEP_SOURCE_DIR}/CMake/embed_string.CMake)
embed_string("FSWEEP_LICENSE_TEXT" "${FSWEEP_SOURCE_DIR}/COPYING" "${CMAKE_CURRENT_SOURCE_DIR}/src/license.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/license.cpp")
embed_string("FSWEEP_CREDITS_TEXT" "${FSWEEP_SOURCE_DIR}/CREDITS" "${CMAKE_CURRENT_SOURCE_DIR}/src/credits.cpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/credits.cpp")

set(FSWEEP_DESKTOP_SOURCES
    "AboutDialog.cpp"
    "AboutDialog.hpp"
    "ConfigDialog.cpp"
    "ConfigDialog.hpp"
    "DesktopApp.cpp"
    "DesktopApp.hpp"
    "DesktopView.cpp"
    "DesktopView.hpp"
    "GameFrame.cpp"
    "GameFrame.hpp"
    "GamePanel.cpp"
    "GamePanel.hpp"
    "GamePanelState.hpp"
    "icon.cpp"
    "icon.hpp"
    "license.cpp"
    "license.hpp"
    "LicenseDialog.cpp"
    "LicenseDialog.hpp"
    "main.cpp"
    "PixelScaleDialog.cpp"
    "PixelScaleDialog.hpp"
    "spritesheet.cpp"
    "spritesheet.hpp"
    "wx_id.hpp"
    "wx_include.hpp"
)
list(
    TRANSFORM FSWEEP_DESKTOP_SOURCES
     PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/src/")
source_group("sources"
    FILES ${FSWEEP_DESKTOP_SOURCES}
)
if (WIN32)
    # wxWidgets requires this for win32.
    add_executable(fsweep_desktop_view WIN32
        ${FSWEEP_DESKTOP_SOURCES}
    )
else()
    add_executable(fsweep_desktop_view
        ${FSWEEP_DESKTOP_SOURCES}
    )
endif()
target_link_libraries(fsweep_desktop_view
    PUBLIC
        fsweep::model
        wx::net
        wx::core
        wx::base
)
target_include_directories(fsweep_desktop_view
    PUBLIC
        "${FSWEEP_SOURCE_DIR}/extern/wxWidgets/include"
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
    install(FILES "${FSWEEP_SOURCE_DIR}/COPYING" DESTINATION ${CMAKE_INSTALL_BINDIR})
    set(CPACK_RESOURCE_FILE_LICENSE "${FSWEEP_SOURCE_DIR}/COPYING")
    set(CPACK_STRIP_FILES TRUE)
    set(CPACK_THREADS 0)
    include(CPack)
endif()
