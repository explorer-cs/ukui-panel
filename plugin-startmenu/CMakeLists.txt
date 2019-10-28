set(PLUGIN "startmenu")

set(HEADERS
    startmenu.h
    actionview.h
    lxqtmainmenuconfiguration.h
    menustyle.h
)

set(SOURCES
    startmenu.cpp
    actionview.cpp
    lxqtmainmenuconfiguration.cpp
    menustyle.cpp
)

set(UIS
    startmenu.ui
    lxqtmainmenuconfiguration.ui
)

set(LIBRARIES
    lxqt
    lxqt-globalkeys
    lxqt-globalkeys-ui
)

install(DIRECTORY img/
        DESTINATION ${PACKAGE_DATA_DIR}/plugin-startmenu/img)
install(DIRECTORY /usr/local/share/ukui/translations/ukui-panel
    DESTINATION /usr/local/share/lxqt/translations)
BUILD_UKUI_PLUGIN(${PLUGIN})
