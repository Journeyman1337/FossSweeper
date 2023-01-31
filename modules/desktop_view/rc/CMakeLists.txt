# SPDX-FileCopyrightText: 2022-2023 Daniel Valcour <fosssweeper@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later

#
# Copyright (c) 2022-2023 Daniel Valcour
#
# This file is part of FossSweeper.
# 
# FossSweeper is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
# 
# FossSweeper is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along with FossSweeper. If not, see <https://www.gnu.org/licenses/>.
# 

if(WIN32)
    target_sources(fsweep_desktop_view
        PRIVATE
            "fosssweeper.rc"
    )
elseif(APPLE)
    set_source_files_properties("$fosssweeper.icns"
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
              MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/osxbundle.plist.in"
    )
    target_sources(fsweep_desktop_view
        PRIVATE
            "fosssweeper.icns"
    )
elseif(UNIX)
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/fosssweeper.desktop.in" "${CMAKE_CURRENT_SOURCE_DIR}/fosssweeper.desktop")
        target_sources(fsweep_desktop_view
        PRIVATE
            "fosssweeper.desktop"
    )
else()
    message(FATAL_ERROR "Unsupported platform for fsweep::desktop_view.")
endif()