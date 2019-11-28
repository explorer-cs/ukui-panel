set(PROJECT ukui-panel)

set(PRIV_HEADERS
    panelpluginsmodel.h
    windownotifier.h
    ukuipanel.h
    ukuipanelapplication.h
    ukuipanelapplication_p.h
    ukuipanellayout.h
    plugin.h
    pluginsettings_p.h
    ukuipanellimits.h
    popupmenu.h
    pluginmoveprocessor.h
    ukuipanelpluginconfigdialog.h
    config/configpaneldialog.h
    config/configpanelwidget.h
    config/configpluginswidget.h
    config/addplugindialog.h
)

# using LXQt namespace in the public headers.
set(PUB_HEADERS
    ukuipanelglobals.h
    pluginsettings.h
    iukuipanelplugin.h
    iukuipanel.h
    comm_func.h
)

set(SOURCES
    main.cpp
    panelpluginsmodel.cpp
    windownotifier.cpp
    ukuipanel.cpp
    ukuipanelapplication.cpp
    ukuipanellayout.cpp
    plugin.cpp
    pluginsettings.cpp
    popupmenu.cpp
    pluginmoveprocessor.cpp
    ukuipanelpluginconfigdialog.cpp
    config/configpaneldialog.cpp
    config/configpanelwidget.cpp
    config/configpluginswidget.cpp
    config/addplugindialog.cpp
    comm_func.cpp
)

set(UI
    config/configpanelwidget.ui
    config/configpluginswidget.ui
    config/addplugindialog.ui
)

set(LIBRARIES
    lxqt
)

file(GLOB CONFIG_FILES resources/*.conf resources/*.qss)
############################################

add_definitions(-DCOMPILE_UKUI_PANEL)

set(PLUGIN_DESKTOPS_DIR "${CMAKE_INSTALL_FULL_DATAROOTDIR}/ukui/${PROJECT}")
add_definitions(-DPLUGIN_DESKTOPS_DIR=\"${PLUGIN_DESKTOPS_DIR}\")

if (WITH_SCREENSAVER_FALLBACK)
    message(STATUS "Building with conversion of deprecated 'screensaver' plugin")
    add_definitions(-DWITH_SCREENSAVER_FALLBACK "-DUKUI_LOCK_DESKTOP=\"${CMAKE_INSTALL_FULL_DATAROOTDIR}/applications/lxqt-lockscreen.desktop\"")
endif ()

project(${PROJECT})

set(QTX_LIBRARIES Qt5::Widgets Qt5::Xml Qt5::DBus)

# Translations
lxqt_translate_ts(QM_FILES SOURCES
    UPDATE_TRANSLATIONS
        ${UPDATE_TRANSLATIONS}
    SOURCES
        ${PUB_HEADERS}
        ${PRIV_HEADERS}
        ${SOURCES}
        ${UI}
    INSTALL_DIR
    "${UKUI_TRANSLATIONS_DIR}/${PROJECT_NAME}"
)

lxqt_app_translation_loader(SOURCES ${PROJECT_NAME})
add_subdirectory(dbus-server)
add_executable(${PROJECT}
    ${PUB_HEADERS}
    ${PRIV_HEADERS}
    ${QM_FILES}
    ${SOURCES}
    ${UI}
)

target_link_libraries(${PROJECT}
    ${LIBRARIES}
    ${QTX_LIBRARIES}
    KF5::WindowSystem
    ${STATIC_PLUGINS}
    dbus-server
)

install(TARGETS ${PROJECT} RUNTIME DESTINATION bin)
install(FILES ${CONFIG_FILES} DESTINATION ${CMAKE_INSTALL_DATADIR}/ukui)
install(FILES ${PUB_HEADERS} DESTINATION include/ukui)
install(FILES
    man/ukui-panel.1
    DESTINATION "${CMAKE_INSTALL_MANDIR}/man1"
    COMPONENT Runtime
)
install(FILES
    resources/ukui-panel.desktop
    DESTINATION "${LXQT_ETC_XDG_DIR}/autostart/"
    COMPONENT Runtime
)
message("^^^^^^^^^^^^^^LXQT_ETC_XDG_DIR"${LXQT_ETC_XDG_DIR})
