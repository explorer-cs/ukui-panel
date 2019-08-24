[ -f /home/kylin/panel/ukui-panel-3.0/menu/desktop-directories/lxqt-settings.directory.in ] || exit 0
echo '[lxde-qt.lxqt-settings_directory]'
echo 'type = DESKTOP'
echo 'source_lang = en'
echo 'source_file = menu/desktop-directories/lxqt-settings.directory.in'
echo 'file_filter = menu/translations/lxqt-settings_<lang>.directory'
echo ''
