
add_library(Qt5::OpenGLRendererPlugin MODULE IMPORTED)

set(_Qt5OpenGLRendererPlugin_MODULE_DEPENDENCIES "3DRender;3DCore;Gui;3DRender;3DCore;OpenGLExtensions;Gui;Core;Core")

foreach(_module_dep ${_Qt5OpenGLRendererPlugin_MODULE_DEPENDENCIES})
    if(NOT Qt5${_module_dep}_FOUND)
        find_package(Qt5${_module_dep}
            1.0.0 ${_Qt53DRender_FIND_VERSION_EXACT}
            ${_Qt53DRender_DEPENDENCIES_FIND_QUIET}
            ${_Qt53DRender_FIND_DEPENDENCIES_REQUIRED}
            PATHS "${CMAKE_CURRENT_LIST_DIR}/.." NO_DEFAULT_PATH
        )
    endif()
endforeach()

_qt5_3DRender_process_prl_file(
    "${_qt53DRender_install_prefix}/plugins/renderers/libopenglrenderer.prl" RELEASE
    _Qt5OpenGLRendererPlugin_STATIC_RELEASE_LIB_DEPENDENCIES
    _Qt5OpenGLRendererPlugin_STATIC_RELEASE_LINK_FLAGS
)


set_property(TARGET Qt5::OpenGLRendererPlugin PROPERTY INTERFACE_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Qt53DRender_OpenGLRendererPlugin_Import.cpp"
)

_populate_3DRender_plugin_properties(OpenGLRendererPlugin RELEASE "renderers/libopenglrenderer.a" FALSE)

list(APPEND Qt53DRender_PLUGINS Qt5::OpenGLRendererPlugin)
set_property(TARGET Qt5::3DRender APPEND PROPERTY QT_ALL_PLUGINS_renderers Qt5::OpenGLRendererPlugin)
# $<GENEX_EVAL:...> wasn't added until CMake 3.12, so put a version guard around it
if(CMAKE_VERSION VERSION_LESS "3.12")
    set(_manual_plugins_genex "$<TARGET_PROPERTY:QT_PLUGINS>")
    set(_plugin_type_genex "$<TARGET_PROPERTY:QT_PLUGINS_renderers>")
    set(_no_plugins_genex "$<TARGET_PROPERTY:QT_NO_PLUGINS>")
else()
    set(_manual_plugins_genex "$<GENEX_EVAL:$<TARGET_PROPERTY:QT_PLUGINS>>")
    set(_plugin_type_genex "$<GENEX_EVAL:$<TARGET_PROPERTY:QT_PLUGINS_renderers>>")
    set(_no_plugins_genex "$<GENEX_EVAL:$<TARGET_PROPERTY:QT_NO_PLUGINS>>")
endif()
set(_user_specified_genex
    "$<IN_LIST:Qt5::OpenGLRendererPlugin,${_manual_plugins_genex};${_plugin_type_genex}>"
)
set(_user_specified_genex_versionless
    "$<IN_LIST:Qt::OpenGLRendererPlugin,${_manual_plugins_genex};${_plugin_type_genex}>"
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
                "$<STREQUAL:$<TARGET_PROPERTY:Qt5::OpenGLRendererPlugin,QT_PLUGIN_EXTENDS>,Qt::3DRender>,"
                "$<STREQUAL:$<TARGET_PROPERTY:Qt5::OpenGLRendererPlugin,QT_PLUGIN_EXTENDS>,>"
            ">,"
            "$<NOT:$<IN_LIST:Qt5::OpenGLRendererPlugin,${_no_plugins_genex}>>,"
            "$<NOT:$<IN_LIST:Qt::OpenGLRendererPlugin,${_no_plugins_genex}>>"
        ">"
    ">:Qt5::OpenGLRendererPlugin>"
)
set_property(TARGET Qt5::3DRender APPEND PROPERTY INTERFACE_LINK_LIBRARIES
    ${_plugin_genex}
)
set_property(TARGET Qt5::OpenGLRendererPlugin APPEND PROPERTY INTERFACE_LINK_LIBRARIES
    "Qt5::3DRender;Qt5::3DCore;Qt5::Gui;Qt5::3DRender;Qt5::3DCore;Qt5::OpenGLExtensions;Qt5::Gui;Qt5::Core;Qt5::Core"
)
set_property(TARGET Qt5::OpenGLRendererPlugin PROPERTY QT_PLUGIN_TYPE "renderers")
set_property(TARGET Qt5::OpenGLRendererPlugin PROPERTY QT_PLUGIN_EXTENDS "")
set_property(TARGET Qt5::OpenGLRendererPlugin PROPERTY QT_PLUGIN_CLASS_NAME "OpenGLRendererPlugin")
