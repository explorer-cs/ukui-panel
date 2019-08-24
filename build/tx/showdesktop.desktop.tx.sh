[ -f /home/kylin/panel/ukui-panel-3.0/plugin-showdesktop/resources/showdesktop.desktop.in ] || exit 0
echo '[lxde-qt.showdesktop_desktop]'
echo 'type = DESKTOP'
echo 'source_lang = en'
echo 'source_file = plugin-showdesktop/resources/showdesktop.desktop.in'
echo 'file_filter = plugin-showdesktop/translations/showdesktop_<lang>.desktop'
echo ''
