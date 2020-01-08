set(PLUGIN "taskview")

set(HEADERS
    taskview.h
)

set(SOURCES
    taskview.cpp
)

set(UIS
)

install(FILES
    img/taskview.svg
    DESTINATION "${LXQT_DATA_DIR}/plugin-taskview/img"
    COMPONENT Runtime
)
BUILD_UKUI_PLUGIN(${PLUGIN})
