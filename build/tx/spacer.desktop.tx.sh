[ -f /home/kylin/work/ukui-panel/plugin-spacer/resources/spacer.desktop.in ] || exit 0
echo '[lxqt.spacer_desktop]'
echo 'type = DESKTOP'
echo 'source_lang = en'
echo 'source_file = plugin-spacer/resources/spacer.desktop.in'
echo 'file_filter = plugin-spacer/translations/spacer_<lang>.desktop'
echo ''
