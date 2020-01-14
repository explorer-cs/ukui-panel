set(PLUGIN "taskview")

set(HEADERS
    taskview.h
)

set(SOURCES
    taskview.cpp
)

set(UIS
)
set(LIBRARIES
    Qt5Xdg
)

install(FILES
    img/taskview.svg
    DESTINATION "${PACKAGE_DATA_DIR}/plugin-taskview/img"
    COMPONENT Runtime
)
BUILD_UKUI_PLUGIN(${PLUGIN})
