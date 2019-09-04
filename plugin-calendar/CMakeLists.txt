set(PLUGIN "calendar")

set(HEADERS
    ukuicalendar.h
)

set(SOURCES
    ukuicalendar.cpp
)

find_package(Qt5WebKit)
find_package(Qt5WebKitWidgets)

link_libraries(libQt5WebKitWidgets.so.5 libQt5WebKit.so.5)

# note the trailing slash
install(DIRECTORY html/
        DESTINATION ${PACKAGE_DATA_DIR}/plugin-calendar/html)

install(DIRECTORY style/
        DESTINATION ${PACKAGE_DATA_DIR}/plugin-calendar/style)

#install(FILES ukui-calendar.rc calendar-button-bg.png
#        DESTINATION "${PACKAGE_DATA_DIR}/plugin-calendar")

BUILD_UKUI_PLUGIN(${PLUGIN})
