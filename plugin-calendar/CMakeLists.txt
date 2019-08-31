set(PLUGIN "calendar")

set(HEADERS
    ukuicalendar.h
)

set(SOURCES
    ukuicalendar.cpp
)


find_package(Qt5WebKit)
find_package(Qt5WebKitWidgets)

include_directories(/usr/include/x86_64-linux-gnu/qt5/QtWebKitWidgets/)

link_directories(/usr/lib/x86_64-linux-gnu/)

link_libraries(libQt5WebKitWidgets.so.5 libQt5WebKit.so.5)

BUILD_UKUI_PLUGIN(${PLUGIN})
#BUILD_LXQT_PLUGIN(${PLUGIN})
