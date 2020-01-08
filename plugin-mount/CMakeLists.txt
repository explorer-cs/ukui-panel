set(PLUGIN "mount")

set(HEADERS
    ukuimountplugin.h
    button.h
    menudiskitem.h
    popup.h
    actions/deviceaction.h
    actions/deviceaction_info.h
    actions/deviceaction_menu.h
    actions/deviceaction_nothing.h
)

set(SOURCES
    ukuimountplugin.cpp
    button.cpp
    menudiskitem.cpp
    popup.cpp
    actions/deviceaction.cpp
    actions/deviceaction_info.cpp
    actions/deviceaction_menu.cpp
    actions/deviceaction_nothing.cpp
)



find_package(KF5Solid ${QT_MINIMUM_VERSION} REQUIRED)
set(LIBRARIES Qt5Xdg KF5::Solid)

BUILD_UKUI_PLUGIN(${PLUGIN})
