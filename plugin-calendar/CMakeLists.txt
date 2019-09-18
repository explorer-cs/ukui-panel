
set(PLUGIN "calendar")

set(HEADERS
    ukuicalendar.h
    ukuiwebviewdialog.h
)

set(SOURCES
    ukuicalendar.cpp
    ukuiwebviewdialog.cpp
)

set(UIS
    ukuiwebviewdialog.ui
)

find_package(Qt5WebKit)
find_package(Qt5WebKitWidgets)
find_package(PkgConfig)

#configure_file(no_keywords link_pkgconfig)

include_directories(/usr/include/glib-2.0/ /usr/lib/x86_64-linux-gnu/glib-2.0/include/)

ADD_DEFINITIONS(-DQT_NO_KEYWORDS)
link_libraries(libQt5WebKitWidgets.so.5 libQt5WebKit.so.5 glib-2.0.so)
install(DIRECTORY html/
        DESTINATION ${PACKAGE_DATA_DIR}/plugin-calendar/html)

install(DIRECTORY style/
        DESTINATION ${PACKAGE_DATA_DIR}/plugin-calendar/style)

#install(FILES ukui-calendar.rc calendar-button-bg.png
#        DESTINATION "${PACKAGE_DATA_DIR}/plugin-calendar")

#ADD_DEFINITIONS(-DQT_NO_KEYWORDS)
BUILD_UKUI_PLUGIN(${PLUGIN})
