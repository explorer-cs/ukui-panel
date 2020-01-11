set(PLUGIN "segmentation")

set(HEADERS
<<<<<<< HEAD
    segmentation.h
)

set(SOURCES
    segmentation.cpp
=======
    startmenu.h
)

set(SOURCES
    startmenu.cpp
>>>>>>> master
)

set(UIS
)

install(FILES
<<<<<<< HEAD
    img/segmentation.svg img/segmentationh.svg
=======
    img/segmentation.svg
>>>>>>> master
    DESTINATION "${LXQT_DATA_DIR}/plugin-segmentation/img"
    COMPONENT Runtime
)
set(UKUI_TRANSLATIONS_DAT "/usr/local/share/")
file(GLOB UKUI_TRANSLATIONS_SOURCE ${UKUI_TRANSLATIONS_DAT}ukui/translations/ukui-panel/ukui-panel_zh_CN.qm )
BUILD_UKUI_PLUGIN(${PLUGIN})
