set(PLUGIN "taskbar")

set(HEADERS
    ukuitaskbar.h
    ukuitaskbutton.h
    ukuitaskbarconfiguration.h
    ukuitaskbarplugin.h
    ukuitaskgroup.h
    ukuigrouppopup.h
)

set(SOURCES
    ukuitaskbar.cpp
    ukuitaskbutton.cpp
    ukuitaskbarconfiguration.cpp
    ukuitaskbarplugin.cpp
    ukuitaskgroup.cpp
    ukuigrouppopup.cpp
)

set(UIS
    ukuitaskbarconfiguration.ui
)

set(LIBRARIES
    lxqt
    lxqt-globalkeys
    Qt5Xdg
)

BUILD_UKUI_PLUGIN(${PLUGIN})
