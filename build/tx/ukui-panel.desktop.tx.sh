[ -f /home/kylin/panel/ukui-panel-3.0/autostart/ukui-panel.desktop.in ] || exit 0
echo '[lxde-qt.ukui-panel_desktop]'
echo 'type = DESKTOP'
echo 'source_lang = en'
echo 'source_file = autostart/ukui-panel.desktop.in'
echo 'file_filter = autostart/translations/ukui-panel_<lang>.desktop'
echo ''
