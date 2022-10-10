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
if(WIN32)
    target_sources(fsweep_desktop_view
        PRIVATE
            "fosssweeper.rc"
    )
elseif(APPLE)
    add_executable(fsweep_desktop_view MACOSX_BUNDLE ""  )
    set_source_files_properties("${CMAKE_CURRENT_SOURCE_DIR}/rc/fosssweeper.icns"
        PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources"
    )
    set_target_properties(fsweep_desktop_view PROPERTIES
              MACOSX_BUNDLE_BUNDLE_NAME "FossSweeper"
              MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
              MACOSX_BUNDLE_INFO_STRING "An open source clone of a popular mine avoidance game."
              MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
              MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION}
              MACOSX_BUNDLE_ICON_FILE "fosssweeper.icns"
              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/rc/osxbundle.plist.in"
    )
    target_sources(fsweep_desktop_view
        PRIVATE
            "fosssweeper.icns"
    )
elseif(UNIX)
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/rc/fosssweeper.desktop.in" "${CMAKE_CURRENT_SOURCE_DIR}/rc/fosssweeper.desktop")
        target_sources(fsweep_desktop_view
        PRIVATE
            "fosssweeper.desktop"
    )
else()
    message(FATAL_ERROR "Unsupported platform for fsweep::desktop_view.")
endif()
target_include_directories(fsweep_desktop_view
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src/"
        "${FSWEEP_CMAKE_SOURCE_DIR}/extern/wxWidgets/include"
)
target_sources(fsweep_desktop_view
    PUBLIC
        "AboutDialog.cpp"
        "ConfigDialog.cpp"
        "DesktopApp.cpp"
        "DesktopTimer.cpp"
        "DesktopView.cpp"
        "GameFrame.cpp"
        "GamePanel.cpp"
        "icon.cpp"
        "main.cpp"
        "PixelScaleDialog.cpp"
        "spritesheet.cpp"
        "TextDialog.cpp"
        "AboutDialog.hpp"
        "DesktopApp.hpp"
        "DesktopTimer.hpp"
        "DesktopView.hpp"
        "GameFrame.hpp"
        "GamePanel.hpp"
        "GamePanelState.hpp"
        "icon.hpp"
        "PixelScaleDialog.hpp"
        "spritesheet.hpp"
        "TextDialog.hpp"
        "wx_include.hpp"
)
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
