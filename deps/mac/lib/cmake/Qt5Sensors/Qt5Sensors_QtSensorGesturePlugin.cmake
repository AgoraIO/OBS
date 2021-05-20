
add_library(Qt5::QtSensorGesturePlugin MODULE IMPORTED)

set(_Qt5QtSensorGesturePlugin_MODULE_DEPENDENCIES "Sensors;Core")

foreach(_module_dep ${_Qt5QtSensorGesturePlugin_MODULE_DEPENDENCIES})
    if(NOT Qt5${_module_dep}_FOUND)
        find_package(Qt5${_module_dep}
            1.0.0 ${_Qt5Sensors_FIND_VERSION_EXACT}
            ${_Qt5Sensors_DEPENDENCIES_FIND_QUIET}
            ${_Qt5Sensors_FIND_DEPENDENCIES_REQUIRED}
            PATHS "${CMAKE_CURRENT_LIST_DIR}/.." NO_DEFAULT_PATH
        )
    endif()
endforeach()

_qt5_Sensors_process_prl_file(
    "${_qt5Sensors_install_prefix}/plugins/sensorgestures/libqtsensorgestures_plugin.prl" RELEASE
    _Qt5QtSensorGesturePlugin_STATIC_RELEASE_LIB_DEPENDENCIES
    _Qt5QtSensorGesturePlugin_STATIC_RELEASE_LINK_FLAGS
)


set_property(TARGET Qt5::QtSensorGesturePlugin PROPERTY INTERFACE_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/Qt5Sensors_QtSensorGesturePlugin_Import.cpp"
)

_populate_Sensors_plugin_properties(QtSensorGesturePlugin RELEASE "sensorgestures/libqtsensorgestures_plugin.a" FALSE)

list(APPEND Qt5Sensors_PLUGINS Qt5::QtSensorGesturePlugin)
set_property(TARGET Qt5::Sensors APPEND PROPERTY QT_ALL_PLUGINS_sensorgestures Qt5::QtSensorGesturePlugin)
# $<GENEX_EVAL:...> wasn't added until CMake 3.12, so put a version guard around it
if(CMAKE_VERSION VERSION_LESS "3.12")
    set(_manual_plugins_genex "$<TARGET_PROPERTY:QT_PLUGINS>")
    set(_plugin_type_genex "$<TARGET_PROPERTY:QT_PLUGINS_sensorgestures>")
    set(_no_plugins_genex "$<TARGET_PROPERTY:QT_NO_PLUGINS>")
else()
    set(_manual_plugins_genex "$<GENEX_EVAL:$<TARGET_PROPERTY:QT_PLUGINS>>")
    set(_plugin_type_genex "$<GENEX_EVAL:$<TARGET_PROPERTY:QT_PLUGINS_sensorgestures>>")
    set(_no_plugins_genex "$<GENEX_EVAL:$<TARGET_PROPERTY:QT_NO_PLUGINS>>")
endif()
set(_user_specified_genex
    "$<IN_LIST:Qt5::QtSensorGesturePlugin,${_manual_plugins_genex};${_plugin_type_genex}>"
)
set(_user_specified_genex_versionless
    "$<IN_LIST:Qt::QtSensorGesturePlugin,${_manual_plugins_genex};${_plugin_type_genex}>"
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
                "$<STREQUAL:$<TARGET_PROPERTY:Qt5::QtSensorGesturePlugin,QT_PLUGIN_EXTENDS>,Qt::Sensors>,"
                "$<STREQUAL:$<TARGET_PROPERTY:Qt5::QtSensorGesturePlugin,QT_PLUGIN_EXTENDS>,>"
            ">,"
            "$<NOT:$<IN_LIST:Qt5::QtSensorGesturePlugin,${_no_plugins_genex}>>,"
            "$<NOT:$<IN_LIST:Qt::QtSensorGesturePlugin,${_no_plugins_genex}>>"
        ">"
    ">:Qt5::QtSensorGesturePlugin>"
)
set_property(TARGET Qt5::Sensors APPEND PROPERTY INTERFACE_LINK_LIBRARIES
    ${_plugin_genex}
)
set_property(TARGET Qt5::QtSensorGesturePlugin APPEND PROPERTY INTERFACE_LINK_LIBRARIES
    "Qt5::Sensors;Qt5::Core"
)
set_property(TARGET Qt5::QtSensorGesturePlugin PROPERTY QT_PLUGIN_TYPE "sensorgestures")
set_property(TARGET Qt5::QtSensorGesturePlugin PROPERTY QT_PLUGIN_EXTENDS "-")
set_property(TARGET Qt5::QtSensorGesturePlugin PROPERTY QT_PLUGIN_CLASS_NAME "QtSensorGesturePlugin")
