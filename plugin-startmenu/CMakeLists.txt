set(PLUGIN "startmenu")

set(HEADERS
    startmenu.h
    actionview.h
    lxqtmainmenuconfiguration.h
    menustyle.h
    src/color.h
    src/CommonUseWidget/commonusewidget.h
    src/CommonUseWidget/fullcommonusewidget.h
    src/FunctionWidget/fullfunctionbuttonwidget.h
    src/FunctionWidget/fullfunctionwidget.h
    src/FunctionWidget/functionbuttonwidget.h
    src/FunctionWidget/functionwidget.h
    src/LetterWidget/fullletterbuttonwidget.h
    src/LetterWidget/fullletterwidget.h
    src/LetterWidget/letterbuttonwidget.h
    src/LetterWidget/letterwidget.h
    src/MainViewWidget/mainviewwidget.h
    src/SearchResultWidget/fullsearchresultwidget.h
    src/SearchResultWidget/searchresultwidget.h
    src/SideBarWidget/sidebarwidget.h
    src/MainWindow/mainwindow.h


)

set(SOURCES
    startmenu.cpp
    actionview.cpp
    lxqtmainmenuconfiguration.cpp
    menustyle.cpp
    src/CommonUseWidget/commonusewidget.cpp
    src/CommonUseWidget/fullcommonusewidget.cpp
    src/FunctionWidget/fullfunctionbuttonwidget.cpp
    src/FunctionWidget/fullfunctionwidget.cpp
    src/FunctionWidget/functionbuttonwidget.cpp
    src/FunctionWidget/functionwidget.cpp
    src/LetterWidget/fullletterbuttonwidget.cpp
    src/LetterWidget/fullletterwidget.cpp
    src/LetterWidget/letterbuttonwidget.cpp
    src/LetterWidget/letterwidget.cpp
    src/MainViewWidget/mainviewwidget.cpp
    src/SearchResultWidget/fullsearchresultwidget.cpp
    src/SearchResultWidget/searchresultwidget.cpp
    src/SideBarWidget/sidebarwidget.cpp
    src/MainWindow/mainwindow.cpp



)

set(UIS
    startmenu.ui
    lxqtmainmenuconfiguration.ui
    src/CommonUseWidget/commonusewidget.ui
    src/CommonUseWidget/fullcommonusewidget.ui
    src/FunctionWidget/fullfunctionbuttonwidget.ui
    src/FunctionWidget/fullfunctionwidget.ui
    src/FunctionWidget/functionbuttonwidget.ui
    src/FunctionWidget/functionwidget.ui
    src/LetterWidget/fullletterbuttonwidget.ui
    src/LetterWidget/fullletterwidget.ui
    src/LetterWidget/letterbuttonwidget.ui
    src/LetterWidget/letterwidget.ui
    src/MainViewWidget/mainviewwidget.ui
    src/SearchResultWidget/fullsearchresultwidget.ui
    src/SearchResultWidget/searchresultwidget.ui
    src/SideBarWidget/sidebarwidget.ui
    src/MainWindow/mainwindow.ui



)

set(LIBRARIES
    lxqt
    lxqt-globalkeys
    lxqt-globalkeys-ui

)

install(DIRECTORY img/
        DESTINATION ${PACKAGE_DATA_DIR}/plugin-startmenu/img)
BUILD_UKUI_PLUGIN(${PLUGIN})
