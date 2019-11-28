set(PLUGIN "startmenu")

set(HEADERS
    startmenu.h
)

set(SOURCES
    startmenu.cpp
)

set(UIS
)

set(LIBRARIES
    lxqt
    lxqt-globalkeys
    lxqt-globalkeys-ui
)

find_package(GTK2 2.6 REQUIRED gtk)
include_directories(${GTK2_INCLUDE_DIRS})
ADD_DEFINITIONS(-DQT_NO_KEYWORDS)
link_libraries(${GTK2_LIBRARIES})

install(FILES
    img/startmenu.svg  img/taskview.svg
    DESTINATION "${LXQT_DATA_DIR}/plugin-startmenu/img"
    COMPONENT Runtime
)
set(UKUI_TRANSLATIONS_DAT "/usr/local/share/")
file(GLOB UKUI_TRANSLATIONS_SOURCE ${UKUI_TRANSLATIONS_DAT}ukui/translations/ukui-panel/ukui-panel_zh_CN.qm )
install (FILES ${UKUI_TRANSLATIONS_SOURCE}
    DESTINATION "${UKUI_TRANSLATIONS_DAT}lxqt/translations/ukui-panel"
    )
install(DIRECTORY "${UKUI_TRANSLATIONS_DAT}lxqt/translations/ukui-panel"
    DESTINATION "${UKUI_TRANSLATIONS_DAT}lxqt/translations")



BUILD_UKUI_PLUGIN(${PLUGIN})
