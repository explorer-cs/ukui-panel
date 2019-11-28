set(PLUGIN "powerswitch")

set(HEADERS
    powerswitch.h
)

set(SOURCES
    powerswitch.cpp
)

set(UIS
)

set(LIBRARIES
    lxqt
    lxqt-globalkeys
    lxqt-globalkeys-ui
)
install(FILES
    img/powerswitch.svg
    DESTINATION "${LXQT_DATA_DIR}/plugin-powerswitch/img"
    COMPONENT Runtime
)
BUILD_UKUI_PLUGIN(${PLUGIN})
