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

set(FSWEEP_DESKTOP_SOURCES
    "AboutDialog.cpp"
    "AboutDialog.hpp"
    "ConfigDialog.cpp"
    "ConfigDialog.hpp"
    "DesktopApp.cpp"
    "DesktopApp.hpp"
    "DesktopTimer.cpp"
    "DesktopTimer.hpp"
    "DesktopView.cpp"
    "DesktopView.hpp"
    "GameFrame.cpp"
    "GameFrame.hpp"
    "GamePanel.cpp"
    "GamePanel.hpp"
    "GamePanelState.hpp"
    "icon.cpp"
    "icon.hpp"
    "main.cpp"
    "PixelScaleDialog.cpp"
    "PixelScaleDialog.hpp"
    "spritesheet.cpp"
    "spritesheet.hpp"
    "TextDialog.cpp"
    "TextDialog.hpp"
    "wx_include.hpp"
)
list(
    TRANSFORM FSWEEP_DESKTOP_SOURCES
    PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/src/")
source_group("sources"
    FILES ${FSWEEP_DESKTOP_SOURCES}
)
if (WIN32)
    # windows resource file with the file icon for the exe
    set(FSWEEP_DESKTOP_RESOURCES
        "fosssweeper.rc"
    )
    list(
        TRANSFORM FSWEEP_DESKTOP_RESOURCES
        PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/rc/")
    source_group("resources"
        FILES ${FSWEEP_DESKTOP_RESOURCES}
    )
    # wxWidgets requires main to be WinMain in Win32
    add_executable(fsweep_desktop_view WIN32
        ${FSWEEP_DESKTOP_SOURCES}
        ${FSWEEP_DESKTOP_RESOURCES}
    )
elseif(APPLE)
    set(FSWEEP_MACOSX_BUNDLE_ICON_FILE "fosssweeper.icns")
    set(FSWEEP_DESKTOP_OSX_ICON "${CMAKE_CURRENT_SOURCE_DIR}/rc/${FSWEEP_MACOSX_BUNDLE_ICON_FILE}")

    add_executable(fsweep_desktop_view MACOSX_BUNDLE
        ${FSWEEP_DESKTOP_SOURCES}
        ${FSWEEP_DESKTOP_OSX_ICON}
    )
    set_source_files_properties(FSWEEP_DESKTOP_OSX_ICON 
        PROPERTIES
            MACOSX_PACKAGE_LOCATION "Resources"
    )
    set_target_properties(fsweep_desktop_view PROPERTIES
              MACOSX_BUNDLE_BUNDLE_NAME "FossSweeper"
              MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
              MACOSX_BUNDLE_INFO_STRING "An open source clone of a popular mine avoidance game."
              MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
              MACOSX_BUNDLE_LONG_VERSION_STRING ${PROJECT_VERSION}
              MACOSX_BUNDLE_ICON_FILE "${FSWEEP_MACOSX_BUNDLE_ICON_FILE}"
              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/rc/osxbundle.plist.in"
    )
elseif(UNIX)
    add_executable(fsweep_desktop_view
        ${FSWEEP_DESKTOP_SOURCES}
    )
else()
    message(FATAL_ERROR "Unsupported platform for fsweep::desktop_view.")
endif()
target_link_libraries(fsweep_desktop_view
    PUBLIC
        fsweep::generated
        fsweep::model
        wx::net
        wx::core
        wx::base
)
target_include_directories(fsweep_desktop_view
    PUBLIC
        "${FSWEEP_CMAKE_SOURCE_DIR}/extern/wxWidgets/include"
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
      configure_file("${CMAKE_CURRENT_SOURCE_DIR}/rc/fosssweeper.desktop.in" "${CMAKE_CURRENT_SOURCE_DIR}/rc/fosssweeper.desktop")
      install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/rc/fosssweeper.desktop" DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/applications")
    elseif(APPLE)
        string(APPEND CMAKE_INSTALL_PREFIX "FossSweeper.app/Contents")
    endif()
    set(CPACK_RESOURCE_FILE_LICENSE "${FSWEEP_CMAKE_SOURCE_DIR}/COPYING")
    set(CPACK_STRIP_FILES TRUE)
    set(CPACK_THREADS 0)
    include(CPack)
endif()
