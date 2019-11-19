set(PLUGIN "recyclebin")

set(HEADERS
    recyclebin.h
)

set(SOURCES
    recyclebin.cpp
)

set(UIS
)

set(LIBRARIES
    lxqt
    lxqt-globalkeys
    lxqt-globalkeys-ui
)
install(FILES
    img/recyclebin.svg
    DESTINATION "${LXQT_DATA_DIR}/plugin-recyclebin/img"
    COMPONENT Runtime
)
BUILD_UKUI_PLUGIN(${PLUGIN})
