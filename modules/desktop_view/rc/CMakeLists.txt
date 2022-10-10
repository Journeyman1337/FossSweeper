if(WIN32)
    target_sources(fsweep_desktop_view
        PRIVATE
            "fosssweeper.rc"
    )
elseif(APPLE)
    add_executable(fsweep_desktop_view MACOSX_BUNDLE ""  )
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