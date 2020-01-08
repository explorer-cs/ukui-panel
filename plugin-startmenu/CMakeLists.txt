set(PLUGIN "startmenu")

set(HEADERS
    startmenu.h
)

set(SOURCES
    startmenu.cpp
)

set(UIS
)

install(FILES
    img/startmenu.svg  img/taskview.svg img/ukui-panel_zh_CN.qm
    DESTINATION "${LXQT_DATA_DIR}/plugin-startmenu/img"
    COMPONENT Runtime
)
set(UKUI_TRANSLATIONS_DAT "/usr/local/share/")
file(GLOB UKUI_TRANSLATIONS_SOURCE ${UKUI_TRANSLATIONS_DAT}ukui/translations/ukui-panel/ukui-panel_zh_CN.qm )
BUILD_UKUI_PLUGIN(${PLUGIN})
