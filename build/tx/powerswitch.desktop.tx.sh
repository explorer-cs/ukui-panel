[ -f /home/kylin/work/ukui-panel/plugin-powerswitch/resources/powerswitch.desktop.in ] || exit 0
echo '[lxqt.powerswitch_desktop]'
echo 'type = DESKTOP'
echo 'source_lang = en'
echo 'source_file = plugin-powerswitch/resources/powerswitch.desktop.in'
echo 'file_filter = plugin-powerswitch/translations/powerswitch_<lang>.desktop'
echo ''
