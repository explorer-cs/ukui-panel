[ -f /home/kylin/panel/ukui-panel-3.0/autostart/lxqt-panel.desktop.in ] || exit 0
echo '[lxde-qt.lxqt-panel_desktop]'
echo 'type = DESKTOP'
echo 'source_lang = en'
echo 'source_file = autostart/lxqt-panel.desktop.in'
echo 'file_filter = autostart/translations/lxqt-panel_<lang>.desktop'
echo ''
