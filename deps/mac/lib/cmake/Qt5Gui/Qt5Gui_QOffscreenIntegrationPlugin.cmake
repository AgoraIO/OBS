
add_library(Qt5::QOffscreenIntegrationPlugin MODULE IMPORTED)

set(_Qt5QOffscreenIntegrationPlugin_MODULE_DEPENDENCIES "EventDispatcherSupport;FontDatabaseSupport;Gui;Gui;Core;Core")

foreach(_module_dep ${_Qt5QOffscreenIntegrationPlugin_MODULE_DEPENDENCIES})
    if(NOT Qt5${_module_dep}_FOUND)
        find_package(Qt5${_module_dep}
            1.0.0 ${_Qt5Gui_FIND_VERSION_EXACT}
            ${_Qt5Gui_DEPENDENCIES_FIND_QUIET}
            ${_Qt5Gui_FIND_DEPENDENCIES_REQUIRED}
            PATHS "${CMAKE_CURRENT_LIST_DIR}/.." NO_DEFAULT_PATH
        )
    endif()
endforeach()

_qt5_Gui_process_prl_file(
    "${_qt5Gui_install_prefix}/plugins/platforms/libqoffscreen.prl" RELEASE
    _Qt5QOffscreenIntegrationPlugin_STATIC_RELEASE_LIB_DEPENDENCIES
    _Qt5QOffscreenIntegrationPlugin_STATIC_RELEASE_LINK_FLAGS
)


set_property(TARGET Qt5::QOffscreenIntegrationPlugin PROPERTY INTERFACE_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Qt5Gui_QOffscreenIntegrationPlugin_Import.cpp"
)

_populate_Gui_plugin_properties(QOffscreenIntegrationPlugin RELEASE "platforms/libqoffscreen.a" FALSE)

list(APPEND Qt5Gui_PLUGINS Qt5::QOffscreenIntegrationPlugin)
set_property(TARGET Qt5::Gui APPEND PROPERTY QT_ALL_PLUGINS_platforms Qt5::QOffscreenIntegrationPlugin)
# $<GENEX_EVAL:...> wasn't added until CMake 3.12, so put a version guard around it
if(CMAKE_VERSION VERSION_LESS "3.12")
    set(_manual_plugins_genex "$<TARGET_PROPERTY:QT_PLUGINS>")
    set(_plugin_type_genex "$<TARGET_PROPERTY:QT_PLUGINS_platforms>")
    set(_no_plugins_genex "$<TARGET_PROPERTY:QT_NO_PLUGINS>")
else()
    set(_manual_plugins_genex "$<GENEX_EVAL:$<TARGET_PROPERTY:QT_PLUGINS>>")
    set(_plugin_type_genex "$<GENEX_EVAL:$<TARGET_PROPERTY:QT_PLUGINS_platforms>>")
    set(_no_plugins_genex "$<GENEX_EVAL:$<TARGET_PROPERTY:QT_NO_PLUGINS>>")
endif()
set(_user_specified_genex
    "$<IN_LIST:Qt5::QOffscreenIntegrationPlugin,${_manual_plugins_genex};${_plugin_type_genex}>"
)
set(_user_specified_genex_versionless
    "$<IN_LIST:Qt::QOffscreenIntegrationPlugin,${_manual_plugins_genex};${_plugin_type_genex}>"
)
string(CONCAT _plugin_genex
    "$<$<OR:"
        # Add this plugin if it's in the list of manually specified plugins or in the list of
        # explicitly included plugin types.
        "${_user_specified_genex},"
        "${_user_specified_genex_versionless},"
        # Add this plugin if all of the following are true:
        # 1) the list of explicitly included plugin types is empty
        # 2) the QT_PLUGIN_EXTENDS property for the plugin is empty or equal to the current
        #    module name
        # 3) the user hasn't explicitly excluded the plugin.
        "$<AND:"
            "$<STREQUAL:${_plugin_type_genex},>,"
            "$<OR:"
                # FIXME: The value of CMAKE_MODULE_NAME seems to be wrong (e.g for Svg plugin
                # it should be Qt::Svg instead of Qt::Gui).
                "$<STREQUAL:$<TARGET_PROPERTY:Qt5::QOffscreenIntegrationPlugin,QT_PLUGIN_EXTENDS>,Qt::Gui>,"
                "$<STREQUAL:$<TARGET_PROPERTY:Qt5::QOffscreenIntegrationPlugin,QT_PLUGIN_EXTENDS>,>"
            ">,"
            "$<NOT:$<IN_LIST:Qt5::QOffscreenIntegrationPlugin,${_no_plugins_genex}>>,"
            "$<NOT:$<IN_LIST:Qt::QOffscreenIntegrationPlugin,${_no_plugins_genex}>>"
        ">"
    ">:Qt5::QOffscreenIntegrationPlugin>"
)
set_property(TARGET Qt5::Gui APPEND PROPERTY INTERFACE_LINK_LIBRARIES
    ${_plugin_genex}
)
set_property(TARGET Qt5::QOffscreenIntegrationPlugin APPEND PROPERTY INTERFACE_LINK_LIBRARIES
    "Qt5::EventDispatcherSupport;Qt5::FontDatabaseSupport;Qt5::Gui;Qt5::Gui;Qt5::Core;Qt5::Core"
)
set_property(TARGET Qt5::QOffscreenIntegrationPlugin PROPERTY QT_PLUGIN_TYPE "platforms")
set_property(TARGET Qt5::QOffscreenIntegrationPlugin PROPERTY QT_PLUGIN_EXTENDS "-")
set_property(TARGET Qt5::QOffscreenIntegrationPlugin PROPERTY QT_PLUGIN_CLASS_NAME "QOffscreenIntegrationPlugin")
